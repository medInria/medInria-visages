// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////


#include "animaSymmetryPlane.h"
#include "animaSymmetryPlaneToolBox.h"

#include <QtGui>

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkSmartPointer.h>

#include <medAbstractView.h>
#include <medRunnableProcess.h>
#include <medJobManager.h>

#include <medAbstractDataImage.h>

#include <medToolBoxFactory.h>
#include <medFilteringSelectorToolBox.h>
#include <medProgressionStack.h>

#include <pyramidalSymmetryBridge.h>


class animaSymmetryPlaneToolBoxPrivate
{
public:

    QComboBox *metricComboBox;
    QComboBox *optTypeComboBox;
    QSpinBox *optMaxIterations;
    QSpinBox *histogramSize;
    QDoubleSpinBox * searchRadiusValue;
    QDoubleSpinBox * searchAngleRadiusValue;
    QDoubleSpinBox * finalRadiusValue;
    QSpinBox *numberOfPyramidLevelsValue;
    QSpinBox *numberOfThreadsValue;


    dtkSmartPointer <dtkAbstractProcess> process;
    medProgressionStack * progression_stack;
};

animaSymmetryPlaneToolBox::animaSymmetryPlaneToolBox(QWidget *parent) : medFilteringAbstractToolBox(parent), d(new animaSymmetryPlaneToolBoxPrivate)
{
    QWidget *widget = new QWidget(this);

    QPushButton *runButton = new QPushButton(tr("Run"), this);
    QPushButton *saveRealignTransformFileButton = new QPushButton(tr("Save realign transform"), this);
    QPushButton *saveTransformFileButton = new QPushButton(tr("Save transform"), this);

    this->setTitle("animaSymmetryPlane");

    // progression stack
    d->progression_stack = new medProgressionStack(widget);
    QHBoxLayout *progressStackLayout = new QHBoxLayout;
    progressStackLayout->addWidget(d->progression_stack);

    //Metrics selection combobox
    d->metricComboBox = new QComboBox;
    d->metricComboBox->setToolTip("Similarity metric between blocks");
    QStringList metricList;
    metricList << "MeanSquares" << "MutualInformation";
    d->metricComboBox->addItems ( metricList );

    //Optimizer type selection combobox
    d->optTypeComboBox = new QComboBox;
    QStringList optTypeList;
    optTypeList << "Newuoa" << "Powell";
    d->optTypeComboBox->addItems ( optTypeList );


    d->optMaxIterations = new QSpinBox;
    d->optMaxIterations->setToolTip("Maximum Local Optimizer Iterations");
    d->optMaxIterations->setMaximum(200);
    d->optMaxIterations->setMinimum(1);
    d->optMaxIterations->setValue(100);

    d->histogramSize = new QSpinBox;
    d->histogramSize->setToolTip("Histogram Size for Mutual Information");
    d->histogramSize->setMaximum(200);
    d->histogramSize->setValue(120);

    d->searchRadiusValue = new QDoubleSpinBox;
    d->searchRadiusValue->setToolTip("The search radius (exhaustive search window, rho start for newuoa");
    d->searchRadiusValue->setValue(2);

    d->searchAngleRadiusValue = new QDoubleSpinBox;
    d->searchRadiusValue->setToolTip("The search angle radius (rho start for newuoa on rigid transforms angles part");
    d->searchAngleRadiusValue->setValue(5);

    d->finalRadiusValue = new QDoubleSpinBox;
    d->finalRadiusValue->setToolTip("The final radius (rho end for newuoa");
    d->finalRadiusValue->setDecimals(4);
    d->finalRadiusValue->setValue(0.001);

    d->numberOfPyramidLevelsValue = new QSpinBox;
    d->numberOfPyramidLevelsValue->setToolTip("Number of pyramid levels");
    d->numberOfPyramidLevelsValue->setValue(3);

    d->numberOfThreadsValue = new QSpinBox;
    d->numberOfThreadsValue->setMinimum(1);
    d->numberOfThreadsValue->setValue(2);


    QLabel *metricLabel = new QLabel(tr("Metric:"));
    QHBoxLayout *metricLayout = new QHBoxLayout;
    metricLayout->addWidget ( metricLabel );
    metricLayout->addWidget ( d->metricComboBox );

    QLabel *optTypeLabel = new QLabel(tr("Optimizer type:"));
    QHBoxLayout *optTypeLayout = new QHBoxLayout;
    optTypeLayout->addWidget ( optTypeLabel );
    optTypeLayout->addWidget ( d->optTypeComboBox );

    QLabel *optIterationLabel = new QLabel(tr("Max optimizer iterations:"));
    QHBoxLayout *optIterationLayout = new QHBoxLayout;
    optIterationLayout->addWidget ( optIterationLabel );
    optIterationLayout->addWidget ( d->optMaxIterations );

    QLabel *histogramSizeLabel = new QLabel(tr("Histogram size:"));
    QHBoxLayout *histogramSizeLayout = new QHBoxLayout;
    histogramSizeLayout->addWidget ( histogramSizeLabel );
    histogramSizeLayout->addWidget ( d->histogramSize );

    QLabel *searchRadiusLabel = new QLabel(tr("Search radius:"));
    QHBoxLayout *searchRadiusLayout = new QHBoxLayout;
    searchRadiusLayout->addWidget ( searchRadiusLabel );
    searchRadiusLayout->addWidget ( d->searchRadiusValue );

    QLabel *searchAngleRadiusLabel = new QLabel(tr("Search angle radius:"));
    QHBoxLayout *searchAngleRadiusLayout = new QHBoxLayout;
    searchAngleRadiusLayout->addWidget ( searchAngleRadiusLabel );
    searchAngleRadiusLayout->addWidget ( d->searchAngleRadiusValue );

    QLabel *finalRadiusLabel = new QLabel(tr("Final Radius:"));
    QHBoxLayout *finalRadiusLayout = new QHBoxLayout;
    finalRadiusLayout->addWidget ( finalRadiusLabel );
    finalRadiusLayout->addWidget ( d->finalRadiusValue );

    QLabel *pyramidLevelsLabel = new QLabel(tr("Pyramid levels:"));
    QHBoxLayout *pyramidLevelsLayout = new QHBoxLayout;
    pyramidLevelsLayout->addWidget ( pyramidLevelsLabel );
    pyramidLevelsLayout->addWidget ( d->numberOfPyramidLevelsValue );

    QLabel *threadsLabel = new QLabel(tr("Number of threads:"));
    QHBoxLayout *threadsLayout = new QHBoxLayout;
    threadsLayout->addWidget ( threadsLabel );
    threadsLayout->addWidget ( d->numberOfThreadsValue );


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(metricLayout);
    layout->addLayout(optTypeLayout);
    layout->addLayout(optIterationLayout);
    layout->addLayout(histogramSizeLayout);
    layout->addLayout(searchRadiusLayout);
    layout->addLayout(searchAngleRadiusLayout);
    layout->addLayout(finalRadiusLayout);
    layout->addLayout(pyramidLevelsLayout);
    layout->addLayout(threadsLayout);
    layout->addWidget(runButton);

    layout->addWidget(saveTransformFileButton);
    layout->addWidget(saveRealignTransformFileButton);

    layout->addWidget(d->progression_stack);

    widget->setLayout ( layout );
    this->addWidget ( widget );

    connect(runButton, SIGNAL(clicked()), this, SLOT(run()));
    connect(saveTransformFileButton, SIGNAL(clicked()), this, SLOT(saveTransformFile()));
    connect(saveRealignTransformFileButton, SIGNAL(clicked()), this, SLOT(saveRealignTransformFile()));
    connect(d->metricComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateMetric(int)));

    //explicit call to updateMetric with default value to update other parameters (histrogram size,...)
    updateMetric(0);
}

