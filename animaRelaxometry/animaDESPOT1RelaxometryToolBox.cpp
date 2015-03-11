/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <animaDESPOT1Relaxometry.h>
#include <animaDESPOT1RelaxometryToolBox.h>
#include <itkMultiThreader.h>

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

#include <medAbstractImageData.h>

#include <medToolBoxFactory.h>
#include <medFilteringSelectorToolBox.h>
#include <medProgressionStack.h>
#include <medPluginManager.h>

class animaDESPOT1RelaxometryToolBoxPrivate
{
public:
    dtkSmartPointer <animaDESPOT1Relaxometry> process;
    medProgressionStack * progression_stack;

    QDoubleSpinBox *trTime;
    QDoubleSpinBox *firstFlipAngle;
    QDoubleSpinBox *secondFlipAngle;
    QDoubleSpinBox *upperBoundM0;
    QDoubleSpinBox *upperBoundT1;
    QDoubleSpinBox *backgroundSignalThreshold;
    QSpinBox *numberOfThreadsValue;
};

animaDESPOT1RelaxometryToolBox::animaDESPOT1RelaxometryToolBox(QWidget *parent) : medFilteringAbstractToolBox(parent), d(new animaDESPOT1RelaxometryToolBoxPrivate)
{
    QWidget *widget = new QWidget(this);
    
    QPushButton *runButton = new QPushButton(tr("Run"), this);
    
    this->setTitle("DESPOT1 Relaxometry");
    
    // progression stack
    d->progression_stack = new medProgressionStack(widget);
    
    d->trTime = new QDoubleSpinBox;
    d->trTime->setValue(15);
    d->trTime->setRange(0, 500);
    d->trTime->setDecimals(2);

    d->firstFlipAngle = new QDoubleSpinBox;
    d->firstFlipAngle->setValue(5);
    d->firstFlipAngle->setRange(0, 180);
    d->firstFlipAngle->setDecimals(1);

    d->secondFlipAngle = new QDoubleSpinBox;
    d->secondFlipAngle->setValue(30);
    d->secondFlipAngle->setRange(0, 180);
    d->secondFlipAngle->setDecimals(1);

    d->upperBoundM0 = new QDoubleSpinBox;
    d->upperBoundM0->setRange(0, 10000);
    d->upperBoundM0->setValue(5000);
    d->upperBoundM0->setDecimals(1);

    d->upperBoundT1 = new QDoubleSpinBox;
    d->upperBoundT1->setRange(0, 10000);
    d->upperBoundT1->setValue(5000);
    d->upperBoundT1->setDecimals(1);

    d->backgroundSignalThreshold = new QDoubleSpinBox;
    d->backgroundSignalThreshold->setValue(10);
    d->backgroundSignalThreshold->setRange(0, 1000);
    d->backgroundSignalThreshold->setDecimals(1);

    d->numberOfThreadsValue = new QSpinBox;
    d->numberOfThreadsValue->setValue(itk::MultiThreader::GetGlobalDefaultNumberOfThreads());
    d->numberOfThreadsValue->setRange(1, itk::MultiThreader::GetGlobalDefaultNumberOfThreads());

    QLabel *trTimeLabel = new QLabel(tr("Acq. TR time:"));
    QHBoxLayout *trTimeLayout = new QHBoxLayout;
    trTimeLayout->addWidget ( trTimeLabel );
    trTimeLayout->addWidget ( d->trTime );

    QLabel *firstFALabel = new QLabel(tr("First flip angle:"));
    QHBoxLayout *firstFALayout = new QHBoxLayout;
    firstFALayout->addWidget ( firstFALabel );
    firstFALayout->addWidget ( d->firstFlipAngle );

    QLabel *secondFALabel = new QLabel(tr("Second flip angle:"));
    QHBoxLayout *secondFALayout = new QHBoxLayout;
    secondFALayout->addWidget ( secondFALabel );
    secondFALayout->addWidget ( d->secondFlipAngle );

    QLabel *upperBoundM0Label = new QLabel(tr("Upper bound M0:"));
    QHBoxLayout *upperBoundM0Layout = new QHBoxLayout;
    upperBoundM0Layout->addWidget ( upperBoundM0Label );
    upperBoundM0Layout->addWidget ( d->upperBoundM0 );

    QLabel *upperBoundT1Label = new QLabel(tr("Upper bound T1:"));
    QHBoxLayout *upperBoundT1Layout = new QHBoxLayout;
    upperBoundT1Layout->addWidget ( upperBoundT1Label );
    upperBoundT1Layout->addWidget ( d->upperBoundT1 );

    QLabel *signalBckgdThrLabel = new QLabel(tr("Signal threshold:"));
    QHBoxLayout *signalBckgdThrLayout = new QHBoxLayout;
    signalBckgdThrLayout->addWidget ( signalBckgdThrLabel );
    signalBckgdThrLayout->addWidget ( d->backgroundSignalThreshold );

    QLabel *threadsLabel = new QLabel(tr("Number of threads:"));
    QHBoxLayout *threadsLayout = new QHBoxLayout;
    threadsLayout->addWidget ( threadsLabel );
    threadsLayout->addWidget ( d->numberOfThreadsValue );

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(trTimeLayout);
    layout->addLayout(firstFALayout);
    layout->addLayout(secondFALayout);
    layout->addLayout(upperBoundM0Layout);
    layout->addLayout(upperBoundT1Layout);
    layout->addLayout(signalBckgdThrLayout);
    layout->addLayout(threadsLayout);
    layout->addWidget(runButton);
    layout->addWidget(d->progression_stack);

    widget->setLayout(layout);
    this->addWidget(widget);
    
    connect(runButton, SIGNAL(clicked()), this, SLOT(run()));

    // Add about plugin
    medPluginManager* pm = medPluginManager::instance();
    dtkPlugin* plugin = pm->plugin ( "animaSymmetryPlanePlugin" );
    setAboutPluginButton ( plugin );
    setAboutPluginVisibility( true );
}

