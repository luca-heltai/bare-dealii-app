//--------------------------------------------------------------------
//
//    Copyright (C) 2005 by Luca Heltai
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//--------------------------------------------------------------------

#ifndef __template_class_h__
#define __template_class_h__

// Grid libraries
#include <deal.II/grid/tria.h>

// C++ libraries
#include <fstream>

/**
 * Empty container class, to use as a template.
 *
 * @author Luca Heltai, 2005-2014
 */
template <int dim>
class TemplateClass {
 public:
  void run();
  
 private:
  Triangulation<dim> tria;
};

#endif
