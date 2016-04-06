#include "animaSymmetryPlaneProcessPresenter.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QProgressBar>
#include <QFileDialog>

#include <medIntParameterPresenter.h>
#include <medDoubleParameterPresenter.h>

#include <itkTransformFileWriter.h>

animaSymmetryPlaneProcessPresenter::animaSymmetryPlaneProcessPresenter(medAbstractSymmetryPlaneAlignmentProcess *parent)
    : medAbstractSymmetryPlaneAlignmentProcessPresenter(parent)
{
    m_process = qobject_cast <animaSymmetryPlaneProcess *> (parent);

    m_optimizerMaximumIterations = new medIntParameterPresenter(m_process->optimizerMaximumIterations());
    m_histogramSize = new medIntParameterPresenter(m_process->histogramSize());
    m_pyramidLevelsNumber = new medIntParameterPresenter(m_process->pyramidLevelsNumber());

    m_searchRadius = new medDoubleParameterPresenter(m_process->searchRadius());
    m_searchAngleRadius = new medDoubleParameterPresenter(m_process->searchAngleRadius());
    m_finalRadius = new medDoubleParameterPresenter(m_process->finalRadius());

    m_progressionPresenter = new medIntParameterPresenter(m_process->progression());
}

medAbstractSymmetryPlaneAlignmentProcess* animaSymmetryPlaneProcessPresenter::process() const
{
    return m_process;
}

QWidget *animaSymmetryPlaneProcessPresenter::buildToolBoxWidget()
{
    QWidget *tbWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    tbWidget->setLayout(mainLayout);

    // Parameters:
    QComboBox *metricComboBox = new QComboBox;
    metricComboBox->setToolTip("Similarity metric between blocks");
    QStringList metricList;
    metricList << "MutualInformation" << "MeanSquares";
    metricComboBox->addItems (metricList);
    metricComboBox->setCurrentIndex(1);
    connect(metricComboBox,SIGNAL(currentIndexChanged(int)),m_process,SLOT(setMetric(int)));
    mainLayout->addWidget(metricComboBox);

    //Optimizer type selection combobox
    QComboBox *optTypeComboBox = new QComboBox;
    QStringList optTypeList;
    optTypeList << "Newuoa" << "Powell";
    optTypeComboBox->addItems (optTypeList);
    connect(optTypeComboBox,SIGNAL(currentIndexChanged(int)),m_process,SLOT(setOptimizerType(int)));
    mainLayout->addWidget(optTypeComboBox);

    QFormLayout *parametersLayout = new QFormLayout;

    parametersLayout->addRow(m_optimizerMaximumIterations->parameter()->caption(), m_optimizerMaximumIterations->buildWidget());
    parametersLayout->addRow(m_histogramSize->parameter()->caption(), m_histogramSize->buildWidget());
    parametersLayout->addRow(m_searchRadius->parameter()->caption(), m_searchRadius->buildWidget());
    parametersLayout->addRow(m_searchAngleRadius->parameter()->caption(), m_searchAngleRadius->buildWidget());
    parametersLayout->addRow(m_finalRadius->parameter()->caption(), m_finalRadius->buildWidget());
    parametersLayout->addRow(m_pyramidLevelsNumber->parameter()->caption(), m_pyramidLevelsNumber->buildWidget());

    mainLayout->addLayout(parametersLayout);
    mainLayout->addWidget(this->buildRunButton());
    mainLayout->addWidget(this->buildCancelButton());

    QPushButton *saveRealignTransformFileButton = new QPushButton(tr("Save realign transform"));
    connect(saveRealignTransformFileButton, SIGNAL(clicked()), this, SLOT(saveRealignTransformFile()));
    mainLayout->addWidget(saveRealignTransformFileButton);

    mainLayout->addWidget(m_progressionPresenter->buildProgressBar());

    return tbWidget;
}

void animaSymmetryPlaneProcessPresenter::saveRealignTransformFile()
{
    QString fileName = QFileDialog::getSaveFileName(0, tr("Save realign transform file"),QDir::homePath());

     if(!fileName.isEmpty())
     {
         if(m_process)
         {
             animaSymmetryPlaneProcess::TransformPointer outTrsf = m_process->outputRealignTransform();
             if (!outTrsf)
                 return;

             itk::TransformFileWriter::Pointer writer = itk::TransformFileWriter::New();
             writer->SetInput(outTrsf);
             writer->SetFileName(fileName.toStdString());
             writer->Update();
         }
     }
}
