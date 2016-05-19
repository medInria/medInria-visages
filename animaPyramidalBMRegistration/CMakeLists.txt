cmake_minimum_required(VERSION 3.1.0)

set(TARGET_NAME animaPyramidalBMRegistrationPlugin)

## #################################################################
## Setup version numbering
## #################################################################

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

## #################################################################
## Resolve dependencies
## #################################################################

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(ANIMA REQUIRED)
include(${ANIMA_USE_FILE})
include(ITKLibs)

## #################################################################
## Input
## #################################################################

list_source_files(${TARGET_NAME}
    .
    )

list_header_directories_to_include(${TARGET_NAME}
  ${${TARGET_NAME}_HEADERS}
  )

## #################################################################
## Build rules
## #################################################################

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

## #############################################################################
## Link
## #############################################################################

target_link_libraries(${TARGET_NAME}
  Qt5::Core
  dtkCoreSupport
  dtkLog
  medCoreLegacy
  medRegistration
  AnimaOptimizers
  ITKOptimizers
  ${ITKIO_LIBRARIES}
  ${ITK_TRANSFORM_LIBRARIES}
)

set_target_properties(${TARGET_NAME} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins_legacy
  )

if (WIN32)
  set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins_legacy
    )
endif()

## #################################################################
## Install rules
## #################################################################

install(TARGETS ${TARGET_NAME}
  RUNTIME DESTINATION plugins_legacy
  LIBRARY DESTINATION plugins_legacy
  ARCHIVE DESTINATION lib
  )
