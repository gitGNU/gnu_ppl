m4_define(`dnl', `m4_dnl')`'dnl
m4_divert(-1)

dnl This m4 file generates the file ppl_prolog.icc
dnl using the code in ppl_interface_generator_prolog_icc_code.m4.

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

dnl This file generates ppl_prolog.icc.
dnl
dnl Include files defining macros that generate the non-fixed part.
m4_include(`ppl_interface_generator_prolog_cc_code.m4')
m4_include(`ppl_interface_generator_prolog_procedure_generators.m4')

m4_divert`'dnl
%<--%<--%<-- ppl_prolog_main.hh
/* Prolog interface code.
m4_include(`ppl_interface_generator_copyright')
*/
m4_divert(-1)

dnl m4_add_bop_assign_code(Class, CPP_Class)
dnl
dnl Adds the extra code used by the binary operators.
m4_define(`m4_add_bop_assign_code', `dnl
m4_replace_all_patterns_in_string($1,
  bop_assign_code,
  m4_pattern_list)`'dnl
')

dnl m4_pre_extra_class_code(Class_Counter)
dnl Prefix extra code for each class.
m4_define(`m4_pre_extra_class_code', `dnl
m4_define(`m4_current_interface', m4_interface_class`'$1)`'dnl
%<--%<--%<-- ppl_prolog_main.hh
`#'include "ppl_prolog_`'m4_current_interface.hh"
%<--%<--%<-- ppl_prolog_`'m4_current_interface.hh
/* Prolog m4_current_interface interface code.
*/
m4_add_bop_assign_code($1)`'dnl
m4_undefine(`m4_current_interface')`'dnl
')

m4_divert`'dnl
dnl
`#'include "ppl_prolog_common.hh"`'dnl
dnl
dnl Generate the non-fixed part of the file.
m4_all_code`'dnl
dnl
dnl End of file generation.
