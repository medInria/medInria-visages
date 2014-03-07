// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////


#include "animaPyramidalBMRegistration.h"
#include "animaPyramidalBMRegistrationToolBox.h"

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
#include <medRegistrationSelectorToolBox.h>
#include <medProgressionStack.h>
#include <medPluginManager.h>
#include <medToolBoxTab.h>

#include <rpiCommonTools.hxx>
#include <rpiAnimaPyramidalBMRegistration.h>

class animaPyramidalBMRegistrationToolBoxPrivate
{
public:
 
    QLineEdit *initTransformFileEdit;
    QString initTransformFile;
    
    //Block Initialisation Parameters
    QSpinBox *blockSize;
    QSpinBox *blockSpacing;
    QDoubleSpinBox *stdThreshold;

    //Block Match Parameters
    QComboBox *transform;
    QComboBox * metric;
    QComboBox * optimzer;
    QSpinBox *maxIterations;
    QDoubleSpinBox * minError;
    QSpinBox *optIterations;
    QDoubleSpinBox * searchRadius;
    QDoubleSpinBox * searchAngleRadius;
    QDoubleSpinBox * searchSkewRadius;
    QDoubleSpinBox * searchScaleRadius;
    QDoubleSpinBox * finalRadius;
    QDoubleSpinBox * stepSize;
    QDoubleSpinBox * translateUpperBound;
    QDoubleSpinBox * angleUpperBound;
    QDoubleSpinBox * skewUpperBound;
    QDoubleSpinBox * scaleUpperBound;

    //Agregation Parameters:
    QComboBox *agregator;
    QComboBox *outputTransform;
    QDoubleSpinBox * agregThreshold;
    QDoubleSpinBox * stoppingThreshold;
    
    //Pyramid parameters:
    QSpinBox *pyramidLevels;
    QSpinBox *lastLevel;
    
    //Global Parameters:
    QSpinBox *threads;
      

    medProgressionStack * progression_stack;
};

