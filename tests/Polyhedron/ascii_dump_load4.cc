/* Test Polyhedron::ascii_dump() and Polyhedron::ascii_load():
   we test these functions in the case that the file does not contain
   the right thing.
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
#include "files.hh"
#include <string>
#include <fstream>

using std::string;
using std::fstream;
using std::ios_base;

namespace {

const char* my_file = "ascii_dump_load4.dat";

void
test1() {

  nout << "test1()" << endl;

  Variable A(0);
  Variable B(1);

  C_Polyhedron ph(2);
  ph.add_constraint(A == 2);
  ph.add_constraint(B >= 0);

  fstream f;
  open(f, my_file, ios_base::out);
  ph.ascii_dump(f);
  close(f);

  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok = ph2.ascii_load(f);
  close(f);

  if (!ok)
    exit(1);
}

void
test2() {

  nout << "test2()" << endl;

  Variable A(0);
  Variable B(1);

  C_Polyhedron ph(2);
  ph.add_constraint(A == 2);
  ph.add_constraint(B >= 0);

  fstream f;
  open(f, my_file, ios_base::out);
  ph.ascii_dump(f);
  close(f);

  open(f, my_file, ios_base::in | ios_base::out);
  string str;
  do
    f >> str;
  while (str != "=");
  f.seekp(0, ios_base::cur);
  f << "A";
  close(f);

  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok = !ph2.ascii_load(f);
  close(f);

  if (!ok)
    exit(1);
}

void
test3() {

  nout << "test3()" << endl;

  Variable A(0);
  Variable B(1);

  NNC_Polyhedron ph1(2);
  ph1.add_constraint(A == 2);
  ph1.add_constraint(B >= 0);

  Constraint_System cs = ph1.constraints();

  C_Polyhedron ph(6);
  ph.add_constraints(cs);

  fstream f;
  open(f, my_file, ios_base::out);
  ph.ascii_dump(f);
  close(f);

  open(f, my_file, ios_base::in | ios_base::out);
  string str;
  do
    f >> str;
  while (str != "=");
  f.seekp(-6, ios_base::cur);
  f << "A";
  close(f);

  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok = !ph2.ascii_load(f);
  close(f);

  if (!ok)
    exit(1);
}

void
test4() {

  nout << "test4()" << endl;

  Variable A(0);
  Variable B(1);

  C_Polyhedron ph(2);
  ph.add_constraint(A >= 0);
  ph.add_constraint(B >= 0);

  fstream f;
  open(f, my_file, ios_base::out);
  ph.ascii_dump(f);
  close(f);

  open(f, my_file, ios_base::in | ios_base::out);
  string str;
  do
    f >> str;
  while (str != "NECESSARILY_CLOSED");
  f.seekp(-2, ios_base::cur);
  f << "A";
  close(f);

  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok = !ph2.ascii_load(f);
  close(f);

  if (!ok)
    exit(1);
}

void
test5() {

  nout << "test5()" << endl;

  Variable A(0);
  Variable B(1);

  C_Polyhedron ph(2);
  ph.add_constraint(A >= 0);
  ph.add_constraint(B >= 0);

  fstream f;
  open(f, my_file, ios_base::out);
  ph.ascii_dump(f);
  close(f);

  open(f, my_file, ios_base::in | ios_base::out);
  string str;
  do
    f >> str;
  while (str != "x");
  f.seekp(1, ios_base::cur);
  f << "A";
  close(f);

  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok = !ph2.ascii_load(f);
  close(f);

  if (!ok)
    exit(1);
}

void
test6() {

  nout << "test6()" << endl;

  Variable A(0);
  Variable B(1);

  C_Polyhedron ph(2);
  ph.add_constraint(A >= 0);
  ph.add_constraint(B >= 0);

  fstream f;
  open(f, my_file, ios_base::out);
  ph.ascii_dump(f);
  close(f);

  open(f, my_file, ios_base::in | ios_base::out);
  string str;
  do
    f >> str;
  while (str != "(not_sorted)");
  f.seekp(-2, ios_base::cur);
  f << "A";
  close(f);

  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok = !ph2.ascii_load(f);
  close(f);

  if (!ok)
    exit(1);
}

void
test7() {

  nout << "test7()" << endl;

  Variable A(0);
  Variable B(1);

  C_Polyhedron ph(2);
  ph.add_constraint(A >= 0);
  ph.add_constraint(B >= 0);

  ph.generators();

  fstream f;
  open(f, my_file, ios_base::out);
  ph.ascii_dump(f);
  close(f);

  open(f, my_file, ios_base::in | ios_base::out);
  string str;
  do
    f >> str;
  while (str != "sat_c");
  do
    f >> str;
  while (str != "x");
  f.seekp(0, ios_base::cur);
  f << " A";
  close(f);

  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok = !ph2.ascii_load(f);
  close(f);

  if (!ok)
    exit(1);
}

void
test8() {

  nout << "test8()" << endl;

  Variable A(0);
  Variable B(1);

  C_Polyhedron ph(2);
  ph.add_constraint(A >= 0);
  ph.add_constraint(B >= 0);

  ph.generators();

  fstream f;
  open(f, my_file, ios_base::out);
  ph.ascii_dump(f);
  close(f);

  open(f, my_file, ios_base::in | ios_base::out);
  string str;
  do
    f >> str;
  while (str != "sat_c");
  f.seekp(8, ios_base::cur);
  f << " A";
  close(f);

  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok = !ph2.ascii_load(f);
  close(f);

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
  DO_TEST(test5);
  DO_TEST(test6);
  DO_TEST(test7);
  DO_TEST(test8);

  return 0;
}
CATCH
