/* LinExpression class implementation (non-inline functions).
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


#include <config.h>

#include "LinExpression.defs.hh"
#include "Constraint.defs.hh"
#include "Generator.defs.hh"

namespace PPL = Parma_Polyhedra_Library;


PPL::LinExpression::LinExpression(const Constraint& c)
  : Row(Row::Type(), c.space_dimension() + 1) {
  LinExpression& e = *this;
  for (dimension_type i = size(); i-- > 0; )
    e[i] = c[i];
}


PPL::LinExpression::LinExpression(const Generator& g)
  : Row(Row::Type(), g.space_dimension() + 1) {
  LinExpression& e = *this;
  // Do not copy the divisor of `g'.
  for (dimension_type i = size(); --i > 0; )
    e[i] = g[i];
}


PPL::LinExpression
PPL::operator+(const LinExpression& e1, const LinExpression& e2) {
  dimension_type e1_size = e1.size();
  dimension_type e2_size = e2.size();
  dimension_type min_size;
  dimension_type max_size;
  const LinExpression* p_e_max;
  if (e1_size > e2_size) {
    min_size = e2_size;
    max_size = e1_size;
    p_e_max = &e1;
  }
  else {
    min_size = e1_size;
    max_size = e2_size;
    p_e_max = &e2;
  }

  LinExpression r(max_size, false);
  dimension_type i = max_size;
  while (i > min_size) {
    --i;
    r[i] = (*p_e_max)[i];
  }
  while (i > 0) {
    --i;
    r[i] = e1[i] + e2[i];
  }

  return r;
}


PPL::LinExpression
PPL::operator+(const Integer& n, const LinExpression& e) {
  LinExpression r(e);
  r[0] += n;
  return r;
}


PPL::LinExpression
PPL::operator-(const LinExpression& e) {
  LinExpression r(e);
  for (dimension_type i = e.size(); i-- > 0; )
    negate(r[i]);
  return r;
}


PPL::LinExpression
PPL::operator-(const LinExpression& e1, const LinExpression& e2) {
  dimension_type e1_size = e1.size();
  dimension_type e2_size = e2.size();
  if (e1_size > e2_size) {
    LinExpression r(e1_size, false);
    dimension_type i = e1_size;
    while (i > e2_size) {
      --i;
      r[i] = e1[i];
    }
    while (i > 0) {
      --i;
      r[i] = e1[i] - e2[i];
    }
    return r;
  }
  else {
    LinExpression r(e2_size, false);
    dimension_type i = e2_size;
    while (i > e1_size) {
      --i;
      r[i] = -e2[i];
    }
    while (i > 0) {
      --i;
      r[i] = e1[i] - e2[i];
    }
    return r;
  }
}


PPL::LinExpression
PPL::operator-(const Integer& n, const LinExpression& e) {
  LinExpression r(e);
  for (dimension_type i = e.size(); i-- > 0; )
    negate(r[i]);
  r[0] += n;

  return r;
}


PPL::LinExpression
PPL::operator*(const Integer& n, const LinExpression& e) {
  LinExpression r(e);
  for (dimension_type i = e.size(); i-- > 0; )
    r[i] *= n;
  return r;
}


PPL::LinExpression&
PPL::operator+=(LinExpression& e1, const LinExpression& e2) {
  dimension_type e1_size = e1.size();
  dimension_type e2_size = e2.size();
  if (e1_size >= e2_size)
    for (dimension_type i = e2_size; i-- > 0; )
      e1[i] += e2[i];
  else {
    LinExpression e(e2);
    for (dimension_type i = e1_size; i-- > 0; )
      e[i] += e1[i];
    std::swap(e1, e);
  }
  return e1;
}


PPL::LinExpression&
PPL::operator+=(LinExpression& e, const Variable& v) {
  dimension_type e_size = e.size();
  dimension_type vpos = v.id() + 1;
  if (e_size <= vpos) {
    LinExpression new_e(e, vpos+1);
    std::swap(e, new_e);
  }
  ++e[vpos];
  return e;
}


PPL::LinExpression&
PPL::operator-=(LinExpression& e1, const LinExpression& e2) {
  dimension_type e1_size = e1.size();
  dimension_type e2_size = e2.size();
  if (e1_size >= e2_size)
    for (dimension_type i = e2_size; i-- > 0; )
      e1[i] -= e2[i];
  else {
    LinExpression e(e1, e2_size);
    for (dimension_type i = e2_size; i-- > 0; )
      e[i] -= e2[i];
    std::swap(e1, e);
  }
  return e1;
}


PPL::LinExpression&
PPL::operator-=(LinExpression& e, const Variable& v) {
  dimension_type e_size = e.size();
  dimension_type vpos = v.id() + 1;
  if (e_size <= vpos) {
    LinExpression new_e(e, vpos+1);
    std::swap(e, new_e);
  }
  --e[vpos];
  return e;
}

PPL::LinExpression&
PPL::operator*=(LinExpression& e, const Integer& n) {
  dimension_type e_size = e.size();
  for (dimension_type i = e_size; i-- > 0; )
    e[i] *= n;
  return e;
}
