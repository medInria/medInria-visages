
#include "vistalProcessBiasRemoval.h"
#include "vistalProcessBiasRemovalToolBox.h"

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

class vistalProcessBiasRemovalToolBoxPrivate
{
public:
        QRadioButton *slope;
        QLineEdit *sigma;
        QLineEdit *beta;
        QLineEdit *neighborhoodSize;
        QLineEdit *volumeOfSearch;
        QRadioButton *weightingMethod;
        QRadioButton *neighborhoodType;

        QCheckBox *blockApproach;
        QLineEdit *distanceBetweenBlocks;
        QCheckBox *testOnMean;
        QLineEdit *minimumMeanRatio;
        QCheckBox *testOnVar;
        QLineEdit *minimumVarianceRatio;
        QLineEdit *n_thread;

        dtkAbstractProcess *process;
};

vistalProcessBiasRemovalToolBox::vistalProcessBiasRemovalToolBox(QWidget *parent) : medToolBoxFilteringCustom(parent), d(new vistalProcessBiasRemovalToolBoxPrivate)
{
      // Parameters:

      QLabel *slopeLabel = new QLabel("Slope :");
      d->slope = new QRadioButton("adaptive");
      d->slope->setChecked(true);
      QRadioButton *constantSlope = new QRadioButton("constant");

      QButtonGroup *slopeButtonGroup = new QButtonGroup(this);
      slopeButtonGroup->addButton(d->slope);
      slopeButtonGroup->addButton(constantSlope);
      slopeButtonGroup->setExclusive(true);

      QLabel *sigmaLabel = new QLabel("Sigma : ");
      d->sigma = new QLineEdit("0");

      QHBoxLayout *sigmaBox = new QHBoxLayout();
      sigmaBox->addWidget(sigmaLabel);
      sigmaBox->addWidget(d->sigma);

      QLabel *betaLabel = new QLabel("Beta : ");
      d->beta = new QLineEdit("0.5");

      QHBoxLayout *betaBox = new QHBoxLayout();
      betaBox->addWidget(betaLabel);
      betaBox->addWidget(d->beta);

      QLabel *neighborhoodSizeLabel = new QLabel("Neighborhood size :");
      d->neighborhoodSize = new QLineEdit("1");

      QHBoxLayout *nghborhd = new QHBoxLayout();
      nghborhd->addWidget(neighborhoodSizeLabel);
      nghborhd->addWidget(d->neighborhoodSize);

      QLabel *volumeOfSearchLabel = new QLabel("Volume Of Search :");
      d->volumeOfSearch = new QLineEdit("5");

      QHBoxLayout *volOfSrch = new QHBoxLayout();
      volOfSrch->addWidget(volumeOfSearchLabel);
      volOfSrch->addWidget(d->volumeOfSearch);

      QLabel *weightingMethodLabel = new QLabel("Weighting method :");
      d->weightingMethod = new QRadioButton("Pearson divergence");
      d->weightingMethod->setChecked(true);
      QRadioButton *classicExp = new QRadioButton("classic exponentional");

      QButtonGroup *weightingMethodGroup = new QButtonGroup(this);
      weightingMethodGroup->addButton(d->weightingMethod);
      weightingMethodGroup->addButton(classicExp);
      weightingMethodGroup->setExclusive(true);

      QLabel *neighborhoodLabel = new QLabel("Neighborhood type: ");
      d->neighborhoodType = new QRadioButton("isotropic");
      d->neighborhoodType->setChecked(true);
      QRadioButton *cubic = new QRadioButton("cubic");

      QButtonGroup *neighborhoodGroup = new QButtonGroup(this);
      neighborhoodGroup->addButton(d->neighborhoodType);
      neighborhoodGroup->addButton(cubic);
      neighborhoodGroup->setExclusive(true);

      QVBoxLayout *parametersLayout = new QVBoxLayout();
      parametersLayout->addWidget(slopeLabel);
      parametersLayout->addWidget(d->slope);
      parametersLayout->addWidget(constantSlope);
      parametersLayout->addWidget(sigmaLabel);
      parametersLayout->addLayout(sigmaBox);
      parametersLayout->addWidget(betaLabel);
      parametersLayout->addLayout(betaBox);
      parametersLayout->addWidget(neighborhoodSizeLabel);
      parametersLayout->addLayout(nghborhd);
      parametersLayout->addWidget(volumeOfSearchLabel);
      parametersLayout->addLayout(volOfSrch);
      parametersLayout->addWidget(weightingMethodLabel);
      parametersLayout->addWidget(d->weightingMethod);
      parametersLayout->addWidget(classicExp);
      parametersLayout->addWidget(neighborhoodLabel);
      parametersLayout->addWidget(d->neighborhoodType);
      parametersLayout->addWidget(cubic);

      QGroupBox *groupParameters = new QGroupBox("Mandatory");
      groupParameters->setLayout(parametersLayout);

      // Options:

      d->blockApproach = new QCheckBox("Use block approach");
      d->blockApproach->setChecked(true);

      QLabel *distanceBetBlocks = new QLabel("Distance between blocks :");
      d->distanceBetweenBlocks = new QLineEdit("2");

      QHBoxLayout *distBetBlocks = new QHBoxLayout();
      distBetBlocks->addWidget(distanceBetBlocks);
      distBetBlocks->addWidget(d->distanceBetweenBlocks);

      d->testOnMean = new QCheckBox("Use test on mean");
      d->testOnMean->setChecked(true);

      QLabel *minMeanRatioLabel = new QLabel("Lowest bound of mean ratio :");
      d->minimumMeanRatio = new QLineEdit("0.95");

      QHBoxLayout *minMeanRat = new QHBoxLayout();
      minMeanRat->addWidget(minMeanRatioLabel);
      minMeanRat->addWidget(d->minimumMeanRatio);

      d->testOnVar = new QCheckBox("Use test on variance");
      d->testOnVar->setChecked(true);

      QLabel *minVarRatioLabel = new QLabel("Lowest bound of variance ratio :");
      d->minimumVarianceRatio = new QLineEdit("0.5");

      QHBoxLayout *minVarRat = new QHBoxLayout();
      minVarRat->addWidget(minVarRatioLabel);
      minVarRat->addWidget(d->minimumVarianceRatio);

      QLabel *numberOfThreads = new QLabel("Multithread :");
      d->n_thread = new QLineEdit("2");

      QVBoxLayout *optionsLayout = new QVBoxLayout();
      optionsLayout->addWidget(d->blockApproach);
      optionsLayout->addWidget(distanceBetBlocks);
      optionsLayout->addWidget(d->distanceBetweenBlocks);
      optionsLayout->addWidget(d->testOnMean);
      optionsLayout->addWidget(minMeanRatioLabel);
      optionsLayout->addWidget(d->minimumMeanRatio);
      optionsLayout->addWidget(d->testOnVar);
      optionsLayout->addWidget(minVarRatioLabel);
      optionsLayout->addWidget(d->minimumVarianceRatio);
      optionsLayout->addWidget(numberOfThreads);
      optionsLayout->addWidget(d->n_thread);

      QGroupBox *groupOptions = new QGroupBox("Optional");
      groupOptions->setLayout(optionsLayout);

      // Run button:

      QPushButton *runButton = new QPushButton(tr("Run"));

      // Principal layout:

      QVBoxLayout *layprinc = new QVBoxLayout();
      layprinc->addWidget(groupParameters);
      layprinc->addWidget(groupOptions);
      layprinc->addWidget(runButton);

      QWidget *widget = new QWidget(this);
      widget->setLayout(layprinc);

      // Main toolbox:
      this->setTitle("NLMeans settings");
      this->addWidget(widget);

      connect(runButton, SIGNAL(clicked()), this, SLOT(run()));

}

