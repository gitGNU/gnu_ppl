/* Polyhedron Java class declaration and implementation.
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


//! A closed convex polyhedron.
/*! \ingroup PPL_Java_interface
  An object of the class Polyhedron represents a convex polyhedron
  in the vector space \f$\Rset^n\f$.
*/
public class Polyhedron extends PPL_Object {

    /*! \brief
      Returns <CODE>true</CODE> if and only if \p this is
      an empty polyhedron.
    */
    public native boolean is_empty();
    /*! \brief
      Returns <CODE>true</CODE> if and only if \p this
      is a universe polyhedron.
    */
    public native boolean is_universe();

    /*! \brief
      Returns <CODE>true</CODE> if and only if \p this
      is a topologically closed subset of the vector space.
    */
    public native boolean is_topologically_closed();

    /*! \brief
      Returns <CODE>true</CODE> if and only if \p this
      is a bounded polyhedron.
    */
    public native boolean is_bounded();

    //! Returns <CODE>true</CODE> if and only if \p this and \p y are disjoint.
    /*!
      \exception RuntimeErrorException
      Thrown if \p x and \p y are topology-incompatible or
      dimension-incompatible.
    */
    public native boolean is_disjoint_from(Polyhedron y);

    /*! \brief
      Returns <CODE>true</CODE> if and only if \p expr is
      bounded from above in \p this.

      \exception RuntimeErrorException
      Thrown if \p expr and \p this are dimension-incompatible.
    */

    public native boolean bounds_from_above(Linear_Expression expr);
    /*! \brief
      Returns <CODE>true</CODE> if and only if \p expr is
      bounded from below in \p this.

      \exception RuntimeErrorException
      Thrown if \p expr and \p this are dimension-incompatible.
    */

    public native boolean bounds_from_below(Linear_Expression expr);
    //! Returns <CODE>true</CODE> if and only if \p this contains \p y.
    /*!
      \exception RuntimeErrorException
      Thrown if \p this and \p y are topology-incompatible or
      dimension-incompatible.
    */

    public native boolean contains(Polyhedron p);

    /*! \brief
      Returns <CODE>true</CODE> if and only if \p this
      strictly contains \p y.

      \exception RuntimeErrorException
      Thrown if \p this and \p y are topology-incompatible or
      dimension-incompatible.
    */
    public native boolean strictly_contains(Polyhedron p);

    /*! \brief
      Adds an object \p c that represents a constraint to the system of
      constraints of \p this (without minimizing the result).

      \exception RuntimeErrorException
      Thrown if \p this and constraint \p c are topology-incompatible
      or dimension-incompatible.
    */
    public native void add_constraint(Constraint c);

    /*! \brief
      Adds an object \p c that represents a constraint to the system of
      constraints of \p this, minimizing the result

      \return
      <CODE>false</CODE> if and only if the result is empty.

      \exception RuntimeErrorException
      Thrown if \p this and constraint \p c are topology-incompatible
      or dimension-incompatible.
    */
    public native boolean add_constraint_and_minimize(Constraint c);

    /*! \brief
      Adds an object \p g that represents a generator to the system of
      generators of \p this (without minimizing the result).

      \exception RuntimeErrorException
      Thrown if \p this and generator \p g are topology-incompatible or
      dimension-incompatible, or if \p this is an empty polyhedron and
      \p g is not a point.
    */
    public native void add_generator(Generator g);

    /*! \brief
       Adds an object \p g that represents a generator to the system of
       generators of \p this, minimizing the result.

      \return
      <CODE>false</CODE> if and only if the result is empty.


      \exception RuntimeErrorException
      Thrown if \p this and generator \p g are topology-incompatible or
      dimension-incompatible, or if \p this is an empty polyhedron and
      \p g is not a point.
    */
    public native boolean add_generator_and_minimize(Generator g);

    /*! \brief
      Adds an object \p cs that represents a constraint system to the system
      of constraints of \p this (without minimizing the result).

      \param cs
      Contains a representation of the constraints that will be added to the
      system of constraints of \p this.

      \exception RuntimeErrorException
      Thrown if \p this and \p cs are topology-incompatible or
      dimension-incompatible.
    */
    public native void add_constraints(Constraint_System cs);

