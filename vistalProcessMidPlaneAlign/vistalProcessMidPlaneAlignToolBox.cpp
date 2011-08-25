
#include "vistalProcessMidPlaneAlign.h"
#include "vistalProcessMidPlaneAlignToolBox.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewInteractor.h>

#include <medCore/medRunnableProcess.h>
#include <medCore/medJobManager.h>
#include <medAbstractDataImage.h>

#include <medToolBoxFactory.h>
#include <medToolBoxFiltering.h>
#include <medToolBoxFilteringCustom.h>
#include <medProgressionStack.h>

#include <QtGui>

class vistalProcessMidPlaneAlignToolBoxPrivate
{
public:
    QDoubleSpinBox *rhob;
    QDoubleSpinBox *rhoe;
    QSpinBox *maxf;

    dtkAbstractProcess* process;
    medProgressionStack * progression_stack;

};

vistalProcessMidPlaneAlignToolBox::vistalProcessMidPlaneAlignToolBox(QWidget *parent) : medToolBoxFilteringCustom(parent), d(new vistalProcessMidPlaneAlignToolBoxPrivate)
{
      // Parameters:

      QLabel *mxLbl = new QLabel("Max Function Call :");
      d->maxf = new QSpinBox();
      d->maxf->setRange(10,10000);
      d->maxf->setValue(500);
      QHBoxLayout* maxfunL = new QHBoxLayout;
      maxfunL->addWidget(mxLbl);
      maxfunL->addWidget(d->maxf);

      QLabel* rbLbl = new QLabel("Initial Search Radius:");
      d->rhob = new QDoubleSpinBox;
      d->rhob->setRange(0, 1000);
      d->rhob->setValue(5);
      QHBoxLayout* rbL = new QHBoxLayout;
      rbL->addWidget(rbLbl);
      rbL->addWidget(d->rhob);

      QLabel* reLbl = new QLabel("Final Radius:");
      d->rhoe = new QDoubleSpinBox;
      d->rhoe->setRange(0, 1);
      d->rhoe->setValue(5e-2);
      d->rhoe->setDecimals(5);

      QHBoxLayout* reL = new QHBoxLayout;
      reL->addWidget(reLbl);
      reL->addWidget(d->rhoe);

      QVBoxLayout *parametersLayout = new QVBoxLayout;
      parametersLayout->addLayout(maxfunL);
      parametersLayout->addLayout(rbL);
      parametersLayout->addLayout(reL);

      // Run button:

      QPushButton *runButton = new QPushButton(tr("Run"));

      // Principal layout:

      QWidget *widget = new QWidget;
      d->progression_stack = new medProgressionStack(widget);

      QVBoxLayout *layprinc = new QVBoxLayout();
      layprinc->addLayout(parametersLayout);
      layprinc->addWidget(runButton);
      layprinc->addWidget(d->progression_stack);

      widget->setLayout(layprinc);

      // Main toolbox:
      this->setTitle("Symmetry Plane settings");
      this->addWidget(widget);

      connect(runButton, SIGNAL(clicked()), this, SLOT(run()));

}

vistalProcessMidPlaneAlignToolBox::~vistalProcessMidPlaneAlignToolBox(void)
{
    delete d;

    d = NULL;
}

bool vistalProcessMidPlaneAlignToolBox::registered(void)
{
    return medToolBoxFactory::instance()->registerCustomFilteringToolBox("Mid-Sagittal Plane realign",
                                                                           createVistalProcessMidPlaneAlignToolBox);
}


dtkAbstractData* vistalProcessMidPlaneAlignToolBox::processOutput(void)
{
        if(!d->process)
            return NULL;

        return d->process->output();
}


void vistalProcessMidPlaneAlignToolBox::run(void)
{
    if(!this->parent())
        return;

    d->process = dtkAbstractProcessFactory::instance()->create("vistalProcessMidPlaneAlign");

    if(!this->parent()->data())
        return;

    d->process->setInput(this->parent()->data());

    d->process->setParameter((double)d->maxf->value(),0);
    d->process->setParameter((double)d->rhob->value(),1);
    d->process->setParameter((double)d->rhoe->value(),2);

    medRunnableProcess *runProcess = new medRunnableProcess;
    runProcess->setProcess (d->process);

    d->progression_stack->addJobItem(runProcess, "Progress:");

    connect (runProcess, SIGNAL (success  (QObject*)),  this, SIGNAL (success ()));
    connect (runProcess, SIGNAL (failure  (QObject*)),  this, SIGNAL (failure ()));
//    d->process->run();
    medJobManager::instance()->registerJobItem(runProcess);
    QThreadPool::globalInstance()->start(dynamic_cast<QRunnable*>(runProcess));

}

medToolBoxFilteringCustom *createVistalProcessMidPlaneAlignToolBox(QWidget *parent)
{
    return new vistalProcessMidPlaneAlignToolBox(parent);
}
