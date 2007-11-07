/* Test Direct_Product<NNC_Polyhedron, Grid>.
   Copyright (C) 2001-2007 Roberto Bagnara <bagnara@cs.unipr.it>

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The PPL is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#include "ppl_test.hh"

using namespace Parma_Polyhedra_Library::IO_Operators;

#define PH_IS_NNC
// #define PH_IS_FIRST

#ifdef PH_IS_NNC
typedef NNC_Polyhedron Poly;
#else
typedef C_Polyhedron Poly;
#endif

#ifdef PH_IS_FIRST
typedef Domain_Product<Poly, Grid>::Direct_Product Product;
#else
typedef Domain_Product<Grid, Poly>::Direct_Product Product;
#endif

namespace {

// Universe product in 0 dimensions
bool
test01() {
  Product dp1;

  Product dp2(0, UNIVERSE);

  bool ok = (dp1 == dp2);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2, "*** dp2 congruences ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok;
}

// Empty product(dims, type)
bool
test02() {
  Product dp1(3);

  Product dp2(3, EMPTY);

  bool ok = (dp1 != dp2);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2, "*** dp2 congruences ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok;
}

// Product(cgs), add_congruence(cg)
bool
test03() {
  Variable A(0);

  const Congruence_System cgs((A %= 0) / 4);

  Product dp1(cgs);

  Product dp2(1);
  dp2.add_congruence((A %= 0) / 4);

  bool ok = (dp1 == dp2);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2, "*** dp2 congruences ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok;
}

// Product(cgs), domain1(), domain2()
bool
test04() {
  Variable A(0);

  Congruence_System cgs((A %= 0) / 4);

  Product dp(cgs);

  Poly known_ph(1);

  Grid known_gr(1);
  known_gr.add_congruence((A %= 0) / 4);

#ifdef PH_IS_FIRST
  bool ok = (dp.domain2() == known_gr
	     && dp.domain1() == known_ph);
#else
  bool ok = (dp.domain1() == known_gr
	     && dp.domain2() == known_ph);
#endif

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// Product(cs), add_constraint(c)
bool
test05() {
  Variable A(0);

  const Constraint_System cs(A >= 0);

  Product dp1(cs);

  Product dp2(1);
  dp2.add_constraint(static_cast<const Constraint>(A >= 0));

  bool ok = (dp1 == dp2);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2, "*** dp2 congruences ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok;
}

// Product(cs), add_congruence(c)
bool
test06() {
  Variable A(0);

  Constraint_System cs(A == 9);

  Product dp1(cs);

  Product dp2(1);
  dp2.add_constraint(A == 9);

  Grid known_gr(1);
  known_gr.add_congruence(A == 9);

#ifdef PH_IS_FIRST
  bool ok = (dp1 == dp2 && dp1.domain2() == known_gr);
#else
  bool ok = (dp1 == dp2 && dp1.domain1() == known_gr);
#endif

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2, "*** dp2 congruences ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok;
}

#if 0
// Product(ggs), add_grid_generator(g)
// FIXME: The constructor for a grid_generator and add_grid_generator
//        behave differently - hence the need for adding universe generators.
bool
test07() {
  Variable A(0);
  Variable B(1);

  const Grid_Generator_System gs(grid_point(A + B));

  Product dp(gs);

  Product known_dp(2, EMPTY);
  known_dp.add_grid_generator(grid_point(A + B));
  known_dp.add_generator(point());
  known_dp.add_generator(line(A));
  known_dp.add_generator(line(B));

  bool ok = (dp == known_dp);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// Product(ggs), add_generator(g)
// FIXME: The constructor for a grid_generator and add_grid_generator
//        behave differently - hence the need for adding universe grid
//        generators.
bool
test08() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Generator_System gs(point(A + 7*C));

  Product dp(gs);

  Product known_dp(3, EMPTY);
  known_dp.add_generator(point(A + 7*C));
  known_dp.add_grid_generator(grid_point());
  known_dp.add_grid_generator(grid_line(A));
  known_dp.add_grid_generator(grid_line(B));
  known_dp.add_grid_generator(grid_line(C));

  bool ok = (dp == known_dp);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  print_congruences(known_dp, "*** known_dp congruences ***");
  print_constraints(known_dp, "*** known_dp constraints ***");

  return ok;
}
#endif

// Product(bounding_box)
bool
test09() {
  Variable B(1);

  Rational_Box box(2);
  box.add_constraint(3*B == 2);

  Product dp(box);

  Product known_dp(2);
  known_dp.add_constraint(3*B == 2);

  bool ok = (dp == known_dp);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// FIXME: Waiting for covering box methods, details in
//        Direct_Product.defs.hh.
#if 0
// Product(covering_box)
bool
test10() {
  Variable B(1);

  Rational_Box box(2);
  box.add_constraint(A == 0);
  box.add_constraint(3*B >= 2);
  box.add_constraint(3*B <= 3);

  Product dp(box, From_Covering_Box());

  Product known_dp(2);
  known_dp.add_congruence(3*B %= 0);

  bool ok = (dp == known_dp);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}
#endif

// operator=
bool
test11() {
  Variable A(0);
  Variable B(1);

  Constraint_System cs(A + B <= 9);

  Product dp1(cs);
  dp1.add_congruence((A %= 9) / 19);

  Product dp2 = dp1;

  bool ok = (dp1 == dp2);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2, "*** dp2 congruences ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok;
}

// Copy constructor.
bool
test12() {
  Variable A(0);
  Variable B(2);

  Constraint_System cs(A - B == 0);

  Product dp1(cs);

  Product dp2(dp1);

  bool ok = (dp1 == dp2);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2, "*** dp2 congruences ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok;
}

// congruences()
bool
test13() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp(3);
  dp.add_congruence(A %= 9);
  dp.add_congruence(B + C %= 3);

  Congruence_System cgs;
  cgs.insert(B + C %= 0);
  cgs.insert(A %= 0);

  Grid known_gr(cgs);

  Grid gr(dp.congruences());

  bool ok = gr == known_gr;

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// minimized_congruences()
bool
test14() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp(3);
  dp.add_congruence(B + C %= 3);
  dp.add_constraint(A >= 9);
  dp.add_constraint(A <= 9);

  Congruence_System cgs;
  cgs.insert(B + C %= 3);

  Grid known_gr(cgs);

  Grid gr(dp.minimized_congruences());

  bool ok = gr == known_gr;

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// constraints()
bool
test15() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp(3);
  dp.add_congruence((B + C %= 3) / 0);
#ifdef PH_IS_NNC
  dp.add_constraint(A > 9);
#else
  dp.add_constraint(A >= 9);
#endif
  dp.add_constraint(A <= 11);

  Poly ph(dp.space_dimension());
  ph.add_constraints(dp.constraints());

  Poly known_ph(dp.space_dimension());
  known_ph.add_constraint(B + C == 3);
  known_ph.add_constraint(A <= 11);
#ifdef PH_IS_NNC
  known_ph.add_constraint(A > 9);
#else
  known_ph.add_constraint(A >= 9);
#endif

  bool ok = (ph == known_ph);

  print_constraints(ph, "*** ph ***");

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// minimized_constraints()
bool
test16() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp(3);
  dp.add_congruence((B + C %= 3) / 0);
#ifdef PH_IS_NNC
  dp.add_constraint(A > 9);
#else
  dp.add_constraint(A >= 9);
#endif
  dp.add_constraint(A <= 11);

  Poly ph(dp.space_dimension());
  ph.add_constraints(dp.constraints());

  Poly known_ph(dp.space_dimension());
  known_ph.add_constraint(B + C == 3);
#ifdef PH_IS_NNC
  known_ph.add_constraint(A > 9);
#else
  known_ph.add_constraint(A >= 9);
#endif
  known_ph.add_constraint(A <= 11);

  bool ok = (ph == known_ph);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

#if 0
// generators()
bool
test17() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp(3);
  dp.add_congruence((B + C %= 3) / 0);
#ifdef PH_IS_NNC
  dp.add_constraint(A > 9);
#else
  dp.add_constraint(A >= 9);
#endif
  dp.add_constraint(A <= 11);

  Poly ph(dp.space_dimension());
  ph.add_generators(dp.generators());

  Poly known_ph(dp.space_dimension());

  bool ok = (ph == known_ph);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// minimized_generators()
bool
test18() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp(3);
  dp.add_congruence((B + C %= 3) / 0);
#ifdef PH_IS_NNC
  dp.add_constraint(A > 9);
#else
  dp.add_constraint(A >= 9);
#endif
  dp.add_constraint(A <= 11);

  Poly ph(dp.space_dimension());
  ph.add_generators(dp.generators());

  Poly known_ph(dp.space_dimension());

  bool ok = (ph == known_ph);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// grid_generators()
bool
test19() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp(3);
  dp.add_congruence((B + C %= 3) / 0);
#ifdef PH_IS_NNC
  dp.add_constraint(A > 9);
#else
  dp.add_constraint(A >= 9);
#endif
  dp.add_constraint(A <= 11);

  dimension_type d = dp.space_dimension();

  Grid gr(d);

  Grid known_gr(dp.space_dimension());

  bool ok = (gr == known_gr);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// minimized_grid_generators()
bool
test20() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp(3);
  dp.add_congruence((B + C %= 3) / 0);
#ifdef PH_IS_NNC
  dp.add_constraint(A > 9);
#else
  dp.add_constraint(A >= 9);
#endif
  dp.add_constraint(A <= 11);

  dimension_type d = dp.space_dimension();

  Grid gr(d);

  Grid known_gr(dp.space_dimension());

  bool ok = (gr == known_gr);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}
#endif

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
  DO_TEST(test02);
  DO_TEST(test03);
  DO_TEST(test04);
  DO_TEST(test05);
  DO_TEST(test06);
//  DO_TEST(test07);
//  DO_TEST(test08);
  DO_TEST(test09);
  //DO_TEST(test10);
  DO_TEST(test11);
  DO_TEST(test12);
  DO_TEST(test13);
//   DO_TEST(test14);
  DO_TEST(test15);
  DO_TEST(test16);
//  DO_TEST(test17);
//  DO_TEST(test18);
//  DO_TEST(test19);
//  DO_TEST(test20);
END_MAIN