animaPyramidalBMRegistrationToolBox::animaPyramidalBMRegistrationToolBox(QWidget *parent) : medRegistrationAbstractToolBox(parent), d(new animaPyramidalBMRegistrationToolBoxPrivate)
{
    //QWidget *widget = new QWidget(this);
    //QToolBox *widget = new QToolBox(this);
    medToolBoxTab *widget = new medToolBoxTab(this);

    QPushButton *runButton = new QPushButton(tr("Run"), this);

    this->setTitle("Pyramidal BM Registration");

    // progression stack
    d->progression_stack = new medProgressionStack(widget);
    QHBoxLayout *progressStackLayout = new QHBoxLayout;
    progressStackLayout->addWidget(d->progression_stack);
    
    
    d->initTransformFileEdit = new QLineEdit;
    QPushButton *openTransformFileButton = new QPushButton(tr("..."), this);


    // Block Initialisation Parameters
    d->blockSize = new QSpinBox;
    d->blockSize->setToolTip("Size of the blocks");
    d->blockSize->setValue(5);
    
    d->blockSpacing = new QSpinBox;
    d->blockSpacing->setToolTip("Spacing between blocks");
    d->blockSpacing->setValue(5);
    
    d->stdThreshold = new QDoubleSpinBox;
    d->stdThreshold->setToolTip("Threshold block standard deviation");
    d->stdThreshold->setValue(5);
    

    // Block Match Parameters
    d->transform = new QComboBox;
    d->transform->setToolTip("Transformation computed between blocks");
    QStringList transformList;
    transformList << "Translation" << "Rigid" << "Affine";
    d->transform->addItems ( transformList );
    
    d->metric = new QComboBox;
    d->metric->setToolTip("Similarity metric between blocks");
    QStringList metricList;
    metricList << "SquaredCorrelation" << "Correlation" << "MeanSquares";
    d->metric->addItems ( metricList );
    
    d->optimzer = new QComboBox;
    d->optimzer->setToolTip("Optimizer for optimal block search");
    QStringList optimzerList;
    optimzerList << "Exhaustive" << "Bobyqa";
    d->optimzer->addItems ( optimzerList );
    d->optimzer->setCurrentIndex(2);
    
    d->maxIterations = new QSpinBox;
    d->maxIterations->setToolTip("Maximum Block Match Iteration");
    d->maxIterations->setValue(10);
    
    d->minError = new QDoubleSpinBox;
    d->minError->setToolTip("Minimal distance between consecutive estimated transforms");
    d->minError->setDecimals(3);
    d->minError->setValue(0.01);   
    
    d->optIterations = new QSpinBox;
    d->optIterations->setToolTip("Maximum Local Optimizer Iterations");
    d->optIterations->setRange(0,10000);
    d->optIterations->setValue(100);
    
    d->searchRadius = new QDoubleSpinBox;
    d->searchRadius->setToolTip("The search radius (exhaustive search window, rho start for newuoa");
    d->searchRadius->setValue(2);
    
    d->searchAngleRadius = new QDoubleSpinBox;
    d->searchAngleRadius->setToolTip("The search angle radius (rho start for newuoa on angles part)");
    d->searchAngleRadius->setValue(5);
    
    d->searchSkewRadius = new QDoubleSpinBox;
    d->searchSkewRadius->setToolTip("The search skew radius (rho start for newuoa on skews part)");
    d->searchSkewRadius->setValue(5);
    
    d->searchScaleRadius = new QDoubleSpinBox;
    d->searchScaleRadius->setToolTip("The search scale radius (rho start for newuoa on scales part)");
    d->searchScaleRadius->setValue(0.1);

    d->finalRadius = new QDoubleSpinBox;
    d->finalRadius->setToolTip("The final radius (rho end for newuoa)");
    d->finalRadius->setDecimals(4);
    d->finalRadius->setValue(0.001);
    
    d->stepSize = new QDoubleSpinBox;
    d->stepSize->setToolTip("The  stepping size (for exhaustive search)");
    d->stepSize->setValue(1);

    d->translateUpperBound = new QDoubleSpinBox;
    d->translateUpperBound->setToolTip("The upper bound on translation for bobyqa (in mm)");
    d->translateUpperBound->setValue(50);
    
    d->angleUpperBound = new QDoubleSpinBox;
    d->angleUpperBound->setToolTip("The upper bound on angles for bobyqa (in degrees)");
    d->angleUpperBound->setRange(0,360);
    d->angleUpperBound->setValue(180);
    
    d->skewUpperBound = new QDoubleSpinBox;
    d->skewUpperBound->setToolTip("The upper bound on skews for bobyqa (in degrees)");
    d->skewUpperBound->setRange(0,360);
    d->skewUpperBound->setValue(45);
    
    d->scaleUpperBound = new QDoubleSpinBox;
    d->scaleUpperBound->setToolTip("The upper bound on scales for bobyqa");
    d->scaleUpperBound->setValue(3);
    


    // Agregation Parameters:
    d->agregator = new QComboBox;
    d->agregator->setToolTip("Type of Agregator");
    QStringList agregatorList;
    agregatorList << "MEstimation" << "LeastSquares" << "LeastTrimmedSquares";
    d->agregator->addItems ( agregatorList );
    
    d->outputTransform = new QComboBox;    
    d->outputTransform->setToolTip("Type of Estimated transformations");
    QStringList outputTransformList;
    outputTransformList << "Rigid" << "Translation" << "Affine";
    d->outputTransform->addItems (outputTransformList );
    
    d->agregThreshold = new QDoubleSpinBox;
    d->agregThreshold->setToolTip("Agregator threshold value (for M-estimation or LTS)");
    d->agregThreshold->setValue(0.7);
    d->agregThreshold->setMaximum(1.0);
    d->agregThreshold->setSingleStep(0.1);
    
    d->stoppingThreshold = new QDoubleSpinBox;
    d->stoppingThreshold->setToolTip("LTS Stopping Threshold");
    d->stoppingThreshold->setDecimals(3);
    d->stoppingThreshold->setValue(0.01);
    

    // Pyramid parameters:
    d->pyramidLevels = new QSpinBox;
    d->pyramidLevels->setToolTip("Number of pyramid levels");
    d->pyramidLevels->setValue(4);
    
    d->lastLevel = new QSpinBox;
    d->lastLevel->setToolTip("Index of the last pyramid level explored (0 is full resolution)");
    d->lastLevel->setValue(1);
    
     
    // Global Parameters:  
    d->threads = new QSpinBox;
    d->threads->setToolTip("Number of Execution Threads");
    d->threads->setValue(itk::MultiThreader::GetGlobalDefaultNumberOfThreads());
    d->threads->setRange(1, itk::MultiThreader::GetGlobalDefaultNumberOfThreads());

    
    // Tranform Parameters Layout
    QHBoxLayout *transformLayout = new QHBoxLayout;
    QLabel *initTransformLabel = new QLabel(tr("Init. Transform"));
    transformLayout->addWidget(initTransformLabel);
    transformLayout->addWidget(d->initTransformFileEdit);
    transformLayout->addWidget(openTransformFileButton);
    

    // Block Initialisation Parameters Layout
    QFormLayout *blockInitLayout = new QFormLayout();
    blockInitLayout->addRow(new QLabel(tr("Block size"),this),d->blockSize);
    blockInitLayout->addRow(new QLabel(tr("Block spacing"),this),d->blockSpacing);
    blockInitLayout->addRow(new QLabel(tr("Std Threshold"),this),d->stdThreshold);

    QGroupBox *blockInitGroupBox = new QGroupBox(tr("Block Initialisation Parameters"));
    blockInitGroupBox->setLayout(blockInitLayout);


    // Block Match Parameters Layout
    QFormLayout *blockMatchLayout = new QFormLayout();
    blockMatchLayout->addRow(new QLabel(tr("Transform"),this),d->transform);
    blockMatchLayout->addRow(new QLabel(tr("Metric"),this),d->metric);
    blockMatchLayout->addRow(new QLabel(tr("Optimzer"),this),d->optimzer);
    blockMatchLayout->addRow(new QLabel(tr("Max Iterations"),this),d->maxIterations);
    blockMatchLayout->addRow(new QLabel(tr("Min error"),this),d->minError);
    blockMatchLayout->addRow(new QLabel(tr("Optimzer Iterations"),this),d->optIterations);
    blockMatchLayout->addRow(new QLabel(tr("Search Radius"),this),d->searchRadius);
    blockMatchLayout->addRow(new QLabel(tr("Search Angle Radius"),this),d->searchAngleRadius);
    blockMatchLayout->addRow(new QLabel(tr("Search Skew Radius"),this),d->searchSkewRadius);
    blockMatchLayout->addRow(new QLabel(tr("Seardch Scale Radius"),this),d->searchScaleRadius);
    blockMatchLayout->addRow(new QLabel(tr("Final Radius"),this),d->finalRadius);
    blockMatchLayout->addRow(new QLabel(tr("Step Size"),this),d->stepSize);
    blockMatchLayout->addRow(new QLabel(tr("Translate Upper"),this),d->translateUpperBound);
    blockMatchLayout->addRow(new QLabel(tr("Angle Upper"),this),d->angleUpperBound);
    blockMatchLayout->addRow(new QLabel(tr("Skew Upper"),this),d->skewUpperBound);
    blockMatchLayout->addRow(new QLabel(tr("Scale Upper"),this),d->scaleUpperBound);

    QGroupBox *blockMatchGroupBox = new QGroupBox(tr("Block Match Parameters"));
    blockMatchGroupBox->setAutoFillBackground(false);
    blockMatchGroupBox->setBackgroundRole(this->backgroundRole());
    blockMatchGroupBox->setLayout(blockMatchLayout);
    blockMatchGroupBox->setForegroundRole(this->foregroundRole());
    
      
    // Agregation Parameters Layout
    QFormLayout *agregationParamLayout = new QFormLayout();
    agregationParamLayout->addRow(new QLabel(tr("Agregator"),this),d->agregator);
    agregationParamLayout->addRow(new QLabel(tr("Output Transform"),this),d->outputTransform);
    agregationParamLayout->addRow(new QLabel(tr("Agreg. Threshold"),this),d->agregThreshold);
    agregationParamLayout->addRow(new QLabel(tr("Stopping Threshold"),this),d->stoppingThreshold);

    QGroupBox *agregationParamGroupBox = new QGroupBox(tr("Agregation Parameters"));
    agregationParamGroupBox->setLayout(agregationParamLayout);
    
    
    // Pyramid Parameters Layout   
    QFormLayout *pyramidParamLayout = new QFormLayout();
    pyramidParamLayout->addRow(new QLabel(tr("Pyramid Levels"),this),d->pyramidLevels);
    pyramidParamLayout->addRow(new QLabel(tr("Last Level"),this),d->lastLevel);

    QGroupBox *pyramidParamGroupBox = new QGroupBox(tr("Pyramid Parameters"));
    pyramidParamGroupBox->setLayout(pyramidParamLayout);
    
    
    // Global Parameters Layout 
    QFormLayout *globalParamLayout = new QFormLayout();
    globalParamLayout->addRow(new QLabel(tr("Threads"),this),d->threads);

    QGroupBox *globalParamGroupBox = new QGroupBox(tr("Global Parameters"));
    globalParamGroupBox->setLayout(globalParamLayout);
    
    QWidget *header = new QWidget;
    QVBoxLayout *layoutheader = new QVBoxLayout(header);   
    layoutheader->addWidget(runButton);
    layoutheader->addWidget(d->progression_stack);
    
    QWidget *page1 = new QWidget;
    QVBoxLayout *layout1 = new QVBoxLayout(page1);   
    layout1->addLayout(transformLayout);
    layout1->addWidget(blockInitGroupBox);
    layout1->addWidget(agregationParamGroupBox);
    layout1->addWidget(pyramidParamGroupBox);
    layout1->addWidget(globalParamGroupBox);
     
    QWidget *page2 = new QWidget;
    QVBoxLayout *layout2 = new QVBoxLayout(page2);
    layout2->addWidget(blockMatchGroupBox);
  
    widget->addTab(page1, "Main");
    widget->addTab(page2, "Block Match Parameters ");
   
    this->addWidget( header );
    this->addWidget( widget );

    connect(runButton, SIGNAL(clicked()), this, SLOT(run()));
    connect(openTransformFileButton, SIGNAL (clicked()), this, SLOT(openTransformFile()));
    
    connect(d->optimzer, SIGNAL(currentIndexChanged(int)), this, SLOT(updateBMParams(int)));
    connect(d->metric, SIGNAL(currentIndexChanged(int)), this, SLOT(updateBMParams(int)));
    connect(d->transform, SIGNAL(currentIndexChanged(int)), this, SLOT(updateBMParams(int)));
    connect(d->agregator, SIGNAL(currentIndexChanged(int)), this, SLOT(updateBMParams(int)));
    
    updateBMParams(0);
    
    // Add about plugin
    medPluginManager* pm = medPluginManager::instance();
    dtkPlugin* plugin = pm->plugin ( "animaPyramidalBMRegistrationPlugin" );
    setAboutPluginButton ( plugin );
    setAboutPluginVisibility( true );
}

