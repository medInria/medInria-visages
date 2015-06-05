/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <animaT2Relaxometry.h>
#include <animaT2RelaxometryToolBox.h>
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
#include <medDropSite.h>

#include <medAbstractImageData.h>

#include <medToolBoxFactory.h>
#include <medFilteringSelectorToolBox.h>
#include <medProgressionStack.h>
#include <medPluginManager.h>
#include <medDataManager.h>

class animaT2RelaxometryToolBoxPrivate
{
public:
    dtkSmartPointer <animaT2Relaxometry> process;
    medProgressionStack * progression_stack;

    QDoubleSpinBox *trTime;
    QDoubleSpinBox *echoSpacing;
    QDoubleSpinBox *upperBoundM0;
    QDoubleSpinBox *upperBoundT2;
    QDoubleSpinBox *backgroundSignalThreshold;
    QSpinBox *numberOfThreadsValue;

    medDropSite *t1MapDropSite;
    dtkSmartPointer <medAbstractImageData> t1Map;
};

animaT2RelaxometryToolBox::animaT2RelaxometryToolBox(QWidget *parent) : medFilteringAbstractToolBox(parent), d(new animaT2RelaxometryToolBoxPrivate)
{
    QWidget *widget = new QWidget(this);
    
    QPushButton *runButton = new QPushButton(tr("Run"), this);
    
    this->setTitle("T2 Relaxometry");
    
    // progression stack
    d->progression_stack = new medProgressionStack(widget);

    d->t1MapDropSite = new medDropSite;
    d->t1MapDropSite->setCanAutomaticallyChangeAppereance(false);
    connect(d->t1MapDropSite, SIGNAL(objectDropped(const medDataIndex &)), this, SLOT(setT1Map(const medDataIndex &)));
    
    d->trTime = new QDoubleSpinBox;
    d->trTime->setRange(0, 10000);
    d->trTime->setValue(4500);
    d->trTime->setDecimals(1);

    d->echoSpacing = new QDoubleSpinBox;
    d->echoSpacing->setValue(10);
    d->echoSpacing->setRange(0, 100);
    d->echoSpacing->setDecimals(1);

    d->upperBoundM0 = new QDoubleSpinBox;
    d->upperBoundM0->setRange(0, 10000);
    d->upperBoundM0->setValue(5000);
    d->upperBoundM0->setDecimals(1);

    d->upperBoundT2 = new QDoubleSpinBox;
    d->upperBoundT2->setRange(0, 10000);
    d->upperBoundT2->setValue(800);
    d->upperBoundT2->setDecimals(1);

    d->backgroundSignalThreshold = new QDoubleSpinBox;
    d->backgroundSignalThreshold->setValue(10);
    d->backgroundSignalThreshold->setRange(0, 1000);
    d->backgroundSignalThreshold->setDecimals(1);

    d->numberOfThreadsValue = new QSpinBox;
    d->numberOfThreadsValue->setValue(itk::MultiThreader::GetGlobalDefaultNumberOfThreads());
    d->numberOfThreadsValue->setRange(1, itk::MultiThreader::GetGlobalDefaultNumberOfThreads());

    QVBoxLayout *t1DropLayout = new QVBoxLayout;
    t1DropLayout->addWidget(d->t1MapDropSite);
    t1DropLayout->addWidget(new QLabel("Initial T1 image"));
    t1DropLayout->setAlignment(Qt::AlignCenter);

    QLabel *trTimeLabel = new QLabel(tr("Acq. TR time:"));
    QHBoxLayout *trTimeLayout = new QHBoxLayout;
    trTimeLayout->addWidget ( trTimeLabel );
    trTimeLayout->addWidget ( d->trTime );

    QLabel *echoSpacingLabel = new QLabel(tr("Echo spacing:"));
    QHBoxLayout *echoSpacingLayout = new QHBoxLayout;
    echoSpacingLayout->addWidget ( echoSpacingLabel );
    echoSpacingLayout->addWidget ( d->echoSpacing );

    QLabel *upperBoundM0Label = new QLabel(tr("Upper bound M0:"));
    QHBoxLayout *upperBoundM0Layout = new QHBoxLayout;
    upperBoundM0Layout->addWidget ( upperBoundM0Label );
    upperBoundM0Layout->addWidget ( d->upperBoundM0 );

    QLabel *upperBoundT2Label = new QLabel(tr("Upper bound T2:"));
    QHBoxLayout *upperBoundT2Layout = new QHBoxLayout;
    upperBoundT2Layout->addWidget ( upperBoundT2Label );
    upperBoundT2Layout->addWidget ( d->upperBoundT2 );

    QLabel *signalBckgdThrLabel = new QLabel(tr("Signal threshold:"));
    QHBoxLayout *signalBckgdThrLayout = new QHBoxLayout;
    signalBckgdThrLayout->addWidget ( signalBckgdThrLabel );
    signalBckgdThrLayout->addWidget ( d->backgroundSignalThreshold );

    QLabel *threadsLabel = new QLabel(tr("Number of threads:"));
    QHBoxLayout *threadsLayout = new QHBoxLayout;
    threadsLayout->addWidget ( threadsLabel );
    threadsLayout->addWidget ( d->numberOfThreadsValue );

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(t1DropLayout);
    layout->addLayout(trTimeLayout);
    layout->addLayout(echoSpacingLayout);
    layout->addLayout(upperBoundM0Layout);
    layout->addLayout(upperBoundT2Layout);
    layout->addLayout(signalBckgdThrLayout);
    layout->addLayout(threadsLayout);
    layout->addWidget(runButton);
    layout->addWidget(d->progression_stack);

    widget->setLayout(layout);
    this->addWidget(widget);
    
    connect(runButton, SIGNAL(clicked()), this, SLOT(run()), Qt::UniqueConnection);
}

