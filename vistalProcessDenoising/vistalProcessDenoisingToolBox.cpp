
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

};

vistalProcessDenoisingToolBox::vistalProcessDenoisingToolBox(QWidget *parent) : medToolBoxFilteringCustom(parent), d(new vistalProcessDenoisingToolBoxPrivate)
{
      // Parameters:

      QCheckBox *slope = new QCheckBox();
      slope->setChecked(true);

      QLineEdit *sigma = new QLineEdit("0");
      QLineEdit *beta = new QLineEdit("1");
      QLineEdit *neighborhoodSize = new QLineEdit("1");
      QLineEdit *volumeOfSearch = new QLineEdit("5");

      QCheckBox *weightingMethod = new QCheckBox();
      weightingMethod->setChecked(true);

      QCheckBox *neighborhoodType = new QCheckBox();
      neighborhoodType->setChecked(true);

      QFormLayout *parametersLayout = new QFormLayout();
      parametersLayout->addRow("Adaptive or constant slope ?",slope);
      parametersLayout->addRow("S&igma :",sigma);
      parametersLayout->addRow("&Beta :",beta);
      parametersLayout->addRow("&Neighboring size :",neighborhoodSize);
      parametersLayout->addRow("&Volume of search :",volumeOfSearch);
      parametersLayout->addRow("&Weighting method (Pearson divergence or classical exponential) ?",weightingMethod);
      parametersLayout->addRow("&Isotropic or cubic neighborhood ?",neighborhoodType);

      QGroupBox *groupParameters = new QGroupBox("Parameters");
      groupParameters->setLayout(parametersLayout);

      // Options:

      QCheckBox *blockApproach = new QCheckBox();
      blockApproach->setChecked(true);

      QLineEdit *distanceBetweenBlocks = new QLineEdit("2");

      QCheckBox *testOnMean = new QCheckBox();
      testOnMean->setChecked(true);

      QLineEdit *minimumMeanRatio = new QLineEdit("0.95");

      QCheckBox *testOnVar = new QCheckBox();
      testOnVar->setChecked(true);

      QLineEdit *minimumVarianceRatio = new QLineEdit("0.5");

      QLineEdit *n_thread = new QLineEdit("1");

      QFormLayout *optionsLayout = new QFormLayout();
      optionsLayout->addRow("NL means based on block approach ?",blockApproach);
      optionsLayout->addRow("Distance between blocks :",distanceBetweenBlocks);
      optionsLayout->addRow("Test on mean ?",testOnMean);
      optionsLayout->addRow("Lowest bound of mean ratio :",minimumMeanRatio);
      optionsLayout->addRow("Test on variance ?",testOnVar);
      optionsLayout->addRow("Lowest bound of variance ratio :",minimumVarianceRatio);
      optionsLayout->addRow("Number of threads :",n_thread);

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
      this->setWidget(widget);
      
      connect(runButton, SIGNAL(clicked()), this, SLOT(run()));


//      connect(slope,SIGNAL(stateChanged()),this,SLOT(setSlopeType(int)));
//      connect(sigma,SIGNAL(textChanged()),this,SLOT(setSigma));
//      connect(beta,SIGNAL(textChanged()),this,SLOT(setBeta));
//      connect(neighborhoodSize,SIGNAL(),this,SLOT(setNeighborhoodSize));
//      connect(volumeOfSearch,SIGNAL(),this,SLOT(setSearchVolumeSize));
//      connect(weightingMethod,SIGNAL(),this,SLOT(setWeightingMethod));
//      connect(neighborhoodType,SIGNAL(),this,SLOT(setNeighborhoodType));
//
//      connect(blockApproach,SIGNAL(),this,SLOT(setBlockApproach));
//      connect(distanceBetweenBlocks,SIGNAL(),this,SLOT(setDistanceBetweenBlocks));
//      connect(testOnMean,SIGNAL(),this,SLOT(setTestOnMean));
//      connect(minimumMeanRatio,SIGNAL(),this,SLOT(setMinimumMeanRatio));
//      connect(testOnVar,SIGNAL(),this,SLOT(setTestOnVar));
//      connect(minimumVarianceRatio,SIGNAL(),this,SLOT(setMinimumVarRatio));
//      connect(n_thread,SIGNAL(),this,SLOT(setNumberOfThreads));
//
//      connect(runButton, SIGNAL(clicked()), this, SLOT(run()));

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

void vistalProcessDenoisingToolBox::run(void)
{
    if(!this->parent())
        return;

    // Many choices here

//    dtkAbstractProcess *process = dtkAbstractProcessFactory::instance()->create("vistalProcessDenoising");

    // itkProcessRegistration *process_registration = dynamic_cast<itkProcessRegistration *>(process);
    // process->setMyWonderfullParameter(fronTheGui);
    // process->setMyWonderfullParameter(fronTheGui);

    // or ...

    // itkProcessRegistration *process = new itkProcessRegistration;
    // process->setMyWonderfullParameter(fronTheGui);
    // process->setMyWonderfullParameter(fronTheGui);

    // ----

//    if (!process)
//        return;
    
/*    process->setInput(fixedData,  0);
    process->setInput(movingData, 1);

    if (process->run()==0) {

        dtkAbstractData *output = process->output();

	if(output) {
	    movingView->setData(output);
	    fixedView->unlink (movingView);
	    fixedView->link (movingView);
	    movingView->update();
	    
	    if (fuseView) {
	        if (dtkAbstractViewInteractor *interactor = fuseView->interactor("v3dViewFuseInteractor")) {
		    interactor->setData(output, 1);
		    fuseView->update();
		}
	    }
	}
    }
*/    
//    delete process;
}

medToolBoxFilteringCustom *createVistalProcessDenoisingToolBox(void)
{
    return new vistalProcessDenoisingToolBox;
}
