#pragma once

#ifdef WIN32
    #ifdef animaDataMCMImagePlugin_EXPORTS
        #define ANIMADATAMCMIMAGEPLUGIN_EXPORT __declspec(dllexport)
    #else
        #define ANIMADATAMCMIMAGEPLUGIN_EXPORT __declspec(dllimport)
    #endif
#else
    #define ANIMADATAMCMIMAGEPLUGIN_EXPORT
#endif
