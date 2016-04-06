#pragma once

#include <medAbstractDiffusionModelEstimationProcessPresenter.h>
#include <animaMCMEstimationPluginExport.h>
#include <animaMCMEstimationProcess.h>
#include <medProcessPresenterFactory.h>

class medIntParameterPresenter;
class medBoolParameterPresenter;
class ANIMAMCMESTIMATIONPLUGIN_EXPORT animaMCMEstimationProcessPresenter: public medAbstractDiffusionModelEstimationProcessPresenter
{
    Q_OBJECT

public:
    animaMCMEstimationProcessPresenter(medAbstractDiffusionModelEstimationProcess *parent);
    virtual medAbstractDiffusionModelEstimationProcess* process() const;

    virtual QWidget *buildToolBoxWidget();

private:
    animaMCMEstimationProcess *m_process;

    medIntParameterPresenter *m_nbFascicles;
    medBoolParameterPresenter *m_freeWaterCompartment;

    medIntParameterPresenter *m_nbRandomRestarts;
    medIntParameterPresenter *m_nbOptRestarts;

    medBoolParameterPresenter *m_fixWeights;
    medBoolParameterPresenter *m_fixDiff;
    medBoolParameterPresenter *m_fixFWDiff;
    medBoolParameterPresenter *m_fixKappa;
    medBoolParameterPresenter *m_fixEAF;

    medBoolParameterPresenter *m_commonCompartmentWeights;
    medBoolParameterPresenter *m_commonDiffusivities;
    medBoolParameterPresenter *m_commonKappa;
    medBoolParameterPresenter *m_commonEAF;

    medIntParameterPresenter *m_progressionPresenter;
};

MED_DECLARE_PROCESS_PRESENTER_CREATOR(medAbstractDiffusionModelEstimationProcess, animaMCMEstimationProcess)
