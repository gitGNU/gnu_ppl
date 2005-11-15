/* Constraint_System class implementation: primal_simplex().
   Copyright (C) 2001-2005 Roberto Bagnara <bagnara@cs.unipr.it>

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

#include <config.h> 
#include "globals.types.hh"
#include "globals.defs.hh"
#include "Row.defs.hh"
#include "Matrix.defs.hh"
#include "Linear_Row.defs.hh"
#include "Linear_System.defs.hh"
#include "Linear_Expression.defs.hh"
#include "Constraint_System.defs.hh"
#include "Constraint_System.inlines.hh"
#include "Generator.defs.hh"
#include <stdexcept>
#include <sstream>
#include <map>
#include <deque>

#ifndef PPL_NOISY_SIMPLEX
#define PPL_NOISY_SIMPLEX 0
#endif

#ifdef PPL_NOISY_SIMPLEX
#include <iostream>
#endif

#ifndef PPL_SIMPLEX_ENABLE_STEEPEST_EDGE
#define PPL_SIMPLEX_ENABLE_STEEPEST_EDGE 0
#endif

namespace {

#if PPL_NOISY_SIMPLEX
unsigned num_iterations = 0;
#endif

using namespace Parma_Polyhedra_Library;

//! \brief
//! Checks for optimality and, if it does not hold, computes the column
//! index of the variable entering the base of the LP problem.
/*!
  \return
  The column index of the variable that enters the base. If no such
  variable exists, optimality was achieved and <CODE>0</CODE> is retuned.
  
  \param tableau 
  The constraint tableau for the LP problem.
 
  \param cost_function
  The expression to be optimized.
  
  \param base
  The base of the LP problem.

  To compute the entering_index, the steepest edge algorithm chooses
  the index `j' such that \f$\frac{d_{j}}{\|\Delta x^{j} \|}\f$ is the
  largest in absolute value, where
  \f[
    \|\Delta x^{j} \|
      = \left(
          1+\sum_{i=1}^{m} \alpha_{ij}^2
        \right)^{\frac{1}{2}}.
  \f]
  Recall that, due to the Integer implementation of the algorithm, our
  tableau doesn't contain the ``real'' \f$\alpha\f$ values, but these
  can be computed dividing the value of the cofficient by the value of
  the variable in base. Obviously the result may not be an Integer, so
  we will proceed in another way: the following code will compute the
  lcm of all the variables in base to get the good ``weight'' of each
  Coefficient of the tableau.
*/
dimension_type
steepest(const Matrix& tableau,
	 const Row& cost,
	 const std::vector<dimension_type>& base) {
  // The lcm of all the coefficients of the variable in base.
  TEMP_INTEGER(lcm_basis);
  lcm_basis = 1;
  // Compute lcm_basis.
  const dimension_type base_size = base.size();
  for (dimension_type i = base_size; i-- > 0; )
    lcm_assign(lcm_basis, tableau[i][base[i]]);
  // This Vector will contain the value that will be multiplied to each 
  // computed coefficient of the tableau.
  std::vector<Coefficient> right_mult(base_size);
  for (dimension_type j = base_size; j-- > 0; )
    exact_div_assign(right_mult[j], lcm_basis, tableau[j][base[j]]);
  // Here we compute the square of `lcm_basis'. Since `lcm_basis' is
  // no longer needed, we directly compute the square into it.
  lcm_basis *= lcm_basis;

  // These variables are declared here to increase speed computation.
  TEMP_INTEGER(challenger_num);
  TEMP_INTEGER(scalar_value);
  TEMP_INTEGER(challenger_den);
  TEMP_INTEGER(challenger_value);
  TEMP_INTEGER(current_value);

  TEMP_INTEGER(current_num);
  TEMP_INTEGER(current_den); 
  dimension_type entering_index = 0;
  const int cost_sign = sgn(cost[cost.size() - 1]);
  const dimension_type tableau_num_rows = tableau.num_rows();
  for (dimension_type i = tableau.num_columns() - 1; i-- > 1; ) {
    const Coefficient& cost_i = cost[i];
    if (sgn(cost_i) == cost_sign) {
      // We can't apply the square root to each \f$\|\Delta x^{j}\|\f$.
      // The workaround is to compute the square of `cost[i]'.
      challenger_num = cost_i * cost_i;
      challenger_den = 0;
      for (dimension_type j = tableau_num_rows; j-- > 0; ) {
	const Coefficient& tableau_ji = tableau[j][i];
	// FIXME: the test seems to speed up the GMP computation.
	if (tableau_ji != 0) {
	  scalar_value = tableau_ji * right_mult[j];
	  add_mul_assign(challenger_den, scalar_value, scalar_value);
	}
      }
      // The `1' of the denominator of the original formula must be 
      // substituted (still related to the Integer implementation) to  
      // the square of `lcm_basis' (already in `lcm_basis').
      challenger_den += lcm_basis;
      // Initialize the first value: this will be the first value to beat.
      if (entering_index == 0) {
	std::swap(current_num, challenger_num);
	std::swap(current_den, challenger_den);
	entering_index = i;
 	continue;
      }
      challenger_value = challenger_num * current_den;
      current_value = current_num * challenger_den;
      // Update the values, if the challeger wins. 
      if (challenger_value > current_value) {
	std::swap(current_num, challenger_num);
	std::swap(current_den, challenger_den);
	entering_index = i;
      }
    }
  }
  return entering_index;
}


