m4_define(`dnl', `m4_dnl')`'dnl
m4_divert(-1)
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

dnl Classes to be implemented and C++ versions of these classes.
m4_include(ppl_interface_instantiations.m4)

dnl =====================================================================
dnl ===== The first set of macros here initialise the class names   =====
dnl ===== using "@" separated lists and defined                     =====
dnl ===== by macros in ppl_interface_instantiations.m4.             =====
dnl =====================================================================


dnl m4_init_class_definitions
dnl
dnl Macro called by m4_all_code in m4_interface_generators_common.m4
dnl
dnl For all the classes required by the configuration and specified
dnl by m4_interface_classes_names and m4_cplusplus_classes_names
dnl in <build_dir>/interfaces/m4_interface_instantiations.m4
dnl this defines macros for their interface and cplusplus names,
dnl their components and 'entities' related to these components.
dnl
dnl The Boolean flag m4_class_definitions_initialized is set to true
dnl to avoid repeated generation when more than one set of code is
dnl generated for any one file.
m4_define(`m4_init_class_definitions', `dnl
m4_init_interface_classes(m4_interface_classes_names)`'dnl
m4_init_cplusplus_classes(m4_cplusplus_classes_names)`'dnl
m4_define(`m4_class_definitions_initialized', `true')`'dnl
')
dnl ---------------------------------------------------------------------
dnl =====  any extra macros needed for both interfaces and          =====
dnl =====  cplusplus names go here                           .      =====
dnl ---------------------------------------------------------------------

dnl m4_prefix_polyhedron(Class, String)
dnl
dnl Every occurrence of Polyhedron in the name is replaced by
dnl String_Polyhedron.
m4_define(`m4_prefix_polyhedron', `dnl
m4_patsubst($1, Polyhedron, $2_Polyhedron)`'dnl
')

dnl ---------------------------------------------------------------------
dnl =====  Macros for m4_interface_class<class_num> are defined     =====
dnl =====  here.                                                    =====
dnl ---------------------------------------------------------------------

dnl m4_init_interface_classes(Class_List)
dnl
dnl Parses the @-separated list of class names Class_List
dnl for the names of the classes used to form the names of procedures
dnl in the user interface.
m4_define(`m4_init_interface_classes', `dnl
m4_init_interface_classes_aux(1, $1)')

dnl m4_init_interface_classes_aux(Class_Counter, Class_List)
dnl
dnl Class_Counter - is the index to the first class in Class_List;
dnl Class_List    - is a tail part of the input list of interface
dnl                 class names.
dnl The macro also defines m4_num_classes to be the number of classes
dnl in the full list (ie counter + number in the current list - 1).
dnl The macro calls m4_init_interface_names to define the next
dnl interface names and then to to call this macro to recursively
dnl process the rest of the list.
m4_define(`m4_init_interface_classes_aux', `dnl
m4_ifelse($2, `',  `m4_define(m4_num_classes, m4_decr($1))',
  m4_regexp(`$2', `\([^@]+\)@?\(.*\)',
    `m4_init_interface_names($1, \1, \2)'))`'dnl
')

dnl m4_init_interface_names(Class_Counter, Class, Class_List)
dnl
dnl Class_Counter - is the index to the first class in Class_List;
dnl Class         - is the interface class name, as input;
dnl Class_List    - is a tail part of the input list of interface
dnl                 class names.
m4_define(`m4_init_interface_names', `dnl
m4_define(m4_interface_class`'$1, $2)`'dnl
m4_init_interface_classes_aux(m4_incr($1), $3)`'dnl
')

dnl ---------------------------------------------------------------------
dnl =====  Macros for m4_cplusplus_class<class_num> and             =====
dnl =====  its components are defined here.                         =====
dnl ---------------------------------------------------------------------

dnl m4_init_cplusplus_classes(Class_List)
dnl
dnl Parses the "@"-separated list of class names Class_List
dnl to be used in the C++ code implementing the interface procedures.
dnl Note that first the "," is replaced by "COMMA" using the macro
dnl m4_subst_comma because the ',' in the product class is wrongly
dnl parsed by m4.
dnl First all the macros m4_cplusplus_class`'Class_Counter
dnl are defined and then the components are parsed and their entities
dnl defined by additional macros.
m4_define(`m4_init_cplusplus_classes',   `dnl
dnl First all the macros m4_cplusplus_class`'Class_Counter
dnl are defined.
m4_init_cplusplus_classes_aux(1, m4_subst_comma($@))`'dnl
dnl Then the components are parsed and their entities are
dnl defined by additional macros.
m4_init_all_cplusplus_class_components(1)`'dnl
')

dnl m4_subst_comma(String1, String2,...)
dnl
dnl String1, String2,... is the "@"-separated list of C++ class names
dnl provided by the configuration.
dnl As the product classes have their arguments ","-separated,
dnl the "," separates the list into macro arguments.
dnl This macro iterates through these macro arguments, replacing the
dnl "," by "COMMA" so that the C++ names are handled as intended.
m4_define(`m4_subst_comma',
`m4_ifelse($#, 0, , $#, 1, $1,
  `$1`'COMMA`'m4_subst_comma(m4_shift($@))')')

dnl m4_init_cplusplus_classes_aux(Class_Counter, Class_List)
dnl
dnl Class_Counter - is the index to the next class in Class_List;
dnl Class_List    - is a tail part of the input list of cplusplus
dnl                 class names.
dnl The macro calls m4_init_cplusplus_names to define the
dnl cplusplus names (which calls this macro recursively).
dnl The COMMA pattern is revised to @COMMA@ as soon as a class name
dnl has been separated from the @-separated list of classes.
m4_define(`m4_init_cplusplus_classes_aux', `dnl
m4_ifelse($2, `',  `',
  m4_regexp(`$2', `\([^@]+\)@?\(.*\)',
    `m4_init_cplusplus_names(`$1',
      m4_patsubst(\1, COMMA, @COMMA@), `\2')'))`'dnl
')

dnl m4_init_cplusplus_names(Class_Counter, Class, Class_List)
dnl
dnl Class_Counter - is the index to the next class in Class_List;
dnl Class         - is the cplusplus class name, as input;
dnl Class_List    - is a tail part of the input list of cplusplus
dnl                 class names.
dnl This defines m4_cplusplus_class`'Class_Counter
dnl and then calls m4_init_cplusplus_classes_aux to process the rest
dnl of the list of classes.
m4_define(`m4_init_cplusplus_names', `dnl
m4_define(m4_cplusplus_class`'$1, `$2')`'dnl
m4_init_cplusplus_classes_aux(m4_incr($1), $3)`'dnl
')

dnl m4_init_all_cplusplus_class_components(Class_Counter)
dnl
dnl Class_Counter - is the index to the next class in Class_List;
dnl
dnl For each class, this parses the name, finding and defining
dnl schemas for its class kind and group.
dnl For classes that have a sub-component "<...>" part
dnl this also parses and defines macros for these components.
m4_define(`m4_init_all_cplusplus_class_components', `dnl
m4_init_cplusplus_class_components($1, m4_cplusplus_class`'$1, class)`'dnl
m4_ifelse($1, m4_num_classes, ,
    `m4_init_all_cplusplus_class_components(m4_incr($1))')
')

dnl m4_init_cplusplus_class_components(Class_Counter,
dnl                                    String, Macro_Specifier)
dnl
dnl Class_Counter - is the index to Class;
dnl Class         - is the cplusplus class name, as input;
dnl Macro_Specifier
dnl               - is the component of the macro name that
dnl                 determines the precise component it refers to.
dnl
dnl Initially (at the top level), the Macro_Specifier is just "class".
dnl For each component in the name the string "_body" is added.
dnl Thus for Pointset_Powerset<BD_Shape<long> > with Class_Counter = 4
dnl and interface names Pointset_Powerset_BD_Shape_long
dnl with BD_Shape_long defined for the component:
dnl
dnl m4_cplusplus_class4 = Pointset_Powerset<BD_Shape<long> >
dnl m4_interface_class4 = Pointset_Powerset_BD_Shape_long
dnl m4_class_kind4 = Pointset_Powerset
dnl m4_class_group4 = pointset_powerset
dnl m4_class_body_body4 = BD_Shape<long>
dnl m4_cplusplus_class_body4 = BD_Shape<long>
dnl m4_interface_class_body4 = BD_Shape_long
dnl m4_class_body_kind4 = BD_Shape
dnl m4_class_body_group4 = bd_shape
dnl m4_class_body_body4 = long
dnl
dnl For the Product classes, the body is parsed into a "1st"
dnl and "2nd" component:
dnl Thus for Direct_Product<Grid,BD_Shape<long> > with Class_Counter = 5
dnl and interface names Product_BD_Shape_long
dnl with Grid and BD_Shape_long for the components:
dnl m4_cplusplus_class5 = Direct_Product<Grid@COMMA@BD_Shape<long> >
dnl m4_interface_class5 = Direct_Product_Grid_BD_Shape_long
dnl m4_class_kind5 = Direct_Product
dnl m4_class_group5 = product
dnl m4_class_body5 = Grid@COMMA@BD_Shape<long>
dnl m4_class_body_1st5 = Grid
dnl m4_cplusplus_class_body_1st5 = Grid
dnl m4_interface_class_body_1st5 = Grid
dnl m4_class_body_1st_kind5 = Grid
dnl m4_class_body_1st_group5 = grid
dnl m4_class_body_2nd5 = BD_Shape<long>
dnl m4_cplusplus_class_body_2nd5 = BD_Shape<long>
dnl m4_interface_class_body_2nd5 = BD_Shape<long>
dnl m4_class_body_2nd_kind5 = BD_Shape
dnl m4_class_body_2nd_group5 = bd_shape
dnl m4_class_body_2nd_body5 = long
dnl
m4_define(`m4_init_cplusplus_class_components', `dnl
m4_get_kind($1, $2, $3)`'dnl
m4_get_group($1, $3)`'dnl
m4_get_body($1, $2, $3)`'dnl
dnl
m4_ifelse(m4_$3_group$1, pointset_powerset,
  `m4_parse_body_for_powerset($1, $3)')`'dnl
dnl
m4_ifelse(m4_$3_group$1, product,
  `m4_parse_body_for_product($1, $3)')`'dnl
dnl
')

dnl m4_get_kind(Class_Counter, String, Macro_Specifier)
dnl m4_get_body(Class_Counter, String, Macro_Specifier)
dnl m4_get_group(Class_Counter, Macro_Specifier)
dnl
dnl Class_Counter - is the index to Class;
dnl String        - a cplusplus class name.
dnl Macro_Specifier
dnl               - is the component of the macro name that
dnl                 determines the precise component it refers to.
dnl
dnl The head (Macro_Specifier_kind) and the body of
dnl the C++ class name in String are separated out.
dnl m4_Macro_Specifier_kind`'Class_Counter = the first part before the "<"
dnl m4_Macro_Specifier_body`'Class_Counter = the rest
dnl and m4_Macro_Specifier_body`'Class_Counter defines the group to which this
dnl class belongs.
dnl
dnl For example:
dnl If Macro_Specifier = class, String = Polyhedron and Class_Counter = 1
dnl m4_class_kind1 => `Polyhedron'
dnl m4_class_body1 => `'
dnl If String = Pointset_Powerset<BD_Shape<signed char> >
dnl               and Class_Counter = 2
dnl m4_class_kind2 => `Pointset_Powerset'
dnl m4_class_body2 => `BD_Shape<signed char>'
dnl m4_class_group2 => `pointset_powerset'
m4_define(`m4_get_body',
  `m4_define(m4_$3_body`'$1,
    m4_ifelse($2, `', ,
               m4_index(`$2', <), -1, `',
                 m4_regexp(`$2', `[^ <]+[<]\(.*\w>?\)[ ]*[>]', `\1')))`'dnl
')

m4_define(`m4_get_kind',
  `m4_define(m4_$3_kind`'$1,
    `m4_ifelse($2, `', ,
               m4_index($2, <), -1, m4_remove_topology($2),
                 m4_regexp($2, `\([^ <]+\)[.]*', `\1'))')`'dnl
')

m4_define(`m4_get_group',
  `m4_define(m4_$2_group`'$1, `')`'dnl
m4_get_group_aux($1, $2, m4_class_groups)')

m4_define(`m4_get_group_aux', `dnl
m4_ifelse($#, 0, , $#, 1, , $#, 2, , $#, 3,
    m4_get_group_aux2($1, $2, $3, m4_$3_group),
    `m4_ifelse(m4_get_group_aux2($1, $2, $3, m4_$3_group), 0,
      `m4_get_group_aux($1, $2, m4_shift(m4_shift(m4_shift($@))))')')')

m4_define(`m4_get_group_aux2', `dnl
m4_ifelse($#, 0, , $#, 1, , $#, 2, 0, $#, 3, 0, $#, 4,
  `m4_ifelse(`$4', m4_$2_kind$1,
    `m4_define(m4_$2_group`'$1, `$3')', 0)',
  `m4_ifelse(`$4', m4_$2_kind$1,
    `m4_define(m4_$2_group`'$1, `$3')',
    m4_get_group_aux2($1, $2, $3, m4_shift(m4_shift(m4_shift(m4_shift($@)))))`'dnl
)')')


dnl m4_get_class_index(String)
dnl
dnl String        - a cplusplus class name.
dnl
dnl This finds the class counter from the cpp name.
m4_define(`m4_get_class_index', `dnl
m4_forloop(m4_ind, 1, m4_num_classes, `dnl
m4_ifelse(m4_remove_topology($1),
  m4_echo_unquoted(m4_cplusplus_class`'m4_ind),
  m4_ind)`'dnl
')`'dnl
')

dnl m4_parse_body_for_powerset(Class_Counter, Macro_Specifier)
dnl
dnl Class_Counter - is the index to Class;
dnl Macro_Specifier
dnl               - is the component of the macro name that
dnl                 determines the precise component it refers to.
dnl
m4_define(`m4_parse_body_for_powerset', `dnl
m4_define(`m4_interface_$2_body$1',
  m4_interface_class`'m4_get_class_index(m4_$2_body$1))`'dnl
m4_define(`m4_cplusplus_$2_body$1', m4_$2_body$1)`'dnl
m4_init_cplusplus_class_components($1, m4_$2_body$1, $2_body)`'dnl
')

dnl m4_parse_body_for_product(Class_Counter, Macro_Specifier)
dnl
dnl Class_Counter - is the index to Class;
dnl Macro_Specifier
dnl               - is the component of the macro name that
dnl                 determines the precise component it refers to.
dnl
m4_define(`m4_parse_body_for_product', `dnl
m4_define(`m4_$2_body_1st$1',
  `m4_regexp(m4_$2_body$1, `\([^@]*\).*', `\1')')`'dnl
m4_define(`m4_$2_body_2nd$1',
  `m4_regexp(m4_$2_body$1, `\([^@]*\)@COMMA@\(.*\)', `\2')')`'dnl
m4_define(`m4_interface_$2_body_1st$1',
  m4_interface_class`'m4_get_class_index(m4_$2_body_1st$1))`'dnl
m4_define(`m4_cplusplus_$2_body_1st$1', m4_$2_body_1st$1)`'dnl
m4_define(`m4_interface_$2_body_2nd$1',
  m4_interface_class`'m4_get_class_index(m4_$2_body_2nd$1))`'dnl
m4_define(`m4_cplusplus_$2_body_2nd$1', m4_$2_body_2nd$1)`'dnl
m4_init_cplusplus_class_components($1, m4_$2_body_1st$1, $2_body_1st)`'dnl
m4_init_cplusplus_class_components($1, m4_$2_body_2nd$1, $2_body_2nd)`'dnl
')

dnl m4_get_class_topology(Class)
dnl
dnl expands to the empty string unless the class is
dnl C_Polyhedron or NNC_Polyhedron, in which case it expands to
dnl "C_" or "NNC_" respectively.
m4_define(`m4_get_class_topology', `dnl
m4_ifelse(m4_index($1, C_), 0, C_,
m4_index($1, NNC_), 0, NNC_)`'dnl
')


dnl m4_get_disjunct_topology(Class_Counter)
dnl
dnl expands to the empty string unless the disjunct is
dnl C_Polyhedron or NNC_Polyhedron, in which case it expands to
dnl "C_" or "NNC_" respectively.
m4_define(`m4_get_disjunct_topology', `dnl
m4_ifelse(m4_index(m4_class_body`'$1, C_), 0, C_,
m4_index(m4_class_body`'$1, NNC_), 0, NNC_)`'dnl
')

dnl m4_remove_topology(Class_Name)
dnl
dnl expands to the class name unless it is
dnl C_Polyhedron or NNC_Polyhedron, in which case it expands to
dnl "Polyhedron".
m4_define(`m4_remove_topology', `dnl
m4_ifelse(m4_index($1, C_), 0, Polyhedron,
            m4_index($1, NNC_), 0, Polyhedron, $1)`'dnl
')

dnl =====================================================================
dnl ===== The next set of macros define the groups used to          =====
dnl ===== specify to which classes the schematic procedures apply;  =====
dnl ===== see ppl_interface_generators_common_procedure_list.m4     =====
dnl ===== and <interface>/ppl_interface_generators_<interface>_dat.m4 ===
dnl =====================================================================

dnl m4_group_names expands to all the group names.
dnl
dnl Each group_name in the expansion should
dnl have a corresponding definition for
dnl "m4_`'group_name`'_group
dnl which must be defined as a (comma separated) list of class kinds.
dnl
dnl If more groups are wanted, then these must be added to this list.
dnl and the list of class_kinds they include be defined.
dnl If a group_name occurs in the extra text preceded by a - after
dnl a procedure name, then no code for any classes in that group is generated.
dnl Conversely, if a group_name preceded by a + occurs in the extra text after
dnl a procedure name, then code for those classes in that group that are
dnl not covered by a - is generated.
dnl
dnl More formally, if the extra text for a procedure includes
dnl +g1 +g2 ''' +gm and -h1 -h2 ... -hn
dnl where g1,g2, ..., gm and h1, h2, ..., hn are group names,
dnl then the actual class kinds that code will be generated for
dnl will be determined using set difference "\":
dnl (m4_g1_group union m4_g2_group union ... union m4_gm_group)\
dnl (m4_h1_group union m4_h2_group union ... union m4_hn_group)
dnl
dnl That is: in case of conflict between the + and - groups,
dnl the - takes precedence over the +;
dnl all class kinds for group_names preceded by - are filtered away.
dnl For instance, with:
dnl "+shape -bd_shape"
dnl following a procedure name, only code (for that procedure)
dnl for the Polyhedron and Octagonal_Shape class will be generated.
m4_define(`m4_group_names', `dnl
all,
simple_pps,
simple,
shape,
wr_shape,
polyhedron,
grid,
bd_shape,
octagonal_shape,
pointset_powerset,
product')

dnl A sublist of the same groups whose elements are disjoint.
dnl These are used to define the m4_class_group`'class_index
dnl which is used for the "pattern" replacements (see below).
m4_define(`m4_class_groups', `dnl
polyhedron,
grid,
wr_shape,
pointset_powerset,
product')

m4_define(`m4_all_group',
  `Polyhedron, Grid, BD_Shape, Octagonal_Shape,
   Pointset_Powerset, m4_product_group')
m4_define(`m4_simple_pps_group', `m4_simple_group, Pointset_Powerset')
m4_define(`m4_simple_group', `Grid, m4_shape_group')
m4_define(`m4_shape_group', `Polyhedron, m4_wr_shape_group')
m4_define(`m4_wr_shape_group', `BD_Shape, Octagonal_Shape')
m4_define(`m4_polyhedron_group', Polyhedron)
m4_define(`m4_grid_group', Grid)
m4_define(`m4_bd_shape_group', BD_Shape)
m4_define(`m4_octagonal_shape_group', Octagonal_Shape)
m4_define(`m4_pointset_powerset_group', Pointset_Powerset)
m4_define(`m4_product_group',
  `Direct_Product, Smash_Product, Constraints_Product')

dnl =====================================================================
dnl ===== The next set of macros define the replacements            =====
dnl ===== for the patterns used                                     =====
dnl =====================================================================

dnl ---------------------------------------------------------------------
dnl First the list of patterns. Note that the order is important.
dnl ---------------------------------------------------------------------

dnl m4_pattern_list
dnl
dnl Returns a list of patterns (in lowercase) used for the generation
dnl of procedure names and code schemas.
m4_define(`m4_pattern_list', `dnl
class,
cpp_class,
cppdef_class,
friend,
intopology,
topology,
cpp_disjunct,
disjunct,
classtopology,
build_represent,
get_represent,
relation_represent,
add_represent,
partition,
superclass,
recycle,
dimension,
generator,
point,
constrainer,
has_property,
simplify,
abovebelow,
maxmin,
embedproject,
affimage,
comparison,
binop,
binminop,
ub_exact,
disjunct_extrapolation,
disjunct_widen,
widenexpn,
widen,
extrapolation,
narrow,
limitedbounded,
box,
incdec,
beginend,
membytes')

dnl ---------------------------------------------------------------------
dnl Define the replacements for these patterns
dnl ---------------------------------------------------------------------

dnl ---------------------------------------------------------------------
dnl pattern == class
dnl The class being generated
dnl ---------------------------------------------------------------------

dnl The interface class name.
m4_define(`m4_class_replacement', m4_interface_class`'$1)

dnl The cplusplus name.
m4_define(`m4_cpp_class_replacement', m4_cplusplus_class`'$1)

dnl The direct product full cplusplus name.
m4_define(`m4_product_cpp_class_replacement',
     Domain_Product<`'m4_cplusplus_class_body_1st$1@COMMA@`'m4_cplusplus_class_body_2nd$1 >::`'m4_class_kind$1)

dnl The defined cplusplus name (the default is as before).
m4_define(`m4_cppdef_class_replacement', m4_cplusplus_class`'$1)

dnl The defined direct product cplusplus name.
m4_define(`m4_product_cppdef_class_replacement',
m4_interface_class`'$1)

dnl ---------------------------------------------------------------------
dnl pattern == friend
dnl A class can be built from any other class named as a "friend".
dnl A friend must be one of the classes named in the instantiations
dnl ---------------------------------------------------------------------

dnl Some of the class specific friend replacements use the next two macros:
dnl m4_same_class_string/4 and m4_same_class_string_aux/4

dnl m4_same_class_string(String, Name_Type, Class_Name_Type, Topology)
dnl
dnl String = class kind or cplusplus_class name (= the class body)
dnl depending on Class_Name_Type.
dnl Name_Type  = "interface" or "cplusplus".
dnl Class_Name_Type = "class_kind" or "cplusplus_class".
dnl This and the "_aux"  macros are needed to define the friend replacements.
dnl The macro expands to a list of either the full interface name or cplusplus
dnl name, depending on whether $2 = "interface" or "cplusplus"
m4_define(`m4_same_class_string', `dnl
dnl Find all interface class names for $1 in the class list.
m4_forloop(m4_ind, 1, m4_num_classes, `dnl
m4_same_class_string_aux(
  $1, m4_$4`'m4_ind, m4_$2_class`'m4_ind, $3)`'dnl
')`'dnl
')

m4_define(`m4_same_class_string_aux', `dnl
dnl comma is a separator so the first element has no comma.
m4_ifelse($1, $2,
  `m4_ifelse(m4_replace_list_start, 0,
     `m4_undefine(`m4_replace_list_start')$4`'$3',
    `, '$4`'$3)')`'dnl
')

dnl The friend class name.
dnl There is the interface name as default friend,
dnl the interface name but where "Polyhedron" does not include
dnl the topology (alt_friend), and the C++ name (cppx_friend).
dnl
dnl To allow for other classes to be friends,
dnl we cannot just take a predefined list of friends as some
dnl may not be instantiated and available.
m4_define(`m4_friend_replacement', `m4_all_friends(interface)')

m4_define(`m4_friend_alt_replacement', `dnl
m4_all_friends(interface, no_topology)`'dnl
')

m4_define(`m4_friend_cppx_replacement',`m4_all_friends(cplusplus)')

m4_define(`m4_all_friends', `dnl
m4_patsubst(m4_all_friends_aux($1, $2), `@COMMA@', `, ')`'dnl
')
m4_define(`m4_all_friends_aux', `dnl
m4_forloop(m4_ind, 1, m4_num_classes, `dnl
m4_ifelse(m4_echo_unquoted(m4_class_kind`'m4_ind), Pointset_Powerset, ,
m4_echo_unquoted(m4_class_group`'m4_ind), product, , `dnl
m4_define(`m4_friend_class', m4_`'$1`'_class`'m4_ind)`'dnl
m4_ifelse(m4_friend_class, Polyhedron,
          m4_ifelse($2, `',
          m4_one_friend(C_`'m4_friend_class@COMMA@NNC_`'m4_friend_class),
          m4_one_friend(m4_friend_class@COMMA@m4_friend_class)),
          m4_one_friend(m4_friend_class))`'dnl
m4_undefine(`m4_friend_class')')')`'dnl
')

m4_define(`m4_one_friend', `dnl
m4_ifelse(m4_ind, 1, `$1', @COMMA@`'$1)`'dnl
')

dnl For Pointset_Powerset class kind, if the body is C_Polyhedron
dnl or NNC_Polyhedron, and Polyhedron is generated, then C_Polyhedron
dnl (if the body is C_Polyhedron) or NNC_Polyhedron
dnl (if the body is NNC_Polyhedron) is a friend.
dnl
m4_define(`m4_Pointset_Powerset_friend_replacement', `dnl
dnl
m4_interface_class$1,
m4_get_class_topology(m4_cplusplus_class_body$1)`'dnl
m4_interface_class_body$1`'dnl
')

m4_define(`m4_Pointset_Powerset_friend_alt_replacement', `dnl
dnl
m4_interface_class$1, m4_interface_class_body$1`'dnl
')

m4_define(`m4_Pointset_Powerset_friend_cppx_replacement', `dnl
dnl
m4_cplusplus_class$1, m4_cplusplus_class_body$1`'dnl
')

dnl For product class kinds, C_Polyhedron, NNC_Polyhedron, BD_Shape,
dnl Octagonal_Shape and other products are all friends.
dnl
m4_define(`m4_product_friend_replacement',
  `m4_all_friends(interface), m4_interface_class$1`'dnl
')

m4_define(`m4_product_friend_alt_replacement',
  `m4_all_friends(interface, no_topology), m4_interface_class$1`'dnl
')

m4_define(`m4_product_friend_cppx_replacement',
  `m4_all_friends(cplusplus),
     Domain_Product<`'m4_cplusplus_class_body_1st$1`'@COMMA@`'m4_cplusplus_class_body_2nd$1`' >::`'m4_class_kind$1')
)

dnl ---------------------------------------------------------------------
dnl pattern == topology or intopology
dnl This is C_ or NNC_ if the class is Polyhedron and `' otherwise
dnl ---------------------------------------------------------------------

dnl The topology of the domain element. The default is the empty string.
m4_define(`m4_topology_replacement', `')
m4_define(`m4_Polyhedron_topology_replacement', `C_, NNC_')

dnl The topology used to copy from another element of the domain
m4_define(`m4_intopology_replacement', `')
m4_define(`m4_Polyhedron_intopology_replacement', `C_, NNC_')

dnl ---------------------------------------------------------------------
dnl pattern == widen
dnl ---------------------------------------------------------------------
dnl The widening operators.
m4_define(`m4_widen_replacement', `')
m4_define(`m4_Polyhedron_widen_replacement', `BHRZ03, H79')
m4_define(`m4_Grid_widen_replacement', `congruence, generator')
m4_define(`m4_BD_Shape_widen_replacement', `BHMZ05, H79')
m4_define(`m4_Octagonal_Shape_widen_replacement', `BHMZ05')
m4_define(`m4_Pointset_Powerset_widen_replacement', `BHZ03')
dnl The alt_replacement defines the certificates for the widenings
m4_define(`m4_Polyhedron_widen_alt_replacement', `BHRZ03, H79')
m4_define(`m4_BD_Shape_widen_alt_replacement', `H79, H79')
m4_define(`m4_Octagonal_Shape_widen_alt_replacement', `H79')
m4_define(`m4_Grid_widen_alt_replacement', `Grid, Grid')

dnl ---------------------------------------------------------------------
dnl pattern == extrapolation
dnl ---------------------------------------------------------------------
m4_define(`m4_extrapolation_replacement', `NONE')
m4_define(`m4_BD_Shape_extrapolation_replacement',
  `CC76')
m4_define(`m4_Octagonal_Shape_extrapolation_replacement',
   `CC76')

dnl ---------------------------------------------------------------------
dnl pattern == widenexp
dnl The limited/bounded extrapolation operators.
dnl ---------------------------------------------------------------------
m4_define(`m4_widenexpn_replacement', `m4_widen_replacement')
m4_define(`m4_Polyhedron_widenexpn_replacement',
  `m4_Polyhedron_widen_replacement')
m4_define(`m4_Grid_widenexpn_replacement', `m4_Grid_widen_replacement')
m4_define(`m4_BD_Shape_widenexpn_replacement',
  `m4_BD_Shape_widen_replacement,
   m4_BD_Shape_extrapolation_replacement')
m4_define(`m4_Octagonal_Shape_widenexpn_replacement',
   `m4_Octagonal_Shape_widen_replacement,
    m4_Octagonal_Shape_extrapolation_replacement')
m4_define(`m4_Pointset_Powerset_widenexpn_replacement',
  `m4_Pointset_Powerset_widen_replacement')

dnl ---------------------------------------------------------------------
dnl pattern == narrow
dnl ---------------------------------------------------------------------
m4_define(`m4_narrow_replacement', `CC76')

dnl ---------------------------------------------------------------------
dnl pattern == limitedbounded
dnl limited/bounded are qualifiers for widening and extrapolation
dnl operations.
dnl ---------------------------------------------------------------------
m4_define(`m4_limitedbounded_replacement', `limited')
m4_define(`m4_Polyhedron_limitedbounded_replacement', `limited, bounded')


dnl ---------------------------------------------------------------------
dnl pattern == box
dnl The shape classes have bounding boxes while the grid classes also
dnl have covering boxes.
dnl ---------------------------------------------------------------------
m4_define(`m4_box_replacement', `bounding_box')
m4_define(`m4_Grid_box_replacement', `m4_box_replacement, covering_box')

dnl ---------------------------------------------------------------------
dnl pattern == dimension
dnl ---------------------------------------------------------------------
m4_define(`m4_dimension_replacement', `space_dimension, affine_dimension')
m4_define(`m4_Pointset_Powerset_dimension_replacement',`space_dimension')

dnl ---------------------------------------------------------------------
dnl pattern == generator
dnl The different kinds of objects use to generate a class.
dnl ---------------------------------------------------------------------
m4_define(`m4_generator_replacement', `generator')
m4_define(`m4_Grid_generator_replacement', `grid_generator')

dnl  The different kinds of points.
m4_define(`m4_point_replacement', `point')
m4_define(`m4_Grid_point_replacement', `grid_point')

dnl  The constrainer objects used to describe a class.
m4_define(`m4_constrainer_replacement', `constraint')
m4_define(`m4_Grid_constrainer_replacement', `congruence')

dnl ---------------------------------------------------------------------
dnl pattern == cpp_disjunct or disjunct
dnl The different kinds of objects that are elements of a Pointset_Powerset.
dnl ---------------------------------------------------------------------

dnl If the class is C_Polyhderon or NNC_Polyhedron the topology is removed
dnl but the class topology replacement is then also defined.
m4_define(`m4_cpp_disjunct_replacement', `dnl
m4_remove_topology(m4_cplusplus_class_body`'$1)`'dnl
m4_define(`m4_classtopology_replacement',
  `m4_get_class_topology(m4_cplusplus_class_body`'$1)')`'dnl
')

dnl If the class is C_Polyhderon or NNC_Polyhedron the topology is removed
dnl but the class topology replacement is then also defined.
m4_define(`m4_disjunct_replacement', `dnl
m4_remove_topology(m4_interface_class_body`'$1)`'dnl
m4_define(`m4_classtopology_replacement',
  `m4_get_class_topology(m4_class_body`'$1)')`'dnl
')

dnl ---------------------------------------------------------------------
dnl pattern == disjunct_widen
dnl ---------------------------------------------------------------------

dnl FIXME: To be eliminated soon.
m4_define(`m4_disjunct_kind', m4_class_body_kind$1)`'dnl
')

m4_define(`m4_disjunct_widen_replacement',
  `m4_echo_unquoted(m4_`'m4_remove_topology(m4_disjunct_kind($1))`'_widen_replacement)')

m4_define(`m4_disjunct_widen_alt_replacement',
  `m4_echo_unquoted(m4_`'m4_remove_topology(m4_disjunct_kind($1))`'_widen_alt_replacement)')

dnl ---------------------------------------------------------------------
dnl pattern == disjunct_extrapolation
dnl ---------------------------------------------------------------------

m4_define(`m4_disjunct_extrapolation_replacement',
  `m4_echo_unquoted(m4_`'m4_remove_topology(m4_disjunct_kind($1))`'_extrapolation_replacement)')

m4_define(`m4_disjunct_extrapolation_alt_replacement',
  `m4_echo_unquoted(m4_`'m4_remove_topology(m4_disjunct_kind($1))`'_extrapolation_alt_replacement)')


dnl ---------------------------------------------------------------------
dnl pattern == build_represent
dnl  The different kinds of objects that can build a class.
dnl ---------------------------------------------------------------------

m4_define(`m4_build_represent_replacement',
         `constraint, congruence, generator')
m4_define(`m4_Grid_build_represent_replacement',
         `constraint, grid_generator, congruence')
m4_define(`m4_Pointset_Powerset_build_represent_replacement',
         `constraint, congruence')
m4_define(`m4_product_build_represent_replacement',
         `constraint, congruence')

dnl  The different kinds of alternative objects that can build
dnl  the same class.
dnl  At the moment, this is just used for the test data generator.
m4_define(`m4_build_represent_alt_replacement',
          `generator, congruence, constraint')
m4_define(`m4_Grid_build_represent_alt_replacement',
         `constraint, congruence, grid_generator')
m4_define(`m4_Pointset_Powerset_build_represent_alt_replacement',
         `constraint, congruence')
m4_define(`m4_product_build_represent_alt_replacement',
         `constraint, congruence')

dnl ---------------------------------------------------------------------
dnl pattern == relation_represent
dnl  The different kinds of objects that can have a relation with a class.
dnl ---------------------------------------------------------------------

m4_define(`m4_relation_represent_replacement', `constraint, generator')
m4_define(`m4_Polyhedron_relation_represent_replacement',
         `m4_relation_represent_replacement, congruence')
m4_define(`m4_Grid_relation_represent_replacement',
         `m4_relation_represent_replacement, congruence, grid_generator')
m4_define(`m4_Pointset_Powerset_relation_represent_replacement',
         `m4_relation_represent_replacement, congruence')
m4_define(`m4_Product_relation_represent_replacement',
         `m4_relation_represent_replacement, congruence')

dnl The type of these relations with a class.
m4_define(`m4_relation_represent_alt_replacement', `con, gen')
m4_define(`m4_Polyhedron_relation_represent_alt_replacement',
         `con, gen, con')
m4_define(`m4_Grid_relation_represent_alt_replacement',
         `con, gen, con, gen')
m4_define(`m4_Pointset_Powerset_relation_represent_alt_replacement',
         `con, gen, con')
m4_define(`m4_product_relation_represent_alt_replacement',
         `con, gen, con')

dnl ---------------------------------------------------------------------
dnl pattern == add_represent
dnl The different kinds of objects that can be added to a class.
dnl ---------------------------------------------------------------------

m4_define(`m4_add_represent_replacement', `constraint, congruence')
m4_define(`m4_Polyhedron_add_represent_replacement',
         `m4_add_represent_replacement, generator')
m4_define(`m4_Grid_add_represent_replacement',
         `m4_add_represent_replacement, grid_generator')

dnl ---------------------------------------------------------------------
dnl pattern == get_represent
dnl The different kinds of objects that can be obtained from a
dnl class description.
dnl ---------------------------------------------------------------------

m4_define(`m4_get_represent_replacement', `constraint')
m4_define(`m4_Polyhedron_get_represent_replacement',
         `constraint, generator, congruence')
m4_define(`m4_Grid_get_represent_replacement',
         `congruence, grid_generator')

dnl ---------------------------------------------------------------------
dnl pattern == recycle_represent
dnl The recycling argument which is only needed for the Polyhedron
dnl or Grid class.
dnl ---------------------------------------------------------------------

m4_define(`m4_recycle_replacement', `')
m4_define(`m4_Polyhedron_recycle_replacement',
         `@COMMA@ Recycle_Input()')
m4_define(`m4_Grid_recycle_replacement',
         `@COMMA@ Recycle_Input()')

dnl ---------------------------------------------------------------------
dnl pattern == superclass
dnl The "superclass" is the most general class for the disjunct kind.
dnl For grids it is Grid and for all the other simple classes,
dnl it is NNC_Polyhedron. The default is NONE.
dnl ---------------------------------------------------------------------

m4_define(`m4_superclass_replacement', `NONE')
m4_define(`m4_Pointset_Powerset_superclass_replacement',
          `m4_ifelse(
          m4_echo_unquoted(m4_disjunct_kind($1)),
          `Grid', `Grid', `NNC_Polyhedron')')

dnl ---------------------------------------------------------------------
dnl pattern == partition
dnl The "partition" which is currently only available for the Polyhedron
dnl and Grid Pointset_Powerset classes.
dnl FIXME: However because of differences between the
dnl linear and approximate partitions, we have to have these
dnl separate. Thus approximate_partition for Grids
dnl is defined without any pattern.
dnl ---------------------------------------------------------------------

m4_define(`m4_partition_replacement', `NONE')
m4_define(`m4_Pointset_Powerset_partition_replacement',
  `m4_ifelse(m4_echo_unquoted(m4_remove_topology(m4_disjunct_kind($1))),
      `Polyhedron', `linear_partition')')

dnl ---------------------------------------------------------------------
dnl pattern == has_prperty
dnl The unary "has_property" predicates check properties of the domains
dnl The check "contains_integer_point" is not available for the
dnl product domains.
dnl ---------------------------------------------------------------------

m4_define(`m4_has_property_replacement', `is_empty, is_universe,
            is_bounded, contains_integer_point, is_topologically_closed')
m4_define(`m4_Polyhedron_has_property_replacement',
          `m4_has_property_replacement, is_discrete')
m4_define(`m4_Grid_has_property_replacement',
          `m4_has_property_replacement, is_discrete')
m4_define(`m4_product_has_property_replacement',
          `is_empty, is_universe, is_bounded, is_topologically_closed,
            is_discrete')

dnl ---------------------------------------------------------------------
dnl pattern == simplify
dnl This just groups two methods that modify a domain element.
dnl ---------------------------------------------------------------------

m4_define(`m4_simplify_replacement', `topological_closure_assign')
m4_define(`m4_Pointset_Powerset_simplify_replacement',
          `m4_simplify_replacement, pairwise_reduce')

dnl ---------------------------------------------------------------------
dnl pattern -- above/below
dnl Used for the bounds_from_above and bounds_from_below methods.
dnl ---------------------------------------------------------------------

m4_define(`m4_abovebelow_replacement', `above, below')

dnl ---------------------------------------------------------------------
dnl pattern == maxmin
dnl Maximize or Minimize
dnl ---------------------------------------------------------------------

m4_define(`m4_maxmin_replacement', `maximize, minimize')

dnl  Embed or project
m4_define(`m4_embedproject_replacement', `and_embed, and_project')

dnl  Affine_image or affine_preimage
m4_define(`m4_affimage_replacement', `affine_image, affine_preimage')

dnl  One object can be contained, strictly contained or disjoint in the other.
m4_define(`m4_comparison_replacement',
         `contains, strictly_contains, is_disjoint_from')
m4_define(`m4_Pointset_Powerset_comparison_replacement',
         `m4_comparison_replacement,
          geometrically_covers, geometrically_equals')

dnl  The different kinds of binary operators.
m4_define(`m4_binop_replacement',
         `intersection_assign, upper_bound_assign, difference_assign,
          concatenate_assign, time_elapse_assign')
m4_define(`m4_Polyhedron_binop_replacement',
         `m4_binop_replacement, poly_hull_assign, poly_difference_assign')
m4_define(`m4_Grid_binop_replacement',
         `m4_binop_replacement, join_assign')
m4_define(`m4_BD_Shape_binop_replacement',
         `m4_binop_replacement, bds_hull_assign')
m4_define(`m4_Octagonal_Shape_binop_replacement',
         `m4_binop_replacement, oct_hull_assign')
m4_define(`m4_Pointset_Powerset_binop_replacement',
          `m4_ifelse(
          m4_echo_unquoted(m4_remove_topology(m4_class_body_kind$1)), Polyhedron,
          `intersection_assign, poly_difference_assign, concatenate_assign,
           time_elapse_assign',
          `m4_class_body_kind$1', Grid,
          `intersection_assign, poly_difference_assign, concatenate_assign,
           time_elapse_assign',
          `intersection_assign, concatenate_assign,
           time_elapse_assign')')

dnl  The different kinds of "and_minimize" binary operators.
m4_define(`m4_binminop_replacement', `intersection_assign_and_minimize')
m4_define(`m4_Polyhedron_binminop_replacement',
         `m4_binminop_replacement, poly_hull_assign_and_minimize')
m4_define(`m4_Grid_binminop_replacement',
         `m4_binminop_replacement, join_assign_and_minimize')

dnl  The different kinds of "upper_bound_if_exact" binary operators.
m4_define(`m4_ub_exact_replacement', `upper_bound_assign_if_exact')
m4_define(`m4_Polyhedron_ub_exact_replacement',
         `m4_ub_exact_replacement, poly_hull_assign_if_exact')
m4_define(`m4_Grid_ub_exact_replacement',
         `m4_ub_exact_replacement, join_assign_if_exact')

dnl  The iterators for the Powerset domains can increment or decrement
m4_define(`m4_incdec_replacement', `increment, decrement')

dnl  The C++ replacements for the increment/decrement operators.
m4_define(`m4_incdec_cppx_replacement', `++, --')

dnl  The Java replacements for the increment/decrement operators.
m4_define(`m4_incdec_alt_replacement', `next, prev')

dnl  The iterators for the Powerset domains have a begin and end iterator
m4_define(`m4_beginend_replacement', `begin, end')

dnl  The total and external memory query methods for all the domains
dnl  and the size query to the pointset powerset domain.
m4_define(`m4_membytes_replacement',
  `external_memory_in_bytes, total_memory_in_bytes')
m4_define(`m4_Pointset_Powerset_membytes_replacement',
  `m4_membytes_replacement, size')
