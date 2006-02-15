/* Test BD_Shape::BHMZ05_widening_assign().
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
  Variable x(0);
  Variable y(1);

  TBD_Shape bd1(2);
  bd1.add_constraint(x <= 1);
  bd1.add_constraint(x - y <= 2);
  bd1.add_constraint(y - x <= 7);

  TBD_Shape bd2(2);
  bd2.add_constraint(x - y <= 2);
  bd2.add_constraint(-x <= 3);
  bd2.add_constraint(x <= 0);
  bd2.add_constraint(y - x <= 2);

  print_constraints(bd1, "*** bd1 ***");
  print_constraints(bd2, "*** bd2 ***");

  bd1.BHMZ05_widening_assign(bd2);

  BD_Shape<mpq_class> known_result(2);
  known_result.add_constraint(x - y <= 2);

  bool ok = (BD_Shape<mpq_class>(bd1) == known_result) ;

  print_constraints(bd1, "*** bd1.BHMZ05_widening_assign(bd2) ***");

  return ok;
}

bool
test02() {
  TBD_Shape bd1;
  TBD_Shape bd2(0, EMPTY);

  print_constraints(bd1, "*** bd1 ***");
  print_constraints(bd2, "*** bd2 ***");

  bd1.BHMZ05_widening_assign(bd2);

  BD_Shape<mpq_class> known_result;

  bool ok = (BD_Shape<mpq_class>(bd1) == known_result) ;

  print_constraints(bd1, "*** After bd1.BHMZ05_widening_assign(bd2) ***");

  return ok;
}

bool
test03() {
  Variable A(0);
  Variable B(1);
  Variable C(2);
  Variable D(3);
  Variable E(4);

  TBD_Shape bd1(5);
  bd1.add_constraint(A >= 0);
  bd1.add_constraint(B >= 0);
  bd1.add_constraint(C >= 1);
  bd1.add_constraint(D >= 0);
  bd1.add_constraint(E >= 0);
  bd1.add_constraint(C - D <= 76);
  bd1.add_constraint(C - E <= 76);
  bd1.add_constraint(E - D == 0);

  TBD_Shape bd2(5);
  bd2.add_constraint(A >= 0);
  bd2.add_constraint(B >= 0);
  bd2.add_constraint(C >= 1);
  bd2.add_constraint(D >= 0);
  bd2.add_constraint(E >= 0);
  bd2.add_constraint(C - D <= 75);
  bd2.add_constraint(C - E <= 75);
  bd2.add_constraint(E - D == 0);

  print_constraints(bd1, "*** bd1 ***");
  print_constraints(bd2, "*** bd2 ***");

  bd1.BHMZ05_widening_assign(bd2);

  BD_Shape<mpq_class> known_result(5);
  known_result.add_constraint(A >= 0);
  known_result.add_constraint(B >= 0);
  known_result.add_constraint(C >= 1);
  known_result.add_constraint(D >= 0);
  known_result.add_constraint(E - D == 0);

  bool ok = (BD_Shape<mpq_class>(bd1) == known_result) ;

  print_constraints(bd1, "*** bd1.BHMZ05_widening_assign(bd2) ***");

  return ok;
}

bool
test04() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  TBD_Shape bd1(3);
  bd1.add_constraint(A - B <= 1);

  TBD_Shape bd2(3);
  bd2.add_constraint(A - B <= 1);
  bd2.add_constraint(A - C <= 1);
  bd2.add_constraint(C - B <= 0);

  print_constraints(bd1, "*** bd1 ***");
  print_constraints(bd2, "*** bd2 ***");

  bd1.BHMZ05_widening_assign(bd2);

  BD_Shape<mpq_class> known_result(3);

  bool ok = (BD_Shape<mpq_class>(bd1) == known_result) ;

  print_constraints(bd1, "*** bd1.BHMZ05_widening_assign(bd2) ***");

  return ok;
}

bool
test05() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  TBD_Shape bd1(3);
  bd1.add_constraint(A - B <= 1);
  bd1.add_constraint(A - B >= 2);

  TBD_Shape bd2(3);
  bd2.add_constraint(A - B <= 1);
  bd2.add_constraint(A - B >= 2);
  bd2.add_constraint(A - C <= 1);
  bd2.add_constraint(C - B <= 0);

  print_constraints(bd1, "*** bd1 ***");
  print_constraints(bd2, "*** bd2 ***");

  bd1.BHMZ05_widening_assign(bd2);

  BD_Shape<mpq_class> known_result(3, EMPTY);

  bool ok = (BD_Shape<mpq_class>(bd1) == known_result) ;

  print_constraints(bd1, "*** bd1.BHMZ05_widening_assign(bd2) ***");

  return ok;
}

TBD_Shape
aux_test06(int i, Variable a, Variable b, Variable c) {
  using namespace IO_Operators;

  TBD_Shape bd(3);
  if (i == 0) {
    bd.add_constraint(0 <= a-b);
    bd.add_constraint(     a-b <= 0);
    bd.add_constraint(-1 <= b-c);
    bd.add_constraint(      b-c <= 1);
  }
  else {
    bd.add_constraint(-i <= a-b);
    bd.add_constraint(      a-b <= i);
    bd.add_constraint(-1 <= b-c);
    bd.add_constraint(      b-c <= 1);
    bd.add_constraint(-i <= a-c);
    bd.add_constraint(      a-c <= i);
  }

  nout << "*** n_" << i << " ***" << endl
       << bd << endl;

  // Force closure.
  (void) (bd == bd);
  return bd;
}

bool
test06() {
  using namespace IO_Operators;

  Variable a(0);
  Variable b(1);
  Variable c(2);
  unsigned i = 0;
  TBD_Shape m_i = aux_test06(i, a, b, c);
  TBD_Shape m_i_next;
  while (i < 100) {

    nout << "*** m_" << i << " ***" << endl
	 << m_i << endl;

    m_i_next = aux_test06(++i, a, b, c);
    m_i_next.bds_hull_assign(m_i);
    m_i_next.BHMZ05_widening_assign(m_i);
    // Force closure.
    (void) (m_i_next == m_i_next);
    if (m_i == m_i_next) {
      BD_Shape<mpq_class> known_result(3);
      known_result.add_constraint(-1 <= b-c);
      known_result.add_constraint(      b-c <= 1);

      bool ok = (BD_Shape<mpq_class>(m_i) == known_result) ;

      nout << "*** m_" << i << " (fixpoint) ***" << endl
	   << m_i << endl;
      print_constraints(known_result, "*** known_result ***");

      return ok;
    }
    m_i = m_i_next;
  }

  return false;
}

bool
test07() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  TBD_Shape bd1(3);
  bd1.add_constraint(A - B <= 1);

  TBD_Shape bd2(3);
  bd2.add_constraint(A - B <= 1);
  bd2.add_constraint(A - B >= 2);
  bd2.add_constraint(A - C <= 1);
  bd2.add_constraint(C - B <= 0);

  print_constraints(bd1, "*** bd1 ***");
  print_constraints(bd2, "*** bd2 ***");

  BD_Shape<mpq_class> known_result(bd1);

  bd1.BHMZ05_widening_assign(bd2);

  bool ok = (BD_Shape<mpq_class>(bd1) == known_result) ;

  print_constraints(bd1, "*** bd1.BHMZ05_widening_assign(bd2) ***");

  return ok;
}

bool
test08() {
  Variable x(0);
  Variable y(1);

  Constraint_System cs1;
  cs1.insert(x >= 0);
  cs1.insert(x <= 1);
  cs1.insert(y == 0);

  TBD_Shape bd1(cs1);

  Constraint_System cs2;
  cs2.insert(x <= 1);
  cs2.insert(y >= 0);
  cs2.insert(y - x <= 0);

  TBD_Shape bd2(cs2);

  print_constraints(bd1, "*** bd1 ****");
  print_constraints(bd2, "*** bd2 ****");

  BD_Shape<mpq_class> known_result(bd2);

  bd2.BHMZ05_widening_assign(bd1);

  bool ok = (BD_Shape<mpq_class>(bd2) == known_result) ;

  print_constraints(bd2,
		    "*** bd2.BHMZ05_widening_assign(bd1) ***");

  return ok;
}

} // namespace

BEGIN_MAIN
  NEW_TEST(test01);
  NEW_TEST(test02);
  NEW_TEST(test03);
  NEW_TEST(test04);
  NEW_TEST(test05);
  NEW_TEST(test06);
  NEW_TEST(test07);
  NEW_TEST(test08);
END_MAIN
