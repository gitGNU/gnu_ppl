dnl Copyright (C) 2001-2008 Roberto Bagnara <bagnara@cs.unipr.it>
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
m4_divert(-1)

dnl Code for generating the domain elements to be used in the tests.
dnl Note that if a test may change these at all, then a copy should be used.
m4_define(`m4_add_init_class_code', `dnl
let @LTOPOLOGY@@LCLASS@01
  = ppl_new_@TOPOLOGY@@CLASS@_from_space_dimension 3 Universe;;
ppl_@TOPOLOGY@@CLASS@_add_@CONSTRAINER@s
  @LTOPOLOGY@@LCLASS@01 @CONSTRAINER@s01;;
let @LTOPOLOGY@@LCLASS@02
  = ppl_new_@TOPOLOGY@@CLASS@_from_space_dimension 3 Universe;;
ppl_@TOPOLOGY@@CLASS@_add_@CONSTRAINER@s
  @LTOPOLOGY@@LCLASS@02 @CONSTRAINER@s02;;
let @LTOPOLOGY@@LCLASS@03
  = ppl_new_@TOPOLOGY@@CLASS@_from_space_dimension 3 Universe;;
ppl_@TOPOLOGY@@CLASS@_add_@CONSTRAINER@s
  @LTOPOLOGY@@LCLASS@03 @CONSTRAINER@s03;;
print_newline();;
')

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_from_space_dimension_code',
`
print_string "testing ppl_new_@TOPOLOGY@@CLASS@_from_space_dimension" ;;
print_newline();;
print_string ("space_dimension: ");;
for i = 6 downto 0 do
  (let @LTOPOLOGY@@LCLASS@
    = ppl_new_@TOPOLOGY@@CLASS@_from_space_dimension i Empty
    in let dimension
       =  ppl_@TOPOLOGY@@CLASS@_space_dimension(@LTOPOLOGY@@LCLASS@)
       in printf "%d, " dimension)
done;;
print_newline();;

')

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_from_@FRIEND@_code',
`
print_string "testing ppl_new_@TOPOLOGY@@CLASS@_from_@FRIEND@: " ;;
let ps
  = ppl_new_@FRIEND@_from_space_dimension 3 Universe;;
let ps1
  = ppl_new_@TOPOLOGY@@CLASS@_from_@FRIEND@(ps);;
let out = if (ppl_@FRIEND@_OK ps & ppl_@TOPOLOGY@@CLASS@_OK ps1)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`__ppl_new_@TOPOLOGY@@CLASS@_from_@FRIEND@_with_complexity_code',
`
print_string
  "testing ppl_new_@TOPOLOGY@@CLASS@_from_@FRIEND@_with_complexity: " ;;
let ps
  = ppl_new_@FRIEND@_from_space_dimension 3 Universe;;
let ps1
  = ppl_new_@TOPOLOGY@@CLASS@_from_@FRIEND@_with_complexity ps ;;
let out = if (ppl_@FRIEND@_OK ps & ppl_@TOPOLOGY@@CLASS@_OK ps1)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_from_@BUILD_REPRESENT@s_code',
`
print_string "testing ppl_new_@TOPOLOGY@@CLASS@_from_@BUILD_REPRESENT@s: " ;;
let @LTOPOLOGY@@LCLASS@
  = ppl_new_@TOPOLOGY@@CLASS@_from_@BUILD_REPRESENT@s(@BUILD_REPRESENT@s1);;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@TOPOLOGY@@CLASS@_@UB_EXACT@_code',
`
print_string "testing ppl_@TOPOLOGY@@CLASS@_@UB_EXACT@: " ;;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy02
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let _result
  =  ppl_@TOPOLOGY@@CLASS@_@UB_EXACT@ copy01 copy02;;
let out
  = if (ppl_@TOPOLOGY@@CLASS@_OK copy01 & ppl_@TOPOLOGY@@CLASS@_OK copy02)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_swap_code',
`
print_string "testing ppl_@CLASS@_swap: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy02
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_swap copy01 copy02;;
let out
  = if (ppl_@TOPOLOGY@@CLASS@_OK copy01 & ppl_@TOPOLOGY@@CLASS@_OK copy02)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@DIMENSION@_code',
`
print_string "testing ppl_@CLASS@_@DIMENSION@: " ;;
let dim
  =  ppl_@TOPOLOGY@@CLASS@_@DIMENSION@ @LTOPOLOGY@@LCLASS@01;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
printf "@DIMENSION@: %d" dim;;
print_newline();;
')

m4_define(`ppl_@CLASS@_relation_with_@RELATION_REPRESENT@_code',
`
print_string "testing ppl_@CLASS@_relation_with_@RELATION_REPRESENT@: " ;;
let _result
  = ppl_@TOPOLOGY@@CLASS@_relation_with_@RELATION_REPRESENT@
    @LTOPOLOGY@@LCLASS@01 @RELATION_REPRESENT@1;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_get_@GET_REPRESENT@s_code',
`
print_string "testing ppl_@CLASS@_get_@GET_REPRESENT@s: ";;
let @GET_REPRESENT@s = ppl_@TOPOLOGY@@CLASS@_get_@GET_REPRESENT@s
  @LTOPOLOGY@@LCLASS@01;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
List.iter print_@GET_REPRESENT@ @GET_REPRESENT@s;;
print_newline();;
')

m4_define(`ppl_@CLASS@_@HAS_PROPERTY@_code',
`
print_string "testing ppl_@CLASS@_@HAS_PROPERTY@: ";;
let result = ppl_@TOPOLOGY@@CLASS@_@HAS_PROPERTY@ @LTOPOLOGY@@LCLASS@01;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
printf "@HAS_PROPERTY@: %b" result;;
print_newline();;
')

m4_define(`ppl_@CLASS@_@SIMPLIFY@_code',
`
print_string "testing ppl_@CLASS@_@SIMPLIFY@: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_@SIMPLIFY@ copy01;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_bounds_from_@ABOVEBELOW@_code',
`
print_string "testing ppl_@CLASS@_bounds_from_@ABOVEBELOW@: " ;;
let _result
  =  ppl_@TOPOLOGY@@CLASS@_bounds_from_above @LTOPOLOGY@@LCLASS@01 e2;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@MAXMIN@_code',
`
print_string "testing ppl_@CLASS@_@MAXMIN@: ";;
let (is_bounded, num, den, is_supremum)
  = ppl_@TOPOLOGY@@CLASS@_@MAXMIN@ @LTOPOLOGY@@LCLASS@01 e3;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
print_int(Z.to_int num);;
print_string "/";;
print_int(Z.to_int den);;
print_string (", bound: ");;
print_string (string_of_bool is_bounded);;
print_string (", sup: ");;
print_string (string_of_bool is_supremum);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@MAXMIN@_with_point_code',
`
print_string "testing ppl_@CLASS@_@MAXMIN@_with_point: ";;
let (is_bounded, num, den, is_supremum, pt)
  = ppl_@TOPOLOGY@@CLASS@_@MAXMIN@_with_point @LTOPOLOGY@@LCLASS@01 e3;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
print_int(Z.to_int num);;
print_string "/";;
print_int(Z.to_int den);;
print_string (", bound: ");;
print_string (string_of_bool is_bounded);;
print_string (", sup: ");;
print_string (string_of_bool is_supremum);;
print_string (", ");;
print_generator(pt);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@COMPARISON@_@CLASS@_code',
`
print_string "testing ppl_@CLASS@_@COMPARISON@_@CLASS@: " ;;
let b = ppl_@TOPOLOGY@@CLASS@_@COMPARISON@_@TOPOLOGY@@CLASS@
  @LTOPOLOGY@@LCLASS@01 @LTOPOLOGY@@LCLASS@02;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01
               & ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@02)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_equals_@CLASS@_code',
`
print_string "testing ppl_@CLASS@_equals_@CLASS@: " ;;
let b = ppl_@TOPOLOGY@@CLASS@_equals_@TOPOLOGY@@CLASS@
  @LTOPOLOGY@@LCLASS@01 @LTOPOLOGY@@LCLASS@02;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01
               & ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@02)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_OK_code',
`
print_string "testing ppl_@CLASS@_OK: ";;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01
               & ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@02)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@_code',
`
print_string "testing ppl_@TOPOLOGY@@CLASS@_add_@ADD_REPRESENT@: " ;;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_add_@ADD_REPRESENT@ copy01 @ADD_REPRESENT@1;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@_and_minimize_code',
`
print_string
  "testing ppl_@TOPOLOGY@@CLASS@_add_@ADD_REPRESENT@_and_minimize: " ;;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let b = ppl_@TOPOLOGY@@CLASS@_add_@ADD_REPRESENT@_and_minimize
  copy01 @ADD_REPRESENT@1;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@s_code',
`
print_string "testing ppl_@TOPOLOGY@@CLASS@_add_@ADD_REPRESENT@s: " ;;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_add_@ADD_REPRESENT@s copy01 @ADD_REPRESENT@s1;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@s_and_minimize_code',
`
print_string
  "testing ppl_@TOPOLOGY@@CLASS@_add_@ADD_REPRESENT@s_and_minimize: " ;;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let b = ppl_@TOPOLOGY@@CLASS@_add_@ADD_REPRESENT@s_and_minimize
  copy01 @ADD_REPRESENT@s1;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_refine_with_@REFINE_REPRESENT@_code',
`
print_string
  "testing ppl_@TOPOLOGY@@CLASS@_refine_with_@REFINE_REPRESENT@: " ;;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_refine_with_@REFINE_REPRESENT@
  copy01 @REFINE_REPRESENT@01;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_refine_with_@REFINE_REPRESENT@s_code',
`
print_string
  "testing ppl_@TOPOLOGY@@CLASS@_refine_with_@REFINE_REPRESENT@s: " ;;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_refine_with_@REFINE_REPRESENT@s
  copy01 @REFINE_REPRESENT@s01;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@BINOP@_code',
`
print_string "testing ppl_@CLASS@_@BINOP@: " ;;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy02
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_@BINOP@ copy01 copy02;;
let out
  = if (ppl_@TOPOLOGY@@CLASS@_OK copy01 & ppl_@TOPOLOGY@@CLASS@_OK copy02)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@BINMINOP@_code',
`
print_string "testing ppl_@CLASS@_@BINMINOP@: " ;;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy02
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let b = ppl_@TOPOLOGY@@CLASS@_@BINMINOP@ copy01 copy02;;
let out
  = if (ppl_@TOPOLOGY@@CLASS@_OK copy01 & ppl_@TOPOLOGY@@CLASS@_OK copy02)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@AFFIMAGE@_code',
`
print_string "testing ppl_@CLASS@_@AFFIMAGE@: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_@AFFIMAGE@ copy01 1 ((Z.of_int 2) */ v2) (Z.from_int 2);;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_bounded_@AFFIMAGE@_code',
`
print_string "testing ppl_@CLASS@_bounded_@AFFIMAGE@: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_bounded_@AFFIMAGE@ copy01 1
  ((Z.of_int 2) */ v2) v2 (Z.from_int 10);;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_generalized_@AFFIMAGE@_code',
`
print_string "testing ppl_@CLASS@_generalized_@AFFIMAGE@: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_generalized_@AFFIMAGE@
  copy01 1 Equal_RS v1 (Z.from_int 10);;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_generalized_@AFFIMAGE@_lhs_rhs_code',
`
print_string "testing ppl_@CLASS@_generalized_@AFFIMAGE@_lhs_rhs: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_generalized_@AFFIMAGE@_lhs_rhs
  copy01 ((Z.of_int 1) */ v0) Equal_RS (linear_expression_of_int 7);;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_generalized_@AFFIMAGE@_with_congruence_code',
`
print_string "testing ppl_@CLASS@_generalized_@AFFIMAGE@_with_congruence: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_generalized_@AFFIMAGE@_with_congruence
  copy01 1 Equal_RS v1 (Z.from_int 10);;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_generalized_@AFFIMAGE@_lhs_rhs_with_congruence_code',
`
print_string "testing ppl_@CLASS@_generalized_@AFFIMAGE@_lhs_rhs_with_congruence: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_generalized_@AFFIMAGE@_lhs_rhs_with_congruence
  copy01 ((Z.of_int 1) */ v0) Equal_RS (linear_expression_of_int 7);;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_add_space_dimensions_@EMBEDPROJECT@_code',
`
print_string "testing ppl_@CLASS@_add_space_dimensions_@EMBEDPROJECT@: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_add_space_dimensions_@EMBEDPROJECT@ copy01 2;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_remove_space_dimensions_code',
`
print_string "testing ppl_@CLASS@_remove_space_dimensions: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let dimensions_to_remove = [2;0];;
ppl_@TOPOLOGY@@CLASS@_remove_space_dimensions copy01 dimensions_to_remove;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_remove_higher_space_dimensions_code',
`
print_string "testing ppl_@CLASS@_remove_higher_space_dimensions: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_remove_higher_space_dimensions copy01 1;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_expand_space_dimension_code',
`
print_string "testing ppl_@CLASS@_expand_space_dimension: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_expand_space_dimension copy01 1 1;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_fold_space_dimensions_code',
`
print_string "testing ppl_@CLASS@_fold_space_dimensions: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let dimensions_to_fold = [1];;
ppl_@TOPOLOGY@@CLASS@_fold_space_dimensions copy01 dimensions_to_fold 0;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_map_space_dimensions_code',
`
print_string "testing ppl_@CLASS@_map_space_dimensions: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let dimensions_to_map = [(0,1);(1,2);(2,0);];;
ppl_@TOPOLOGY@@CLASS@_map_space_dimensions copy01 dimensions_to_map;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_constrains_code',
`
print_string "testing ppl_@CLASS@_constrains: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_constrains copy01 1;;
ppl_@TOPOLOGY@@CLASS@_map_space_dimensions copy01 dimensions_to_map;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_unconstrain_space_dimension_code',
`
print_string "testing ppl_@CLASS@_unconstrain_space_dimension: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
ppl_@TOPOLOGY@@CLASS@_unconstrain_space_dimension copy01 1;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_unconstrain_space_dimensions_code',
`
print_string "testing ppl_@CLASS@_unconstrain_space_dimensions: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let dimensions_to_unconstrain = [1];;
ppl_@TOPOLOGY@@CLASS@_unconstrain_space_dimensions
  copy01 dimensions_to_unconstrain;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@MEMBYTES@_code',
`
print_string "testing ppl_@CLASS@_@MEMBYTES@: " ;;
let mb
  =  ppl_@TOPOLOGY@@CLASS@_@MEMBYTES@ @LTOPOLOGY@@LCLASS@01;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
printf "@MEMBYTES@: %d" mb;;
print_newline();;
')

m4_define(`ppl_@CLASS@_@WIDEN@_widening_assign_code',
`
print_string "testing ppl_@CLASS@_@WIDEN@_widening_assign: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy03
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@03);;
ppl_@TOPOLOGY@@CLASS@_@WIDEN@_widening_assign copy01 copy03 ;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@WIDEN@_widening_assign_with_tokens_code',
`
print_string "testing ppl_@CLASS@_@WIDEN@_widening_assign_with_tokens_code: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy03
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@03);;
let tokens
  = ppl_@TOPOLOGY@@CLASS@_@WIDEN@_widening_assign_with_tokens copy01 copy03 5;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
