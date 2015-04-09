cmake_minimum_required(VERSION 2.8.9)

project(animaRelaxometryPlugin)

## #############################################################################
## Setup version numbering
## #############################################################################

set(${PROJECT_NAME}_VERSION_MAJOR 1 CACHE STRING "${PROJECT_NAME} major version number." FORCE)
set(${PROJECT_NAME}_VERSION_MINOR 0 CACHE STRING "${PROJECT_NAME} minor version number." FORCE)
set(${PROJECT_NAME}_VERSION_BUILD 0 CACHE STRING "${PROJECT_NAME} build version number." FORCE)
set(${PROJECT_NAME}_VERSION
  "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_BUILD}")

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UP)
add_definitions(-D${PROJECT_NAME_UP}_VERSION="${${PROJECT_NAME}_VERSION}")


## #############################################################################
## Resolve dependencies
## #############################################################################

find_package(dtk REQUIRED)
include(${dtk_USE_FILE})
include(dtkPlugin)

find_package(MEDINRIA REQUIRED)
include(${MEDINRIA_USE_FILE})

find_package(ANIMA REQUIRED)
include (${ANIMA_USE_FILE})

## #############################################################################
## Qt Automoc
## #############################################################################

set(CMAKE_AUTOMOC ON)
#   Find includes in corresponding build (and source) directories
#   (nedded for generated files)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


## #############################################################################
## Input
## #############################################################################

set(${PROJECT_NAME}_HEADERS
  animaRelaxometryPlugin.h
  animaDESPOT1RelaxometryToolBox.h
  animaDESPOT1Relaxometry.h
  animaT2RelaxometryToolBox.h
  animaT2Relaxometry.h
  )

set(${PROJECT_NAME}_SOURCES
  animaRelaxometryPlugin.cpp
  animaDESPOT1RelaxometryToolBox.cpp
  animaDESPOT1Relaxometry.cpp
  animaT2RelaxometryToolBox.cpp
  animaT2Relaxometry.cpp
  )


## #############################################################################
## Build rules
## #############################################################################


add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  )


## #############################################################################
## Links.
## #############################################################################

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkLog
  dtkCore
  medCore
  ${ITKIO_LIBRARIES}
  AnimaOptimizers
  ${NLOPT_LIBRARY}
  )


## #############################################################################
## Install rules
## #############################################################################

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION plugins
  LIBRARY DESTINATION plugins
  ARCHIVE DESTINATION lib
  )

