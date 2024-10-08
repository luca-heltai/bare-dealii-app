// ---------------------------------------------------------------------
//
// Copyright (C) 2024 by Luca Heltai
//
// This file is part of the bare-dealii-app application, based on the deal.II library.
//
//  The bare-dealii-app application is free software; you can use it, redistribute it,
//  and/or modify it under the terms of the Apache-2.0 License WITH
//  LLVM-exception as published by the Free Software Foundation; either version
//  3.0 of the License, or (at your option) any later version. The full text of
//  the license can be found in the file LICENSE at the top level of the 
//  bare-dealii-app distribution. 
// 
// ---------------------------------------------------------------------


#ifndef dealii_laplacian_h
#define dealii_laplacian_h

#include <deal.II/dofs/dof_handler.h>

#include <deal.II/fe/fe_q.h>

#include <deal.II/grid/tria.h>

#include <deal.II/lac/affine_constraints.h>
#include <deal.II/lac/dynamic_sparsity_pattern.h>
#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/vector.h>

#include <fstream>

using namespace dealii;

template <int dim>
class Laplacian
{
public:
  Laplacian();

  void
  run();

private:
  void
  setup_system();
  void
  assemble_system();
  void
  solve();
  void
  refine_grid();
  void
  output_results(const unsigned int cycle) const;

  Triangulation<dim> triangulation;

  FE_Q<dim>       fe;
  DoFHandler<dim> dof_handler;


  AffineConstraints<double> constraints;

  SparseMatrix<double> system_matrix;
  SparsityPattern      sparsity_pattern;

  Vector<double> solution;
  Vector<double> system_rhs;
};

#endif