animaPyramidalBMRegistrationToolBox::~animaPyramidalBMRegistrationToolBox(void)
{
    delete d;
    
    d = NULL;
}

bool animaPyramidalBMRegistrationToolBox::registered(void)
{
    return medToolBoxFactory::instance()->
    registerToolBox<animaPyramidalBMRegistrationToolBox>("animaPyramidalBMRegistrationToolBox",
                               tr("Pyramidal BM Registration"),
                               tr("Pyramidal global block-matching registration"),
                               QStringList() << "registration");
}

void animaPyramidalBMRegistrationToolBox::run(void)
{ 
    if(!this->parentToolBox())
        return;

    dtkSmartPointer <dtkAbstractProcess> process;

    if (this->parentToolBox()->process() &&
        (this->parentToolBox()->process()->identifier() == "animaPyramidalBMRegistration"))
    {
        process = this->parentToolBox()->process();   
    }
    else
    {
        process = dtkAbstractProcessFactory::instance()->createSmartPointer("animaPyramidalBMRegistration");

        this->parentToolBox()->setProcess(process);
    }
    
    dtkSmartPointer<dtkAbstractData> fixedData = this->parentToolBox()->fixedData();
    dtkSmartPointer<dtkAbstractData> movingData = this->parentToolBox()->movingData();    
    
    if (!fixedData || !movingData)
        return;
    
    animaPyramidalBMRegistration *process_Registration = dynamic_cast<animaPyramidalBMRegistration *>(process.data());
    if (!process_Registration)
    {
        qWarning() << "registration process doesn't exist" ;
        return;
    }

    // Setting process arguments
    process_Registration->initTransformFile( d->initTransformFile );
    process_Registration->setBlockSize( d->blockSize->value() );
    process_Registration->setBlockSpacing( d->blockSpacing->value() );
    process_Registration->setStDevThreshold( d->stdThreshold->value() );
    process_Registration->setTransform( d->transform->currentIndex() );
    process_Registration->setMetric( d->metric->currentIndex() );
    process_Registration->setOptimizer( d->optimzer->currentIndex() );
    process_Registration->setMaximumIterations( d->maxIterations->value() );
    process_Registration->setMinimalTransformError( d->minError->value() );
    process_Registration->setOptimizerMaximumIterations( d->optIterations->value() );
    process_Registration->setSearchRadius( d->searchRadius->value() );
    process_Registration->setSearchAngleRadius( d->searchAngleRadius->value() );
    process_Registration->setSearchSkewRadius( d->searchSkewRadius->value() );
    process_Registration->setSearchScaleRadius( d->searchScaleRadius->value() );
    process_Registration->setStepSize( d->stepSize->value() );
    process_Registration->setTranlateUpperBound( d->translateUpperBound->value() );
    process_Registration->setAngleUpperBound( d->angleUpperBound->value() );
    process_Registration->setSkewUpperBound( d->skewUpperBound->value() );
    process_Registration->setScaleUpperBound( d->scaleUpperBound->value() );
    process_Registration->setAgregator( d->agregator->currentIndex() );
    process_Registration->setOutputTransformType( d->outputTransform->currentIndex() );
    process_Registration->setAgregThreshold( d->agregThreshold->value() );
    process_Registration->setSeStoppingThreshold( d->stoppingThreshold->value() );
    process_Registration->setNumberOfPyramidLevels( d->pyramidLevels->value() );
    process_Registration->setLastPyramidLevel( d->lastLevel->value() );
    process_Registration->setNumberOfThreads( d->threads->value() );
    
    process->setInput(fixedData,  0);
    process->setInput(movingData, 1);
    
    medRunnableProcess *runProcess = new medRunnableProcess;
    runProcess->setProcess (process);
    
    d->progression_stack->addJobItem(runProcess, tr("Progress:"));
    //If there is no observer to track the progression,
    //make the progress bar spin:
    //d->progression_stack->setActive(runProcess,true);
    
    connect (runProcess, SIGNAL (success  (QObject*)),  this, SIGNAL (success ()));
    connect (runProcess, SIGNAL (failure  (QObject*)),  this, SIGNAL (failure ()));
    connect (runProcess, SIGNAL (cancelled (QObject*)), this, SIGNAL (failure ()));
    //First have the moving progress bar,
    //and then display the remaining % when known
    connect (runProcess, SIGNAL(activate(QObject*,bool)),
             d->progression_stack, SLOT(setActive(QObject*,bool)));
    
    
    medJobManager::instance()->registerJobItem(runProcess);
    QThreadPool::globalInstance()->start(dynamic_cast<QRunnable*>(runProcess));
}