vistalProcessBiasRemovalToolBox::~vistalProcessBiasRemovalToolBox(void)
{
    delete d;
    
    d = NULL;
}

bool vistalProcessBiasRemovalToolBox::registered(void)
{
    return medToolBoxFactory::instance()->registerCustomFilteringToolBox("BiasRemovalFilter",
                                                                           createVistalProcessBiasRemovalToolBox);
}


dtkAbstractData* vistalProcessBiasRemovalToolBox::processOutput(void)
{
        if(!d->process)
            return NULL;

        return d->process->output();
}


void vistalProcessBiasRemovalToolBox::run(void)
{
    if(!this->parent())
        return;

    d->process = dtkAbstractProcessFactory::instance()->create("vistalProcessBiasRemoval");

    if(!this->parent()->data())
        return;

    d->process->setInput(this->parent()->data());

    d->process->setParameter(d->sigma->text().toDouble(),0);
    d->process->setParameter(d->beta->text().toDouble(),1);
    d->process->setParameter((float)(d->slope->isChecked()),2);
    d->process->setParameter((float)(d->neighborhoodType->isChecked()),3);
    d->process->setParameter(d->neighborhoodSize->text().toDouble(),4);
    d->process->setParameter(d->volumeOfSearch->text().toDouble(),5);
    d->process->setParameter((float)(d->testOnMean->checkState() == Qt::Checked),6);
    d->process->setParameter((float)(d->testOnVar->checkState() == Qt::Checked),7);
    d->process->setParameter(d->minimumMeanRatio->text().toDouble(),8);
    d->process->setParameter(d->minimumVarianceRatio->text().toDouble(),9);
    d->process->setParameter((float)(d->weightingMethod->isChecked() == Qt::Checked),10);
    d->process->setParameter((float)(d->blockApproach->checkState() == Qt::Checked),11);
    d->process->setParameter(d->distanceBetweenBlocks->text().toDouble(),12);
    d->process->setParameter(d->n_thread->text().toDouble(),13);

    if(d->process->update()==0)
        emit success();
    else
        emit failure();

}

medToolBoxFilteringCustom *createVistalProcessBiasRemovalToolBox(QWidget *parent)
{
    return new vistalProcessBiasRemovalToolBox(parent);
}