animaT2RelaxometryToolBox::~animaT2RelaxometryToolBox()
{
    delete d;
    
    d = NULL;
}

void animaT2RelaxometryToolBox::setT1Map(const medDataIndex &index)
{
    d->t1Map = dynamic_cast <medAbstractImageData *> (medDataManager::instance()->retrieveData(index));

    if (!d->t1Map)
        return;

    d->t1MapDropSite->setPixmap(medDataManager::instance()->thumbnail(index).scaled(d->t1MapDropSite->sizeHint()));
}

bool animaT2RelaxometryToolBox::registered()
{
    return medToolBoxFactory::instance()->registerToolBox<animaT2RelaxometryToolBox>();
}

dtkPlugin* animaT2RelaxometryToolBox::plugin()
{
    medPluginManager* pm = medPluginManager::instance();
    dtkPlugin* plugin = pm->plugin ( "animaRelaxometryPlugin" );
    return plugin;
}

void animaT2RelaxometryToolBox::update(medAbstractData *data)
{

}

medAbstractData* animaT2RelaxometryToolBox::processOutput()
{
    if(!d->process)
        return NULL;
    
    return d->process->output();
}

void animaT2RelaxometryToolBox::run()
{
    if(!this->parentToolBox())
        return;
    
    d->process = dtkAbstractProcessFactory::instance()->createSmartPointer("animaT2Relaxometry");
    
    if(!this->parentToolBox()->data())
        return;
    
    d->process->setInputImage(this->parentToolBox()->data());
    d->process->setTRTime(d->trTime->value());
    d->process->setEchoSpacing(d->echoSpacing->value());
    d->process->setUpperBoundM0(d->upperBoundM0->value());
    d->process->setUpperBoundT2(d->upperBoundT2->value());
    d->process->setBackgroundSignalThreshold(d->backgroundSignalThreshold->value());
    if (d->t1Map)
        d->process->setT1Map(d->t1Map.data());
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
