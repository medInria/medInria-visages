#pragma once
#include <animaRelaxometryPluginExport.h>

#include <medAbstractRelaxometryEstimationProcessPresenter.h>
#include <animaDESPOT1RelaxometryProcess.h>
#include <medProcessPresenterFactory.h>

class medIntParameterPresenter;
class medDoubleParameterPresenter;

class ANIMARELAXOMETRYPLUGIN_EXPORT animaDESPOT1RelaxometryProcessPresenter : public medAbstractRelaxometryEstimationProcessPresenter
{
    Q_OBJECT
    
public:
    animaDESPOT1RelaxometryProcessPresenter(medAbstractRelaxometryEstimationProcess *parent);
    virtual medAbstractRelaxometryEstimationProcess* process() const;

    virtual QWidget *buildToolBoxWidget();
    
private:
    animaDESPOT1RelaxometryProcess *m_process;

    medDoubleParameterPresenter *m_trTime;
    medDoubleParameterPresenter *m_firstFlipAngle;
    medDoubleParameterPresenter *m_secondFlipAngle;
    medDoubleParameterPresenter *m_upperBoundM0;
    medDoubleParameterPresenter *m_upperBoundT1;
    medDoubleParameterPresenter *m_backgroundSignalThreshold;

    medIntParameterPresenter *m_progressionPresenter;
};

MED_DECLARE_PROCESS_PRESENTER_CREATOR(medAbstractRelaxometryEstimationProcess, animaDESPOT1RelaxometryProcess)