//! Linearly combines \p x with \p y so that <CODE>*this[k]</CODE> is 0.
/*!
  \param x
  The Row that will be combined with \p y object.

  \param y
  The Row that will be combined with \p x object.

  \param k
  The position of \p *this that have to be \f$0\f$.

  Computes a linear combination of \p x and \p y having
  the element of index \p k equal to \f$0\f$. Then it assigns
  the resulting Linear_Row to \p x and normalizes it.
*/
void
linear_combine(Row& x, const Row& y, const dimension_type k) {
  assert(x.size() == y.size());
  assert(y[k] != 0 && x[k] != 0);
  // Let g be the GCD between `x[k]' and `y[k]'.
  // For each i the following computes
  //   x[i] = x[i]*y[k]/g - y[i]*x[k]/g.
  TEMP_INTEGER(normalized_x_k);
  TEMP_INTEGER(normalized_y_k);
  normalize2(x[k], y[k], normalized_x_k, normalized_y_k);
  for (dimension_type i = x.size(); i-- > 0; )
    if (i != k) {
      Coefficient& x_i = x[i];
      x_i *= normalized_y_k;
#if 1
      // FIXME: the test seems to speed up the GMP computation.
      const Coefficient& y_i = y[i];
      if (y_i != 0)
	sub_mul_assign(x_i, y_i, normalized_x_k);
#else
      sub_mul_assign(x_i, y[i], normalized_x_k);
#endif
    }
  x[k] = 0;
  x.normalize();
} 

// See pag 42-43 of Papadimitriou. 

//! \brief
//! Swaps two variables in base during the simplex algorithm,
//! performing the needed linear combinations.
/*!
  \param tableau
  The constraints of the LP problem.

  \param cost_function
  The cost function of the LP problem.

  \param entering_var_index
  The index of the variable entering the base.

  \param exiting_base_index
  The index of the row exiting the base.
*/
void
swap_base(Matrix& tableau,
	  Row& cost_function,
	  const dimension_type entering_var_index,
	  const dimension_type exiting_base_index) {
  const Row& tableau_out = tableau[exiting_base_index];
  // Linearly combine the constraints.
  for (dimension_type i = tableau.num_rows(); i-- > 0; ) {
    Row& tableau_i = tableau[i];
    if (i != exiting_base_index && tableau_i[entering_var_index] != 0)
      linear_combine(tableau_i, tableau_out, entering_var_index);
  }
  // Linearly combine the cost function.
  if (cost_function[entering_var_index] != 0)
    linear_combine(cost_function, tableau_out, entering_var_index);
}


// See pag. 47 of Papadimitriou.

//! \brief
//! Checks for optimality and, if it does not hold, computes the column
//! index of the variable entering the base of the LP problem.
//! Implemented with anti-cycling rule.
/*!
  \return
  The column index of the variable that enters the base. If no such
  variable exists, optimality was achieved and <CODE>0</CODE> is retuned.

  \param cost_function
  The expression to be optimized.
*/
dimension_type
get_entering_var_index(const Row& cost_function) {
  // The variable entering the base is the first one whose coefficient
  // in the cost function has the same sign the cost function itself.
  // If no such variable exists, then we met the optimality condition
  // (and return 0 to the caller).

  // Get the "sign" of the cost function.
  const dimension_type cost_sign_index = cost_function.size() - 1;
  const int cost_sign = sgn(cost_function[cost_sign_index]);
  assert(cost_sign != 0);
  for (dimension_type i = 1; i < cost_sign_index; ++i)
    if (sgn(cost_function[i]) == cost_sign)
      return i;
  // No variable has to enter the base:
  // the cost function was optimized.
  return 0;
}

// See pag. 47 + 50 of Papadimitriou.  

