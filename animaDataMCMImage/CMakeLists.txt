cmake_minimum_required(VERSION 2.8.9)

project(animaDataMCMImagePlugin)

## #############################################################################
## Setup version numbering
## #############################################################################

set(${PROJECT_NAME}_VERSION_MAJOR ${medInria_VERSION_MAJOR} CACHE STRING "${PROJECT_NAME} major version number." FORCE)
set(${PROJECT_NAME}_VERSION_MINOR ${medInria_VERSION_MINOR} CACHE STRING "${PROJECT_NAME} minor version number." FORCE)
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

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(ANIMA REQUIRED)
include(${ANIMA_USE_FILE})

## #############################################################################
## Qt Automoc
## #############################################################################

set(CMAKE_AUTOMOC ON)
#   Find includes in corresponding build (and source) directories
#   (needed for generated files)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

## #############################################################################
## List Sources
## #############################################################################

INCLUDE_DIRECTORIES(
  datas
  interactors
  readers
  writers
  )

set(${PROJECT_NAME}_HEADERS
  animaDataMCMImagePlugin.h
  datas/animaDataMCMImageFloat3.h
  datas/animaDataMCMImageDouble3.h
  readers/animaDataMCMImageReader.h
  writers/animaDataMCMImageWriterBase.h
  writers/animaMetaDataMCMImageWriter.h
  writers/animaNiftiDataMCMImageWriter.h
  interactors/animaMCMITKToVTKFilter.h
  interactors/animaMCMITKToVTKFilter.hxx
  interactors/vtkMCMGlyph.h
  interactors/vtkMCMSource.h
  interactors/vtkMCMManager.h
  interactors/vtkMCMVisuManager.h
  interactors/animaDataMCMImageVtkViewInteractor.h
  )

set(${PROJECT_NAME}_SOURCES
  animaDataMCMImagePlugin.cpp
  datas/animaDataMCMImageFloat3.cpp
  datas/animaDataMCMImageDouble3.cpp
  readers/animaDataMCMImageReader.cpp
  writers/animaDataMCMImageWriterBase.cpp
  writers/animaMetaDataMCMImageWriter.cpp
  writers/animaNiftiDataMCMImageWriter.cpp
  interactors/vtkMCMGlyph.cxx
  interactors/vtkMCMSource.cxx
  interactors/vtkMCMManager.cxx
  interactors/vtkMCMVisuManager.cxx
  interactors/animaDataMCMImageVtkViewInteractor.cpp
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
  dtkCore
  dtkLog
  ${ITKIO_LIBRARIES}
  medCore
  medLog
  medVtkInria
  vtkCommon
  vtkRendering
  AnimaSpecialFunctions
  )

## #############################################################################
## Install rules
## #############################################################################

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION plugins
  LIBRARY DESTINATION plugins
  ARCHIVE DESTINATION lib
  )
