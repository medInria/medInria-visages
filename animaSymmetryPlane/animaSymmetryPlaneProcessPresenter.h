#pragma once
#include "animaSymmetryPlanePluginExport.h"

#include <medAbstractSymmetryPlaneAlignmentProcessPresenter.h>
#include <animaSymmetryPlaneProcess.h>
#include <medProcessPresenterFactory.h>

class medIntParameterPresenter;
class medDoubleParameterPresenter;

class ANIMASYMMETRYPLANEPLUGIN_EXPORT animaSymmetryPlaneProcessPresenter : public medAbstractSymmetryPlaneAlignmentProcessPresenter
{
    Q_OBJECT

public:
    animaSymmetryPlaneProcessPresenter(medAbstractSymmetryPlaneAlignmentProcess *parent);
    virtual medAbstractSymmetryPlaneAlignmentProcess* process() const;

    virtual QWidget *buildToolBoxWidget();

public slots:
    void saveRealignTransformFile();

private:
    animaSymmetryPlaneProcess *m_process;

    medIntParameterPresenter *m_optimizerMaximumIterations;
    medIntParameterPresenter *m_histogramSize;
    medIntParameterPresenter *m_pyramidLevelsNumber;

    medDoubleParameterPresenter *m_upperBoundAngle;
    medDoubleParameterPresenter *m_upperBoundDistance;

    medIntParameterPresenter *m_progressionPresenter;
};

MED_DECLARE_PROCESS_PRESENTER_CREATOR(medAbstractSymmetryPlaneAlignmentProcess, animaSymmetryPlaneProcess)
