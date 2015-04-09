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


#include "utilities.h"
#include "parameter_acceptor.h"
#include "parsed_grid_generator.h"
#include "parsed_finite_element.h"
#include "parsed_function.h"

#include <deal.II/numerics/matrix_tools.h>

class Parameters : public ParameterAcceptor
{
public:
  Parameters() : ParameterAcceptor("Global parameters") {};


  virtual void declare_parameters(ParameterHandler &prm)
  {
    add_parameter(prm, &refinement, "Refinement level", "5",
                  Patterns::Integer());
    add_parameter(prm, &dirichlet_id, "Dirichlet id", "0",
                  Patterns::Integer());
  };

  unsigned int refinement;
  unsigned int dirichlet_id;
};

int main ()
{
  try
    {
      ParsedGridGenerator<2> pgg("Grid");
      ParsedFiniteElement<2,2> pfe("Finite Element");
      ParsedFunction<2> permeability("Permeability coefficients");
      ParsedFunction<2> dirichlet_bc("Dirichlet boundary conditions");
      ParsedFunction<2> forcing_term("Forcing term");

      Parameters p;

      ParameterAcceptor::initialize("parameters.prm");

      SparsityPattern      sparsity;
      SparseMatrix<double> matrix;
      ConstraintMatrix     constraints;

      Vector<double>       solution;
      Vector<double>       rhs;

      auto tria = pgg.serial();
      tria->refine_global(p.refinement);

      auto fe = pfe();
      DoFHandler<2> dh(*tria);
      dh.distribute_dofs(*fe);

      // Initialize matrix and vectors
      DynamicSparsityPattern d_sparsity(dh.n_dofs());
      DoFTools::make_sparsity_pattern (dh, d_sparsity);
      sparsity.copy_from(d_sparsity);
      matrix.reinit (sparsity);

      solution.reinit(dh.n_dofs());
      rhs.reinit(dh.n_dofs());

      // Add boundary conditions
      VectorTools::interpolate_boundary_values(dh, p.dirichlet_id,
                                               dirichlet_bc, constraints);

      constraints.close();

      QGauss<2> quad(2*fe->degree+1);
      MatrixCreator::create_laplace_matrix (StaticMappingQ1<2>::mapping,
                                            dh, quad, matrix,
                                            forcing_term, rhs, &permeability, constraints);

      SparseDirectUMFPACK inverse;
      inverse.factorize(matrix);
      inverse.vmult(solution, rhs);
      constraints.distribute(solution);

      DataOut<2> data_out;
      data_out.attach_dof_handler (dh);
      data_out.add_data_vector (solution, "solution");
      data_out.build_patches ();
      std::ofstream output ("solution.vtu");
      data_out.write_vtu (output);
    }
  catch (std::exception &exc)
    {
      std::cerr << std::endl << std::endl
                << "----------------------------------------------------"
                << std::endl;
      std::cerr << "Exception on processing: " << std::endl
                << exc.what() << std::endl
                << "Aborting!" << std::endl
                << "----------------------------------------------------"
                << std::endl;

      return 1;
    }
  catch (...)
    {
      std::cerr << std::endl << std::endl
                << "----------------------------------------------------"
                << std::endl;
      std::cerr << "Unknown exception!" << std::endl
                << "Aborting!" << std::endl
                << "----------------------------------------------------"
                << std::endl;
      return 1;
    };

  return 0;
}
