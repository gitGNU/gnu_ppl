m4_define(`dnl', `m4_dnl')
dnl This file generates ppl_ciao_predicate_check.pl
/* XSB Prolog interface: XSB Prolog part for checking all predicates.
m4_include(`ppl_interface_generator_copyright')
*/

:- compiler_options([xpp_on]).
:- import xpp_include_dir/1 from parse.
:- assert(xpp_include_dir('.')).

:- import append/3, length/2, member/2 from basics.
:- import
m4_divert(1)
   from ppl_xsb.

:- [ppl_xsb].

#include "pl_check.pl"

prolog_system('XSB').

main :-
    (check_all ->
        write('OK')
    ;
        write('FAILURE')
    ),
    nl.

:- main.
m4_divert`'dnl
m4_include(`ppl_interface_generator_prolog_systems.m4')dnl
m4_define(`m4_extension', `m4_ifelse($4, 0, , `COMMA
')	  $1/$2')dnl
m4_patsubst(ppl_prolog_sys_code, COMMA, `,')`'dnl
m4_undivert(1)`'dnl