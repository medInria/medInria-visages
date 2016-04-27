#pragma once

#include <medAbstractRelaxometryEstimationProcess.h>
#include <medAbstractData.h>

#include <itkSmartPointer.h>
#include <itkProcessObject.h>

#include <animaRelaxometryPluginExport.h>
#include <medDoubleParameter.h>
#include <medIntParameter.h>

class ANIMARELAXOMETRYPLUGIN_EXPORT animaDESPOT1RelaxometryProcess : public medAbstractRelaxometryEstimationProcess
{
    Q_OBJECT
    
public:
    animaDESPOT1RelaxometryProcess(QObject* parent = NULL);
    virtual ~animaDESPOT1RelaxometryProcess();

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
    medDoubleParameter *firstFlipAngle() const;
    medDoubleParameter *secondFlipAngle() const;
    medDoubleParameter *upperBoundM0() const;
    medDoubleParameter *upperBoundT1() const;
    medDoubleParameter *backgroundSignalThreshold() const;
    
private:
    template <class PixelType> medAbstractJob::medJobExitStatus _run();

    itk::SmartPointer<itk::ProcessObject> m_despot1filter;

    medDoubleParameter *m_trTime;
    medDoubleParameter *m_firstFlipAngle;
    medDoubleParameter *m_secondFlipAngle;
    medDoubleParameter *m_upperBoundM0;
    medDoubleParameter *m_upperBoundT1;
    medDoubleParameter *m_backgroundSignalThreshold;
};

inline medAbstractRelaxometryEstimationProcess* animaDESPOT1RelaxometryProcessCreator()
{
    return new animaDESPOT1RelaxometryProcess();
}
