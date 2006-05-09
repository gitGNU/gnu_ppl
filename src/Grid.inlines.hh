/* Grid class implementation: inline functions.
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

#ifndef PPL_Grid_inlines_hh
#define PPL_Grid_inlines_hh 1

#include "Grid_Generator.defs.hh"
#include "Grid_Generator_System.defs.hh"
#include <algorithm>

namespace Parma_Polyhedra_Library {

inline dimension_type
Grid::max_space_dimension() {
  using std::min;
  // One dimension is reserved to have a value of type dimension_type
  // that does not represent a legal dimension.
  return min(std::numeric_limits<dimension_type>::max() - 1,
	     min(Congruence_System::max_space_dimension(),
		 Grid_Generator_System::max_space_dimension()
		 )
	     );
}

inline void
Grid::set_congruences_up_to_date() {
  status.set_c_up_to_date();
}

inline
Grid::Grid(const Congruence_System& ccgs) {
  if (ccgs.space_dimension() > max_space_dimension())
    throw_space_dimension_overflow("Grid(ccgs)",
				   "the space dimension of ccgs "
				   "exceeds the maximum allowed "
				   "space dimension");
  construct(ccgs);
}

inline
Grid::Grid(Congruence_System& cgs) {
  if (cgs.space_dimension() > max_space_dimension())
    throw_space_dimension_overflow("Grid(cgs)",
				   "the space dimension of cgs "
				   "exceeds the maximum allowed "
				   "space dimension");
  construct(cgs);
}

inline
Grid::Grid(const Grid_Generator_System& gs) {
  if (gs.space_dimension() > max_space_dimension())
    throw_space_dimension_overflow("Grid(gs)",
				   "the space dimension of gs "
				   "exceeds the maximum allowed "
				   "space dimension");
  construct(gs);
}

inline
Grid::Grid(Grid_Generator_System& gs) {
  if (gs.space_dimension() > max_space_dimension())
    throw_space_dimension_overflow("Grid(gs)",
				   "the space dimension of gs "
				   "exceeds the maximum allowed "
				   "space dimension");
  construct(gs);
}

inline
Grid::~Grid() {
}

inline memory_size_type
Grid::total_memory_in_bytes() const {
  return sizeof(*this) + external_memory_in_bytes();
}

inline dimension_type
Grid::space_dimension() const {
  return space_dim;
}

inline void
Grid::upper_bound_assign(const Grid& y) {
  join_assign(y);
}

inline bool
Grid::upper_bound_assign_if_exact(const Grid& y) {
  return join_assign_if_exact(y);
}

inline void
Grid::difference_assign(const Grid& y) {
  grid_difference_assign(y);
}

inline void
Grid::swap(Grid& y) {
  std::swap(con_sys, y.con_sys);
  std::swap(gen_sys, y.gen_sys);
  std::swap(status, y.status);
  std::swap(space_dim, y.space_dim);
  std::swap(dim_kinds, y.dim_kinds);
}

} // namespace Parma_Polyhedra_Library

/*! \relates Parma_Polyhedra_Library::Grid */
inline void
std::swap(Parma_Polyhedra_Library::Grid& x,
	  Parma_Polyhedra_Library::Grid& y) {
  x.swap(y);
}

namespace Parma_Polyhedra_Library {

inline bool
Grid::marked_empty() const {
  return status.test_empty();
}

inline bool
Grid::congruences_are_up_to_date() const {
  return status.test_c_up_to_date();
}

inline bool
Grid::generators_are_up_to_date() const {
  return status.test_g_up_to_date();
}

inline bool
Grid::congruences_are_minimized() const {
  return status.test_c_minimized();
}

inline bool
Grid::generators_are_minimized() const {
  return status.test_g_minimized();
}

inline void
Grid::set_generators_up_to_date() {
  status.set_g_up_to_date();
}

inline void
Grid::set_congruences_minimized() {
  set_congruences_up_to_date();
  status.set_c_minimized();
}

inline void
Grid::set_generators_minimized() {
  set_generators_up_to_date();
  status.set_g_minimized();
}

inline void
Grid::clear_empty() {
  status.reset_empty();
}

inline void
Grid::clear_congruences_minimized() {
  status.reset_c_minimized();
}

inline void
Grid::clear_generators_minimized() {
  status.reset_g_minimized();
}

inline void
Grid::clear_congruences_up_to_date() {
  clear_congruences_minimized();
  status.reset_c_up_to_date();
  // Can get rid of con_sys here.
}

inline void
Grid::clear_generators_up_to_date() {
  clear_generators_minimized();
  status.reset_g_up_to_date();
  // Can get rid of gen_sys here.
}

inline bool
Grid::bounds_from_above(const Linear_Expression& expr) const {
  return bounds(expr, "bounds_from_above(e)");
}

inline bool
Grid::bounds_from_below(const Linear_Expression& expr) const {
  return bounds(expr, "bounds_from_below(e)");
}

inline bool
Grid::maximize(const Linear_Expression& expr,
	       Coefficient& sup_n, Coefficient& sup_d, bool& maximum) const {
  return max_min(expr, "maximize(e, ...)", sup_n, sup_d, maximum);
}

inline bool
Grid::maximize(const Linear_Expression& expr,
	       Coefficient& sup_n, Coefficient& sup_d, bool& maximum,
	       Grid_Generator& point) const {
  return max_min(expr, "maximize(e, ...)", sup_n, sup_d, maximum, &point);
}

inline bool
Grid::minimize(const Linear_Expression& expr,
	       Coefficient& inf_n, Coefficient& inf_d, bool& minimum) const {
  return max_min(expr, "minimize(e, ...)", inf_n, inf_d, minimum);
}

inline bool
Grid::minimize(const Linear_Expression& expr,
	       Coefficient& inf_n, Coefficient& inf_d, bool& minimum,
	       Grid_Generator& point) const {
  return max_min(expr, "minimize(e, ...)", inf_n, inf_d, minimum, &point);
}

inline void
Grid::normalize_divisors(Grid_Generator_System& sys) {
  TEMP_INTEGER(divisor);
  divisor = 1;
  normalize_divisors(sys, divisor);
}

/*! \relates Grid */
inline bool
operator!=(const Grid& x, const Grid& y) {
  return !(x == y);
}

inline bool
Grid::strictly_contains(const Grid& y) const {
  const Grid& x = *this;
  return x.contains(y) && !y.contains(x);
}

inline void
Grid::topological_closure_assign() {
  return;
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_Grid_inlines_hh)
