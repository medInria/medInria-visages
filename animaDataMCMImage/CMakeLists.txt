cmake_minimum_required(VERSION 3.1.0)

set(TARGET_NAME animaDataMCMImagePlugin)

## #############################################################################
## Setup version numbering
## #############################################################################

set(${TARGET_NAME}_VERSION_MAJOR 3 CACHE STRING "${TARGET_NAME} major version number." FORCE)
set(${TARGET_NAME}_VERSION_MINOR 0 CACHE STRING "${TARGET_NAME} minor version number." FORCE)
set(${TARGET_NAME}_VERSION_BUILD 0 CACHE STRING "${TARGET_NAME} build version number." FORCE)
set(${TARGET_NAME}_VERSION
  "${${TARGET_NAME}_VERSION_MAJOR}.${${TARGET_NAME}_VERSION_MINOR}.${${TARGET_NAME}_VERSION_BUILD}")

mark_as_advanced(${TARGET_NAME}_VERSION_MAJOR)
mark_as_advanced(${TARGET_NAME}_VERSION_MINOR)
mark_as_advanced(${TARGET_NAME}_VERSION_BUILD)

string(TOUPPER ${TARGET_NAME} TARGET_NAME_UP)
add_definitions(-D${TARGET_NAME_UP}_VERSION="${${TARGET_NAME}_VERSION}")

## #############################################################################
## Resolve dependencies
## #############################################################################

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(ANIMA_PRIVATE REQUIRED)
include(${ANIMA_PRIVATE_USE_FILE})
include(ITKLibs)

## #############################################################################
## List Sources
## #############################################################################

list_source_files(${TARGET_NAME}
  .
  datas
  interactors
  readers
  writers
  )

list_header_directories_to_include(${TARGET_NAME}
  ${${TARGET_NAME}_HEADERS}
  )

## #############################################################################
## Build rules
## #############################################################################

add_library(${TARGET_NAME} SHARED
  ${${TARGET_NAME}_CFILES}
  ${${TARGET_NAME}_QRC}
  )

## #############################################################################
## include directories.
## #############################################################################

target_include_directories(${TARGET_NAME}
  PRIVATE ${${TARGET_NAME}_INCLUDE_DIRS}
  )
# PRIVATE because plugins are not supposed to be used somewhere else

## #############################################################################
## Link
## #############################################################################

target_link_libraries(${TARGET_NAME}
  Qt5::Core
  dtkCoreSupport
  dtkLog
  ${ITKIO_LIBRARIES}
  medCoreLegacy
  medLog
  medVtkInria
  vtkCommonCore
  vtkInteractionStyle
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingOpenGL
  vtkRenderingVolumeOpenGL
  AnimaMCM
  AnimaMCMPrivate
  AnimaSpecialFunctions
  ${TinyXML2_LIBRARY}
  )

set_target_properties(${TARGET_NAME} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins_legacy
  )

if (WIN32)
  set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins_legacy
    )
endif()

## #############################################################################
## Install rules
## #############################################################################

install(TARGETS ${TARGET_NAME}
  RUNTIME DESTINATION plugins
  LIBRARY DESTINATION plugins
  ARCHIVE DESTINATION lib
  )
