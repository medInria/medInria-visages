#pragma once

#include <animaMultiCompartmentModel.h>
#include <medAbstractTypedDiffusionModelImageData.h>
#include <animaDataMCMImagePluginExport.h>

class animaDataMCMImageDouble3Private;

class ANIMADATAMCMIMAGEPLUGIN_EXPORT animaDataMCMImageDouble3 : public medAbstractTypedDiffusionModelImageData<3,double>
{
    Q_OBJECT
    MED_DATA_INTERFACE("Anima MCM Image (double3)",
                       "Anima MCM Image (double3)")
public:
             animaDataMCMImageDouble3();
    virtual ~animaDataMCMImageDouble3();

    static bool registered();

    typedef anima::MultiCompartmentModel MCModelType;
    typedef MCModelType::Pointer MCModelPointer;

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
    animaDataMCMImageDouble3Private *d;
};