print_string "tokens after widening = ";;
print_int tokens;;
print_newline();;
')

m4_define(`ppl_@CLASS@_@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign_code',
`
print_string
  "testing ppl_@CLASS@_@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy03
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@03);;
ppl_@TOPOLOGY@@CLASS@_@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign
  copy01 copy03 @CONSTRAINER@s04;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign_with_tokens_code',
`
print_string
  "testing ppl_@CLASS@_@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign_with_tokens: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy03
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@03);;
let tokens
  = ppl_@TOPOLOGY@@CLASS@_@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign_with_tokens
  copy01 copy03 @CONSTRAINER@s04 10;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
print_string "tokens after widening = ";;
print_int tokens;;
print_newline();;
')

m4_define(`ppl_@CLASS@_@EXTRAPOLATION@_extrapolation_assign_code',
`
print_string "testing ppl_@CLASS@_@EXTRAPOLATION@_extrapolation_assign: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy03
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@03);;
ppl_@TOPOLOGY@@CLASS@_@EXTRAPOLATION@_extrapolation_assign copy01 copy03 ;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@EXTRAPOLATION@_extrapolation_assign_with_tokens_code',
`
print_string "testing ppl_@CLASS@_@EXTRAPOLATION@_extrapolation_assign_with_tokens_code: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy03
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@03);;
let tokens
  = ppl_@TOPOLOGY@@CLASS@_@EXTRAPOLATION@_extrapolation_assign_with_tokens
    copy01 copy03 5;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
