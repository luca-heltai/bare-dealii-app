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

#ifndef __lh_laplacian_h
#define __lh_laplacian_h

#include <iostream>

#include "utilities.h"
#include "parameter_acceptor.h"
#include "parsed_grid_generator.h"
#include "parsed_finite_element.h"
#include "parsed_function.h"
#include "error_handler.h"

template <int dim, int spacedim=dim>
class Laplacian : public ParameterAcceptor
{
public:
  Laplacian();

  virtual void declare_parameters(ParameterHandler &prm);

  void run();

private:
  unsigned int initial_refinement;
  unsigned int n_cycles;
  std::vector<unsigned int> dirichlet_ids;

  ParsedGridGenerator<dim,spacedim> pgg;
  ParsedFiniteElement<dim,spacedim> pfe;
  ParsedFunction<spacedim> permeability;
  ParsedFunction<spacedim> dirichlet_bc;
  ParsedFunction<spacedim> forcing_term;
  ParsedFunction<spacedim> exact_solution;
  ErrorHandler<1> eh;
};

#endif
