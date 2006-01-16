/* Test Polyhedra_Powerset<PH>.
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

using namespace Parma_Polyhedra_Library::IO_Operators;

namespace {

Variable x(0);

void
test1() {
  Constraint_System cs = Constraint_System::zero_dim_empty();
  Polyhedra_Powerset<C_Polyhedron> ps(cs);
  if (!ps.OK())
    exit(1);
}

void
test2() {
  Constraint_System cs;
  Polyhedra_Powerset<NNC_Polyhedron> nnc_ps(1, EMPTY);

  cs.clear();
  cs.insert(x > 0);
  cs.insert(x <= 1);
  nnc_ps.add_disjunct(NNC_Polyhedron(cs));

  cs.clear();
  cs.insert(x >= 0);
  cs.insert(x < 1);
  nnc_ps.add_disjunct(NNC_Polyhedron(cs));

  Polyhedra_Powerset<C_Polyhedron> c_ps(nnc_ps);

  if (!c_ps.OK())
    exit(1);
}

void
test3() {
  Constraint_System cs;
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);

  cs.clear();
  cs.insert(x >= 0);
  cs.insert(x <= 2);
  c_ps.add_disjunct(C_Polyhedron(cs));

  cs.clear();
  cs.insert(x >= 1);
  cs.insert(x <= 3);
  c_ps.add_disjunct(C_Polyhedron(cs));

  c_ps.add_constraint(x == 1);

  Polyhedra_Powerset<NNC_Polyhedron> nnc_ps(c_ps);

  if (!nnc_ps.OK())
    exit(1);
}

void
test4() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;

  cs.insert(x >= 0);
  cs.insert(x <= 2);
  c_ps.add_disjunct(C_Polyhedron(cs));

  cs.clear();
  cs.insert(x >= 1);
  cs.insert(x <= 3);
  c_ps.add_disjunct(C_Polyhedron(cs));

  c_ps.concatenate_assign(c_ps);

  if (!c_ps.OK())
    exit(1);
}

void
test5() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);

  bool ok = c_ps.is_bottom();

  c_ps.add_disjunct(C_Polyhedron(1, UNIVERSE));

  bool ok1 = c_ps.is_top();

  c_ps.total_memory_in_bytes();
  c_ps.external_memory_in_bytes();

  if (!ok || !ok1)
    exit(1);
}

void
test6() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;
  cs.insert(x >= 0);
  c_ps.add_disjunct(C_Polyhedron(cs));

  Polyhedra_Powerset<C_Polyhedron> c_ps1(1, EMPTY);
  Constraint_System cs1;
  cs1.insert(x >= 0);
  cs1.insert(x <= 2);
  c_ps1.add_disjunct(C_Polyhedron(cs1));

  bool ok = c_ps1.definitely_entails(c_ps);

  if (!ok)
    exit(1);
}

void
test7() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;

  cs.insert(x >= 0);
  cs.insert(x <= 2);
  c_ps.add_disjunct(C_Polyhedron(cs));

  cs.clear();
  cs.insert(x >= 1);
  cs.insert(x <= 3);
  c_ps.add_disjunct(C_Polyhedron(cs));

  bool ok = (c_ps.size() == 2);

  if (!ok)
    exit(1);
}

void
test8() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;

  cs.insert(x >= 0);
  cs.insert(x <= 2);
  c_ps.add_disjunct(C_Polyhedron(cs));

  cs.clear();
  cs.insert(x >= 0);
  cs.insert(x <= 3);
  c_ps.add_disjunct(C_Polyhedron(cs));
  c_ps.omega_reduce();

  bool ok = (c_ps.size() == 1);

  if (!ok)
    exit(1);
}

void
test9() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  bool ok = (c_ps.space_dimension() == 1);

  if (!ok)
    exit(1);
}

void
test10() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;
  cs.insert(x >= 0);
  cs.insert(x <= 2);
  Constraint_System cs1 = cs;
  c_ps.add_disjunct(C_Polyhedron(cs));
  c_ps.drop_disjunct(c_ps.begin());

  bool ok = c_ps.empty();

  Constraint_System cs2 = cs1;
  c_ps.add_disjunct(C_Polyhedron(cs1));

  cs.insert(x >= 0);
  cs.insert(x <= 3);
  c_ps.add_disjunct(C_Polyhedron(cs));
  c_ps.drop_disjuncts(c_ps.begin(), c_ps.end());

  bool ok1 = c_ps.empty();

  if (!ok || !ok1)
    exit(1);
}

void
test11() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;

  cs.insert(x >= 0);
  cs.insert(x <= 2);
  c_ps.add_disjunct(C_Polyhedron(cs));

  Polyhedra_Powerset<C_Polyhedron> c_ps1;
  c_ps1 = c_ps;

  bool ok = !c_ps.empty();

  if (ok)
    exit(1);
}

void
test12() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;

  cs.insert(x >= 0);
  cs.insert(x <= 2);
  c_ps.add_disjunct(C_Polyhedron(cs));

  Polyhedra_Powerset<C_Polyhedron> c_ps1(1, EMPTY);
  c_ps.swap(c_ps1);

  bool ok = (c_ps1.empty() && !c_ps.empty());

  if (ok)
    exit(1);
}

void
test13() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;

  cs.insert(x >= 0);
  cs.insert(x <= 2);
  c_ps.add_disjunct(C_Polyhedron(cs));

  cs.clear();
  cs.insert(x >= 1);
  cs.insert(x <= 3);

  Polyhedra_Powerset<C_Polyhedron> c_ps1(1, EMPTY);
  c_ps.least_upper_bound_assign(c_ps1);

  cs.clear();
  cs.insert(x >= 0);
  cs.insert(x <= 3);

  Polyhedra_Powerset<C_Polyhedron> c_ps_expected(1, EMPTY);
  c_ps_expected.add_disjunct(C_Polyhedron(cs));

  bool ok = c_ps.definitely_entails(c_ps_expected);
  bool ok1 = c_ps_expected.definitely_entails(c_ps);

  if (!ok || !ok1)
    exit(1);
}

void
test14() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;

  cs.insert(x >= 0);
  cs.insert(x <= 2);
  c_ps.add_disjunct(C_Polyhedron(cs));

  cs.clear();
  cs.insert(x >= 1);
  cs.insert(x <= 3);

  Polyhedra_Powerset<C_Polyhedron> c_ps1(1, EMPTY);
  c_ps.upper_bound_assign(c_ps1);

  cs.clear();
  cs.insert(x >= 0);
  cs.insert(x <= 3);

  Polyhedra_Powerset<C_Polyhedron> c_ps_expected(1, EMPTY);
  c_ps_expected.add_disjunct(C_Polyhedron(cs));

  bool ok = c_ps.definitely_entails(c_ps_expected);
  bool ok1 = c_ps_expected.definitely_entails(c_ps);

  if (!ok || !ok1)
    exit(1);
}

void
test15() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;

  cs.insert(x >= 0);
  cs.insert(x <= 2);
  c_ps.add_disjunct(C_Polyhedron(cs));

  Polyhedra_Powerset<C_Polyhedron> c_ps1(1, EMPTY);

  cs.clear();
  cs.insert(x >= 1);
  cs.insert(x <= 3);

  c_ps.meet_assign(c_ps1);

  cs.clear();
  cs.insert(x >= 1);
  cs.insert(x <= 2);
  Polyhedra_Powerset<C_Polyhedron> c_ps_expected(1, EMPTY);
  c_ps_expected.add_disjunct(C_Polyhedron(cs));

  bool ok = c_ps.definitely_entails(c_ps_expected);
  bool ok1 = c_ps_expected.definitely_entails(c_ps);

  if (!ok || !ok1)
    exit(1);
}

void
test16() {
  Polyhedra_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;

  cs.insert(x >= 0);
  cs.insert(x <= 2);
  c_ps.add_disjunct(C_Polyhedron(cs));

  cs.clear();
  cs.insert(x >= 1);
  cs.insert(x <= 3);
  c_ps.add_disjunct(C_Polyhedron(cs));

  c_ps.collapse();

  cs.clear();
  cs.insert(x >= 0);
  cs.insert(x <= 3);
  Polyhedra_Powerset<C_Polyhedron> c_ps_expected(1, EMPTY);
  c_ps_expected.add_disjunct(C_Polyhedron(cs));

  bool ok = c_ps.definitely_entails(c_ps_expected);
  bool ok1 = c_ps_expected.definitely_entails(c_ps);
  bool ok2 = (c_ps.size() == 1);

  if (!ok || !ok1 || !ok2)
    exit(1);
}

} // namespace

int main() TRY {
  set_handlers();

  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  test11();
  test12();
  test13();
  test14();
  test15();
  test16();

  return 0;
}
CATCH
