/* Test ascii_dump() 5 ascii_load(): we read a non completed file.
   we test these functions in the case that the file does not contain
   the right thing.
   Copyright (C) 2001, 2002 Roberto Bagnara <bagnara@cs.unipr.it>

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
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#include <string>
#include <fstream>
#include "ppl_test.hh"
#include "files.hh"

using namespace std;
using namespace Parma_Polyhedra_Library;

#ifndef NOISY
#define NOISY 0
#endif

const char* my_file = "ascii_dump_load_5.dat";

void
test1() {

  fstream f;
  open(f, my_file, ios_base::out);
  f << "space_dim 2\n"
    << "-ZE -EM  -CM -GM  +CS -GS  -SC -SG\n"
    << "con_sys (up-to-date)\n"
    << "topology NECESSARILY_CLOSED\n"
    << "3 x 3 (not_sorted)\n"
    << "1 0 0"; 
  close(f);
  
  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok =! ph2.ascii_load(f);
  close(f);
  
  if (!ok)
    exit(1);
}

void
test2() {

  fstream f;
  open(f, my_file, ios_base::out);
  f << "space_dim 2\n"
    << "-ZE -EM  -CM -GM  +CS -GS  -SC -SG\n"
    << "con_sys (up-to-date)\n"
    << "topology NECESSARILY_CLOSED\n"
    << "3 x 3 (not_sorted)\n"
    << "1 0 0   >=\n"
    << "0 1 0   >=\n"
    << "0 0 1   >=\n\n"
    << "gen_sys (not_up-to-date)\n"
    << "topology NECESSARILY_CLOSED\n"
    <<" 3 x 3 (not_sorted)\n"
    << "1 0 0"; 
  close(f);
  
  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok =! ph2.ascii_load(f);
  close(f);
  
  if (!ok)
    exit(1);
}

void
test3() {

  fstream f;
  open(f, my_file, ios_base::out);
  f << "space_dim 2\n"
    << "-ZE -EM  -CM -GM  +CS -GS  -SC -SG\n"
    << "con_sys (up-to-date)\n"
    << "topology NECESSARILY_CLOSED\n"
    << "3";
  close(f);
  
  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok =! ph2.ascii_load(f);
  close(f);
  
  if (!ok)
    exit(1);
}


void
test4() {

  fstream f;
  open(f, my_file, ios_base::out);
  f << "space_dim 2\n"
    << "-ZE -EM  -CM -GM  +CS -GS  -SC -SG\n"
    << "con_sys (up-to-date)\n"
    << "topology";
  close(f);
  
  open(f, my_file, ios_base::in);
  C_Polyhedron ph2;
  bool ok =! ph2.ascii_load(f);
  close(f);
  
  if (!ok)
    exit(1);
}

int
main() {
  set_handlers();
  
  test1();
  test2();
  test3();
  test4();

  return 0;
}