print_string "tokens after extrapolation = ";;
print_int tokens;;
print_newline();;
')


m4_define(`ppl_@CLASS@_@EXTRAPOLATION@_narrowing_assign_code',
`
print_string "testing ppl_@CLASS@_@EXTRAPOLATION@_narrowing_assign: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy03
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@03);;
ppl_@TOPOLOGY@@CLASS@_@EXTRAPOLATION@_narrowing_assign copy03 copy01 ;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')


m4_define(`ppl_@CLASS@_BHZ03_@ALT_DISJUNCT_WIDEN@_@DISJUNCT_WIDEN@_widening_assign_code',
`
print_string "testing ppl_@CLASS@_BHZ03_@ALT_DISJUNCT_WIDEN@_@DISJUNCT_WIDEN@_widening_assign: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy03
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@03);;
ppl_@CLASS@_BHZ03_@ALT_DISJUNCT_WIDEN@_@DISJUNCT_WIDEN@_widening_assign copy01 copy03 ;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_BGP99_@DISJUNCT_WIDEN@_extrapolation_assign_code',
`
print_string "testing ppl_@CLASS@_BGP99_@DISJUNCT_WIDEN@_extrapolation_assign: ";;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let copy03
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@03);;
ppl_@CLASS@_BGP99_@DISJUNCT_WIDEN@_extrapolation_assign copy01 copy03 2;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@BEGINEND@_iterator_code',
`
print_string "testing ppl_@BEGINEND@_iterator: " ;;
let it = ppl_@CLASS@_@BEGINEND@_iterator @LTOPOLOGY@@LCLASS@01;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_iterator_equals_iterator_code',
`
print_string "testing ppl_@CLASS@_iterator_equals_iterator: " ;;
let it = ppl_@CLASS@_begin_iterator @LTOPOLOGY@@LCLASS@01;;
let it_begin = ppl_@CLASS@_begin_iterator @LTOPOLOGY@@LCLASS@01;;
let b = ppl_@CLASS@_iterator_equals_iterator it it_begin;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_@INCDEC@_iterator_code',
`
print_string "testing ppl_@CLASS@_@INCDEC@_iterator: " ;;
let it = ppl_@CLASS@_begin_iterator @LTOPOLOGY@@LCLASS@01;;
ppl_@CLASS@_@INCDEC@_iterator it;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_get_disjunct_code',
`
print_string "testing ppl_@CLASS@_get_disjunct: " ;;
let it = ppl_@CLASS@_begin_iterator @LTOPOLOGY@@LCLASS@01;;
let d = ppl_@CLASS@_get_disjunct it;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK @LTOPOLOGY@@LCLASS@01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')

m4_define(`ppl_@CLASS@_drop_disjunct_code',
`
print_string "testing ppl_@CLASS@_drop_disjunct: " ;;
let copy01
  = ppl_new_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@(@LTOPOLOGY@@LCLASS@01);;
let it = ppl_@CLASS@_begin_iterator copy01;;
ppl_@CLASS@_drop_disjunct copy01 it;;
let out = if (ppl_@TOPOLOGY@@CLASS@_OK copy01)
  then "success" else "failed"
    in (print_string out);;
print_newline();;
')