//! \brief
//! Computes the row index of the variable exiting the base
//! of the LP problem. Implemented with anti-cycling rules.
/*!
  \return
  The row index of the variable exiting the base.

  \param tableau
  The constraint tableau for the LP problem.

  \param entering_var_index
  The column index of the variable entering the base.

  \param base
  The base of the LP problem.

  \param unbounded
  Will be set to <CODE>true<\CODE> if and only if the LP problem
  is unbounded.
*/
dimension_type
get_exiting_base_index(const Matrix& tableau,  
		       const dimension_type entering_var_index,
		       std::vector<dimension_type>& base) {
  // The variable exiting the base should be associated to a tableau
  // constraint such that the ratio
  //   tableau[i][entering_var_index] / tableau[i][base[i]]
  // is strictly positive and minimal.

  // Find the first tableau constraint `c' having a positive value for
  //   tableau[i][entering_var_index] / tableau[i][base[i]]
  const dimension_type tableau_num_rows = tableau.num_rows();
  dimension_type exiting_base_index = tableau_num_rows;
  for (dimension_type i = 0; i < tableau_num_rows; ++i) {
    const Row& t_i = tableau[i];
    const int num_sign = sgn(t_i[entering_var_index]);
    if (num_sign != 0 && num_sign == sgn(t_i[base[i]])) {
      exiting_base_index = i;
      break;
    }
  }
  // Check for unboundedness.
  if (exiting_base_index == tableau_num_rows)
    return tableau_num_rows;

  // Reaching this point means that a variable will definitely exit the base.
  TEMP_INTEGER(lcm);
  TEMP_INTEGER(current_min);
  TEMP_INTEGER(challenger);
  for (dimension_type i = exiting_base_index + 1; i < tableau_num_rows; ++i) {
    const Row& t_i = tableau[i];
    const Coefficient& t_ie = t_i[entering_var_index];
    const Coefficient& t_ib = t_i[base[i]];
    const int t_ie_sign = sgn(t_ie);
    if (t_ie_sign != 0 && t_ie_sign == sgn(t_ib)) {
      const Row& t_e = tableau[exiting_base_index];
      const Coefficient& t_ee = t_e[entering_var_index];
      lcm_assign(lcm, t_ee, t_ie);
      exact_div_assign(current_min, lcm, t_ee);
      current_min *= t_e[0];
      current_min = abs(current_min);
      exact_div_assign(challenger, lcm, t_ie);
      challenger *= t_i[0];
      challenger = abs(challenger);
      current_min -= challenger;
      const int sign = sgn(current_min);
      if (sign > 0
	  || (sign == 0 && base[i] < base[exiting_base_index]))
	exiting_base_index = i;
    }
  }
  return exiting_base_index;
}

// See pag 49 of Papadimitriou.

//! The simplex algorithm.
/*! 
  \return
  <CODE>true</CODE> if and if only the algorithm successfully computed
  a feasible solution.

  \param tableau
  The constraint tableau for the LP problem.

  \param cost_function
  The cost function to be maximized. 

  \param base
  The indices of the variables in base.

  To solve the LP problem compute_simplex must receive the problem in this way:

  1) Linear Expressions:
  k + x_1 + x_2 + ... + x_n + s (with s > 0)
  where k is the inhomogeneous term, x_i are the coefficients of the variables
  and s is a special variable that stands for the sign of the cost function.
  In this way is possible to know if the cost function was reversed during 
  the linear combinations. Reasoning in a "PPL way" we can think that this 
  row stands for k + x_1 + x_2 + s = 0, so -s = k + x_1 + x_2 + ...  + x_n.
  We use a matrix instead of a row because in this way is very simple to have
  the cost function of the second_phase. The old objective cost function, if
  compute_simplex is called by first_phase, is stored in the second row.
  
  2) Constraints:
  These are the standard "PPL rows", so there should not be special 
  problems to understand what's in this matrix.
  
  It is assumed that \p tableau and \p expressions have the same
  number of columns (i.e., the same space dimension).
*/
bool
compute_simplex(Matrix& tableau,
		Row& cost_function,
		std::vector<dimension_type>& base) {
  assert(tableau.num_columns() == cost_function.size());
  const dimension_type tableau_num_rows = tableau.num_rows();

  while (true) {
    // Choose the index of the variable entering the base, if any.
    const dimension_type entering_var_index
#if PPL_SIMPLEX_ENABLE_STEEPEST_EDGE
      = steepest(tableau, cost_function, base);
#else
      = get_entering_var_index(cost_function);
#endif
    // If no entering index was computed, the problem is solved.
    if (entering_var_index == 0)
      return true;
    
    // Choose the index of the row exiting the base.
    const dimension_type exiting_base_index
      = get_exiting_base_index(tableau, entering_var_index, base);
    // If no exiting index was computed, the problem is unbounded.
    if (exiting_base_index == tableau_num_rows)
      return false;

    // We have not reached the optimality or unbounded condition:
    // compute the new base and the corresponding vertex of the
    // feasible region.
    base[exiting_base_index] = entering_var_index;
    swap_base(tableau, cost_function, entering_var_index, exiting_base_index);

#if PPL_NOISY_SIMPLEX
    ++num_iterations;
    if (num_iterations % 200 == 0)
      std::cout << "Primal Simplex: iteration "
		<< num_iterations << "." << std::endl;
#endif
  }
}

// See pag 28  Papadimitriou.

