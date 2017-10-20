#pragma once

#include <medAbstractRelaxometryEstimationProcess.h>
#include <medAbstractImageData.h>
#include <medDataIndex.h>

#include <itkSmartPointer.h>
#include <itkProcessObject.h>

#include <animaRelaxometryPluginExport.h>
#include <medDoubleParameter.h>
#include <medIntParameter.h>

class ANIMARELAXOMETRYPLUGIN_EXPORT animaT2RelaxometryProcess : public medAbstractRelaxometryEstimationProcess
{
    Q_OBJECT
    
public:
    animaT2RelaxometryProcess(QObject* parent = NULL);
    virtual ~animaT2RelaxometryProcess();

    static void eventCallback(itk::Object *caller, const itk::EventObject& event, void *clientData)
    {
        medAbstractRelaxometryEstimationProcess *source = reinterpret_cast<medAbstractRelaxometryEstimationProcess *>(clientData);
        itk::ProcessObject *processObject = (itk::ProcessObject*) caller;
        source->progression()->setValue(processObject->GetProgress() * 100);
    }

    virtual medAbstractJob::medJobExitStatus run();
    virtual void cancel();

    virtual QString caption() const;
    virtual QString description() const;

    // Parameters setting
    medDoubleParameter *trTime() const;
    medDoubleParameter *echoSpacing() const;
    medDoubleParameter *upperBoundT2() const;
    medDoubleParameter *backgroundSignalThreshold() const;
    
public slots:
    void setT1Map(const medDataIndex &index);
    
private:
    template <class PixelType> medAbstractJob::medJobExitStatus _run();

    itk::SmartPointer<itk::ProcessObject> m_t2filter;

    medDoubleParameter *m_trTime;
    medDoubleParameter *m_echoSpacing;
    medDoubleParameter *m_upperBoundT2;
    medDoubleParameter *m_backgroundSignalThreshold;

    medAbstractImageData *m_T1Map;
};

inline medAbstractRelaxometryEstimationProcess* animaT2RelaxometryProcessCreator()
{
    return new animaT2RelaxometryProcess();
}
