#include <animaDESPOT1RelaxometryProcessPresenter.h>

#include <QFormLayout>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>

#include <medIntParameterPresenter.h>
#include <medDoubleParameterPresenter.h>

animaDESPOT1RelaxometryProcessPresenter::animaDESPOT1RelaxometryProcessPresenter(medAbstractRelaxometryEstimationProcess *parent)
    : medAbstractRelaxometryEstimationProcessPresenter(parent)
{
    m_process = qobject_cast <animaDESPOT1RelaxometryProcess *> (parent);

    m_trTime = new medDoubleParameterPresenter(m_process->trTime());
    m_firstFlipAngle = new medDoubleParameterPresenter(m_process->firstFlipAngle());
    m_secondFlipAngle = new medDoubleParameterPresenter(m_process->secondFlipAngle());
    m_upperBoundM0 = new medDoubleParameterPresenter(m_process->upperBoundM0());
    m_upperBoundT1 = new medDoubleParameterPresenter(m_process->upperBoundT1());
    m_backgroundSignalThreshold = new medDoubleParameterPresenter(m_process->backgroundSignalThreshold());

    m_progressionPresenter = new medIntParameterPresenter(m_process->progression());
}

medAbstractRelaxometryEstimationProcess* animaDESPOT1RelaxometryProcessPresenter::process() const
{
    return m_process;
}

QWidget *animaDESPOT1RelaxometryProcessPresenter::buildToolBoxWidget()
{
    QWidget *tbWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    tbWidget->setLayout(mainLayout);

    // Parameters:
    QFormLayout *parametersLayout = new QFormLayout;

    parametersLayout->addRow(m_firstFlipAngle->parameter()->caption(), m_firstFlipAngle->buildWidget());
    parametersLayout->addRow(m_secondFlipAngle->parameter()->caption(), m_secondFlipAngle->buildWidget());
    parametersLayout->addRow(m_trTime->parameter()->caption(), m_trTime->buildWidget());
    parametersLayout->addRow(m_upperBoundM0->parameter()->caption(), m_upperBoundM0->buildWidget());
    parametersLayout->addRow(m_upperBoundT1->parameter()->caption(), m_upperBoundT1->buildWidget());
    parametersLayout->addRow(m_backgroundSignalThreshold->parameter()->caption(), m_backgroundSignalThreshold->buildWidget());

    mainLayout->addLayout(parametersLayout);
    mainLayout->addWidget(this->buildRunButton());
    mainLayout->addWidget(this->buildCancelButton());
    mainLayout->addWidget(m_progressionPresenter->buildProgressBar());

    return tbWidget;
}
