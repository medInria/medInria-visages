#include <animaMCMEstimationProcessPresenter.h>

#include <medBoolParameterPresenter.h>
#include <medIntParameterPresenter.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QProgressBar>

animaMCMEstimationProcessPresenter::animaMCMEstimationProcessPresenter(medAbstractDiffusionModelEstimationProcess *parent)
    : medAbstractDiffusionModelEstimationProcessPresenter(parent)
{
    m_process = qobject_cast <animaMCMEstimationProcess *> (parent);

    m_nbFascicles = new medIntParameterPresenter(m_process->nbFascicles());

    m_freeWaterCompartment = new medBoolParameterPresenter(m_process->freeWaterCompartment());
    m_irWaterCompartment = new medBoolParameterPresenter(m_process->irWaterCompartment());
    m_stationaryWaterCompartment = new medBoolParameterPresenter(m_process->stationaryWaterCompartment());
    m_modelSelection = new medBoolParameterPresenter(m_process->modelSelection());

    m_nbRandomRestarts = new medIntParameterPresenter(m_process->nbRandomRestarts());

    m_fixWeights = new medBoolParameterPresenter(m_process->fixWeights());
    m_fixDiff = new medBoolParameterPresenter(m_process->fixDiff());
    m_fixIsoDiffs = new medBoolParameterPresenter(m_process->fixIsoDiffs());
    m_fixKappa = new medBoolParameterPresenter(m_process->fixKappa());
    m_fixEAF = new medBoolParameterPresenter(m_process->fixEAF());

    m_commonDiffusivities = new medBoolParameterPresenter(m_process->commonDiffusivities());
    m_commonKappa = new medBoolParameterPresenter(m_process->commonKappa());
    m_commonEAF = new medBoolParameterPresenter(m_process->commonEAF());

    m_progressionPresenter = new medIntParameterPresenter(m_process->progression());
}

medAbstractDiffusionModelEstimationProcess* animaMCMEstimationProcessPresenter::process() const
{
    return m_process;
}

QWidget *animaMCMEstimationProcessPresenter::buildToolBoxWidget()
{
    bool saveUseRunControls = this->useRunControls();

    this->setUseRunControls(false);
    QWidget *tbWidget = medAbstractDiffusionModelEstimationProcessPresenter::buildToolBoxWidget();
    QVBoxLayout *tbLayout = qobject_cast <QVBoxLayout *> (tbWidget->layout());
    this->setUseRunControls(saveUseRunControls);

    QHBoxLayout *nbFascLayout = new QHBoxLayout;
    QLabel *nbFascLabel = new QLabel(m_nbFascicles->parameter()->caption());
    QWidget *nbFascWidget = m_nbFascicles->buildWidget();
    nbFascWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    nbFascLayout->addWidget(nbFascLabel);
    nbFascLayout->addWidget(nbFascWidget);

    tbLayout->addLayout(nbFascLayout);
    tbLayout->addWidget(m_modelSelection->buildWidget());
    tbLayout->addWidget(m_freeWaterCompartment->buildWidget());
    tbLayout->addWidget(m_irWaterCompartment->buildWidget());
    tbLayout->addWidget(m_stationaryWaterCompartment->buildWidget());

    QHBoxLayout *nbRandomRestartsLayout = new QHBoxLayout;
    QLabel *nbRandomRestartsLabel = new QLabel(m_nbRandomRestarts->parameter()->caption());
    QWidget *nbRandomRestartsWidget = m_nbRandomRestarts->buildWidget();
    nbRandomRestartsWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    nbRandomRestartsLayout->addWidget(nbRandomRestartsLabel);
    nbRandomRestartsLayout->addWidget(nbRandomRestartsWidget);
    tbLayout->addLayout(nbRandomRestartsLayout);

    tbLayout->addWidget(m_fixWeights->buildWidget());
    tbLayout->addWidget(m_fixDiff->buildWidget());
    tbLayout->addWidget(m_fixIsoDiffs->buildWidget());
    tbLayout->addWidget(m_fixKappa->buildWidget());
    tbLayout->addWidget(m_fixEAF->buildWidget());

    tbLayout->addWidget(m_commonDiffusivities->buildWidget());
    tbLayout->addWidget(m_commonKappa->buildWidget());
    tbLayout->addWidget(m_commonEAF->buildWidget());

    if (this->useRunControls())
    {
        tbLayout->addWidget(this->buildRunButton());
        tbLayout->addWidget(this->buildCancelButton());
        tbLayout->addWidget(m_progressionPresenter->buildProgressBar());
    }

    return tbWidget;
}
