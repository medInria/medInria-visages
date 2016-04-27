#pragma once
#include <animaRelaxometryPluginExport.h>

#include <medAbstractRelaxometryEstimationProcessPresenter.h>
#include <animaT2RelaxometryProcess.h>
#include <medProcessPresenterFactory.h>

class medIntParameterPresenter;
class medDoubleParameterPresenter;
class medDropSite;

class ANIMARELAXOMETRYPLUGIN_EXPORT animaT2RelaxometryProcessPresenter : public medAbstractRelaxometryEstimationProcessPresenter
{
    Q_OBJECT
    
public:
    animaT2RelaxometryProcessPresenter(medAbstractRelaxometryEstimationProcess *parent);
    virtual medAbstractRelaxometryEstimationProcess* process() const;

    virtual QWidget *buildToolBoxWidget();

public slots:
    void setT1Map(const medDataIndex &index);
    
private:
    animaT2RelaxometryProcess *m_process;

    medDoubleParameterPresenter *m_trTime;
    medDoubleParameterPresenter *m_echoSpacing;
    medDoubleParameterPresenter *m_upperBoundM0;
    medDoubleParameterPresenter *m_upperBoundT2;
    medDoubleParameterPresenter *m_backgroundSignalThreshold;

    medDropSite *m_t1MapDropSite;

    medIntParameterPresenter *m_progressionPresenter;
};

MED_DECLARE_PROCESS_PRESENTER_CREATOR(medAbstractRelaxometryEstimationProcess, animaT2RelaxometryProcess)