    /*! \brief
       Adds an object \p cs that represents a constraint system to the system
       of constraints of \p this, minimizing the result.

      \return
      <CODE>false</CODE> if and only if the result is empty.

      \param cs
      Contains a representation of the constraints that will be added to the
      system of constraints of \p this.

      \exception RuntimeErrorException
      Thrown if \p this and \p cs are topology-incompatible or
      dimension-incompatible.
    */
    public native boolean add_constraints_and_minimize(Constraint_System cs);

    /*! \brief
      Adds a an object \p gs that represents a generator system in to the
      system of generators of \p this (without minimizing the result).

      \param gs
      Contains a representation of the generators that will be added to the
      system of generators of \p this.

      \exception RuntimeErrorException
      Thrown if \p this and \p gs are topology-incompatible or
      dimension-incompatible, or if \p this is empty and the system of
      generators \p gs is not empty, but has no points.
    */
    public native void add_generators(Generator_System gs);

   /*! \brief
      Adds a an object \p gs that represents a generator system to the system
      of generators of \p this, minimizing the result.

      \return
      <CODE>false</CODE> if and only if the result is empty.

      \param gs
      Contains a representation of the generators that will be added to the
      system of generators of \p this.

      \exception RuntimeErrorException
      Thrown if \p this and \p gs are topology-incompatible or
      dimension-incompatible, or if \p this is empty and the the system
      of generators \p gs is not empty, but has no points.
    */
    public native boolean add_generators_and_minimize(Generator_System gs);

    /*! \brief
      Assigns to \p this the intersection of \p this and \p y.
      The result is not guaranteed to be minimized.

      \exception RuntimeErrorException
      Thrown if \p this and \p y are topology-incompatible or
      dimension-incompatible.
    */
    public native void intersection_assign(Polyhedron p);

    /*! \brief
      Assigns to \p this the intersection of \p this and \p y,
      minimizing the result.

      \return
      <CODE>false</CODE> if and only if the result is empty.

      \exception RuntimeErrorException
      Thrown if \p this and \p y are topology-incompatible or
      dimension-incompatible.
    */
    public native boolean intersection_assign_and_minimize(Polyhedron p);

    /*! \brief
      Assigns to \p this the poly-hull of \p this and \p y.
      The result is not guaranteed to be minimized.

      \exception RuntimeErrorException
      Thrown if \p this and \p y are topology-incompatible or
      dimension-incompatible.
    */
    public native void poly_hull_assign(Polyhedron p);

    /*! \brief
      Assigns to \p this the poly-hull of \p this and \p y,
      minimizing the result.

      \return
      <CODE>false</CODE> if and only if the result is empty.

      \exception RuntimeErrorException
      Thrown if \p this and \p y are topology-incompatible or
      dimension-incompatible.
    */
    public native boolean poly_hull_assign_and_minimize(Polyhedron p);

    /*! \brief
      Assigns to \p this
      the \ref Convex_Polyhedral_Difference "poly-difference"
      of \p this and \p y. The result is not guaranteed to be minimized.

      \exception RuntimeErrorException
      Thrown if \p this and \p y are topology-incompatible or
      dimension-incompatible.
    */
    public native void poly_difference_assign(Polyhedron p);

    //! Same as poly_difference_assign(y).
    public native void difference_assign(Polyhedron p);

    //! Assigns to \p this its topological closure.
    public native void topological_closure_assign();

    /*! \brief
      Returns <CODE>true</CODE> if and only if \p this
      contains at least one integer point.
    */
    public native boolean contains_integer_point();

    //! Returns <CODE>true</CODE> if and only if \p this is discrete.
    public native boolean is_discrete();

    /*! \brief
      Assigns to \p this the result of computing the
      \ref Time_Elapse_Operator "time-elapse" between \p this and \p y.

      \exception RuntimeErrorException
      Thrown if \p this and \p y are topology-incompatible or
      dimension-incompatible.
    */
    public native void time_elapse_assign(Polyhedron p);

