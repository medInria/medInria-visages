
#include "vistalProcessSegmentationSTREM.h"
#include "vistalProcessSegmentationSTREMToolBox.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataImage.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewInteractor.h>

#include <medCore/medRunnableProcess.h>
#include <medCore/medJobManager.h>

#include <medGui/medToolBoxFactory.h>
#include <medGui/medToolBoxFiltering.h>
#include <medGui/medToolBoxFilteringCustom.h>
#include <medGui/medProgressionStack.h>
#include <medGui/medDropSite.h>
#include <medCore/medDataManager.h>

#include <QtGui>

class vistalProcessSegmentationSTREMToolBoxPrivate
{
public:

    medDropSite *dropSiteT1;
    medDropSite *dropSitePD;
    medDropSite *dropSiteT2;
    medDropSite *dropSiteMask;

    dtkAbstractData* dataT1;
    dtkAbstractData* dataPD;
    dtkAbstractData* dataT2;
    dtkAbstractData* dataMask;


    QPushButton *runButton;

    int startLock;

    dtkAbstractProcess* process;
    medProgressionStack * progression_stack;

};

vistalProcessSegmentationSTREMToolBox::vistalProcessSegmentationSTREMToolBox(QWidget *parent) : medToolBoxFilteringCustom(parent), d(new vistalProcessSegmentationSTREMToolBoxPrivate)
{

    d->dropSiteT1 = new medDropSite;
    d->dropSitePD = new medDropSite;
    d->dropSiteT2 = new medDropSite;
    d->dropSiteMask = new medDropSite;

    QGridLayout* imgL = new QGridLayout;
    imgL->addWidget(new QLabel("T1w Image"), 0,0);
    imgL->addWidget(d->dropSiteT1, 1,0);

    imgL->addWidget(new QLabel("PDw Image"), 0, 1);
    imgL->addWidget(d->dropSitePD, 1,1);

    imgL->addWidget(new QLabel("T2 or FLAIR"), 2, 0);
    imgL->addWidget(d->dropSiteT2, 3,0);

    imgL->addWidget(new QLabel("Brain Mask"), 2,1);
    imgL->addWidget(d->dropSiteMask, 3,1);


      // Run button:

      d->runButton = new QPushButton(tr("Run"));

      // Principal layout:

      QWidget *widget = new QWidget;
      d->progression_stack = new medProgressionStack(widget);

      QVBoxLayout *layprinc = new QVBoxLayout();
      layprinc->addLayout(imgL);
      layprinc->addWidget(d->runButton);
//      layprinc->addWidget(d->progression_stack);

      widget->setLayout(layprinc);

      // Main toolbox:
      this->setTitle("Segmentation settings");
      this->addWidget(widget);


      d->runButton->setDisabled(true); // Need to add all the data prior to start

      // Connect the created dropsite
      connect(d->dropSiteT1, SIGNAL(objectDropped()), this, SLOT(onT1ImageDropped()));

      connect(d->dropSiteT2, SIGNAL(objectDropped()), this, SLOT(onT2orFLAIRImageDropped()));
      connect(d->dropSitePD, SIGNAL(objectDropped()), this, SLOT(onPDImageDropped()));
      connect(d->dropSiteMask, SIGNAL(objectDropped()), this, SLOT(onMaskImageDropped()));

      connect(d->runButton, SIGNAL(clicked()), this, SLOT(run()));
}

vistalProcessSegmentationSTREMToolBox::~vistalProcessSegmentationSTREMToolBox(void)
{
    delete d;

    d = NULL;
}

bool vistalProcessSegmentationSTREMToolBox::registered(void)
{
    return medToolBoxFactory::instance()->registerCustomFilteringToolBox("Three Classes EM Segmentation with outliers detection",
                                                                           createVistalProcessSegmentationSTREMToolBox);
}


dtkAbstractData* vistalProcessSegmentationSTREMToolBox::processOutput(void)
{
        if(!d->process)
            return NULL;

        return d->process->output();
}


void vistalProcessSegmentationSTREMToolBox::run(void)
{
    if(!this->parent())
        return;

    d->process = dtkAbstractProcessFactory::instance()->create("vistalProcessSegmentationSTREM");

    if(!this->parent()->data())
        return;

    d->process->setInput(d->dataT1, 0);

//    d->process->setParameter((double)d->maxf->value(),0);
//    d->process->setParameter((double)d->rhob->value(),1);
//    d->process->setParameter((double)d->rhoe->value(),2);

/*    medRunnableProcess *runProcess = new medRunnableProcess;
    runProcess->setProcess (d->process);

    d->progression_stack->addJobItem(runProcess, "Progress:");

    connect (runProcess, SIGNAL (success  (QObject*)),  this, SIGNAL (success ()));
    connect (runProcess, SIGNAL (failure  (QObject*)),  this, SIGNAL (failure ()));
//    d->process->run();
    medJobManager::instance()->registerJobItem(runProcess);
    QThreadPool::globalInstance()->start(dynamic_cast<QRunnable*>(runProcess));
*/
}

void vistalProcessSegmentationSTREMToolBox::onT1ImageDropped()
{
  medDataIndex index = d->dropSiteT1->index();

  if (!index.isValid())
    return;

  d->dataT1 = medDataManager::instance()->data (index).data();

  if (!d->dataT1)
    return;

  d->startLock |= 1;
  if (d->startLock & 15)
      d->runButton->setEnabled(true);

        //emit dataSelected(d->data);
}


void vistalProcessSegmentationSTREMToolBox::onPDImageDropped()
{
  medDataIndex index = d->dropSitePD->index();

  if (!index.isValid())
    return;

  d->dataPD = medDataManager::instance()->data (index).data();

  if (!d->dataPD)
    return;

  d->startLock |= 2;
  if (d->startLock & 15)
      d->runButton->setEnabled(true);


        //emit dataSelected(d->data);
}

void vistalProcessSegmentationSTREMToolBox::onT2orFLAIRImageDropped()
{
  medDataIndex index = d->dropSiteT2->index();

  if (!index.isValid())
    return;

  d->dataT2 = medDataManager::instance()->data (index).data();

  if (!d->dataT2)
    return;
  d->startLock |= 4;
  if (d->startLock & 15)
      d->runButton->setEnabled(true);

        //emit dataSelected(d->data);
}

void vistalProcessSegmentationSTREMToolBox::onMaskImageDropped()
{
  medDataIndex index = d->dropSiteMask->index();

  if (!index.isValid())
    return;

  d->dataMask = medDataManager::instance()->data (index).data();

  if (!d->dataMask)
    return;

  d->startLock |= 6;

  if (d->startLock & 15)
      d->runButton->setEnabled(true);
        //emit dataSelected(d->data);
}



medToolBoxFilteringCustom *createVistalProcessSegmentationSTREMToolBox(QWidget *parent)
{
    return new vistalProcessSegmentationSTREMToolBox(parent);
}
