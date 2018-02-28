#include <animaTensorEstimationProcessPresenter.h>

#include <medIntParameterPresenter.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QProgressBar>

animaTensorEstimationProcessPresenter::animaTensorEstimationProcessPresenter(medAbstractDiffusionModelEstimationProcess *parent)
    : medAbstractDiffusionModelEstimationProcessPresenter(parent)
{
    m_process = qobject_cast <animaTensorEstimationProcess *> (parent);
    m_progressionPresenter = new medIntParameterPresenter(m_process->progression());
}

medAbstractDiffusionModelEstimationProcess* animaTensorEstimationProcessPresenter::process() const
{
    return m_process;
}

QWidget *animaTensorEstimationProcessPresenter::buildToolBoxWidget()
{
    bool saveUseRunControls = this->useRunControls();

    this->setUseRunControls(false);
    QWidget *tbWidget = medAbstractDiffusionModelEstimationProcessPresenter::buildToolBoxWidget();
    QVBoxLayout *tbLayout = qobject_cast <QVBoxLayout *> (tbWidget->layout());
    this->setUseRunControls(saveUseRunControls);

    if (this->useRunControls())
    {
        tbLayout->addWidget(this->buildRunButton());
        tbLayout->addWidget(this->buildCancelButton());
        tbLayout->addWidget(m_progressionPresenter->buildProgressBar());
    }

    return tbWidget;
}
