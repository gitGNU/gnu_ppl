/* Box class declaration.
   Copyright (C) 2001-2007 Roberto Bagnara <bagnara@cs.unipr.it>

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

#ifndef PPL_Box_defs_hh
#define PPL_Box_defs_hh 1

#include "Box.types.hh"
#include "globals.types.hh"
#include "Interval.defs.hh"
#include "Coefficient.defs.hh"
#include "Linear_Expression.types.hh"
#include "Constraint.types.hh"
#include "Constraint_System.types.hh"
#include "Generator.types.hh"
#include "Generator_System.types.hh"
#include "Variable.types.hh"
#include "Variables_Set.types.hh"
#include <vector>
#include <iosfwd>

namespace Parma_Polyhedra_Library {

//! Returns <CODE>true</CODE> if and only if \p x and \p y are the same box.
/*! \relates Box
  Note that \p x and \p y may be dimension-incompatible shapes:
  in this case, the value <CODE>false</CODE> is returned.
*/
template <typename Interval>
bool operator==(const Box<Interval>& x, const Box<Interval>& y);

//! Returns <CODE>true</CODE> if and only if \p x and \p y aren't the same BDS.
/*! \relates BD_Shape
  Note that \p x and \p y may be dimension-incompatible shapes:
  in this case, the value <CODE>true</CODE> is returned.
*/
template <typename Interval>
bool operator!=(const Box<Interval>& x, const Box<Interval>& y);

namespace IO_Operators {

//! Output operator.
/*! \relates Parma_Polyhedra_Library::Box */
template <typename Interval>
std::ostream& operator<<(std::ostream& s, const Box<Interval>& box);

} // namespace IO_Operators

} // namespace Parma_Polyhedra_Library

//! A not necessarily closed, iso-oriented hyperrectangle.
/*! \ingroup PPL_CXX_interface
  A Box object represents the Cartesian product of \f$n\f$
  not necessarily closed and possibly unbounded intervals
  represented by objects of class \p Interval,
  where \f$n\f$ is the space dimension of the box.
*/
template <typename Interval>
class Parma_Polyhedra_Library::Box {
public:
  //! The type of intervals used to implement the box.
  typedef Interval interval_type;

  //! Builds a universe or empty box of the specified space dimension.
  /*!
    \param num_dimensions
    The number of dimensions of the vector space enclosing the box;

    \param kind
    Specifies whether the universe or the empty box has to be built.
  */
  explicit Box(dimension_type num_dimensions = 0,
	       Degenerate_Element kind = UNIVERSE);

  //! Ordinary copy-constructor.
  Box(const Box& y);

  //! Builds a conservative, upward approximation of \p y.
  template <typename Other_Interval>
  explicit Box(const Box<Other_Interval>& y);

  //! Builds a box from the system of constraints \p cs.
  /*!
    The box inherits the space dimension of \p cs.

    \param cs
    A system of constraints: constraints that are not
    \ref Boxes "interval constraints"
    are ignored (even though they may have contributed
    to the space dimension).
  */
  explicit Box(const Constraint_System& cs);

  //! Builds a box recycling a system of constraints \p cs.
  /*!
    The box inherits the space dimension of \p cs.

    \param cs
    A system of constraints: constraints that are not
    \ref Boxes "interval constraints"
    are ignored (even though they may have contributed
    to the space dimension).

    \param dummy
    A dummy tag to syntactically differentiate this one
    from the other constructors.
  */
  Box(const Constraint_System& cs, Recycle_Input dummy);

  //! Builds a box from the system of generators \p gs.
  /*!
    Builds the smallest box containing the polyhedron defined by \p gs.
    The box inherits the space dimension of \p gs.

    \exception std::invalid_argument
    Thrown if the system of generators is not empty but has no points.
  */
  explicit Box(const Generator_System& gs);

  //! Builds a box recycling the system of generators \p gs.
  /*!
    Builds the smallest box containing the polyhedron defined by \p gs.
    The box inherits the space dimension of \p gs.

    \param dummy
    A dummy tag to syntactically differentiate this one
    from the other constructors.

    \exception std::invalid_argument
    Thrown if the system of generators is not empty but has no points.
  */
  Box(const Generator_System& gs, Recycle_Input dummy);

  //! \name Member Functions that Do Not Modify the Box
  //@{

