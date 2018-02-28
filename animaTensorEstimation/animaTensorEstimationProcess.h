#pragma once

#include <medAbstractDiffusionModelEstimationProcess.h>

#include <itkProcessObject.h>
#include <itkSmartPointer.h>
#include <itkCommand.h>

#include <animaTensorEstimationPluginExport.h>
#include <medIntParameter.h>

class ANIMATENSORESTIMATIONPLUGIN_EXPORT animaTensorEstimationProcess: public medAbstractDiffusionModelEstimationProcess
{
    Q_OBJECT
public:
    animaTensorEstimationProcess(QObject* parent = NULL);
    ~animaTensorEstimationProcess();

    static void eventCallback(itk::Object *caller, const itk::EventObject& event, void *clientData)
    {
        medAbstractDiffusionModelEstimationProcess * source = reinterpret_cast<medAbstractDiffusionModelEstimationProcess *>(clientData);
        itk::ProcessObject * processObject = (itk::ProcessObject*) caller;
        source->progression()->setValue(processObject->GetProgress() * 100);
    }

    virtual medAbstractJob::medJobExitStatus run();
    virtual void cancel();

    virtual QString caption() const;
    virtual QString description() const;

private:
    template <class inputType> medAbstractJob::medJobExitStatus _run();

private:
    itk::SmartPointer<itk::ProcessObject> m_estimationfilter;
};

inline medAbstractDiffusionModelEstimationProcess* animaTensorEstimationProcessCreator()
{
    return new animaTensorEstimationProcess();
}
