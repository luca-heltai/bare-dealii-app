// ---------------------------------------------------------------------
//
// Copyright (C) 2024 by Luca Heltai
//
// This file is part of the bare-dealii-app application, based on the 
// deal.II library.
//
// The bare-dealii-app application is free software; you can use it, 
// redistribute it, and/or modify it under the terms of the Apache-2.0 License
// WITH LLVM-exception as published by the Free Software Foundation; either 
// version 3.0 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE.md
// at the top level of the bare-dealii-app distribution. 
// 
// ---------------------------------------------------------------------

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/tria.h>

#include <gtest/gtest.h>

using namespace dealii;

template <class D>
class SimpleClass : public ::testing::Test
{
public:
  Triangulation<D::value> tria;

protected:
  SimpleClass()
  {
    GridGenerator::hyper_cube(tria);
    tria.refine_global(1);
  }
};

using dimensions = ::testing::Types<std::integral_constant<unsigned int, 1>,
                                    std::integral_constant<unsigned int, 2>,
                                    std::integral_constant<unsigned int, 3>>;

TYPED_TEST_SUITE(SimpleClass, dimensions, );



TYPED_TEST(SimpleClass, CheckSize) // NOLINT
{
  auto n_cells = std::pow(2.0, this->tria.dimension);

  ASSERT_EQ(n_cells, this->tria.n_active_cells());
}
