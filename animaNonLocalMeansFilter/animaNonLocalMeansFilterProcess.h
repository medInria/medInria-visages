#pragma once

#include <medAbstractImageDenoisingProcess.h>
#include <medAbstractData.h>

#include <itkProcessObject.h>
#include <itkSmartPointer.h>

#include "animaNonLocalMeansFilterPluginExport.h"
#include <medIntParameter.h>
#include <medDoubleParameter.h>
#include <medBoolParameter.h>

class ANIMANONLOCALMEANSFILTERPLUGIN_EXPORT animaNonLocalMeansFilterProcess : public medAbstractImageDenoisingProcess
{
    Q_OBJECT

public:
    animaNonLocalMeansFilterProcess(QObject* parent = NULL);
    virtual ~animaNonLocalMeansFilterProcess();

    static void eventCallback(itk::Object *caller, const itk::EventObject& event, void *clientData)
    {
        medAbstractImageDenoisingProcess * source = reinterpret_cast<medAbstractImageDenoisingProcess *>(clientData);
        itk::ProcessObject * processObject = (itk::ProcessObject*) caller;
        source->progression()->setValue(processObject->GetProgress() * 100);
    }

    virtual medAbstractJob::medJobExitStatus run();
    virtual void cancel();

    virtual QString caption() const;
    virtual QString description() const;

    // Parameters setting
    medIntParameter *patchHalfSize() const;
    medIntParameter *searchNeighborhood() const;
    medIntParameter *searchStepSize() const;

    medDoubleParameter *weightThreshold() const;
    medDoubleParameter *betaParameter() const;
    medDoubleParameter *meanMinThreshold() const;
    medDoubleParameter *varMinThreshold() const;

    medBoolParameter *temporalImage() const;
    int weightMethod() const;

public slots:
    void setWeightedMethod(int value);

private:
    template <class PixelType>
    medAbstractJob::medJobExitStatus switchDimension(unsigned int const nbDimension);
    template <class ImageType>
    medAbstractJob::medJobExitStatus switchTemporal();
    template <class ImageType>
    medAbstractJob::medJobExitStatus updateNLMeans();
    template <class ImageType>
    medAbstractJob::medJobExitStatus updateNLMeansTemporal();

    itk::SmartPointer<itk::ProcessObject> m_denoisingfilter;
    medIntParameter *m_PatchHalfSize;
    medIntParameter *m_SearchNeighborhood;
    medIntParameter *m_SearchStepSize;
    medDoubleParameter *m_WeightThreshold;
    medDoubleParameter *m_BetaParameter;
    medDoubleParameter *m_MeanMinThreshold;
    medDoubleParameter *m_VarMinThreshold;
    int m_WeightedMethod;
    medBoolParameter *m_TemporalImage;
};

inline medAbstractImageDenoisingProcess* animaNonLocalMeansFilterProcessCreator()
{
    return new animaNonLocalMeansFilterProcess();
}
