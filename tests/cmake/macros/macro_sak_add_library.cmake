#####
##
## Copyright (C) 2012 by the deal.II authors
##
## This file is part of the deal.II library.
##
## <TODO: Full License information>
## This file is dual licensed under QPL 1.0 and LGPL 2.1 or any later
## version of the LGPL license.
##
## Author: Matthias Maier <matthias.maier@iwr.uni-heidelberg.de>
##
#####

#
# A small wrapper around ADD_LIBRARY that will define a target for each
# build type specified in DEAL_II_BUILD_TYPES
#
# It is assumed that the desired compilation configuration is set via
#   DEAL_II_SHARED_LINKER_FLAGS_${build}
#   DEAL_II_CXX_FLAGS_${build}
#   DEAL_II_DEFINITIONS_${build}
#
# as well as the global (for all build types)
#   CMAKE_SHARED_LINKER_FLAGS
#   CMAKE_CXX_FLAGS
#   DEAL_II_DEFINITIONS
#

MACRO(SAK_ADD_LIBRARY _library)

  FOREACH(_build ${DEAL_II_BUILD_TYPES})
    STRING(TOLOWER ${_build} _build_lowercase)

    ADD_LIBRARY(${_library}.${_build_lowercase}
      ${ARGN}
      )

    TARGET_LINK_LIBRARIES(
	${_library}.${_build_lowercase}
	${DEAL_II_LIBRARIES_${_build}}
	${SUNDIALS_LIBRARIES}
	${OpenCASCADE_LIBRARIES} 
	${GSL_LIBRARIES}
    )

    SET_TARGET_PROPERTIES(${_library}.${_build_lowercase} PROPERTIES
      LINK_FLAGS "${DEAL_II_SHARED_LINKER_FLAGS_${_build}}"
      COMPILE_DEFINITIONS "${DEAL_II_DEFINITIONS};${DEAL_II_DEFINITIONS_${_build}}"
      COMPILE_FLAGS "${DEAL_II_CXX_FLAGS_${_build}}"
      LINKER_LANGUAGE "CXX"
      )
    
    INSTALL(TARGETS ${_library}.${_build_lowercase} LIBRARY DESTINATION lib)
    SET(SAK_TARGETS ${SAK_TARGETS} ${_library}.${_build_lowercase})

  ENDFOREACH()

ENDMACRO()