    /*! \brief
      Assigns to \p this the
      \ref Single_Update_Affine_Functions "affine image"
      of \p this under the function mapping variable \p var to the
      affine expression specified by \p expr and \p denominator.

      \param var
      The variable to which the affine expression is assigned;

      \param expr
      An object that represents the numerator of the affine expression;

      \param denominator
      The denominator of the affine expression.

      \exception RuntimeErrorException
      Thrown if \p denominator is zero or if \p expr and \p this are
      dimension-incompatible or if \p var is not a space dimension of
      \p this.

      \if Include_Implementation_Details

      When considering the generators of a polyhedron, the
      affine transformation
      \f[
      \frac{\sum_{i=0}^{n-1} a_i x_i + b}{\mathrm{denominator}}
      \f]
      is assigned to \p var where \p expr is
      \f$\sum_{i=0}^{n-1} a_i x_i + b\f$
      (\f$b\f$ is the inhomogeneous term).

      If constraints are up-to-date, it uses the specialized function
      affine_preimage() (for the system of constraints)
      and inverse transformation to reach the same result.
      To obtain the inverse transformation we use the following observation.

      Observation:
      -# The affine transformation is invertible if the coefficient
      of \p var in this transformation (i.e., \f$a_\mathrm{var}\f$)
      is different from zero.
      -# If the transformation is invertible, then we can write
      \f[
      \mathrm{denominator} * {x'}_\mathrm{var}
      = \sum_{i = 0}^{n - 1} a_i x_i + b
      = a_\mathrm{var} x_\mathrm{var}
      + \sum_{i \neq var} a_i x_i + b,
      \f]
      so that the inverse transformation is
      \f[
      a_\mathrm{var} x_\mathrm{var}
      = \mathrm{denominator} * {x'}_\mathrm{var}
      - \sum_{i \neq j} a_i x_i - b.
      \f]

      Then, if the transformation is invertible, all the entities that
      were up-to-date remain up-to-date. Otherwise only generators remain
      up-to-date.

      In other words, if \f$R\f$ is a \f$m_1 \times n\f$ matrix representing
      the rays of the polyhedron, \f$V\f$ is a \f$m_2 \times n\f$
      matrix representing the points of the polyhedron and
      \f[
      P = \bigl\{\,
      \vect{x} = (x_0, \ldots, x_{n-1})^\mathrm{T}
      \bigm|
      \vect{x} = \vect{\lambda} R + \vect{\mu} V,
      \vect{\lambda} \in \Rset^{m_1}_+,
      \vect{\mu} \in \Rset^{m_2}_+,
      \sum_{i = 0}^{m_2 - 1} \mu_i = 1
      \,\bigr\}
      \f]
      and \f$T\f$ is the affine transformation to apply to \f$P\f$, then
      the resulting polyhedron is
      \f[
      P' = \bigl\{\,
      (x_0, \ldots, T(x_0, \ldots, x_{n-1}),
      \ldots, x_{n-1})^\mathrm{T}
      \bigm|
      (x_0, \ldots, x_{n-1})^\mathrm{T} \in P
      \,\bigr\}.
      \f]

      Affine transformations are, for example:
      - translations
      - rotations
      - symmetries.
      \endif
    */
    public native void affine_image(Variable var, Linear_Expression expr,
				    Coefficient denominator);
    /*! \brief
      Assigns to \p this the
      \ref Single_Update_Affine_Functions "affine preimage"
      of \p this under the function mapping variable \p var to the
      affine expression specified by \p expr and \p denominator.

      \param var
      The variable to which the affine expression is substituted;

      \param expr
      An object that represents the numerator of the affine expression;

      \param denominator
      The denominator of the affine expression.

      \exception RuntimeErrorException
      Thrown if \p denominator is zero or if \p expr and \p this are
      dimension-incompatible or if \p var is not a space dimension of \p this.

      \if Include_Implementation_Details

      When considering constraints of a polyhedron, the affine transformation
      \f[
      \frac{\sum_{i=0}^{n-1} a_i x_i + b}{denominator},
      \f]
      is assigned to \p var where \p expr is
      \f$\sum_{i=0}^{n-1} a_i x_i + b\f$
      (\f$b\f$ is the inhomogeneous term).

      If generators are up-to-date, then the specialized function
      affine_image() is used (for the system of generators)
      and inverse transformation to reach the same result.
      To obtain the inverse transformation, we use the following observation.

      Observation:
      -# The affine transformation is invertible if the coefficient
      of \p var in this transformation (i.e. \f$a_\mathrm{var}\f$)
      is different from zero.
      -# If the transformation is invertible, then we can write
      \f[
      \mathrm{denominator} * {x'}_\mathrm{var}
      = \sum_{i = 0}^{n - 1} a_i x_i + b
      = a_\mathrm{var} x_\mathrm{var}
      + \sum_{i \neq \mathrm{var}} a_i x_i + b,
      \f],
      the inverse transformation is
      \f[
      a_\mathrm{var} x_\mathrm{var}
      = \mathrm{denominator} * {x'}_\mathrm{var}
      - \sum_{i \neq j} a_i x_i - b.
      \f].

      Then, if the transformation is invertible, all the entities that
      were up-to-date remain up-to-date. Otherwise only constraints remain
      up-to-date.

      In other words, if \f$A\f$ is a \f$m \times n\f$ matrix representing
      the constraints of the polyhedron, \f$T\f$ is the affine transformation
      to apply to \f$P\f$ and
      \f[
      P = \bigl\{\,
      \vect{x} = (x_0, \ldots, x_{n-1})^\mathrm{T}
      \bigm|
      A\vect{x} \geq \vect{0}
      \,\bigr\}.
      \f]
      The resulting polyhedron is
      \f[
      P' = \bigl\{\,
      \vect{x} = (x_0, \ldots, x_{n-1}))^\mathrm{T}
      \bigm|
      A'\vect{x} \geq \vect{0}
      \,\bigr\},
      \f]
      where \f$A'\f$ is defined as follows:
      \f[
      {a'}_{ij}
      = \begin{cases}
      a_{ij} * \mathrm{denominator} + a_{i\mathrm{var}}*\mathrm{expr}[j]
      \quad \mathrm{for } j \neq \mathrm{var}; \\
      \mathrm{expr}[\mathrm{var}] * a_{i\mathrm{var}},
      \quad \text{for } j = \mathrm{var}.
      \end{cases}
      \f]
      \endif
    */
    public native void affine_preimage(Variable var, Linear_Expression expr,
				       Coefficient denominator);