animaDESPOT1RelaxometryToolBox::~animaDESPOT1RelaxometryToolBox()
{
    delete d;
    
    d = NULL;
}

bool animaDESPOT1RelaxometryToolBox::registered()
{
    return medToolBoxFactory::instance()->registerToolBox<animaDESPOT1RelaxometryToolBox>();
}

dtkPlugin* animaDESPOT1RelaxometryToolBox::plugin()
{
    medPluginManager* pm = medPluginManager::instance();
    dtkPlugin* plugin = pm->plugin ( "animaRelaxometryPlugin" );
    return plugin;
}

void animaDESPOT1RelaxometryToolBox::update(medAbstractData *data)
{

}

medAbstractData* animaDESPOT1RelaxometryToolBox::processOutput()
{
    if(!d->process)
        return NULL;
    
    return d->process->output();
}

void animaDESPOT1RelaxometryToolBox::run()
{
    if(!this->parentToolBox())
        return;
    
    d->process = dtkAbstractProcessFactory::instance()->createSmartPointer("animaDESPOT1Relaxometry");
    
    if(!this->parentToolBox()->data())
        return;
    
    d->process->setInputImage(this->parentToolBox()->data());
    d->process->setTRTime(d->trTime->value());
    d->process->setFirstFlipAngle(d->firstFlipAngle->value() * M_PI / 180.0);
    d->process->setSecondFlipAngle(d->secondFlipAngle->value() * M_PI / 180.0);
    d->process->setUpperBoundM0(d->upperBoundM0->value());
    d->process->setUpperBoundT1(d->upperBoundT1->value());
    d->process->setBackgroundSignalThreshold(d->backgroundSignalThreshold->value());
    d->process->setNumberOfThreads(d->numberOfThreadsValue->value());

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