//! \brief
//! Adds the slack variables to satisfy the standard form of a LP problem,
//! inserts the "sign" to the cost functions, and makes the
//! necessary swaps to express the problem with the 1st phase base.
/*!
  \param tableau
  The matrix containing the LP problem.

  \param costs
  The matrix containing the original and the adapted cost functions.

  \param base
  The vector that stores the variables in the base of the LP problem.
*/
void   
prepare_first_phase(Matrix& tableau,
		    Matrix& costs,
		    std::vector<dimension_type>& base) {
  // We negate the row if tableau[i][0] <= 0 to get the inhomogeneous term > 0.
  // This simplifies the insertion of the slack variables: the value of the 
  // slack variable of every constraint will be 1.
  const dimension_type tableau_old_n_cols = tableau.num_columns();
  for (dimension_type i = tableau.num_rows(); i-- > 0 ; ) {
    Row& tableau_i = tableau[i];
    if (tableau_i[0] > 0)
      for (dimension_type j = tableau_old_n_cols; j-- > 0; )
	negate(tableau_i[j]);
  }

  // Add the columns for all the slack variables, plus an additional
  // column for the sign of the cost function.
  tableau.add_zero_columns(tableau.num_rows() + 1);
  costs.add_zero_columns(tableau.num_rows() + 1);
  // Modify the tableau and the new cost function by adding
  // the slack variables (which enter the base).
  // As for the cost function, all the slack variables should have
  // coefficient -1.
  Row& new_obj = costs[0];
  Row& old_obj = costs[1];
  for (dimension_type i = 0; i < tableau.num_rows(); ++i) {
    const dimension_type j = tableau_old_n_cols + i;
    tableau[i][j] = 1;
    new_obj[j] = -1;
    base[i] = j;
  }

  // Set the extra-coefficient of the cost functions to record its sign.
  // This is done to keep track of the possible sign's inversion.
  const dimension_type last_obj_index = old_obj.size() - 1;
  old_obj[last_obj_index] = 1;
  new_obj[last_obj_index] = 1;
  
  // Express the problem in terms of the variables in base.
  for (dimension_type i = tableau.num_rows(); i-- > 0; )
    linear_combine(new_obj, tableau[i], base[i]);
}

// See pag 55-56 Papadimitriou.

//! \brief
//! Deletes the non necessary slack variables from the matrix
//! and prepares for the 2nd phase.
/*!
  \param tableau
  The matrix containing the constraints of the LP problem.

  \param costs
  The matrix containing the cost functions.

  \param base
  The variables in base of the LP problem.
*/
void erase_slacks(Matrix& tableau,
		  Matrix& costs,
		  std::vector<dimension_type>& base) {
  const dimension_type tableau_last_index = tableau.num_columns() - 1;
  dimension_type tableau_n_rows = tableau.num_rows();
  const dimension_type first_slack_index = tableau_last_index - tableau_n_rows;

  // Step 1: try to remove from the base all the remaining slack variables.
  for (dimension_type i = 0; i < tableau_n_rows; ++i)
    if (base[i] >= first_slack_index) {
      // Search for a non-zero element to enter the base.
      Row& tableau_i = tableau[i];
      bool redundant = true;
      for (dimension_type j = first_slack_index; j-- > 1; )
	if (tableau_i[j] != 0) {
	  swap_base(tableau, costs[0], j, i);
	  // Adjust the base.
	  base[i] = j;
	  redundant = false;
	  break;
	}
      if (redundant) {
	// No original variable entered the base:
	// the constraint is redundant and should be deleted.
	--tableau_n_rows;
	if (i < tableau_n_rows) {
	  // Replace the redundant row with the last one,
	  // taking care of adjusting the iteration index.
	  tableau_i.swap(tableau[tableau_n_rows]);
	  base[i] = base[tableau_n_rows];
	  --i;
	}
	tableau.erase_to_end(tableau_n_rows);
	base.pop_back();
      }
    }

  // Step 2: Adjust data structures so as to enter phase 2 of the simplex.
  
  // Compute the dimensions of the new tableau.
  const dimension_type new_tableau_n_cols = first_slack_index + 1;
  const dimension_type new_tableau_last_index = first_slack_index;
   
  // Adjust the number of columns of `tableau'.
  tableau.remove_trailing_columns(tableau.num_columns() - new_tableau_n_cols);
  // Zero the last column of the tableau.
  for (dimension_type i = tableau_n_rows; i-- > 0; )
    tableau[i][new_tableau_last_index] = 0;

  // Set the new cost function:
  // first let the second expression become the only one; ...
  Row& cost_function = costs[0];
  cost_function.swap(costs[1]);
  costs.erase_to_end(1);
  // ... then properly set the element in the (new) last column,
  // encoding the kind of optimization; ...
  cost_function[new_tableau_last_index] = cost_function[tableau_last_index];
  // ... and finally remove redundant columns.
  costs.remove_trailing_columns(tableau_last_index - new_tableau_last_index);
}

// See pag 55 of Papadimitriou.