  //! Returns the dimension of the vector space enclosing \p *this.
  dimension_type space_dimension() const;

  /*! \brief
    Returns \f$0\f$, if \p *this is empty; otherwise, returns the
    \ref Affine_Independence_and_Affine_Dimension "affine dimension"
    of \p *this.
  */
  dimension_type affine_dimension() const;

  //! Returns <CODE>true</CODE> if and only if \p *this is an empty box.
  bool is_empty() const;

  //! Returns <CODE>true</CODE> if and only if \p *this is a universe box.
  bool is_universe() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if \p *this
    is a topologically closed subset of the vector space.
  */
  bool is_topologically_closed() const;

  //! Returns <CODE>true</CODE> if and only if \p *this is discrete.
  bool is_discrete() const;

  //! Returns <CODE>true</CODE> if and only if \p *this is a bounded box.
  bool is_bounded() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if \p *this
    contains at least one integer point.
  */
  bool contains_integer_point() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if \p *this contains \p y.
  */
  bool contains(const Box&) const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if \p *this satisfies
    all its invariants.
  */
  bool OK() const;

  //@} Member Functions that Do Not Modify the Box

  //! \name Space-Dimension Preserving Member Functions that May Modify the Box
  //@{

  /*! \brief
    Use the constraint \p c to refine \p *this.

    \param c
    The constraint to be added. If it is not an interval constraint, it
    will be simply ignored.

    \exception std::invalid_argument
    Thrown if \p *this and \p c are dimension-incompatible.
  */
  void add_constraint(const Constraint& c);

  /*! \brief
    Use the constraints in \p cs to refine \p *this.

    \param  cs
    The constraints to be added. Constraints that are not interval
    constraints will be simply ignored.

    \exception std::invalid_argument
    Thrown if \p *this and \p cs are dimension-incompatible.
  */
  void add_constraints(const Constraint_System& cs);

  //! Assigns to \p *this the intersection of \p *this and \p y.
  /*!
    \exception std::invalid_argument
    Thrown if \p *this and \p y are dimension-incompatible.
  */
  void intersection_assign(const Box& y);

  /*! \brief
    Assigns to \p *this the smallest box containing the convex union
    of \p *this and \p y.

    \exception std::invalid_argument
    Thrown if \p *this and \p y are dimension-incompatible.
  */
  void box_hull_assign(const Box& y);

  //! Same as box_hull_assign.
  void upper_bound_assign(const Box& y);

  /*! \brief
    Assigns to \p *this the difference of \p *this and \p y.

    \exception std::invalid_argument
    Thrown if \p *this and \p y are dimension-incompatible.
  */
  void box_difference_assign(const Box& y);

  //! Same as box_difference_assign.
  void difference_assign(const Box& y);

  /*! \brief
    Assigns to \p *this the
    \ref Single_Update_Affine_Functions "affine image"
    of \p *this under the function mapping variable \p var to the
    affine expression specified by \p expr and \p denominator.

    \param var
    The variable to which the affine expression is assigned;

    \param expr
    The numerator of the affine expression;

    \param denominator
    The denominator of the affine expression (optional argument with
    default value 1).

    \exception std::invalid_argument
    Thrown if \p denominator is zero or if \p expr and \p *this are
    dimension-incompatible or if \p var is not a space dimension of
    \p *this.
  */
  void affine_image(Variable var,
		    const Linear_Expression& expr,
		    Coefficient_traits::const_reference denominator
		      = Coefficient_one());

  /*! \brief
    Assigns to \p *this the
    \ref Single_Update_Affine_Functions "affine preimage"
    of \p *this under the function mapping variable \p var to the
    affine expression specified by \p expr and \p denominator.

    \param var
    The variable to which the affine expression is substituted;

    \param expr
    The numerator of the affine expression;

    \param denominator
    The denominator of the affine expression (optional argument with
    default value 1).

    \exception std::invalid_argument
    Thrown if \p denominator is zero or if \p expr and \p *this are
    dimension-incompatible or if \p var is not a space dimension of \p *this.
  */
  void affine_preimage(Variable var,
		       const Linear_Expression& expr,
		       Coefficient_traits::const_reference denominator
		         = Coefficient_one());

