#include "animaNonLocalMeansFilterProcessPresenter.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QPushButton>
#include <QProgressBar>

#include <medBoolParameterPresenter.h>
#include <medIntParameterPresenter.h>
#include <medDoubleParameterPresenter.h>

animaNonLocalMeansFilterProcessPresenter::animaNonLocalMeansFilterProcessPresenter(medAbstractImageDenoisingProcess *parent)
    : medAbstractImageDenoisingProcessPresenter(parent)
{
    m_process = qobject_cast <animaNonLocalMeansFilterProcess *> (parent);

    m_PatchHalfSize = new medIntParameterPresenter(m_process->patchHalfSize());
    m_SearchNeighborhood = new medIntParameterPresenter(m_process->searchNeighborhood());
    m_SearchStepSize = new medIntParameterPresenter(m_process->searchStepSize());

    m_WeightThreshold = new medDoubleParameterPresenter(m_process->weightThreshold());
    m_BetaParameter = new medDoubleParameterPresenter(m_process->betaParameter());
    m_MeanMinThreshold = new medDoubleParameterPresenter(m_process->meanMinThreshold());
    m_VarMinThreshold = new medDoubleParameterPresenter(m_process->varMinThreshold());

    m_TemporalImage = new medBoolParameterPresenter(m_process->temporalImage());
    m_progressionPresenter = new medIntParameterPresenter(m_process->progression());
}

medAbstractImageDenoisingProcess* animaNonLocalMeansFilterProcessPresenter::process() const
{
    return m_process;
}

QWidget *animaNonLocalMeansFilterProcessPresenter::buildToolBoxWidget()
{
    QWidget *tbWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    tbWidget->setLayout(mainLayout);

    // Parameters:
    QFormLayout *parametersLayout = new QFormLayout();

    parametersLayout->addRow(m_PatchHalfSize->parameter()->caption(), m_PatchHalfSize->buildWidget());
    parametersLayout->addRow(m_SearchNeighborhood->parameter()->caption(), m_SearchNeighborhood->buildWidget());
    parametersLayout->addRow(m_SearchStepSize->parameter()->caption(), m_SearchStepSize->buildWidget());
    parametersLayout->addRow(m_WeightThreshold->parameter()->caption(), m_WeightThreshold->buildWidget());
    parametersLayout->addRow(m_BetaParameter->parameter()->caption(), m_BetaParameter->buildWidget());
    parametersLayout->addRow(m_MeanMinThreshold->parameter()->caption(), m_MeanMinThreshold->buildWidget());
    parametersLayout->addRow(m_VarMinThreshold->parameter()->caption(), m_VarMinThreshold->buildWidget());

    QComboBox *weightedMethod = new QComboBox;
    QStringList weightedMethods;
    weightedMethods << "Gaussian" << "Rician";
    weightedMethod->addItems(weightedMethods);
    weightedMethod->setCurrentIndex(m_process->weightMethod());
    parametersLayout->addRow(tr("Noise assumption"), weightedMethod);
    connect(weightedMethod,SIGNAL(currentIndexChanged(int)),m_process,SLOT(setWeightedMethod(int)));

    mainLayout->addLayout(parametersLayout);
    mainLayout->addWidget(m_TemporalImage->buildWidget());
    mainLayout->addWidget(this->buildRunButton());
    mainLayout->addWidget(this->buildCancelButton());
    mainLayout->addWidget(m_progressionPresenter->buildProgressBar());

    return tbWidget;
}
