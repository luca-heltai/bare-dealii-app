//-------------------------------------------------------
//
//    Copyright (C) 2014 by Luca Heltai
//
//    This file is subject to LGPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file LICENCE for the  text  and
//    further information on this license.
//
//-------------------------------------------------------

#include <iostream>

#include <deal.II/grid/tria.h>
#include <deal.II/dofs/dof_handler.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/dofs/dof_accessor.h>
#include <deal.II/fe/fe_q.h>
#include <deal.II/dofs/dof_tools.h>
#include <deal.II/fe/fe_values.h>
#include <deal.II/base/quadrature_lib.h>
#include <deal.II/base/function.h>
#include <deal.II/numerics/vector_tools.h>
#include <deal.II/numerics/matrix_tools.h>
#include <deal.II/lac/sparse_direct.h>
#include <deal.II/lac/vector.h>
#include <deal.II/lac/full_matrix.h>
#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/compressed_sparsity_pattern.h>
#include <deal.II/lac/solver_cg.h>
#include <deal.II/lac/precondition.h>
#include <deal.II/numerics/data_out.h>
#include <fstream>
#include <iostream>

#include "laplacian.h"

#include <deal.II/numerics/matrix_tools.h>


template <int dim, int spacedim>
Laplacian<dim,spacedim>::Laplacian() :
  ParameterAcceptor("Global parameters"),
  pgg("Grid"),
  pfe("Finite element"),
  permeability("Permeability coefficients"),
  dirichlet_bc("Dirichlet boundary conditions"),
  forcing_term("Forcing term"),
  exact_solution("Exact solution"),
  eh("Error handler")
{}

template <int dim, int spacedim>
void Laplacian<dim,spacedim>::declare_parameters(ParameterHandler &prm)
{

  add_parameter(prm, &n_cycles, "Number of cycles", "4",
                Patterns::Integer());

  add_parameter(prm, &initial_refinement, "Initial refinement", "1",
                Patterns::Integer());

  add_parameter(prm, &dirichlet_ids, "Dirichlet boundary ids", "0",
                Patterns::List(Patterns::Integer()));

};



template <int dim, int spacedim>
void Laplacian<dim,spacedim>::run()
{

  SparsityPattern      sparsity;
  SparseMatrix<double> matrix;

  Vector<double>       solution;
  Vector<double>       rhs;

  auto tria = pgg.serial();
  tria->refine_global(initial_refinement);

  auto fe = pfe();
  DoFHandler<dim,spacedim> dh(*tria);

  for (unsigned int cycle=0; cycle<n_cycles; ++cycle)
    {
      // After the first round, make an additional refinement
      if (cycle>0)
        tria->refine_global(1);

      dh.distribute_dofs(*fe);

      ConstraintMatrix     constraints;
      // Initialize matrix and vectors
      DynamicSparsityPattern d_sparsity(dh.n_dofs());
      DoFTools::make_sparsity_pattern (dh, d_sparsity);
      sparsity.copy_from(d_sparsity);
      matrix.reinit (sparsity);

      solution.reinit(dh.n_dofs());
      rhs.reinit(dh.n_dofs());

      // Add boundary conditions for each Dirichlet id
      for (auto id : dirichlet_ids)
        VectorTools::interpolate_boundary_values(dh, id,
                                                 dirichlet_bc, constraints);

      constraints.close();

      QGauss<dim> quad(2*fe->degree+1);
      MatrixCreator::create_laplace_matrix (StaticMappingQ1<dim,spacedim>::mapping,
                                            dh, quad, matrix,
                                            forcing_term, rhs, &permeability, constraints);

      SparseDirectUMFPACK inverse;
      inverse.factorize(matrix);
      inverse.vmult(solution, rhs);
      constraints.distribute(solution);

      DataOut<dim,DoFHandler<dim,spacedim> > data_out;
      data_out.attach_dof_handler (dh);
      data_out.add_data_vector (solution, "solution");
      data_out.build_patches ();
      std::stringstream name;
      name << "solution_" << cycle << ".vtu";
      std::ofstream output (name.str().c_str());
      data_out.write_vtu (output);
      eh.error_from_exact(dh, solution, exact_solution);
    }
  eh.output_table();
}


template class Laplacian<1,1>;
template class Laplacian<2,2>;
template class Laplacian<3,3>;