  /*! \brief
    Assigns to \p *this the image of \p *this with respect to the
    \ref Generalized_Affine_Relations "generalized affine relation"
    \f$\mathrm{var}' \relsym \frac{\mathrm{expr}}{\mathrm{denominator}}\f$,
    where \f$\mathord{\relsym}\f$ is the relation symbol encoded
    by \p relsym.

    \param var
    The left hand side variable of the generalized affine relation;

    \param relsym
    The relation symbol;

    \param expr
    The numerator of the right hand side affine expression;

    \param denominator
    The denominator of the right hand side affine expression (optional
    argument with default value 1).

    \exception std::invalid_argument
    Thrown if \p denominator is zero or if \p expr and \p *this are
    dimension-incompatible or if \p var is not a space dimension of \p *this.
  */
  void generalized_affine_image(Variable var,
				const Relation_Symbol relsym,
				const Linear_Expression& expr,
				Coefficient_traits::const_reference denominator
				  = Coefficient_one());

  /*! \brief
    Assigns to \p *this the preimage of \p *this with respect to the
    \ref Generalized_Affine_Relations "generalized affine relation"
    \f$\mathrm{var}' \relsym \frac{\mathrm{expr}}{\mathrm{denominator}}\f$,
    where \f$\mathord{\relsym}\f$ is the relation symbol encoded
    by \p relsym.

    \param var
    The left hand side variable of the generalized affine relation;

    \param relsym
    The relation symbol;

    \param expr
    The numerator of the right hand side affine expression;

    \param denominator
    The denominator of the right hand side affine expression (optional
    argument with default value 1).

    \exception std::invalid_argument
    Thrown if \p denominator is zero or if \p expr and \p *this are
    dimension-incompatible or if \p var is not a space dimension of \p *this.
  */
  void
  generalized_affine_preimage(Variable var,
			      const Relation_Symbol relsym,
			      const Linear_Expression& expr,
			      Coefficient_traits::const_reference denominator
			      = Coefficient_one());

  /*! \brief
    Assigns to \p *this the image of \p *this with respect to the
    \ref Generalized_Affine_Relations "generalized affine relation"
    \f$\mathrm{lhs}' \relsym \mathrm{rhs}\f$, where
    \f$\mathord{\relsym}\f$ is the relation symbol encoded by \p relsym.

    \param lhs
    The left hand side affine expression;

    \param relsym
    The relation symbol;

    \param rhs
    The right hand side affine expression.

    \exception std::invalid_argument
    Thrown if \p *this is dimension-incompatible with \p lhs or \p rhs.
  */
  void generalized_affine_image(const Linear_Expression& lhs,
				const Relation_Symbol relsym,
				const Linear_Expression& rhs);

  /*! \brief
    Assigns to \p *this the preimage of \p *this with respect to the
    \ref Generalized_Affine_Relations "generalized affine relation"
    \f$\mathrm{lhs}' \relsym \mathrm{rhs}\f$, where
    \f$\mathord{\relsym}\f$ is the relation symbol encoded by \p relsym.

    \param lhs
    The left hand side affine expression;

    \param relsym
    The relation symbol;

    \param rhs
    The right hand side affine expression.

    \exception std::invalid_argument
    Thrown if \p *this is dimension-incompatible with \p lhs or \p rhs.
  */
  void generalized_affine_preimage(const Linear_Expression& lhs,
				   const Relation_Symbol relsym,
				   const Linear_Expression& rhs);

  /*! \brief
    Assigns to \p *this the image of \p *this with respect to the
    \ref Single_Update_Bounded_Affine_Relations "bounded affine relation"
    \f$\frac{\mathrm{lb\_expr}}{\mathrm{denominator}}
         \leq \mathrm{var}'
           \leq \frac{\mathrm{ub\_expr}}{\mathrm{denominator}}\f$.

    \param var
    The variable updated by the affine relation;

    \param lb_expr
    The numerator of the lower bounding affine expression;

    \param ub_expr
    The numerator of the upper bounding affine expression;

    \param denominator
    The (common) denominator for the lower and upper bounding
    affine expressions (optional argument with default value 1).

    \exception std::invalid_argument
    Thrown if \p denominator is zero or if \p lb_expr (resp., \p ub_expr)
    and \p *this are dimension-incompatible or if \p var is not a space
    dimension of \p *this.
  */
  void bounded_affine_image(Variable var,
			    const Linear_Expression& lb_expr,
			    const Linear_Expression& ub_expr,
			    Coefficient_traits::const_reference denominator
			    = Coefficient_one());

