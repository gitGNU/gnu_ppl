/* Non-inline functions for the Old_Interval class and its constituents.
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

#include <config.h>

#include "Old_Interval.defs.hh"
#include <iostream>

namespace PPL = Parma_Polyhedra_Library;

bool
PPL::LBoundary::OK() const {
  if (flag != POS && flag != ZERO) {
#ifndef NDEBUG
    std::cerr << "Invalid flag in LBoundary: " << flag << std::endl;
#endif
    return false;
  }
  return true;
}

bool
PPL::UBoundary::OK() const {
  if (flag != NEG && flag != ZERO) {
#ifndef NDEBUG
    std::cerr << "Invalid flag in UBoundary: " << flag << std::endl;
#endif
    return false;
  }
  return true;
}

bool
PPL::Old_Interval::OK() const {
  return lower.OK() && upper.OK();
}