/* Test BD_Shape::relation_with(c).
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

void test1() {
  Variable A(0);

  TBD_Shape bd(2, EMPTY);

  Poly_Con_Relation rel = bd.relation_with(A >= 0);

  print_constraints(bd, "--- bd ---");
  nout << "bd.relation_with(A >= 0) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::saturates()
    && Poly_Con_Relation::is_included()
    && Poly_Con_Relation::is_disjoint();

  if (rel != known_result)
    exit(1);
}

void test2() {
  // Variable x(0);
  Variable y(1);
  
  TBD_Shape bd(2);
  bd.add_constraint(y <= -1);
  
  Constraint c(y >= 0);
  Poly_Con_Relation rel = bd.relation_with(c);
  
  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_disjoint();

  if (rel != known_result)
    exit(1);
}

void test3() {
  // Variable x(0);
  Variable y(1);
  // Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(y <= 1);

  Constraint c(y >= 0);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::strictly_intersects();
  
  if (rel != known_result)
    exit(1);

}

void test4() {
  // Variable x(0);
  // Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(z >= 1);

  Constraint c(z >= 0);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_included();

  if (rel != known_result)
    exit(1);
}

void test5() {
  Variable x(0);
  // Variable y(1);

  TBD_Shape bd(2);
  bd.add_constraint(x == 1);

  Constraint c(x >= 1);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::saturates()
    && Poly_Con_Relation::is_included();

  if (rel != known_result)
    exit(1);
}

void test6() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(x == 1);
  bd.add_constraint(y <= 0);
  bd.add_constraint(z >= 2);

  Constraint c(x == 1);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::saturates()
    && Poly_Con_Relation::is_included();

  if (rel != known_result)
    exit(1);
}

void test7() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(x >= 3);
  bd.add_constraint(y <= 0);
  bd.add_constraint(z >= 2);

  Constraint c(x == 2);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_disjoint();

  if (rel != known_result)
    exit(1);
}

void test8() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(x <= 3);
  bd.add_constraint(y <= 0);
  bd.add_constraint(z >= 2);

  Constraint c(x == 2);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::strictly_intersects();
  
  if (rel != known_result)
    exit(1);
}

void test9() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(x <= 3);
  bd.add_constraint(y <= 0);
  bd.add_constraint(z >= 2);

  Constraint c(-x >= 2);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::strictly_intersects();

  if (rel != known_result)
    exit(1);
}

} // namespace

int main() TRY {

  DO_TEST(test1);
  DO_TEST(test2);
  DO_TEST(test3);
  DO_TEST(test4);
  DO_TEST(test5);
  DO_TEST(test6);
  DO_TEST(test7);
  DO_TEST(test8);
  DO_TEST(test9);

  return 0;
}
CATCH