animaSymmetryPlaneToolBox::~animaSymmetryPlaneToolBox(void)
{
    delete d;

    d = NULL;
}

bool animaSymmetryPlaneToolBox::registered(void)
{
    return medToolBoxFactory::instance()->
    registerToolBox<animaSymmetryPlaneToolBox>("animaSymmetryPlaneToolBox",
                               tr("Symmetry Plane"),
                               tr("short tooltip description"),
                               QStringList()<< "filtering");
}

dtkAbstractData* animaSymmetryPlaneToolBox::processOutput(void)
{
    if(!d->process)
        return NULL;

    return d->process->output();
}

void animaSymmetryPlaneToolBox::run(void)
{
    if(!this->parentToolBox())
        return;

    d->process = dtkAbstractProcessFactory::instance()->createSmartPointer("animaSymmetryPlane");

    if(!this->parentToolBox()->data())
        return;

    d->process->setInput(this->parentToolBox()->data());

    d->process->setParameter((double)d->metricComboBox->currentIndex(), 0);
    d->process->setParameter((double)d->optTypeComboBox->currentIndex(), 1);
    d->process->setParameter((double)d->optMaxIterations->value(),2);
    d->process->setParameter((double)d->histogramSize->value(), 3);
    d->process->setParameter((double)d->searchRadiusValue->value(),4);
    d->process->setParameter((double)d->searchAngleRadiusValue->value(),5);
    d->process->setParameter((double)d->finalRadiusValue->value(), 6);
    d->process->setParameter((double)d->numberOfPyramidLevelsValue->value(), 7);
    d->process->setParameter((double)d->numberOfThreadsValue->value(), 8);


    medRunnableProcess *runProcess = new medRunnableProcess;
    runProcess->setProcess (d->process);

    d->progression_stack->addJobItem(runProcess, "Progress:");

    d->progression_stack->disableCancel(runProcess);

    connect (runProcess, SIGNAL (success  (QObject*)),  this, SIGNAL (success ()));
    connect (runProcess, SIGNAL (failure  (QObject*)),  this, SIGNAL (failure ()));
    connect (runProcess, SIGNAL (cancelled (QObject*)),  this, SIGNAL (failure ()));

    connect (runProcess, SIGNAL(activate(QObject*,bool)),
             d->progression_stack, SLOT(setActive(QObject*,bool)));


    medJobManager::instance()->registerJobItem(runProcess);
    QThreadPool::globalInstance()->start(dynamic_cast<QRunnable*>(runProcess));
}


void animaSymmetryPlaneToolBox::saveRealignTransformFile(void)
{
     QString fileName = QFileDialog::getSaveFileName(this, tr("Save realign transform file"));

     if(!fileName.isEmpty())
     {
         dtkSmartPointer<animaSymmetryPlane> symmetryPlaneProcess = (dtkSmartPointer<animaSymmetryPlane>)d->process;
         if(symmetryPlaneProcess)
           symmetryPlaneProcess->saveTransformFile(fileName);
     }

}

void animaSymmetryPlaneToolBox::saveTransformFile(void)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save transform file"));

    if(!fileName.isEmpty())
    {
        dtkSmartPointer<animaSymmetryPlane> symmetryPlaneProcess = (dtkSmartPointer<animaSymmetryPlane>)d->process;
        if(symmetryPlaneProcess)
          symmetryPlaneProcess->saveRealignTransformFile(fileName);
    }
}


void animaSymmetryPlaneToolBox::updateMetric(int newValue)
{
    Metric newMetric = (Metric)newValue;
    if(newMetric == MutualInformation)
    {
        d->histogramSize->setEnabled(true);
    }
    else
    {
        d->histogramSize->setEnabled(false);
    }
}

