/* Linear_Expression_Variable class definition and implementation.
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

package ppl_java;

//! A linear expression built from a variable.
/*! \ingroup PPL_Java_interface
 */
public class Linear_Expression_Variable
extends Linear_Expression {

    protected Variable arg;

    //! Builds the object associated to \p v.
    public Linear_Expression_Variable(Variable v) {
	arg = v;
    }

    //! Returns the variable representing the linear expression.
    public Variable argument() {
        return arg;
    }
}