//! \brief
//! Assigns to \p tableau a simplex tableau representing the problem
//! given by the constraints in \p cs and the cost function \p expr,
//! inserting into \p map the informations that are required to go
//! back to the original problem.
/*!
  \return
  <CODE>UNFEASIBLE_PROBLEM</CODE> if the constraint system contains
  any trivially unfeasible constraint (tableau was not computed);
  <CODE>UNBOUNDED_PROBLEM</CODE> if the problem is trivially unbounded
  (the computed tableau contains no constraints);
  <CODE>SOLVED_PROBLEM></CODE> if the problem is neither trivially
  unfeasible nor trivially unbounded (the tableau was computed successfully).

  \param cs
  A matrix containing the constraints of the problem.

  \param cost_function
  The cost function of the problem.

  \param tableau
  A matrix where to store the resulting tableau.

  \param map
  Contains all the pairs (i, j) such that Variable(i) (that was not found
  to be constrained in sign) has been split into two nonnegative variables.
  The "positive" one is represented again by Variable(i), and
  the "negative" one is represented by Variable(j).
*/
Simplex_Status
compute_tableau(const Linear_System& cs,
		Row& cost_function,
		Matrix& tableau,
		std::map<dimension_type, dimension_type>& dim_map) {
  assert(tableau.num_rows() == 0);
  assert(dim_map.size() == 0);

  const dimension_type cs_num_rows = cs.num_rows();
  const dimension_type cs_num_cols = cs.num_columns();
  
  // Step 1:
  // determine variables that are constrained to be nonnegative,
  // detect (non-negativity or tautology) constraints that will not
  // be part of the tableau and count the number of slack variables.
  
  // Counters determining the dimensions of the tableau:
  // initialized here, they will be updated while examining `cs'.
  dimension_type tableau_num_rows = cs_num_rows;
  dimension_type tableau_num_cols = 2*cs_num_cols - 1;
  dimension_type num_slack_variables = 0;

  // On exit, `is_tableau_constraint[i]' will be true if and only if
  // `cs[i]' is neither a tautology (e.g., 1 >= 0) nor a non-negativity
  // constraint (e.g., X >= 0).
  std::deque<bool> is_tableau_constraint(cs_num_rows, true);

  // On exit, `nonnegative_variable[j]' will be true if and only if
  // Variable(j) is bound to be nonnegative in `cs'.
  std::deque<bool> nonnegative_variable(cs_num_cols - 1, false);
  
  // Process each row of the `cs' matrix.
  for (dimension_type i = cs_num_rows; i-- > 0; ) { 
    const Linear_Row& cs_i = cs[i];
    bool found_a_nonzero_coeff = false;
    bool found_many_nonzero_coeffs = false;
    dimension_type nonzero_coeff_column_index = 0;
    for (dimension_type j = cs_num_cols; j-- > 1; ) {
      if (cs_i[j] != 0)
	if (found_a_nonzero_coeff) {
	  found_many_nonzero_coeffs = true;
	  if (cs_i.is_ray_or_point_or_inequality())
	    ++num_slack_variables;
	  break;
	}
	else {
	  nonzero_coeff_column_index = j;
	  found_a_nonzero_coeff = true;
	}
    }
    // If more than one coefficient is nonzero,
    // continue with next constraint. 
    if (found_many_nonzero_coeffs)
      continue;

    if (!found_a_nonzero_coeff) {
      // All coefficients are 0.
      // The constraint is either trivially true or trivially false.
      if (cs_i.is_ray_or_point_or_inequality()) {
	if (cs_i[0] < 0)
	  // A constraint such as -1 >= 0 is trivially false.
	  return UNFEASIBLE_PROBLEM;
      }
      else
	// The constraint is an equality.
	if (cs_i[0] != 0)
	  // A constraint such as 1 == 0 is trivially false.
	  return UNFEASIBLE_PROBLEM;
      // Here the constraint is trivially true.
      is_tableau_constraint[i] = false;
      --tableau_num_rows;
      continue;
    }
    else {
      // Here we have only one nonzero coefficient.
      /* 
	 
      We have the following methods:
      A) Do split the variable and do add the constraint in the tableau.
      B) Don't split the variable and do add the constraint in the tableau.
      C) Don't split the variable and don't add the constraint in the tableau.
	    
      Let the constraint be (a*v + b relsym 0).            
      These are the 12 possible combinations we can have: 
                a |  b | relsym | method
      ----------------------------------	    
      1)       >0 | >0 |   >=   |   A
      2)       >0 | >0 |   ==   |   A
      3)       <0 | <0 |   >=   |   A
      4)       >0 | =0 |   ==   |   B
      5)       >0 | <0 |   ==   |   B
      Note:    <0 | >0 |   ==   | impossible by strong normalization
      Note:    <0 | =0 |   ==   | impossible by strong normalization
      Note:    <0 | <0 |   ==   | impossible by strong normalization
      6)       >0 | <0 |   >=   |   B
      7)       >0 | =0 |   >=   |   C
      8)       <0 | >0 |   >=   |   A
      9)       <0 | =0 |   >=   |   A
       
      The next lines will apply the correct method to each case.
      */     
      
      // The variable index is not equal to the column index.
      const dimension_type nonzero_var_index = nonzero_coeff_column_index - 1;
 
      const int sgn_a = sgn(cs_i[nonzero_coeff_column_index]);
      const int sgn_b = sgn(cs_i[0]);     
      // Cases 1-3: apply method A. 
      if (sgn_a == sgn_b) {
	if (cs_i.is_ray_or_point_or_inequality())
	  ++num_slack_variables;
      }
      // Cases 4-5: apply method B. 
      else if (cs_i.is_line_or_equality()) {
	if (!nonnegative_variable[nonzero_var_index]) {
	  nonnegative_variable[nonzero_var_index] = true;
	  --tableau_num_cols;
	}
      }
      // Case 6: apply method B.
      else if (sgn_b < 0) {
	if (!nonnegative_variable[nonzero_var_index]) {
	  nonnegative_variable[nonzero_var_index] = true;
	  --tableau_num_cols;
	}
	++num_slack_variables;
      }
      // Case 7: apply method C.
      else if (sgn_a > 0) {
	if (!nonnegative_variable[nonzero_var_index]) {
	  nonnegative_variable[nonzero_var_index] = true;
	  --tableau_num_cols;
	}
	is_tableau_constraint[i] = false;
	--tableau_num_rows;
      }
      // Cases 8-9: apply method A.
      else
	++num_slack_variables;
    }
  }

  // The slack variables will be columns in the tableau.
  tableau_num_cols += num_slack_variables;
   
  // Now we can fill the map.
  for (dimension_type i = 0, j = nonnegative_variable.size(),
	 nnv_size = j; i < nnv_size; ++i)
    if (!nonnegative_variable[i]) {
      dim_map.insert(std::make_pair(i, j));
      ++j;
    }

  // Step 2: 
  // set the dimensions for the tableau and the cost function.
  if (tableau_num_rows > 0)
    tableau.add_zero_rows_and_columns(tableau_num_rows,
				      tableau_num_cols,
				      Row::Flags());
  Row tmp(cost_function, tableau_num_cols, tableau_num_cols);
  cost_function.swap(tmp);
  
  // Phase 3:
  // insert all the (possibly transformed) constraints that are not
  // nonnegativity constraints. The transformation includes both
  // the variable splitting (for variables that are unconstrained
  // in sign) and the addition of slack variables (for inequalities
  // in the original problem).

  for (dimension_type k = tableau_num_rows, slack_index = tableau_num_cols,
	 i = cs_num_rows; i-- > 0; )
    if (is_tableau_constraint[i]) {
      // Copy the original constraint in the tableau.
      Row& tableau_k = tableau[--k];
      const Linear_Row& cs_i = cs[i];
      for (dimension_type j = cs_num_cols; j-- > 0; )
	tableau_k[j] = cs_i[j];
      // Add the slack variable, if needed.
      if (cs_i.is_ray_or_point_or_inequality())
	tableau_k[--slack_index] = -1;
    }

  // Split the variables in the tableau and cost function.
  typedef std::map<dimension_type, dimension_type>::const_iterator iter;
  for (iter map_itr = dim_map.begin(),
	 map_end = dim_map.end(); map_itr != map_end; ++map_itr) {
    const dimension_type original_var = (map_itr->first) + 1;
    const dimension_type split_var = (map_itr->second) + 1;
    for (dimension_type i = tableau_num_rows; i-- > 0; ) {
      Row& tableau_i = tableau[i];
      tableau_i[split_var] = -tableau_i[original_var];
    }
    cost_function[split_var] = -cost_function[original_var];
  }

  // If there is no constraint in the tableau, then the feasible region
  // is only delimited by non-negativity constraints. Therefore,
  // the problem is unbounded as soon as the cost function has
  // a variable with a positive coefficient.
  if (tableau_num_rows == 0)
    for (dimension_type i = tableau_num_cols; i-- > 1; )
      if (cost_function[i] > 0)
	return UNBOUNDED_PROBLEM;

  // The problem is neither trivially unfeasible nor trivially unbounded.
  // The tableau was successfull computed and the caller has to figure
  // out which case applies.
  return SOLVED_PROBLEM;
}

