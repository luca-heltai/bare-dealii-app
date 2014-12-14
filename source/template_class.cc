#include "template_class.h"

#include <iostream>

template <int dim>
void TemplateClass<dim>::run() {
  std::cout << "Empty class." << std::endl;
}