  /*! \brief
    Assigns to \p *this the preimage of \p *this with respect to the
    \ref Single_Update_Bounded_Affine_Relations "bounded affine relation"
    \f$\frac{\mathrm{lb\_expr}}{\mathrm{denominator}}
         \leq \mathrm{var}'
           \leq \frac{\mathrm{ub\_expr}}{\mathrm{denominator}}\f$.

    \param var
    The variable updated by the affine relation;

    \param lb_expr
    The numerator of the lower bounding affine expression;

    \param ub_expr
    The numerator of the upper bounding affine expression;

    \param denominator
    The (common) denominator for the lower and upper bounding
    affine expressions (optional argument with default value 1).

    \exception std::invalid_argument
    Thrown if \p denominator is zero or if \p lb_expr (resp., \p ub_expr)
    and \p *this are dimension-incompatible or if \p var is not a space
    dimension of \p *this.
  */
  void bounded_affine_preimage(Variable var,
			       const Linear_Expression& lb_expr,
			       const Linear_Expression& ub_expr,
			       Coefficient_traits::const_reference denominator
			       = Coefficient_one());

  /*! \brief
    Assigns to \p *this the result of computing the
    \ref CC76_extrapolation "CC76-widening" between \p *this and \p y.

    \param y
    A bounding box that <EM>must</EM> be contained in \p *this.

    \param tp
    An optional pointer to an unsigned variable storing the number of
    available tokens (to be used when applying the
    \ref Widening_with_Tokens "widening with tokens" delay technique).

    \exception std::invalid_argument
    Thrown if \p *this and \p y are dimension-incompatible.
  */
  void CC76_widening_assign(const Box& y, unsigned* tp = 0);

  /*! \brief
    Assigns to \p *this the result of computing the
    \ref CC76_extrapolation "CC76-widening" between \p *this and \p y.

    \param y
    A bounding box that <EM>must</EM> be contained in \p *this.

    \param first
    An iterator that points to the first stop-point.

    \param last
    An iterator that points one past the last stop-point.

    \exception std::invalid_argument
    Thrown if \p *this and \p y are dimension-incompatible.
  */
  template <typename Iterator>
  void CC76_widening_assign(const Box& y,
			    Iterator first, Iterator last);

  //@} Space-Dimension Preserving Member Functions that May Modify [...]

  //! \name Member Functions that May Modify the Dimension of the Vector Space
  //@{

  //! Adds \p m new dimensions and embeds the old box into the new space.
  /*!
    \param m
    The number of dimensions to add.

    The new dimensions will be those having the highest indexes in the new
    box, which is defined by a system of interval constraints in which the
    variables running through the new dimensions are unconstrained.
    For instance, when starting from the box \f$\cB \sseq \Rset^2\f$
    and adding a third dimension, the result will be the box
    \f[
      \bigl\{\,
        (x, y, z)^\transpose \in \Rset^3
      \bigm|
        (x, y)^\transpose \in \cB
      \,\bigr\}.
    \f]
  */
  void add_space_dimensions_and_embed(dimension_type m);

  /*! \brief
    Adds \p m new dimensions to the box and does not embed it in
    the new vector space.

    \param m
    The number of dimensions to add.

    The new dimensions will be those having the highest indexes in the
    new box, which is defined by a system of bounded differences in
    which the variables running through the new dimensions are all
    constrained to be equal to 0.
    For instance, when starting from the box \f$\cB \sseq \Rset^2\f$
    and adding a third dimension, the result will be the box
    \f[
      \bigl\{\,
        (x, y, 0)^\transpose \in \Rset^3
      \bigm|
        (x, y)^\transpose \in \cB
      \,\bigr\}.
    \f]
  */
  void add_space_dimensions_and_project(dimension_type m);