    /*! \brief
      Assigns to \p this the image of \p this with respect to the
      \ref Generalized_Affine_Relations "generalized affine relation"
      \f$\mathrm{var}' \relsym \frac{\mathrm{expr}}{\mathrm{denominator}}\f$,
      where \f$\mathord{\relsym}\f$ is the relation symbol encoded
      by \p relsym.

      \param var
      The left hand side variable of the generalized affine relation;

      \param relsym
      The relation symbol;

      \param expr
      An object that represents the numerator of the right hand side affine
      expression;

      \param denominator
      The denominator of the right hand side affine expression.

      \exception RuntimeErrorException
      Thrown if \p denominator is zero or if \p expr and \p this are
      dimension-incompatible or if \p var is not a space dimension of \p this
      or if \p this is a C_Polyhedron and \p relsym is a strict
      relation symbol.
    */
    public native void generalized_affine_image(Variable var,
						Relation_Symbol relsym,
						Linear_Expression expr,
						Coefficient denominator);

    /*! \brief
      Assigns to \p this the preimage of \p this with respect to the
      \ref Generalized_Affine_Relations "generalized affine relation"
      \f$\mathrm{var}' \relsym \frac{\mathrm{expr}}{\mathrm{denominator}}\f$,
      where \f$\mathord{\relsym}\f$ is the relation symbol encoded
      by \p relsym.

      \param var
      An object that represents the left hand side variable of the generalized
      affine relation;

      \param relsym
      The relation symbol;

      \param expr
      An object that represents the numerator of the right hand side affine
      expression;

      \param denominator
      The denominator of the right hand side affine expression.

      \exception RuntimeErrorException
      Thrown if \p denominator is zero or if \p expr and \p this are
      dimension-incompatible or if \p var is not a space dimension of \p this
      or if \p this is a C_Polyhedron and \p relsym is a strict
      relation symbol.
    */
    public native void generalized_affine_preimage(Variable var,
						   Relation_Symbol relsym,
						   Linear_Expression expr,
						   Coefficient denominator);