void animaPyramidalBMRegistrationToolBox::openTransformFile()
{
    d->initTransformFile = QFileDialog::getOpenFileName(this, tr("Open transform file")); 
    d->initTransformFileEdit->setText( d->initTransformFile );
}


void animaPyramidalBMRegistrationToolBox::updateBMParams(int index)
{
    Optimizer opt = (Optimizer) d->optimzer->currentIndex();
    Transform tr = (Transform) d->transform->currentIndex();
    Agregator agreg = (Agregator) d->agregator->currentIndex();
    
    // updates according to Transform
    d->searchAngleRadius->setEnabled(tr == Affine || tr == Rigid);
    d->angleUpperBound->setEnabled( tr == Affine || tr == Rigid);
    
    d->searchScaleRadius->setEnabled(tr == Affine);
    d->scaleUpperBound->setEnabled(tr == Affine);
   
    d->searchSkewRadius->setEnabled(tr == Affine);
    d->skewUpperBound->setEnabled(tr == Affine);
   
    // updates according to Optimizer
    d->translateUpperBound->setEnabled( opt == Bobyqa ); 
    d->angleUpperBound->setEnabled( d->angleUpperBound->isEnabled() && opt == Bobyqa );
    d->scaleUpperBound->setEnabled( d->scaleUpperBound->isEnabled() && opt == Bobyqa );
    d->skewUpperBound->setEnabled( d->skewUpperBound->isEnabled() && opt == Bobyqa );

    d->stepSize->setEnabled( opt == Exhaustive);
    
    d->searchAngleRadius->setEnabled(d->searchAngleRadius->isEnabled() && opt != Exhaustive );
    d->searchScaleRadius->setEnabled(d->searchScaleRadius->isEnabled() && opt != Exhaustive );
    d->searchSkewRadius->setEnabled( d->searchSkewRadius->isEnabled() && opt != Exhaustive );
    
    d->finalRadius->setEnabled( opt != Exhaustive );
    
    // updates according to Agregator
    d->agregThreshold->setEnabled( agreg != LeastSquares);
    d->stoppingThreshold->setEnabled( agreg != LeastSquares);
    
}