  /*! \brief
    Seeing a box as a set of tuples (its points),
    assigns to \p *this all the tuples that can be obtained by concatenating,
    in the order given, a tuple of \p *this with a tuple of \p y.

    Let \f$B \sseq \Rset^n\f$ and \f$D \sseq \Rset^m\f$ be the boxes
    corresponding, on entry, to \p *this and \p y, respectively.
    Upon successful completion, \p *this will represent the box
    \f$R \sseq \Rset^{n+m}\f$ such that
    \f[
      R \defeq
          \Bigl\{\,
            (x_1, \ldots, x_n, y_1, \ldots, y_m)^\transpose
          \Bigm|
            (x_1, \ldots, x_n)^\transpose \in B,
            (y_1, \ldots, y_m)^\transpose \in D
          \,\Bigl\}.
    \f]
    Another way of seeing it is as follows: first increases the space
    dimension of \p *this by adding \p y.space_dimension() new
    dimensions; then adds to the system of constraints of \p *this a
    renamed-apart version of the constraints of \p y.
  */
  void concatenate_assign(const Box& y);

  //! Removes all the specified dimensions.
  /*!
    \param to_be_removed
    The set of Variable objects corresponding to the dimensions to be removed.

    \exception std::invalid_argument
    Thrown if \p *this is dimension-incompatible with one of the Variable
    objects contained in \p to_be_removed.
  */
  void remove_space_dimensions(const Variables_Set& to_be_removed);

  /*! \brief
    Removes the higher dimensions so that the resulting space
    will have dimension \p new_dimension.

    \exception std::invalid_argument
    Thrown if \p new_dimension is greater than the space dimension
    of \p *this.
  */
  void remove_higher_space_dimensions(dimension_type new_dimension);

  /*! \brief
    Remaps the dimensions of the vector space according to
    a \ref Mapping_the_Dimensions_of_the_Vector_Space "partial function".

    \param pfunc
    The partial function specifying the destiny of each dimension.

    The template class Partial_Function must provide the following
    methods.
    \code
      bool has_empty_codomain() const
    \endcode
    returns <CODE>true</CODE> if and only if the represented partial
    function has an empty co-domain (i.e., it is always undefined).
    The <CODE>has_empty_codomain()</CODE> method will always be called
    before the methods below.  However, if
    <CODE>has_empty_codomain()</CODE> returns <CODE>true</CODE>, none
    of the functions below will be called.
    \code
      dimension_type max_in_codomain() const
    \endcode
    returns the maximum value that belongs to the co-domain
    of the partial function.
    \code
      bool maps(dimension_type i, dimension_type& j) const
    \endcode
    Let \f$f\f$ be the represented function and \f$k\f$ be the value
    of \p i.  If \f$f\f$ is defined in \f$k\f$, then \f$f(k)\f$ is
    assigned to \p j and <CODE>true</CODE> is returned.
    If \f$f\f$ is undefined in \f$k\f$, then <CODE>false</CODE> is
    returned.

    The result is undefined if \p pfunc does not encode a partial
    function with the properties described in the
    \ref Mapping_the_Dimensions_of_the_Vector_Space
    "specification of the mapping operator".
  */
  template <typename Partial_Function>
  void map_space_dimensions(const Partial_Function& pfunc);

  //! Creates \p m copies of the space dimension corresponding to \p var.
  /*!
    \param var
    The variable corresponding to the space dimension to be replicated;

    \param m
    The number of replicas to be created.

    \exception std::invalid_argument
    Thrown if \p var does not correspond to a dimension of the vector space.

    \exception std::length_error
    Thrown if adding \p m new space dimensions would cause the
    vector space to exceed dimension <CODE>max_space_dimension()</CODE>.

    If \p *this has space dimension \f$n\f$, with \f$n > 0\f$,
    and <CODE>var</CODE> has space dimension \f$k \leq n\f$,
    then the \f$k\f$-th space dimension is
    \ref expand_space_dimension "expanded" to \p m new space dimensions
    \f$n\f$, \f$n+1\f$, \f$\dots\f$, \f$n+m-1\f$.
  */
  void expand_space_dimension(Variable var, dimension_type m);

  //! Folds the space dimensions in \p to_be_folded into \p var.
  /*!
    \param to_be_folded
    The set of Variable objects corresponding to the space dimensions
    to be folded;

    \param var
    The variable corresponding to the space dimension that is the
    destination of the folding operation.

    \exception std::invalid_argument
    Thrown if \p *this is dimension-incompatible with \p var or with
    one of the Variable objects contained in \p to_be_folded.
    Also thrown if \p var is contained in \p to_be_folded.

    If \p *this has space dimension \f$n\f$, with \f$n > 0\f$,
    <CODE>var</CODE> has space dimension \f$k \leq n\f$,
    \p to_be_folded is a set of variables whose maximum space dimension
    is also less than or equal to \f$n\f$, and \p var is not a member
    of \p to_be_folded, then the space dimensions corresponding to
    variables in \p to_be_folded are \ref fold_space_dimensions "folded"
    into the \f$k\f$-th space dimension.
  */
  void fold_space_dimensions(const Variables_Set& to_be_folded, Variable var);

