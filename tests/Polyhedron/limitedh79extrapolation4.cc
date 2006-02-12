/* Test Polyhedron::limited_H79_extrapolation_assign(): the polyhedra
   are empty or zero-dimensional.
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

void
test1() {
  Variable A(0);
  Variable B(1);

  C_Polyhedron ph1(2, EMPTY);

  C_Polyhedron ph2(2);
  ph2.add_constraint(B >= 0);
  ph2.add_constraint(A - B >= 0);
  ph2.add_constraint(A <= 2);

  Constraint_System cs;
  cs.insert(B <= 4);

  C_Polyhedron known_result(ph2);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");
  print_constraints(cs, "*** cs ***");

  ph2.limited_H79_extrapolation_assign(ph1, cs);

  bool ok = (ph2 == known_result);

  print_constraints(ph2,
		    "*** After ph2.limited_H79_extrapolation_assign(ph1, cs) ***");

  if (!ok)
    exit(1);
}

void
test2() {
  Variable B(1);

  C_Polyhedron ph1(2, EMPTY);

  C_Polyhedron ph2(2, EMPTY);

  Constraint_System cs;
  cs.insert(B <= 4);

  C_Polyhedron known_result(ph2);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");
  print_constraints(cs, "*** cs ***");

  ph2.limited_H79_extrapolation_assign(ph1, cs);

  bool ok = (ph2 == known_result);

  print_constraints(ph2,
		    "*** After ph2.limited_H79_extrapolation_assign(ph1, cs) ***");

  if (!ok)
    exit(1);
}

void
test3() {
  C_Polyhedron ph1;

  C_Polyhedron ph2;

  Constraint_System cs;
  cs.insert(Linear_Expression(2) <= 4);

  C_Polyhedron known_result(ph2);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");
  print_constraints(cs, "*** cs ***");

  ph2.limited_H79_extrapolation_assign(ph1, cs);

  bool ok = (ph2 == known_result);

  print_constraints(ph2,
		    "*** After ph2.limited_H79_extrapolation_assign(ph1, cs) ***");

  if (!ok)
    exit(1);
}

void
test4() {
  Variable A(0);
  Variable B(1);

  C_Polyhedron ph1(2);
  ph1.add_constraint(A >= 2);
  ph1.add_constraint(A <= -2);
  ph1.add_constraint(B == 0);
  C_Polyhedron ph2(2);
  ph1.add_constraint(A >= 2);

  Constraint_System cs;
  cs.insert(B <= 4);

  C_Polyhedron known_result(ph2);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");
  print_constraints(cs, "*** cs ***");

  ph2.limited_H79_extrapolation_assign(ph1, cs);

  bool ok = (ph2 == known_result);

  print_constraints(ph2,
		    "*** After ph2.limited_H79_extrapolation_assign(ph1, cs) ***");

  if (!ok)
    exit(1);
}

} // namespace

int
main() TRY {
  set_handlers();

  DO_TEST(test1);
  DO_TEST(test2);
  DO_TEST(test3);
  DO_TEST(test4);

  return 0;
}
CATCH
