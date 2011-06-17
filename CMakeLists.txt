### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Sep 21 14:48:02 2009 (+0200)
## Version: $Id$
## Last-Updated: Thu Jun 17 09:42:14 2010 (+0200)
##           By: Julien Wintz
##     Update #: 25
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

cmake_minimum_required(VERSION 2.8.1)

project(medinria-plugins)

## #################################################################
## Setup version numbering
## #################################################################

set(${PROJECT_NAME}_VERSION_MAJOR 0 CACHE STRING "${PROJECT_NAME} major
version number.")
set(${PROJECT_NAME}_VERSION_MINOR 1 CACHE STRING "${PROJECT_NAME} minor
version number.")
set(${PROJECT_NAME}_VERSION_BUILD 0 CACHE STRING "${PROJECT_NAME} build
version number.")
set(${PROJECT_NAME}_VERSION
	  "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_BUILD}")

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUILD)

## #################################################################
## Dashboard settings
## #################################################################

enable_testing()

mark_as_advanced(DART_ROOT)

include(Dart)

## #################################################################
## Input
## #################################################################

set(DEPENDS_ON_DTK 1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
include(pack)

option(MEDINRIA_BUILD_VISTALDATAIMAGE_PLUGIN     "Build vistalDataImage plugin" "ON")
option(MEDINRIA_BUILD_VISTALDATAIMAGEREADER_PLUGIN     "Build vistalDataImageReader plugin" "ON")
option(MEDINRIA_BUILD_VISTALDATAIMAGEWRITER_PLUGIN     "Build vistalDataImageWriter plugin" "ON")
option(MEDINRIA_BUILD_VISTALDATAIMAGECONVERTER_PLUGIN     "Build vistalDataImageConverter plugin" "ON")
option(MEDINRIA_BUILD_VISTALPROCESSDENOISING_PLUGIN     "Build vistalProcessDenoising plugin" "ON")
option(MEDINRIA_BUILD_QTSHANOIRDATASOURCE_PLUGIN     "Build qtshanoirDataSource plugin" "OFF")
option(MEDINRIA_BUILD_QTDCMDATASOURCE_PLUGIN     "Build qtdcmDataSource plugin" "OFF")
option(BUILD_DOCUMENTATION "Build documentation")

if (MEDINRIA_BUILD_VISTALDATAIMAGE_PLUGIN)
    add_subdirectory(vistalDataImage)
endif()

if (MEDINRIA_BUILD_VISTALDATAIMAGEREADER_PLUGIN)
    add_subdirectory(vistalDataImageReader)
endif()

if (MEDINRIA_BUILD_VISTALDATAIMAGEWRITER_PLUGIN)
    add_subdirectory(vistalDataImageWriter)
endif()

if (MEDINRIA_BUILD_VISTALDATAIMAGECONVERTER_PLUGIN)
    add_subdirectory(vistalDataImageConverter)
endif()

if (MEDINRIA_BUILD_VISTALDATAIMAGECONVERTER_PLUGIN)    
    set(MEDINRIA_REQUIRES_ITK TRUE)
endif()

if (MEDINRIA_BUILD_VISTALPROCESSDENOISING_PLUGIN)
    add_subdirectory(vistalProcessDenoising)
endif()

if (MEDINRIA_BUILD_QTSHANOIRDATASOURCE_PLUGIN)
    add_subdirectory(qtshanoirDataSource)
endif()

if (MEDINRIA_BUILD_QTDCMDATASOURCE_PLUGIN)
    add_subdirectory(qtdcmDataSource)
endif()

if(BUILD_DOCUMENTATION)
  add_subdirectory(doc)
endif(BUILD_DOCUMENTATION)

## #################################################################
## Build settings
## #################################################################

# On Visual Studio 8 MS deprecated C. This removes all 1.276E1265 security warnings
if(WIN32)
  if(NOT BORLAND)
    if(NOT CYGWIN)
      if(NOT MINGW)
        if(NOT ITK_ENABLE_VISUAL_STUDIO_DEPRECATED_C_WARNINGS)
          add_definitions(
            -D_CRT_FAR_MAPPINGS_NO_DEPRECATE
            -D_CRT_IS_WCTYPE_NO_DEPRECATE
            -D_CRT_MANAGED_FP_NO_DEPRECATE
            -D_CRT_NONSTDC_NO_DEPRECATE
            -D_CRT_SECURE_NO_DEPRECATE
            -D_CRT_SECURE_NO_DEPRECATE_GLOBALS
            -D_CRT_SETERRORMODE_BEEP_SLEEP_NO_DEPRECATE
            -D_CRT_TIME_FUNCTIONS_NO_DEPRECATE
            -D_CRT_VCCLRIT_NO_DEPRECATE
            -D_SCL_SECURE_NO_DEPRECATE
            )
        endif(NOT ITK_ENABLE_VISUAL_STUDIO_DEPRECATED_C_WARNINGS)
      endif(NOT MINGW)
    endif(NOT CYGWIN)
  endif(NOT BORLAND)
endif(WIN32)