  void swap(Box& y);

  //@} // Member Functions that May Modify the Dimension of the Vector Space

  /*! \brief
    Returns a reference the interval that bounds
    the box on the <CODE>k</CODE>-th space dimension.
  */
  const Interval& operator[](dimension_type k) const;

  /*! \brief
    If the <CODE>k</CODE>-th space dimension is unbounded below, returns
    <CODE>false</CODE>. Otherwise returns <CODE>true</CODE> and set
    \p closed, \p n and \p d accordingly.

    Let \f$I\f$ the interval corresponding to the <CODE>k</CODE>-th
    space dimension.  If \f$I\f$ is not bounded from below, simply return
    <CODE>false</CODE>.  Otherwise, set <CODE>closed</CODE>,
    <CODE>n</CODE> and <CODE>d</CODE> as follows: <CODE>closed</CODE>
    is set to <CODE>true</CODE> if the the lower boundary of \f$I\f$
    is closed and is set to <CODE>false</CODE> otherwise;
    <CODE>n</CODE> and <CODE>d</CODE> are assigned the integers
    \f$n\f$ and \f$d\f$ such that the canonical fraction \f$n/d\f$
    corresponds to the greatest lower bound of \f$I\f$.  The fraction
    \f$n/d\f$ is in canonical form if and only if \f$n\f$ and \f$d\f$
    have no common factors and \f$d\f$ is positive, \f$0/1\f$ being
    the unique representation for zero.

    An undefined behavior is obtained if \p k is greater than
    or equal to the space dimension of \p *this.
  */
  bool get_lower_bound(dimension_type k, bool& closed,
		       Coefficient& n, Coefficient& d) const;

  /*! \brief
    If the <CODE>k</CODE>-th space dimension is unbounded above, returns
    <CODE>false</CODE>. Otherwise returns <CODE>true</CODE> and set
    \p closed, \p n and \p d accordingly.

    Let \f$I\f$ the interval corresponding to the <CODE>k</CODE>-th
    space dimension.  If \f$I\f$ is not bounded from above, simply return
    <CODE>false</CODE>.  Otherwise, set <CODE>closed</CODE>,
    <CODE>n</CODE> and <CODE>d</CODE> as follows: <CODE>closed</CODE>
    is set to <CODE>true</CODE> if the the upper boundary of \f$I\f$
    is closed and is set to <CODE>false</CODE> otherwise;
    <CODE>n</CODE> and <CODE>d</CODE> are assigned the integers
    \f$n\f$ and \f$d\f$ such that the canonical fraction \f$n/d\f$
    corresponds to the least upper bound of \f$I\f$.

    An undefined behavior is obtained if \p k is greater than
    or equal to the space dimension of \p *this.
  */
  bool get_upper_bound(dimension_type k, bool& closed,
		       Coefficient& n, Coefficient& d) const;

  //! Causes the box to become empty, i.e., to represent the empty set.
  void set_empty();

  /*! \brief
    Raises the lower bound of the interval corresponding
    to the <CODE>k</CODE>-th space dimension.

    Intersects the interval corresponding to the <CODE>k</CODE>-th
    space dimension
    with \f$[n/d, +\infty)\f$ if <CODE>closed</CODE> is <CODE>true</CODE>,
    with \f$(n/d, +\infty)\f$ if <CODE>closed</CODE> is <CODE>false</CODE>.
    An undefined behavior is obtained if \p k is greater than or equal to
    the space dimension of \p *this or if \p d is equal to zero.
  */
  void raise_lower_bound(dimension_type k, bool closed,
			 Coefficient_traits::const_reference n,
			 Coefficient_traits::const_reference d);