//! \brief
//!  Checks whether variable is in base and assigns to 'row'
//! the row index of which is base.
/*!
  \return
  <CODE>true</CODE> if and only if variable of index \p var_index
  is one of the variables in \p base.

  \param base
  The base of the LP problem.

  \param var_index
  The index of the variable that has to be checked.

  \param row_index
  If <CODE>true</CODE> is returned, it will store the index of the
  tableau constraint corresponding to variable \p var_index.
*/ 
bool
is_in_base(const std::vector<dimension_type>& base,
	   const dimension_type var_index,
	   dimension_type& row_index ) {
  for (row_index = base.size(); row_index-- > 0; )
    if (base[row_index] == var_index)
      return true;
  return false;
}

//! Computes the generator corresponding to \p base.
/*!
  \return
  The computed generator.

  \param tableau
  The constraints of the LP problem.

  \param base
  The base of the LP problem.

  \param map
  Contains all the pairs (i, j) such that Variable(i) (that was not found
  to be constrained in sign) has been split into two nonnegative variables.
  The "positive" one is represented again by Variable(i), and the "negative"
  one is represented by Variable(j).

  \param original_space_dim
  The space dimension of the original LP problem.
*/
Generator
compute_generator(const Matrix& tableau,
		  const std::vector<dimension_type>& base,
		  const std::map<dimension_type, dimension_type>& dim_map,
		  const dimension_type original_space_dim) {
  // We will store in num[] and in den[] the numerators and
  // the denominators of every variable of the original problem.
  std::vector<Coefficient> num(original_space_dim);
  std::vector<Coefficient> den(original_space_dim);
  dimension_type row = 0;

  // We start to compute num[] and den[].
  typedef std::map<dimension_type, dimension_type>::const_iterator iter;
  iter map_end = dim_map.end();

  for (dimension_type i = original_space_dim; i-- > 0; ) {
    Coefficient& num_i = num[i];
    Coefficient& den_i = den[i];
    // Get the value of the variable from the tableau
    // (if it is not a basic variable, the value is 0).
    if (is_in_base(base, i+1, row)) {
      const Row& t_row = tableau[row];
      if (t_row[i+1] > 0) {
	num_i= -t_row[0];
	den_i= t_row[i+1];
      }
      else {
	num_i= t_row[0];
	den_i= -t_row[i+1];
      }
    }
    else {
      num_i = 0;
      den_i = 1;
    }
    // Check whether the variable was split.
    iter map_iter = dim_map.find(i);
    if (map_iter != map_end) {
      // The variable was split: get the value for the negative component,
      // having index map[i] + 1.
      const dimension_type split_i = map_iter->second;
      // Like before, we he have to check if the variable is in base.
      if (is_in_base(base, split_i+1, row)) {
	const Row& t_row = tableau[row];
	TEMP_INTEGER(split_num);
	TEMP_INTEGER(split_den);
	if (t_row[split_i+1] > 0) {
	  split_num = -t_row[0];
	  split_den = t_row[split_i+1];
	}
	else {
	  split_num = t_row[0];
	  split_den = -t_row[split_i+1];
	}
	// We compute the lcm to compute subsequently the difference
	// between the 2 variables.
	TEMP_INTEGER(lcm);
	lcm_assign(lcm, den_i, split_den);
	exact_div_assign(den_i, lcm, den_i);
	exact_div_assign(split_den, lcm, split_den);
	num_i *= den_i;
	sub_mul_assign(num_i, split_num, split_den);
	if (num_i == 0)
	  den_i = 1;
	else
	  den_i = lcm;
      }
      // Note: if the negative component was not in base, then
      // it has value zero and there is nothing left to do.
    }
  }
  
  // Compute the lcm of all denominators.
  TEMP_INTEGER(lcm);
  lcm = den[0];
  for (dimension_type i = 1; i < original_space_dim; ++i) 
    lcm_assign(lcm, den[i]);  
  // Use the denominators to store the numerators' multipliers
  // and then compute the normalized numerators.
  for (dimension_type i = original_space_dim; i-- > 0; ) {
    exact_div_assign(den[i], lcm, den[i]);
    num[i] *= den[i];
  }
  
  // Finally, build the generator.
  Linear_Expression expr;
  for (dimension_type i = original_space_dim; i-- > 0; )
    expr += num[i] * Variable(i);
  return point(expr, lcm);
}


