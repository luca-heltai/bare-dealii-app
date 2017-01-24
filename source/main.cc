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

#include "laplacian.h"
#include <deal.II/base/utilities.h>

int main (int argc, char **argv)
{
  try
    {
      Utilities::MPI::MPI_InitFinalize mpi_initialization(argc, argv,
                                                          numbers::invalid_unsigned_int);
      Laplacian<DIMENSION> problem;
      std::string fname = "parameters_"+std::to_string(DIMENSION) + "d.prm";
      ParameterAcceptor::initialize(fname, "used_"+fname);
      problem.run();

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