  /*! \brief
    Lowers the upper bound of the interval corresponding
    to the <CODE>k</CODE>-th space dimension.

    Intersects the interval corresponding to the <CODE>k</CODE>-th
    space dimension
    with \f$(-\infty, n/d]\f$ if <CODE>closed</CODE> is <CODE>true</CODE>,
    with \f$(-\infty, n/d)\f$ if <CODE>closed</CODE>
    is <CODE>false</CODE>.
    An undefined behavior is obtained if \p k is greater than or equal to
    the space dimension of \p *this or if \p d is equal to zero.
  */
  void lower_upper_bound(dimension_type k, bool closed,
			 Coefficient_traits::const_reference n,
			 Coefficient_traits::const_reference d);

  //! Returns a system of constraints defining \p *this.
  Constraint_System constraints() const;

  //! Returns a minimized system of constraints defining \p *this.
  Constraint_System minimized_constraints() const;

  PPL_OUTPUT_DECLARATIONS

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
  /*! \brief
    Loads from \p s an ASCII representation (as produced by
    ascii_dump(std::ostream&) const) and sets \p *this accordingly.
    Returns <CODE>true</CODE> if successful, <CODE>false</CODE> otherwise.
  */
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
  bool ascii_load(std::istream& s);

private:
  template <typename Other_Interval>
  friend class Parma_Polyhedra_Library::Box;

  friend bool
  Parma_Polyhedra_Library::operator==<Interval>(const Box<Interval>& x,
						const Box<Interval>& y);

  //! The type of sequence used to implement the box.
  typedef std::vector<Interval> Sequence;

  //! A sequence of intervals, one for each dimension of the vector space.
  Sequence seq;

  //! Returns <CODE>true</CODE> if and only if the box is known to be empty.
  /*!
    The return value <CODE>false</CODE> does not necessarily
    implies that \p *this is non-empty.
  */
  bool marked_empty()const;

  /*! \brief
    A Boolean flag indicating emptiness of the box.
    Only meaningful when \p empty_up_to_date is <CODE>true</CODE>.
  */
  mutable bool empty;

  //! Tells whether or not the flag \p empty is meaningful.
  mutable bool empty_up_to_date;

  /*! \brief
    Checks the hard way whether \p *this is an empty box:
    returns <CODE>true</CODE> if and only if it is so.
  */
  bool check_empty() const;

  //! \name Exception Throwers
  //@{
  void throw_dimension_incompatible(const char* method,
				    const Box& x) const;

  void throw_dimension_incompatible(const char* method,
				    dimension_type required_dim) const;

  void throw_dimension_incompatible(const char* method,
				    const Constraint& c) const;

  void throw_dimension_incompatible(const char* method,
				    const Generator& g) const;

  void throw_dimension_incompatible(const char* method,
				    const char* name_row,
				    const Linear_Expression& y) const;

  static void throw_constraint_incompatible(const char* method);

  static void throw_expression_too_complex(const char* method,
					   const Linear_Expression& e);

  static void throw_generic(const char* method, const char* reason);
  //@} // Exception Throwers
};

namespace Parma_Polyhedra_Library {

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Decodes the constraint \p c as a bounded difference.
/*! \relates Box
  \return
  <CODE>true</CODE> if the constraint \p c is an
  \ref Boxes "interval constraint";
  <CODE>false</CODE> otherwise.

  \param c
  The constraint to be decoded.

  \param c_space_dim
  The space dimension of the constraint \p c (it is <EM>assumed</EM>
  to match the actual space dimension of \p c).

  \param c_num_vars
  If <CODE>true</CODE> is returned, then it will be set to the number
  of variables having a non-zero coefficient. The only legal values
  will therefore be 0 and 1.

  \param c_only_var
  If <CODE>true</CODE> is returned and if \p c_num_vars is not set to 0,
  then it will be set to the index of the only variable having
  a non-zero coefficient in \p c.

  \param c_coeff
  If <CODE>true</CODE> is returned and if \p c_num_vars is not set to 0,
  then it will be set to the value of the only non-zero coefficient in \p c.
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
bool extract_interval_constraint(const Constraint& c,
				 const dimension_type c_space_dim,
				 dimension_type& c_num_vars,
				 dimension_type& c_only_var,
				 Coefficient& c_coeff);

} // namespace Parma_Polyhedra_Library

#include "Box.inlines.hh"
#include "Box.templates.hh"

#endif // !defined(PPL_Box_defs_hh)