Simplex_Status
primal_simplex(const Linear_System& cs,
	       Row& cost_function,
	       Generator& maximizing_point,
	       bool satisfiability_check) {
  assert(cost_function.size() <= cs.num_columns());
  // The space dimension of the solution to be computed.
  // Note: here we can not use method Constraint_System::space_dimension(),
  // because if the constraint system is NNC, then even the epsilon
  // dimension has to be interpreted as a normal dimension.
  const dimension_type space_dim = cs.num_columns() - 1;

  // Compute the initial tableau.
  Matrix tableau(0, 0);
  std::map<dimension_type, dimension_type> dim_map;
  Simplex_Status status = compute_tableau(cs, cost_function, tableau, dim_map);

  // Check for trivial cases.
  switch (status) {
  case UNFEASIBLE_PROBLEM:
    return status;
  case UNBOUNDED_PROBLEM:
    if (satisfiability_check)
      // A feasible point has to be returned: the origin.
      // Ensure the right space dimension is obtained.
      maximizing_point = point(0*Variable(space_dim-1));
    return status;
  case SOLVED_PROBLEM:
    // Check for the special case of an empty tableau,
    // in which case a maximizing solution is the origin.
    if (tableau.num_rows() == 0) {
      // Ensure the right space dimension is obtained.
      maximizing_point = point(0*Variable(space_dim-1));
      return status;
    }
    break;
  }

#if PPL_NOISY_SIMPLEX
  num_iterations = 0;
#endif

  // Actually solve the LP problem.
  std::vector<dimension_type> base(tableau.num_rows());
  // This will contain the new cost function for the 1st phase problem.
  Matrix costs(2, cost_function.size());
  costs[1] = cost_function;
  // Adds the necessary slack variables to get the 1st phase problem.
  prepare_first_phase(tableau, costs, base);
  // Solve the first phase of the primal simplex algorithm.
  bool first_phase_successful = compute_simplex(tableau, costs[0], base);
  
#if PPL_NOISY_SIMPLEX
  std::cout << "Primal Simplex: 1st phase ended at iteration "
	    << num_iterations << "." << std::endl;
#endif
  
  // If the first phase problem was not solved or if we found an optimum
  // value different from zero, then the origianl problem is unfeasible.
  if (!first_phase_successful || costs[0][0] != 0) 
    return UNFEASIBLE_PROBLEM;

  // The first phase has found a feasible solution. If only a satisfiability
  // check was requested, we can return that feasible solution.
  if (satisfiability_check) {
    maximizing_point = compute_generator(tableau, base, dim_map, space_dim);
    return SOLVED_PROBLEM;
  }

  // Here the first phase problem succeeded with optimum value zero.
  // Express the old cost function in terms of the computed base.
  Row& old_cost = costs[1];
  for (dimension_type i = tableau.num_rows(); i-- > 0; ) {
    const dimension_type base_i = base[i];
    if (old_cost[base_i] != 0)
      linear_combine(old_cost, tableau[i], base_i);
  }
  // Erase the slack variables.
  erase_slacks(tableau, costs, base);
  // Solve the second phase problem.
  bool second_phase_successful = compute_simplex(tableau, costs[0], base);
  
#if PPL_NOISY_SIMPLEX
  std::cout << "Primal Simplex: 2nd phase ended at iteration "
	    << num_iterations << "." << std::endl;
#endif

  if (second_phase_successful) {
    maximizing_point = compute_generator(tableau, base, dim_map, space_dim);
    return SOLVED_PROBLEM;
  }
  else
    return UNBOUNDED_PROBLEM;
}

} // namespace


