#pragma once
#include "animaNonLocalMeansFilterPluginExport.h"

#include <medAbstractImageDenoisingProcessPresenter.h>
#include <animaNonLocalMeansFilterProcess.h>
#include <medProcessPresenterFactory.h>

class medIntParameterPresenter;
class medDoubleParameterPresenter;
class medBoolParameterPresenter;

class ANIMANONLOCALMEANSFILTERPLUGIN_EXPORT animaNonLocalMeansFilterProcessPresenter : public medAbstractImageDenoisingProcessPresenter
{
    Q_OBJECT

public:
    animaNonLocalMeansFilterProcessPresenter(medAbstractImageDenoisingProcess *parent);
    virtual medAbstractImageDenoisingProcess* process() const;

    virtual QWidget *buildToolBoxWidget();

private:
    animaNonLocalMeansFilterProcess *m_process;

    medIntParameterPresenter *m_PatchHalfSize;
    medIntParameterPresenter *m_SearchNeighborhood;
    medIntParameterPresenter *m_SearchStepSize;
    medDoubleParameterPresenter *m_WeightThreshold;
    medDoubleParameterPresenter *m_BetaParameter;
    medDoubleParameterPresenter *m_MeanMinThreshold;
    medDoubleParameterPresenter *m_VarMinThreshold;
    medBoolParameterPresenter *m_TemporalImage;

    medIntParameterPresenter *m_progressionPresenter;
};

MED_DECLARE_PROCESS_PRESENTER_CREATOR(medAbstractImageDenoisingProcess, animaNonLocalMeansFilterProcess)
