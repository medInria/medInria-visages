# - Try to find MSTOOLS
# Once done this will define
#
#  MSTOOLS_FOUND - system has MSTOOLS
#  MSTOOLS_INCLUDE_DIR - the MSTOOLS include directory
#  MSTOOLS_LIBRARIES - Link these to use MSTOOLS
#  MSTOOLS_NEED_PREFIX - this is set if the functions are prefixed with BZ2_

#=============================================================================
# Copyright 2006-2009 Kitware, Inc.
# Copyright 2006 Alexander Neundorf <neundorf@kde.org>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

FIND_PATH( ${MSTOOLS_DIR} Libraries/Common/mstoolsBaseClass.h
  PATHS 
)

FIND_PATH(MSTOOLS_COMMON_DIR mstoolsBaseClass.h ${MSTOOLS_DIR}/Libraries/Common)
FIND_PATH(MSTOOLS_CLASSIFICATION_DIR mstoolsBaseClass.h ${MSTOOLS_DIR}/Libraries/Classification)

SET(MSTOOLS_INCLUDE_DIR ${MSTOOLS_COMMON_DIR} ${MSTOOLS_CLASSIFICATION_DIR})


FIND_LIBRARY(MSTOOLS_LIBRARIES mstools  )

# handle the QUIETLY and REQUIRED arguments and set MSTOOLS_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE("${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake")
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MSTOOLS DEFAULT_MSG MSTOOLS_LIBRARIES MSTOOLS_INCLUDE_DIR)

IF (MSTOOLS_FOUND)
   INCLUDE(CheckLibraryExists)
   CHECK_LIBRARY_EXISTS(${MSTOOLS_LIBRARIES} readAsFloat "" MSTOOLS_NEED_PREFIX)
ENDIF (MSTOOLS_FOUND)

MARK_AS_ADVANCED(MSTOOLS_INCLUDE_DIR MSTOOLS_LIBRARIES)

