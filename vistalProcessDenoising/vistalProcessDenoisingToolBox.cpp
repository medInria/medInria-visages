
#include "vistalProcessDenoising.h"
#include "vistalProcessDenoisingToolBox.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataImage.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewInteractor.h>

#include <medGui/medToolBoxFactory.h>
#include <medGui/medToolBoxFiltering.h>
#include <medGui/medToolBoxFilteringCustom.h>

#include <QtGui>

class vistalProcessDenoisingToolBoxPrivate
{
public:
        QCheckBox *slope;
        QLineEdit *sigma;
        QLineEdit *beta;
        QLineEdit *neighborhoodSize;
        QLineEdit *volumeOfSearch;
        QCheckBox *weightingMethod;
        QCheckBox *neighborhoodType;

        QCheckBox *blockApproach;
        QLineEdit *distanceBetweenBlocks;
        QCheckBox *testOnMean;
        QLineEdit *minimumMeanRatio;
        QCheckBox *testOnVar;
        QLineEdit *minimumVarianceRatio;
        QLineEdit *n_thread;

        dtkAbstractProcess *process;

};

vistalProcessDenoisingToolBox::vistalProcessDenoisingToolBox(QWidget *parent) : medToolBoxFilteringCustom(parent), d(new vistalProcessDenoisingToolBoxPrivate)
{
      // Parameters:

      d->slope = new QCheckBox();
      d->slope->setChecked(true);

      d->sigma = new QLineEdit("0");
      d->beta = new QLineEdit("1");
      d->neighborhoodSize = new QLineEdit("1");
      d->volumeOfSearch = new QLineEdit("5");

      d->weightingMethod = new QCheckBox();
      d->weightingMethod->setChecked(true);

      d->neighborhoodType = new QCheckBox();
      d->neighborhoodType->setChecked(true);

      QFormLayout *parametersLayout = new QFormLayout();
      parametersLayout->addRow("Adaptive/Constant slope ?",d->slope);
      parametersLayout->addRow("S&igma :",d->sigma);
      parametersLayout->addRow("&Beta :",d->beta);
      parametersLayout->addRow("&Neighboring size :",d->neighborhoodSize);
      parametersLayout->addRow("&Volume of search :",d->volumeOfSearch);
      parametersLayout->addRow("&Weighting method (Pearson divergence/classic exponential) ?",d->weightingMethod);
      parametersLayout->addRow("&Isotropic/Cubic neighborhood ?",d->neighborhoodType);

      QGroupBox *groupParameters = new QGroupBox("Parameters");
      groupParameters->setLayout(parametersLayout);

      // Options:

      d->blockApproach = new QCheckBox();
      d->blockApproach->setChecked(true);
      d->distanceBetweenBlocks = new QLineEdit("2");
      d->testOnMean = new QCheckBox();
      d->testOnMean->setChecked(true);
      d->minimumMeanRatio = new QLineEdit("0.95");
      d->testOnVar = new QCheckBox();
      d->testOnVar->setChecked(true);
      d->minimumVarianceRatio = new QLineEdit("0.5");
      d->n_thread = new QLineEdit("1");

      QFormLayout *optionsLayout = new QFormLayout();
      optionsLayout->addRow("Block approach ?",d->blockApproach);
      optionsLayout->addRow("Distance between blocks :",d->distanceBetweenBlocks);
      optionsLayout->addRow("Test on mean ?",d->testOnMean);
      optionsLayout->addRow("Lowest bound of mean ratio :",d->minimumMeanRatio);
      optionsLayout->addRow("Test on variance ?",d->testOnVar);
      optionsLayout->addRow("Lowest bound of variance ratio :",d->minimumVarianceRatio);
      optionsLayout->addRow("Number of threads :",d->n_thread);

      QGroupBox *groupOptions = new QGroupBox("Options");
      groupOptions->setLayout(optionsLayout);

      // Run button:

      QPushButton *runButton = new QPushButton(tr("Run"));

      // Principal layout:

      QFormLayout *layprinc = new QFormLayout();
      layprinc->addWidget(groupParameters);
      layprinc->addWidget(groupOptions);
      layprinc->addWidget(runButton);

      QWidget *widget = new QWidget(this);
      widget->setLayout(layprinc);

      //Toolbox:
      this->setTitle("NL means - Toolbox");
      this->addWidget(widget);
      
      connect(runButton, SIGNAL(clicked()), this, SLOT(run()));

}

vistalProcessDenoisingToolBox::~vistalProcessDenoisingToolBox(void)
{
    delete d;
    
    d = NULL;
}

bool vistalProcessDenoisingToolBox::registered(void)
{
    return medToolBoxFactory::instance()->registerCustomFilteringToolBox("NLmeansDenoising",
                                                                           createVistalProcessDenoisingToolBox);
}


dtkAbstractData* vistalProcessDenoisingToolBox::processOutput(void)
{
        if(!d->process)
            return NULL;

        return d->process->output();
}




void vistalProcessDenoisingToolBox::run(void)
{
    if(!this->parent())
        return;

    d->process = dtkAbstractProcessFactory::instance()->create("vistalProcessDenoising");

    if(!this->parent()->data())
        return;

    d->process->setInput(this->parent()->data());

    d->process->setParameter(d->sigma->text().toDouble(),0);
    d->process->setParameter(d->beta->text().toDouble(),1);
    d->process->setParameter((float)(d->slope->checkState() == Qt::Checked),2);
    d->process->setParameter((float)(d->neighborhoodType->checkState() == Qt::Checked),3);
    d->process->setParameter(d->neighborhoodSize->text().toDouble(),4);
    d->process->setParameter(d->volumeOfSearch->text().toDouble(),5);
    d->process->setParameter((float)(d->testOnMean->checkState() == Qt::Checked),6);
    d->process->setParameter((float)(d->testOnVar->checkState() == Qt::Checked),7);
    d->process->setParameter(d->minimumMeanRatio->text().toDouble(),8);
    d->process->setParameter(d->minimumVarianceRatio->text().toDouble(),9);
    d->process->setParameter((float)(d->weightingMethod->checkState() == Qt::Checked),10);
    d->process->setParameter((float)(d->blockApproach->checkState() == Qt::Checked),11);
    d->process->setParameter(d->distanceBetweenBlocks->text().toDouble(),12);
    d->process->setParameter(d->n_thread->text().toDouble(),13);

    if(d->process->update()==0)
        emit success();
    else
        emit failure();

}

medToolBoxFilteringCustom *createVistalProcessDenoisingToolBox(QWidget *parent)
{
    return new vistalProcessDenoisingToolBox(parent);
}
