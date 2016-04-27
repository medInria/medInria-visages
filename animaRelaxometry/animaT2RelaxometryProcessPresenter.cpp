#include <animaT2RelaxometryProcessPresenter.h>

#include <QFormLayout>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>

#include <medIntParameterPresenter.h>
#include <medDoubleParameterPresenter.h>
#include <medDropSite.h>
#include <medDataManager.h>

animaT2RelaxometryProcessPresenter::animaT2RelaxometryProcessPresenter(medAbstractRelaxometryEstimationProcess *parent)
    : medAbstractRelaxometryEstimationProcessPresenter(parent)
{
    m_process = qobject_cast <animaT2RelaxometryProcess *> (parent);

    m_trTime = new medDoubleParameterPresenter(m_process->trTime());
    m_echoSpacing = new medDoubleParameterPresenter(m_process->echoSpacing());
    m_upperBoundM0 = new medDoubleParameterPresenter(m_process->upperBoundM0());
    m_upperBoundT2 = new medDoubleParameterPresenter(m_process->upperBoundT2());
    m_backgroundSignalThreshold = new medDoubleParameterPresenter(m_process->backgroundSignalThreshold());

    m_t1MapDropSite = new medDropSite;
    m_t1MapDropSite->setCanAutomaticallyChangeAppereance(false);
    connect(m_t1MapDropSite, SIGNAL(objectDropped(const medDataIndex &)), this, SLOT(setT1Map(const medDataIndex &)));

    m_progressionPresenter = new medIntParameterPresenter(m_process->progression());
}

medAbstractRelaxometryEstimationProcess* animaT2RelaxometryProcessPresenter::process() const
{
    return m_process;
}

QWidget *animaT2RelaxometryProcessPresenter::buildToolBoxWidget()
{
    QWidget *tbWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    tbWidget->setLayout(mainLayout);

    QVBoxLayout *t1DropLayout = new QVBoxLayout;
    t1DropLayout->addWidget(m_t1MapDropSite);
    t1DropLayout->addWidget(new QLabel("Initial T1 image"));
    t1DropLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addLayout(t1DropLayout);

    // Parameters:
    QFormLayout *parametersLayout = new QFormLayout;

    parametersLayout->addRow(m_trTime->parameter()->caption(), m_trTime->buildWidget());
    parametersLayout->addRow(m_echoSpacing->parameter()->caption(), m_echoSpacing->buildWidget());
    parametersLayout->addRow(m_upperBoundM0->parameter()->caption(), m_upperBoundM0->buildWidget());
    parametersLayout->addRow(m_upperBoundT2->parameter()->caption(), m_upperBoundT2->buildWidget());
    parametersLayout->addRow(m_backgroundSignalThreshold->parameter()->caption(), m_backgroundSignalThreshold->buildWidget());

    mainLayout->addLayout(parametersLayout);
    mainLayout->addWidget(this->buildRunButton());
    mainLayout->addWidget(this->buildCancelButton());
    mainLayout->addWidget(m_progressionPresenter->buildProgressBar());

    return tbWidget;
}

void animaT2RelaxometryProcessPresenter::setT1Map(const medDataIndex &index)
{
    m_process->setT1Map(index);
    m_t1MapDropSite->setPixmap(medDataManager::instance()->thumbnail(index).scaled(m_t1MapDropSite->sizeHint()));
}