namespace PPL = Parma_Polyhedra_Library;

Simplex_Status
PPL::Constraint_System::primal_simplex(Linear_Expression& cost_function,
				       Generator& maximizing_point) const {
  return ::primal_simplex(*this, cost_function, maximizing_point, false);
}


Simplex_Status
PPL::Constraint_System::primal_simplex(const Linear_Expression& expr,
				       const Optimization_Kind kind,
				       Coefficient& ext_n,
				       Coefficient& ext_d,
				       Generator& optimizing_point) const {
  // Strict inequality constraints are not supported.
  if (has_strict_inequalities())
    throw std::invalid_argument("PPL::Constraint_System::primal_simplex(): "
				"strict inequality constraints "
				"are not supported.");

  // Make sure the dimension of `expr' is not greater than
  // the dimension of the constraint system.
  if (space_dimension() < expr.space_dimension()) {
    std::ostringstream s;
    s << "PPL::Constraint_System::primal_simplex():" << std::endl
      << "this->space_dimension() == " << space_dimension()
      << ", " << "cost_function->space_dimension() == "
      << expr.space_dimension() << ".";
    throw std::invalid_argument(s.str());
  }

  // Work with a copy of `expr', since it may be modified.
  Linear_Expression cost_function = expr;

  // Minimization is obtained by negating the cost_function.
  if (kind == MINIMIZATION)
    for (dimension_type i = cost_function.size(); i-- > 0; ) 
      negate(cost_function[i]);

  Simplex_Status status
    = ::primal_simplex(*this, cost_function, optimizing_point, false);

  if (status == SOLVED_PROBLEM) {
    // Compute the optimal value of the cost function.
    ext_n = expr.inhomogeneous_term();
    for (dimension_type i = optimizing_point.space_dimension(); i-- > 0; )  
      ext_n += optimizing_point.coefficient(Variable(i))
	       * expr.coefficient(Variable(i));
    // Numerator and denominator should be coprime.
    normalize2(ext_n, optimizing_point.divisor(), ext_n, ext_d);

    // Check the computed generator for feasibility.
    assert(satisfies_all_constraints(optimizing_point));
  }
  return status;
}

bool
PPL::Constraint_System::is_satisfiable(Generator& feasible_point) const {
  // Strict inequality constraints are not supported.
  if (has_strict_inequalities())
    throw std::invalid_argument("PPL::Constraint_System::is_satisfiable(): "
				"strict inequality constraints "
				"are not supported.");

  Linear_Expression cost(0);
  Simplex_Status status = ::primal_simplex(*this, cost, feasible_point, true);

  // Check the computed generator for feasibility.
  assert(status != UNBOUNDED_PROBLEM);
  assert(status == UNFEASIBLE_PROBLEM
	 || satisfies_all_constraints(feasible_point));

  return (status == SOLVED_PROBLEM);
}
