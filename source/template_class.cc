#include "template_class.h"

#include <iostream>

template <int dim>
void TemplateClass<dim>::run() {
  std::cout << "Empty class." << std::endl;
}

// Explicit instantiations
template class TemplateClass<1>;
template class TemplateClass<2>;
template class TemplateClass<3>;
