#pragma once

#include <medAbstractDiffusionModelEstimationProcessPresenter.h>
#include <animaTensorEstimationPluginExport.h>
#include <animaTensorEstimationProcess.h>
#include <medProcessPresenterFactory.h>

class medIntParameterPresenter;
class ANIMATENSORESTIMATIONPLUGIN_EXPORT animaTensorEstimationProcessPresenter: public medAbstractDiffusionModelEstimationProcessPresenter
{
    Q_OBJECT

public:
    animaTensorEstimationProcessPresenter(medAbstractDiffusionModelEstimationProcess *parent);
    virtual medAbstractDiffusionModelEstimationProcess* process() const;

    virtual QWidget *buildToolBoxWidget();

private:
    animaTensorEstimationProcess *m_process;
    medIntParameterPresenter *m_progressionPresenter;
};

MED_DECLARE_PROCESS_PRESENTER_CREATOR(medAbstractDiffusionModelEstimationProcess, animaTensorEstimationProcess)
