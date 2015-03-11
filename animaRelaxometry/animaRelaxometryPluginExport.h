/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#ifdef WIN32
    #ifdef animaRelaxometryPlugin_EXPORTS
        #define ANIMARELAXOMETRYPLUGIN_EXPORT __declspec(dllexport) 
    #else
        #define ANIMARELAXOMETRYPLUGIN_EXPORT __declspec(dllimport) 
    #endif
#else
    #define ANIMARELAXOMETRYPLUGIN_EXPORT
#endif


