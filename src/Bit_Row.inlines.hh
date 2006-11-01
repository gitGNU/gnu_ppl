/* Bit_Row class implementation: inline functions.
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

#ifndef PPL_Bit_Row_inlines_hh
#define PPL_Bit_Row_inlines_hh 1

#include <cassert>
// For the declaration of ffs(3).
#include <cstring>

namespace Parma_Polyhedra_Library {

inline
Bit_Row::Bit_Row() {
  mpz_init(vec);
}

inline
Bit_Row::Bit_Row(const Bit_Row& y) {
  mpz_init_set(vec, y.vec);
}

inline
Bit_Row::~Bit_Row() {
  mpz_clear(vec);
}

inline Bit_Row&
Bit_Row::operator=(const Bit_Row& y) {
  mpz_set(vec, y.vec);
  return *this;
}

inline void
Bit_Row::set(const unsigned long k) {
  mpz_setbit(vec, k);
}

inline void
Bit_Row::clear(const unsigned long k) {
  mpz_clrbit(vec, k);
}

inline void
Bit_Row::clear_from(const unsigned long k) {
  mpz_tdiv_r_2exp(vec, vec, k);
}

inline unsigned long
Bit_Row::count_ones() const {
  assert(vec->_mp_size >= 0);
  return mpn_popcount(vec->_mp_d, vec->_mp_size);
}

inline bool
Bit_Row::empty() const {
  return mpz_sgn(vec) == 0;
}

inline void
Bit_Row::swap(Bit_Row& y) {
  mpz_swap(vec, y.vec);
}

inline void
Bit_Row::clear() {
  mpz_set_ui(vec, 0UL);
}

inline memory_size_type
Bit_Row::external_memory_in_bytes() const {
  return vec[0]._mp_alloc * SIZEOF_MP_LIMB_T;
}

inline memory_size_type
Bit_Row::total_memory_in_bytes() const {
  return sizeof(*this) + external_memory_in_bytes();
}

#if HAVE_DECL_FFS && SIZEOF_MP_LIMB_T == SIZEOF_INT

inline unsigned int
Bit_Row::first_one(mp_limb_t w) {
  return ffs(w)-1;
}

#endif

/*! \relates Bit_Row */
inline void
set_union(const Bit_Row& x, const Bit_Row& y, Bit_Row& z) {
  mpz_ior(z.vec, x.vec, y.vec);
}

} // namespace Parma_Polyhedra_Library


namespace std {

/*! \relates Parma_Polyhedra_Library::Bit_Row */
inline void
swap(Parma_Polyhedra_Library::Bit_Row& x,
     Parma_Polyhedra_Library::Bit_Row& y) {
  x.swap(y);
}

/*! \relates Parma_Polyhedra_Library::Bit_Row */
inline void
iter_swap(std::vector<Parma_Polyhedra_Library::Bit_Row>::iterator x,
	  std::vector<Parma_Polyhedra_Library::Bit_Row>::iterator y) {
  swap(*x, *y);
}

} // namespace std

#endif // !defined(PPL_Bit_Row_inlines_hh)