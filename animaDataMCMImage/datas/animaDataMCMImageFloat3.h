#pragma once

#include <medAbstractTypedDiffusionModelImageData.h>

#include <animaDataMCMImagePluginExport.h>

class animaDataMCMImageFloat3Private;

class ANIMADATAMCMIMAGEPLUGIN_EXPORT animaDataMCMImageFloat3 : public medAbstractTypedDiffusionModelImageData<3,float>
{
    Q_OBJECT
    MED_DATA_INTERFACE("Anima MCM Image (float3)",
                       "Anima MCM Image (float3)")
public:
             animaDataMCMImageFloat3();
    virtual ~animaDataMCMImageFloat3();

    static bool registered();

public slots:
    // derived from dtkAbstractData
    void *output();
    void *data();
    void setData(void* data);
    
public:
    // derived from medAbstractImageData
    int xDimension();
    int yDimension();
    int zDimension();
 
private:
    animaDataMCMImageFloat3Private *d;
};
