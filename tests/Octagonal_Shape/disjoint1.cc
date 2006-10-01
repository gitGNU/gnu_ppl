/* Test Polyhedron::is_disjoint_from(const Octagonal_Shape& y).
   Copyright (C) 2001-2006 Roberto Bagnara <bagnara@cs.unipr.it>

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
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

namespace {

bool
test01() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct1(2);
  oct1.add_constraint(B == 0);
  oct1.add_constraint(A >= 1);
  oct1.add_constraint(A <= 2);

  TOctagonal_Shape oct2(2);
  oct2.add_constraint(A == 0);
  oct2.add_constraint(B >= 1);
  oct2.add_constraint(B <= 2);

  bool disjoint = oct1.is_disjoint_from(oct2);

  print_constraints(oct1, "*** oct1 ***");
  print_constraints(oct2, "*** oct2 ***");

  return disjoint;
}

bool
test02() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct1(2);
  oct1.add_constraint(A + B == 1);
  oct1.add_constraint(A <= 1);
  oct1.add_constraint(B <= 1);

  TOctagonal_Shape oct2(2);
  oct2.add_constraint(A + B <= 2);
  oct2.add_constraint(A >= 0);
  oct2.add_constraint(B >= 3);

  bool disjoint = oct1.is_disjoint_from(oct2);

  print_constraints(oct1, "*** oct1 ***");
  print_constraints(oct2, "*** oct2 ***");

  return disjoint;
}

bool
test03() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct1(2, EMPTY);

  TOctagonal_Shape oct2(2);
  oct2.add_constraint(A - B <= 5);

  bool disjoint = oct1.is_disjoint_from(oct2);

  print_constraints(oct1, "*** oct1 ***");
  print_constraints(oct2, "*** oct2 ***");

  return disjoint;
}

bool
test04() {
  Variable A(0);
  Variable B(1);

  Generator_System gs1;
  gs1.insert(point(A + B));
  gs1.insert(ray(B));

  TOctagonal_Shape oct1(gs1);

  Generator_System gs2;
  gs2.insert(point(A + B));
  gs2.insert(ray(-B));

  TOctagonal_Shape oct2(gs2);

  bool disjoint = oct1.is_disjoint_from(oct2);

  print_constraints(oct1, "*** oct1 ***");
  print_constraints(oct2, "*** oct2 ***");

  return !disjoint;
}

bool
test05() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct1(2);
  oct1.add_constraint(A >= 0);
  oct1.add_constraint(B >= -4);

  TOctagonal_Shape oct2(2, EMPTY);

  bool disjoint = oct1.is_disjoint_from(oct2);

  print_constraints(oct1, "*** oct1 ***");
  print_constraints(oct2, "*** oct2 ***");

  return disjoint;
}

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
  DO_TEST(test02);
  DO_TEST(test03);
  DO_TEST(test04);
  DO_TEST(test05);
END_MAIN