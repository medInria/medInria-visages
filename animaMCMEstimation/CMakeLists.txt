set(TARGET_NAME animaMCMEstimationPlugin)

## #############################################################################
## Resolve dependencies
## #############################################################################

find_package(ANIMA_PRIVATE REQUIRED)
include(${ANIMA_PRIVATE_USE_FILE})
include(ITKLibs)

find_package(ITK)
include(${ITK_USE_FILE})

## #############################################################################
## List Sources
## #############################################################################

list_source_files(${TARGET_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

list_header_directories_to_include(${TARGET_NAME}
  ${${TARGET_NAME}_HEADERS}
  )

## #############################################################################
## add library
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
  Qt5::Widgets
  dtkCore
  dtkCoreSupport
  AnimaMCM
  AnimaRandom
  AnimaPrivateOptimizers
  AnimaSpecialFunctions
  ${NLOPT_LIBRARY}
  ITKOptimizers
  ${ITKIO_LIBRARIES}
  medCore
  medCoreLegacy
  medWidgets
  )

set_target_properties(${TARGET_NAME} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
  )

if (WIN32)
  set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
    )
endif()

## #################################################################
## Install rules
## #################################################################

install(TARGETS ${TARGET_NAME}
  RUNTIME DESTINATION plugins
  LIBRARY DESTINATION plugins
  ARCHIVE DESTINATION lib)

