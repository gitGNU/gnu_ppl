dnl Copyright (C) 2001-2007 Roberto Bagnara <bagnara@cs.unipr.it>
dnl
dnl This file is part of the Parma Polyhedra Library (PPL).
dnl
dnl The PPL is free software; you can redistribute it and/or modify it
dnl under the terms of the GNU General Public License as published by the
dnl Free Software Foundation; either version 3 of the License, or (at your
dnl option) any later version.
dnl
dnl The PPL is distributed in the hope that it will be useful, but WITHOUT
dnl ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
dnl FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
dnl for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software Foundation,
dnl Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.
dnl
dnl For the most up-to-date information see the Parma Polyhedra Library
dnl site: http://www.cs.unipr.it/ppl/ .

m4_divert(-1)dnl

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_from_space_dimension_code',
`int
ppl_new_@TOPOLOGY@@CLASS@_from_space_dimension
(ppl_@CLASS@_t* pph,
 ppl_dimension_type d,
 int empty) try {
  *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(d, empty ? EMPTY : UNIVERSE));
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_from_@INTOPOLOGY@@CLASS@_code',
`int
ppl_new_@TOPOLOGY@@CLASS@_from_@INTOPOLOGY@@CLASS@
(ppl_@CLASS@_t* pph,
 ppl_const_@CLASS@_t ph) try {
  const @INTOPOLOGY@@CPP_CLASS@& phh
    = *static_cast<const @INTOPOLOGY@@CPP_CLASS@*>(to_const(ph));
  *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(phh));
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_from_@UBUILD_REPRESENT@_System_code',
`int
ppl_new_@TOPOLOGY@@CLASS@_from_@UBUILD_REPRESENT@_System
(ppl_@CLASS@_t* pph, ppl_const_@UBUILD_REPRESENT@_System_t cs) try {
  const @UBUILD_REPRESENT@_System& ccs = *to_const(cs);
  *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(ccs));
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_recycle_@UBUILD_REPRESENT@_System_code',
`int
ppl_new_@TOPOLOGY@@CLASS@_recycle_@UBUILD_REPRESENT@_System
(ppl_@CLASS@_t* pph, ppl_@UBUILD_REPRESENT@_System_t cs) try {
  @UBUILD_REPRESENT@_System& ccs = *to_nonconst(cs);
  *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(ccs@RECYCLE@));
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_from_@BOX@_code',
`int
ppl_new_@TOPOLOGY@@CLASS@_from_@BOX@
(ppl_@CLASS@_t* pph,
 ppl_dimension_type (*space_dimension)(void),
 int (*is_empty)(void),
 int (*get_lower_bound)(ppl_dimension_type k, int closed,
			ppl_Coefficient_t n,
			ppl_Coefficient_t d),
 int (*get_upper_bound)(ppl_dimension_type k, int closed,
			ppl_Coefficient_t n,
			ppl_Coefficient_t d)) try {
  dimension_type space_dim = space_dimension();
  if (is_empty())
    *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(space_dim, EMPTY));
  else {
    *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(space_dim, UNIVERSE));
    // Initialization is just to avoid compilation warnings.
    bool closed = false;
    TEMP_INTEGER(n);
    TEMP_INTEGER(d);
    for (dimension_type k = space_dim; k-- > 0; ) {
      if (get_lower_bound(k, closed, to_nonconst(&n), to_nonconst(&d))) {
        if (closed)
          to_nonconst(*pph)->add_constraint(d*Variable(k) >= n);
        else
          to_nonconst(*pph)->add_constraint(d*Variable(k) > n);
      }
      if (get_upper_bound(k, closed, to_nonconst(&n), to_nonconst(&d))) {
        if (closed)
          to_nonconst(*pph)->add_constraint(d*Variable(k) <= n);
        else
          to_nonconst(*pph)->add_constraint(d*Variable(k) < n);
      }
    }
  }
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_delete_@CLASS@_code',
`int
ppl_delete_@CLASS@(ppl_const_@CLASS@_t ph) try {
  delete to_const(ph);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_assign_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@_code',
`int
ppl_assign_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@
(ppl_@CLASS@_t dst,
 ppl_const_@CLASS@_t src) try {
  const @TOPOLOGY@@CPP_CLASS@& ssrc
    = *static_cast<const @TOPOLOGY@@CPP_CLASS@*>(to_const(src));
  @TOPOLOGY@@CPP_CLASS@& ddst
    = *static_cast<@TOPOLOGY@@CPP_CLASS@*>(to_nonconst(dst));
  ddst = ssrc;
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@DIMENSION@_code',
`int
ppl_@CLASS@_@DIMENSION@
(ppl_const_@CLASS@_t ph,
 ppl_dimension_type* m) try {
  *m = to_const(ph)->@DIMENSION@();
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@GET_REPRESENT@s_code',
`int
ppl_@CLASS@_@GET_REPRESENT@s
(ppl_const_@CLASS@_t ph,
 ppl_const_@UGET_REPRESENT@_System_t* pcs) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  const @UGET_REPRESENT@_System& cs = pph.@GET_REPRESENT@s();
  *pcs = to_const(&cs);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_minimized_@GET_REPRESENT@s_code',
`int
ppl_@CLASS@_minimized_@GET_REPRESENT@s
(ppl_const_@CLASS@_t ph,
 ppl_const_@UGET_REPRESENT@_System_t* pcs) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  const @UGET_REPRESENT@_System& cs = pph.minimized_@GET_REPRESENT@s();
  *pcs = to_const(&cs);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_relation_with_@URELATION_REPRESENT@_code',
`int
ppl_@CLASS@_relation_with_@URELATION_REPRESENT@
(ppl_const_@CLASS@_t ph,
 ppl_const_@URELATION_REPRESENT@_t c) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  const @URELATION_REPRESENT@& cc = *to_const(c);
  return pph.relation_with(cc).get_flags();
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@HAS_PROPERTY@_code',
`int
ppl_@CLASS@_@HAS_PROPERTY@(ppl_const_@CLASS@_t ph) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  return pph.@HAS_PROPERTY@() ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_bounds_from_@ABOVEBELOW@_code',
`int
ppl_@CLASS@_bounds_from_@ABOVEBELOW@
(ppl_const_@CLASS@_t ph,
 ppl_const_Linear_Expression_t le) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  const Linear_Expression& lle = *to_const(le);
  return pph.bounds_from_@ABOVEBELOW@(lle) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@MAXMIN@_code',
`int
ppl_@CLASS@_@MAXMIN@
(ppl_const_@CLASS@_t ph,
 ppl_const_Linear_Expression_t le,
 ppl_Coefficient_t sup_n,
 ppl_Coefficient_t sup_d,
 int* poptimum,
 ppl_Generator_t point) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  const Linear_Expression& lle = *to_const(le);
  Coefficient& ssup_n = *to_nonconst(sup_n);
  Coefficient& ssup_d = *to_nonconst(sup_d);
  Generator& ppoint = *to_nonconst(point);
  bool optimum;
  bool ok = pph.@MAXMIN@(lle, ssup_n, ssup_d, optimum, ppoint);
  if (ok)
    *poptimum = optimum ? 1 : 0;
  return ok ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@COMPARISON@_@CLASS@_code',
`int
ppl_@CLASS@_@COMPARISON@_@CLASS@
(ppl_const_@CLASS@_t x,
 ppl_const_@CLASS@_t y) try {
  const @CPP_CLASS@& xx = *to_const(x);
  const @CPP_CLASS@& yy = *to_const(y);
  return xx.@COMPARISON@(yy) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_equals_@CLASS@_code',
`int
ppl_@CLASS@_equals_@CLASS@
(ppl_const_@CLASS@_t x,
 ppl_const_@CLASS@_t y) try {
  const @CPP_CLASS@& xx = *to_const(x);
  const @CPP_CLASS@& yy = *to_const(y);
  return (xx == yy) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_OK_code',
`int
ppl_@CLASS@_OK(ppl_const_@CLASS@_t ph) try {
  return to_const(ph)->OK() ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_topological_closure_assign_code',
`int
ppl_@CLASS@_topological_closure_assign(ppl_@CLASS@_t ph) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  pph.topological_closure_assign();
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@BINOP@_code',
`int
ppl_@CLASS@_@BINOP@
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y) try {
  @CPP_CLASS@& xx = *to_nonconst(x);
  const @CPP_CLASS@& yy = *to_const(y);
  xx.@BINOP@(yy);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@BINMINOP@_code',
`int
ppl_@CLASS@_@BINMINOP@
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y) try {
  @CPP_CLASS@& xx = *to_nonconst(x);
  const @CPP_CLASS@& yy = *to_const(y);
  return xx.@BINMINOP@(yy) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@_code',
`int
ppl_@CLASS@_add_@ADD_REPRESENT@
(ppl_@CLASS@_t ph,
 ppl_const_@UADD_REPRESENT@_t c) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const @UADD_REPRESENT@& cc = *to_const(c);
  pph.add_@ADD_REPRESENT@(cc);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@_and_minimize_code',
`int
ppl_@CLASS@_add_@ADD_REPRESENT@_and_minimize
(ppl_@CLASS@_t ph,
 ppl_const_@UADD_REPRESENT@_t c) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const @UADD_REPRESENT@& cc = *to_const(c);
  return pph.add_@ADD_REPRESENT@_and_minimize(cc) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@s_code',
`int
ppl_@CLASS@_add_@ADD_REPRESENT@s
(ppl_@CLASS@_t ph,
 ppl_const_@UADD_REPRESENT@_System_t cs) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const @UADD_REPRESENT@_System& ccs = *to_const(cs);
  pph.add_@ADD_REPRESENT@s(ccs);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@s_and_minimize_code',
`int
ppl_@CLASS@_add_@ADD_REPRESENT@s_and_minimize
(ppl_@CLASS@_t ph,
 ppl_const_@UADD_REPRESENT@_System_t cs) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const @UADD_REPRESENT@_System& ccs = *to_const(cs);
  return pph.add_@ADD_REPRESENT@s_and_minimize(ccs) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_recycled_@ADD_REPRESENT@s_code',
`int
ppl_@CLASS@_add_recycled_@ADD_REPRESENT@s
(ppl_@CLASS@_t ph,
 ppl_@UADD_REPRESENT@_System_t cs) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  @UADD_REPRESENT@_System& ccs = *to_nonconst(cs);
  pph.add_recycled_@ADD_REPRESENT@s(ccs);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_recycled_@ADD_REPRESENT@s_and_minimize_code',
`int
ppl_@CLASS@_add_recycled_@ADD_REPRESENT@s_and_minimize
(ppl_@CLASS@_t ph,
 ppl_@UADD_REPRESENT@_System_t cs) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  @UADD_REPRESENT@_System& ccs = *to_nonconst(cs);
  return pph.add_recycled_@ADD_REPRESENT@s_and_minimize(ccs) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@AFFIMAGE@_code',
`int
ppl_@CLASS@_@AFFIMAGE@
(ppl_@CLASS@_t ph,
 ppl_dimension_type var,
 ppl_const_Linear_Expression_t le,
 ppl_const_Coefficient_t d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const Linear_Expression& lle = *to_const(le);
  const Coefficient& dd = *to_const(d);
  pph.@AFFIMAGE@(Variable(var), lle, dd);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_bounded_@AFFIMAGE@_code',
`int
ppl_@CLASS@_bounded_@AFFIMAGE@
(ppl_@CLASS@_t ph,
 ppl_dimension_type var,
 ppl_const_Linear_Expression_t lb,
 ppl_const_Linear_Expression_t ub,
 ppl_const_Coefficient_t d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const Linear_Expression& llb = *to_const(lb);
  const Linear_Expression& uub = *to_const(ub);
  const Coefficient& dd = *to_const(d);
  pph.bounded_@AFFIMAGE@(Variable(var), llb, uub, dd);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_generalized_@AFFIMAGE@_code',
`int
ppl_@CLASS@_generalized_@AFFIMAGE@
(ppl_@CLASS@_t ph,
 ppl_dimension_type var,
 enum ppl_enum_Constraint_Type relsym,
 ppl_const_Linear_Expression_t le,
 ppl_const_Coefficient_t d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const Linear_Expression& lle = *to_const(le);
  const Coefficient& dd = *to_const(d);
  pph.generalized_@AFFIMAGE@
    (Variable(var), relation_symbol(relsym), lle, dd);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_generalized_@AFFIMAGE@_lhs_rhs_code',
`int
ppl_@CLASS@_generalized_@AFFIMAGE@_lhs_rhs
(ppl_@CLASS@_t ph,
 ppl_const_Linear_Expression_t lhs,
 enum ppl_enum_Constraint_Type relsym,
 ppl_const_Linear_Expression_t rhs) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const Linear_Expression& llhs = *to_const(lhs);
  const Linear_Expression& rrhs = *to_const(rhs);
  pph.generalized_@AFFIMAGE@(llhs, relation_symbol(relsym), rrhs);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@WIDEN@_widening_assign_with_tokens_code',
`int
ppl_@CLASS@_@WIDEN@_widening_assign_with_tokens
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y,
 unsigned* tp) try {
  @CPP_CLASS@& xx = *to_nonconst(x);
  const @CPP_CLASS@& yy = *to_const(y);
  xx.@WIDEN@_widening_assign(yy, tp);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@WIDEN@_widening_assign_code',
`int
ppl_@CLASS@_@WIDEN@_widening_assign
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y) try {
  return ppl_@CLASS@_@WIDEN@_widening_assign_with_tokens(x, y, 0);
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_limited_@WIDENEXPN@_extrapolation_assign_with_tokens_code',
`int
ppl_@CLASS@_limited_@WIDENEXPN@_extrapolation_assign_with_tokens
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y,
 ppl_const_@UCONSTRAINER@_System_t cs,
 unsigned* tp) try {
  @CPP_CLASS@& xx = *to_nonconst(x);
  const @CPP_CLASS@& yy = *to_const(y);
  const @UCONSTRAINER@_System& ccs = *to_const(cs);
  xx.limited_@WIDENEXPN@_extrapolation_assign(yy, ccs, tp);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_limited_@WIDENEXPN@_extrapolation_assign_code',
`int
ppl_@CLASS@_limited_@WIDENEXPN@_extrapolation_assign
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y,
 ppl_const_@UCONSTRAINER@_System_t cs) try {
  return
    ppl_@CLASS@_limited_@WIDENEXPN@_extrapolation_assign_with_tokens
      (x, y, cs, 0);
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_bounded_@WIDENEXPN@_extrapolation_assign_with_tokens_code',
`int
ppl_@CLASS@_bounded_@WIDENEXPN@_extrapolation_assign_with_tokens
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y,
 ppl_const_@UCONSTRAINER@_System_t cs,
 unsigned* tp) try {
  @CPP_CLASS@& xx = *to_nonconst(x);
  const @CPP_CLASS@& yy = *to_const(y);
  const @UCONSTRAINER@_System& ccs = *to_const(cs);
  xx.bounded_@WIDENEXPN@_extrapolation_assign(yy, ccs, tp);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_bounded_@WIDENEXPN@_extrapolation_assign_code',
`int
ppl_@CLASS@_bounded_@WIDENEXPN@_extrapolation_assign
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y,
 ppl_const_@UCONSTRAINER@_System_t cs) try {
  return
    ppl_@CLASS@_bounded_@WIDENEXPN@_extrapolation_assign_with_tokens
      (x, y, cs, 0);
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_space_dimensions_@EMBEDPROJECT@_code',
`int
ppl_@CLASS@_add_space_dimensions_@EMBEDPROJECT@
(ppl_@CLASS@_t ph,
 ppl_dimension_type d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  pph.add_space_dimensions_@EMBEDPROJECT@(d);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_remove_space_dimensions_code',
`int
ppl_@CLASS@_remove_space_dimensions
(ppl_@CLASS@_t ph,
 ppl_dimension_type ds[],
 size_t n) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  Variables_Set to_be_removed;
  for (ppl_dimension_type i = n; i-- > 0; )
    to_be_removed.insert(ds[i]);
  pph.remove_space_dimensions(to_be_removed);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_remove_higher_space_dimensions_code',
`int
ppl_@CLASS@_remove_higher_space_dimensions
(ppl_@CLASS@_t ph,
 ppl_dimension_type d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  pph.remove_higher_space_dimensions(d);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_map_space_dimensions_code',
`int
ppl_@CLASS@_map_space_dimensions
(ppl_@CLASS@_t ph,
 ppl_dimension_type maps[],
 size_t n) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  PIFunc pifunc(maps, n);
  pph.map_space_dimensions(pifunc);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_expand_space_dimension_code',
`int
ppl_@CLASS@_expand_space_dimension
(ppl_@CLASS@_t ph,
 ppl_dimension_type d,
 ppl_dimension_type m) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  pph.expand_space_dimension(Variable(d), m);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_fold_space_dimensions_code',
`int
ppl_@CLASS@_fold_space_dimensions
(ppl_@CLASS@_t ph,
 ppl_dimension_type ds[],
 size_t n,
 ppl_dimension_type d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  Variables_Set to_be_folded;
  for (ppl_dimension_type i = n; i-- > 0; )
    to_be_folded.insert(ds[i]);
  pph.fold_space_dimensions(to_be_folded, Variable(d));
  return 0;
}
CATCH_ALL

')

m4_divert`'dnl
