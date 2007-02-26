/* Test Box::H79_widening_assign().
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
  Variable x(0);
  Variable y(1);

  TBox box1(2);
  box1.add_constraint(x <= 1);
  box1.add_constraint(x - y <= 2);
  box1.add_constraint(y - x <= 7);

  TBox box2(2);
  box2.add_constraint(x - y <= 2);
  box2.add_constraint(-x <= 3);
  box2.add_constraint(x <= 0);
  box2.add_constraint(y - x <= 2);

  print_constraints(box1, "*** box1 ***");
  print_constraints(box2, "*** box2 ***");

  box1.H79_widening_assign(box2);

  Rational_Box known_result(2);
  known_result.add_constraint(x - y <= 2);

  bool ok = (Rational_Box(box1) == known_result);

  print_constraints(box1, "*** box1.CC76_extrapolation_assign(box2) ***");

  return ok;
}

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
END_MAIN