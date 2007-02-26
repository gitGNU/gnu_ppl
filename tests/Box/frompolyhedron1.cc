/* Test Box::Box(const C_Polyhedron&).
   Copyright (C) 2001-2007 Roberto Bagnara <bagnara@cs.unipr.it>

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

  Constraint_System cs;
  cs.insert(A + 2*B <= 5);
  cs.insert(A + 2*B >= -10);
  cs.insert(A >= 0);
  cs.insert(B <= 7);
  cs.insert(3*A - 5*B <= 18);
  C_Polyhedron ph(cs);

  TBox box1(ph, SIMPLEX_COMPLEXITY);
  TBox box2(ph, ANY_COMPLEXITY);

  Rational_Box known_result(2);
  known_result.add_constraint(A >= 0);
  known_result.add_constraint(11*A <= 61);
  known_result.add_constraint(2*B <= 5);
  known_result.add_constraint(5*B >= -18);
  known_result.add_constraint(11*A - 11*B <= 64);

  bool ok = (box1 == box2
	     && check_result(box1, known_result,
			     "7.50e-7", "4.89e-7", "4.34e-7"));

  print_constraints(box1, "*** box1 ***");
  print_constraints(box2, "*** box2 ***");

  return ok;
}

} // namespace

BEGIN_MAIN
  DO_TEST_F8(test01);
END_MAIN