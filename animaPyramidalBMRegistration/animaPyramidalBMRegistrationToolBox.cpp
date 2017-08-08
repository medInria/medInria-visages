// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "animaPyramidalBMRegistration.h"
#include "animaPyramidalBMRegistrationToolBox.h"

#include <QtGui>

#include <dtkCoreSupport/dtkAbstractProcessFactory.h>
#include <medAbstractRegistrationProcess.h>
#include <dtkCoreSupport/dtkSmartPointer.h>

#include <medRunnableProcess.h>
#include <medJobManagerL.h>

#include <medAbstractImageData.h>

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
    
    //Block Initialisation Parameters
    QSpinBox *blockSize;
    QSpinBox *blockSpacing;
    QDoubleSpinBox *stdThreshold;
    QDoubleSpinBox *percentageKept;

    //Block Match Parameters
    QComboBox *transform;
    QComboBox * metric;
    QComboBox * optimizer;
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
    QCheckBox * initializeOnCenterOfGravity;

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
    
    d->percentageKept = new QDoubleSpinBox;
    d->percentageKept->setToolTip("Percentage of blocks actually used");
    d->percentageKept->setValue(0.8);
    d->percentageKept->setRange(0,1);
    d->percentageKept->setSingleStep(0.01);

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
    
    d->optimizer = new QComboBox;
    d->optimizer->setToolTip("Optimizer for optimal block search");
    QStringList optimizerList;
    optimizerList << "Exhaustive" << "Bobyqa";
    d->optimizer->addItems ( optimizerList );
    d->optimizer->setCurrentIndex(1);
    
    d->maxIterations = new QSpinBox;
    d->maxIterations->setToolTip("Maximum Block Match Iteration");
    d->maxIterations->setValue(10);
    
    d->minError = new QDoubleSpinBox;
    d->minError->setToolTip("Minimal distance between consecutive estimated transforms");
    d->minError->setDecimals(3);
    d->minError->setValue(0.01);   
    d->minError->setSingleStep(0.001);
    
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
    d->searchScaleRadius->setSingleStep(0.01);

    d->finalRadius = new QDoubleSpinBox;
    d->finalRadius->setToolTip("The final radius (rho end for newuoa)");
    d->finalRadius->setDecimals(4);
    d->finalRadius->setValue(0.001);
    d->finalRadius->setSingleStep(0.0001);
    
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
    
    d->initializeOnCenterOfGravity = new QCheckBox;
    d->initializeOnCenterOfGravity->setToolTip("Initialize the transformation on images centers of gravity?");
    d->initializeOnCenterOfGravity->setCheckState(Qt::Checked);

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
    d->agregThreshold->setSingleStep(0.01);
    
    d->stoppingThreshold = new QDoubleSpinBox;
    d->stoppingThreshold->setToolTip("LTS Stopping Threshold");
    d->stoppingThreshold->setDecimals(3);
    d->stoppingThreshold->setValue(0.01);
    d->stoppingThreshold->setSingleStep(0.001);

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

    // Block Initialisation Parameters Layout
    QFormLayout *blockInitLayout = new QFormLayout();
    blockInitLayout->addRow(new QLabel(tr("Block size"),this),d->blockSize);
    blockInitLayout->addRow(new QLabel(tr("Block spacing"),this),d->blockSpacing);
    blockInitLayout->addRow(new QLabel(tr("Std Threshold"),this),d->stdThreshold);
    blockInitLayout->addRow(new QLabel(tr("Percentage kept"),this),d->percentageKept);

    QGroupBox *blockInitGroupBox = new QGroupBox(tr("Block Initialisation Parameters"));
    blockInitGroupBox->setLayout(blockInitLayout);


    // Block Match Parameters Layout
    QFormLayout *blockMatchLayout = new QFormLayout();
    blockMatchLayout->addRow(new QLabel(tr("Transform"),this),d->transform);
    blockMatchLayout->addRow(new QLabel(tr("Metric"),this),d->metric);
    blockMatchLayout->addRow(new QLabel(tr("Optimizer"),this),d->optimizer);
    blockMatchLayout->addRow(new QLabel(tr("Center of mass init"),this),d->initializeOnCenterOfGravity);
    blockMatchLayout->addRow(new QLabel(tr("Max Iterations"),this),d->maxIterations);
    blockMatchLayout->addRow(new QLabel(tr("Min error"),this),d->minError);
    blockMatchLayout->addRow(new QLabel(tr("Optimizer Iterations"),this),d->optIterations);
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
    
    connect(d->optimizer, SIGNAL(currentIndexChanged(int)), this, SLOT(updateBMOptimizerParams(int)));
    connect(d->transform, SIGNAL(currentIndexChanged(int)), this, SLOT(updateBMTransformParams(int)));
    connect(d->agregator, SIGNAL(currentIndexChanged(int)), this, SLOT(updateBMAgregatorParams(int)));
    
    updateBMOptimizerParams(0);
    updateBMTransformParams(0);
    updateBMAgregatorParams(0);
    
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
    registerToolBox<animaPyramidalBMRegistrationToolBox>();
}

