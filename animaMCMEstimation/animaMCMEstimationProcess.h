#pragma once

#include <medAbstractDiffusionModelEstimationProcess.h>

#include <itkProcessObject.h>
#include <itkSmartPointer.h>

#include <medBoolParameter.h>
#include <medIntParameter.h>

#include <animaMCMEstimationPluginExport.h>
#include <animaBaseCompartment.h>

class ANIMAMCMESTIMATIONPLUGIN_EXPORT animaMCMEstimationProcess: public medAbstractDiffusionModelEstimationProcess
{
    Q_OBJECT
public:
    animaMCMEstimationProcess(QObject* parent = NULL);
    ~animaMCMEstimationProcess();

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

    medIntParameter *nbFascicles() const;
    medBoolParameter *freeWaterCompartment() const;

    medIntParameter *nbRandomRestarts() const;
    medIntParameter *nbOptRestarts() const;

    medBoolParameter *fixWeights() const;
    medBoolParameter *fixDiff() const;
    medBoolParameter *fixFWDiff() const;
    medBoolParameter *fixKappa() const;
    medBoolParameter *fixEAF() const;

    medBoolParameter *commonCompartmentWeights() const;
    medBoolParameter *commonDiffusivities() const;
    medBoolParameter *commonKappa() const;
    medBoolParameter *commonEAF() const;

private:
    template <class inputType> medAbstractJob::medJobExitStatus _run();

private:
    itk::SmartPointer<itk::ProcessObject> m_estimationfilter;

    anima::DiffusionModelCompartmentType m_compartmentType;
    medIntParameter *m_nbFascicles;
    medBoolParameter *m_freeWaterCompartment;

    medIntParameter *m_nbRandomRestarts;
    medIntParameter *m_nbOptRestarts;

    medBoolParameter *m_fixWeights;
    medBoolParameter *m_fixDiff;
    medBoolParameter *m_fixFWDiff;
    medBoolParameter *m_fixKappa;
    medBoolParameter *m_fixEAF;

    medBoolParameter *m_commonCompartmentWeights;
    medBoolParameter *m_commonDiffusivities;
    medBoolParameter *m_commonKappa;
    medBoolParameter *m_commonEAF;
};

inline medAbstractDiffusionModelEstimationProcess* animaMCMEstimationProcessCreator()
{
    return new animaMCMEstimationProcess();
}