    /*! \brief
      Assigns to \p this the image of \p this with respect to the
      \ref Generalized_Affine_Relations "generalized affine relation"
      \f$\mathrm{lhs}' \relsym \mathrm{rhs}\f$, where
      \f$\mathord{\relsym}\f$ is the relation symbol encoded by \p relsym.

      \param lhs
      An object that represents the left hand side affine expression;

      \param relsym
      The relation symbol;

      \param rhs
      An object that represents the right hand side affine expression.

      \exception RuntimeErrorException
      Thrown if \p this is dimension-incompatible with \p lhs or \p rhs
      or if \p this is a C_Polyhedron and \p relsym is a strict
      relation symbol.
    */
    public native void generalized_affine_image(Linear_Expression lhs,
						Relation_Symbol relsym,
						Linear_Expression rhs);

    /*! \brief
      Assigns to \p this the preimage of \p this with respect to the
      \ref Generalized_Affine_Relations "generalized affine relation"
      \f$\mathrm{lhs}' \relsym \mathrm{rhs}\f$, where
      \f$\mathord{\relsym}\f$ is the relation symbol encoded by \p relsym.

      \param lhs
      An object that represents the left hand side affine expression;

      \param relsym
      The relation symbol;

      \param rhs
      An object that represents the right hand side affine expression.

      \exception RuntimeErrorException
      Thrown if \p this is dimension-incompatible with \p lhs or \p rhs
      or if \p this is a C_Polyhedron and \p relsym is a strict
      relation symbol.
    */
    public native void generalized_affine_preimage(Linear_Expression lhs,
						   Relation_Symbol relsym,
						   Linear_Expression rhs);

    /*!
      \brief
      Assigns to \p this the image of \p this with respect to the
      \ref Single_Update_Bounded_Affine_Relations "bounded affine relation"
      \f$\frac{\mathrm{lb\_expr}}{\mathrm{denominator}}
      \leq \mathrm{var}'
      \leq \frac{\mathrm{ub\_expr}}{\mathrm{denominator}}\f$.

      \param var
      The variable updated by the affine relation;

      \param lb_expr
      An object that represents the numerator of the lower bounding
      affine expression;

      \param ub_expr
      An object that represents the numerator of the upper bounding affine
      expression;

      \param denominator
      The (common) denominator for the lower and upper bounding
      affine expressions.

      \exception RuntimeErrorException
      Thrown if \p denominator is zero or if \p lb_expr (resp., \p ub_expr)
      and \p this are dimension-incompatible or if \p var is not a space
      dimension of \p this.
    */
    public native void bounded_affine_image(Variable var,
					    Linear_Expression lb_expr,
					    Linear_Expression ub_expr,
					    Coefficient denominator);

    /*!
      \brief
      Assigns to \p this the preimage of \p this with respect to the
      \ref Single_Update_Bounded_Affine_Relations "bounded affine relation"
      \f$\frac{\mathrm{lb\_expr}}{\mathrm{denominator}}
      \leq \mathrm{var}'
      \leq \frac{\mathrm{ub\_expr}}{\mathrm{denominator}}\f$.

      \param var
      The variable updated by the affine relation;

      \param lb_expr
      An object that represents the numerator of the lower bounding affine
      expression;

      \param ub_expr
      An object that represents the numerator of the upper bounding
      affine expression;

      \param denominator
      The (common) denominator for the lower and upper bounding
      affine expressions.

      \exception RuntimeErrorException
      Thrown if \p denominator is zero or if \p lb_expr (resp., \p ub_expr)
      and \p this are dimension-incompatible or if \p var is not a space
      dimension of \p this.
    */
    public native void bounded_affine_preimage(Variable var,
					       Linear_Expression lb_expr,
					       Linear_Expression ub_expr,
					       Coefficient denominator);
}