##
#  CMake script for the step-1 tutorial program:
##

# Set the name of the project and target:
SET(TARGET empty)

# Specify which file contains the main() function
SET(_main source/main.cc)

file(GLOB _files source/*cc)

# Declare all source files the target consists of:
SET(TARGET_SRC
    ${_files}
  )

LIST(REMOVE_ITEM _files
  ${CMAKE_CURRENT_SOURCE_DIR}/${_main}
)

INCLUDE_DIRECTORIES(include)

# Usually, you will not need to modify anything beyond this point...

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

FIND_PACKAGE(deal.II 8.3 REQUIRED
  HINTS ${deal.II_DIR} ${DEAL_II_DIR} ../ ../../ $ENV{DEAL_II_DIR}
  )
IF(NOT ${deal.II_FOUND})
  MESSAGE(FATAL_ERROR "\n"
    "*** Could not locate deal.II. ***\n\n"
    "You may want to either pass a flag -DDEAL_II_DIR=/path/to/deal.II to cmake\n"
    "or set an environment variable \"DEAL_II_DIR\" that contains this path."
    )
ENDIF()

DEAL_II_INITIALIZE_CACHED_VARIABLES()
PROJECT(${TARGET})

ADD_LIBRARY(${TARGET}-lib SHARED ${_files})
ADD_EXECUTABLE(${TARGET} ${_main})
TARGET_LINK_LIBRARIES(${TARGET} ${TARGET}-lib)
SET(TEST_LIBRARIES_RELEASE ${TARGET}-lib)
DEAL_II_SETUP_TARGET(${TARGET} RELEASE)
DEAL_II_SETUP_TARGET(${TARGET}-lib RELEASE)

ADD_LIBRARY(${TARGET}-lib.g SHARED ${_files})
ADD_EXECUTABLE(${TARGET}.g ${_main})
TARGET_LINK_LIBRARIES(${TARGET}.g ${TARGET}-lib.g)
SET(TEST_LIBRARIES_DEBUG ${TARGET}-lib.g)
DEAL_II_SETUP_TARGET(${TARGET}.g DEBUG)
DEAL_II_SETUP_TARGET(${TARGET}-lib.g DEBUG)

ADD_SUBDIRECTORY(tests)