void animaPyramidalBMRegistrationToolBox::run(void)
{ 
    if(!this->parentToolBox())
        return;

    dtkSmartPointer <medAbstractRegistrationProcess> process;

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
    
    dtkSmartPointer<medAbstractData> fixedData = this->parentToolBox()->fixedData();
    dtkSmartPointer<medAbstractData> movingData = this->parentToolBox()->movingData();
    
    if (!fixedData || !movingData)
        return;
    
    animaPyramidalBMRegistration *process_Registration = dynamic_cast<animaPyramidalBMRegistration *>(process.data());
    if (!process_Registration)
    {
        qWarning() << "registration process doesn't exist" ;
        return;
    }

    // Setting process arguments
    process_Registration->setBlockSize( d->blockSize->value() );
    process_Registration->setBlockSpacing( d->blockSpacing->value() );
    process_Registration->setPercentageKept( d->percentageKept->value() );
    process_Registration->setStDevThreshold( d->stdThreshold->value() );
    process_Registration->setTransform( d->transform->currentIndex() );
    process_Registration->setMetric( d->metric->currentIndex() );
    process_Registration->setOptimizer( d->optimizer->currentIndex() );
    process_Registration->setInitializeOnCenterOfGravity( d->initializeOnCenterOfGravity->checkState() == Qt::Checked );
    process_Registration->setMaximumIterations( d->maxIterations->value() );
    process_Registration->setMinimalTransformError( d->minError->value() );
    process_Registration->setOptimizerMaximumIterations( d->optIterations->value() );
    process_Registration->setSearchRadius( d->searchRadius->value() );
    process_Registration->setSearchAngleRadius( d->searchAngleRadius->value() );
    process_Registration->setSearchSkewRadius( d->searchSkewRadius->value() );
    process_Registration->setSearchScaleRadius( d->searchScaleRadius->value() );
    process_Registration->setStepSize( d->stepSize->value() );
    process_Registration->setTranslateUpperBound( d->translateUpperBound->value() );
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
    
    process->setFixedInput(fixedData);
    process->setMovingInput(movingData);
    
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
    
    medJobManagerL::instance()->registerJobItem(runProcess);
    QThreadPool::globalInstance()->start(dynamic_cast<QRunnable*>(runProcess));
}

void animaPyramidalBMRegistrationToolBox::updateBMOptimizerParams(int index)
{
    typedef typename animaPyramidalBMRegistration::RegistrationType::PyramidBMType BMRegistrationType;
    typedef typename BMRegistrationType::Optimizer Optimizer;

    Optimizer opt = (Optimizer) d->optimizer->currentIndex();

    d->translateUpperBound->setEnabled( opt == BMRegistrationType::Bobyqa );
    d->angleUpperBound->setEnabled( d->angleUpperBound->isEnabled() && opt == BMRegistrationType::Bobyqa );
    d->scaleUpperBound->setEnabled( d->scaleUpperBound->isEnabled() && opt == BMRegistrationType::Bobyqa );
    d->skewUpperBound->setEnabled( d->skewUpperBound->isEnabled() && opt == BMRegistrationType::Bobyqa );
    
    d->stepSize->setEnabled( opt == BMRegistrationType::Exhaustive);
    
    d->searchAngleRadius->setEnabled(d->searchAngleRadius->isEnabled() && opt != BMRegistrationType::Exhaustive );
    d->searchScaleRadius->setEnabled(d->searchScaleRadius->isEnabled() && opt != BMRegistrationType::Exhaustive );
    d->searchSkewRadius->setEnabled( d->searchSkewRadius->isEnabled() && opt != BMRegistrationType::Exhaustive );
    
    d->finalRadius->setEnabled( opt != BMRegistrationType::Exhaustive );
}

void animaPyramidalBMRegistrationToolBox::updateBMTransformParams(int index)
{
    typedef typename animaPyramidalBMRegistration::RegistrationType::PyramidBMType BMRegistrationType;
    typedef typename BMRegistrationType::Transform Transform;

    Transform tr = (Transform) d->transform->currentIndex();

    d->searchAngleRadius->setEnabled(tr == BMRegistrationType::Affine || tr == BMRegistrationType::Rigid);
    d->angleUpperBound->setEnabled( tr == BMRegistrationType::Affine || tr == BMRegistrationType::Rigid);
    
    d->searchScaleRadius->setEnabled(tr == BMRegistrationType::Affine);
    d->scaleUpperBound->setEnabled(tr == BMRegistrationType::Affine);
    
    d->searchSkewRadius->setEnabled(tr == BMRegistrationType::Affine);
    d->skewUpperBound->setEnabled(tr == BMRegistrationType::Affine);
}

void animaPyramidalBMRegistrationToolBox::updateBMAgregatorParams(int index)
{
    typedef typename animaPyramidalBMRegistration::RegistrationType::PyramidBMType BMRegistrationType;
    typedef typename BMRegistrationType::Agregator Agregator;

    Agregator agreg = (Agregator) d->agregator->currentIndex();

    d->agregThreshold->setEnabled( agreg != BMRegistrationType::LeastSquares);
    d->stoppingThreshold->setEnabled( agreg != BMRegistrationType::LeastSquares);
}
