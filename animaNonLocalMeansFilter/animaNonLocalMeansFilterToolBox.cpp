// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////


#include "animaNonLocalMeansFilter.h"
#include "animaNonLocalMeansFilterToolBox.h"

#include <QtGui>

#include <medAbstractDataFactory.h>
#include <medAbstractImageData.h>
#include <dtkCore/dtkSmartPointer.h>

#include <medAbstractView.h>
#include <medRunnableProcess.h>
#include <medJobManager.h>

#include <medToolBoxFactory.h>
#include <medFilteringSelectorToolBox.h>
#include <medProgressionStack.h>
#include <medPluginManager.h>

#include <itkMultiThreader.h>
#include <animaNonLocalMeansFilter.h>

class animaNonLocalMeansFilterToolBoxPrivate
{
public:

    QLabel *dataTypeValue;
    QLabel *dataDimensionValue;

    QSpinBox *patchHalfSize;
    QSpinBox *searchNeighborhood;
    QSpinBox *searchStepSize;
    QDoubleSpinBox *weightThreshold;
    QDoubleSpinBox *betaParameter;
    QDoubleSpinBox *meanMinThreshold;
    QDoubleSpinBox *varMinThreshold;
    QSpinBox *nbThread;
    QComboBox *weightedMerthod;
    QRadioButton *temporalImage;
    QRadioButton *notTemporalImage;
    QButtonGroup *temporalImageGroup;

    dtkSmartPointer <animaNonLocalMeansFilter> process;
    medProgressionStack * progression_stack;

};

animaNonLocalMeansFilterToolBox::animaNonLocalMeansFilterToolBox(QWidget *parent) : medFilteringAbstractToolBox(parent), d(new animaNonLocalMeansFilterToolBoxPrivate)
{
    // Parameters:

    QFormLayout *parametersLayout = new QFormLayout();

    d->patchHalfSize = new QSpinBox();
    d->patchHalfSize->setValue(1);
    d->patchHalfSize->setRange(1, 10);
    parametersLayout->addRow(tr("Patch half size"), d->patchHalfSize);

    d->searchNeighborhood = new QSpinBox();
    d->searchNeighborhood->setValue(3);
    d->searchNeighborhood->setRange(1, 20);
    d->searchNeighborhood->setMinimum(1);
    parametersLayout->addRow(tr("Patch search neighborhood size"), d->searchNeighborhood);

    d->searchStepSize = new QSpinBox();
    d->searchStepSize->setValue(1);
    d->searchStepSize->setRange(1, 10);
    parametersLayout->addRow(tr("Patch search step size"), d->searchStepSize);

    d->weightThreshold = new QDoubleSpinBox();
    d->weightThreshold->setValue(0.0);
    parametersLayout->addRow(tr("NL weight threshold"), d->weightThreshold);

    d->betaParameter = new QDoubleSpinBox();
    d->betaParameter->setValue(1);
    parametersLayout->addRow(tr("Beta for local Noise estimation"), d->betaParameter);

    d->meanMinThreshold = new QDoubleSpinBox();
    d->meanMinThreshold->setValue(0.95);
    parametersLayout->addRow(tr("Means Threshold Min"), d->meanMinThreshold);

    d->varMinThreshold = new QDoubleSpinBox();
    d->varMinThreshold->setValue(0.5);
    parametersLayout->addRow(tr("Variance Threshold Min"), d->varMinThreshold);

    d->nbThread = new QSpinBox();
    d->nbThread->setValue(itk::MultiThreader::GetGlobalDefaultNumberOfThreads());
    d->nbThread->setRange(1, itk::MultiThreader::GetGlobalDefaultNumberOfThreads());
    parametersLayout->addRow(tr("Number of Threads"), d->nbThread);

    d->weightedMerthod = new QComboBox();
    QStringList weightedMerthods;
    weightedMerthods << "Gaussian" << "Rician";
    d->weightedMerthod->addItems(weightedMerthods);
    parametersLayout->addRow(tr("Noise assumption"), d->weightedMerthod);

    d->temporalImageGroup = new QButtonGroup();
    d->notTemporalImage = new QRadioButton(tr("No"));
    d->temporalImage = new QRadioButton(tr("Yes"));

    d->temporalImageGroup->addButton(d->notTemporalImage);
    d->temporalImageGroup->setId(d->notTemporalImage, 0);
    d->notTemporalImage->setChecked(true);

    d->temporalImageGroup->addButton(d->temporalImage);
    d->temporalImageGroup->setId(d->temporalImage, 1);

    QVBoxLayout *temporalLayout = new QVBoxLayout();
    temporalLayout->addWidget(d->notTemporalImage);
    temporalLayout->addWidget(d->temporalImage);
    parametersLayout->addRow(tr("Image has a temporal dimension?"), temporalLayout);

    QGroupBox *groupParameters = new QGroupBox("Mandatory");
    groupParameters->setLayout(parametersLayout);

    // progression stack
    d->progression_stack = new medProgressionStack(this);
    QHBoxLayout *progressStackLayout = new QHBoxLayout;
    progressStackLayout->addWidget(d->progression_stack);

    // Run button:
    QPushButton *runButton = new QPushButton(tr("Run"), this);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QLabel * dataTypeLabel = new QLabel (tr("Data type: "));
    d->dataTypeValue = new QLabel(tr("Unknown"));
    QHBoxLayout * dataTypeLayout = new QHBoxLayout;
    dataTypeLayout->addWidget (dataTypeLabel);
    dataTypeLayout->addWidget (d->dataTypeValue);

    QLabel * dataDimensionLabel = new QLabel (tr("Data dimension: "));
    d->dataDimensionValue = new QLabel(tr("Unknown"));
    QHBoxLayout * dataDimensionLayout = new QHBoxLayout;
    dataDimensionLayout->addWidget (dataDimensionLabel);
    dataDimensionLayout->addWidget (d->dataDimensionValue);

    mainLayout->addLayout(dataTypeLayout);
    mainLayout->addLayout(dataDimensionLayout);
    mainLayout->addWidget(groupParameters);
    mainLayout->addWidget(runButton);
    mainLayout->addLayout(progressStackLayout);

    QWidget *widget = new QWidget(this);
    widget->setLayout(mainLayout);
    this->addWidget(widget);

    this->setTitle("Non-Local Means Denoising");

    connect(runButton, SIGNAL(clicked()), this, SLOT(run()));

    // Add about plugin
    medPluginManager* pm = medPluginManager::instance();
    dtkPlugin* plugin = pm->plugin ( "animaNonLocalMeansFilterPlugin" );
    setAboutPluginButton ( plugin );
    setAboutPluginVisibility( true );
}

animaNonLocalMeansFilterToolBox::~animaNonLocalMeansFilterToolBox(void)
{
    delete d;
    d = NULL;
}

bool animaNonLocalMeansFilterToolBox::registered(void)
{
    return medToolBoxFactory::instance()->
    registerToolBox<animaNonLocalMeansFilterToolBox>("animaNonLocalMeansFilterToolBox",
                               tr("Non-Local Means Denoising"),
                               tr("Applies a non local means denoising filter"),
                               QStringList()<< "filtering");
}

medAbstractData* animaNonLocalMeansFilterToolBox::processOutput(void)
{
    if(!d->process)
        return NULL;

    return d->process->output();
}

void animaNonLocalMeansFilterToolBox::run(void)
{
    if(!this->parentToolBox())
        return;

    d->process = new animaNonLocalMeansFilter;

    if(!this->parentToolBox()->data())
        return;

    d->process->setInputImage(this->parentToolBox()->data());

    // Set your parameters here
    medRunnableProcess *runProcess = new medRunnableProcess;
    runProcess->setProcess (d->process);

    d->process->setPatchHalfSize(d->patchHalfSize->value());
    d->process->setSearchNeighborhood(d->searchNeighborhood->value());
    d->process->setSearchStepSize(d->searchStepSize->value());
    d->process->setWeightThreshold(d->weightThreshold->value());
    d->process->setBetaParameter(d->betaParameter->value());
    d->process->setMeanMinThreshold(d->meanMinThreshold->value());
    d->process->setVarMinThreshold(d->varMinThreshold->value());
    d->process->setNumberOfThreads(d->nbThread->value());
    d->process->setWeightedMethod(d->weightedMerthod->currentIndex());
    d->process->setTemporalImage(d->temporalImageGroup->checkedId());
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

void animaNonLocalMeansFilterToolBox::update(medAbstractData* data)
{
    medAbstractImageData *medData = dynamic_cast <medAbstractImageData *> (data);
    if (!medData)
        return;

    QString identifier = medData->identifier();

    unsigned int nbDimension = medData->Dimension();
    d->dataDimensionValue->setText(QString::number(nbDimension));
    d->notTemporalImage->setChecked(true);
    if (nbDimension == 4)
    {
        d->temporalImage->setChecked(true);
    }
    else if (nbDimension != 2 && nbDimension != 3 )
    {
        qWarning() << "Error : pixel type not yet implemented ("
        << identifier
        << ")";
    }
    
    identifier.truncate(identifier.size() - 1);
    
    if ( identifier == "itkDataImageChar" )
    {
        d->dataTypeValue->setText ( "Char" );
    }
    else if ( identifier == "itkDataImageUChar" )
    {
        d->dataTypeValue->setText ( "Unsigned char" );
    }
    else if ( identifier == "itkDataImageShort" )
    {
        d->dataTypeValue->setText ( "Short" );
    }
    else if ( identifier == "itkDataImageUShort" )
    {
        d->dataTypeValue->setText ( "Unsigned short" );
    }
    else if ( identifier == "itkDataImageInt" )
    {
        d->dataTypeValue->setText ( "Int" );
    }
    else if ( identifier == "itkDataImageUInt" )
    {
        d->dataTypeValue->setText ( "Unsigned int" );
    }
    else if ( identifier == "itkDataImageLong" )
    {
        d->dataTypeValue->setText ( "Long" );
    }
    else if ( identifier == "itkDataImageULong" )
    {
        d->dataTypeValue->setText ( "Unsigned long" );
    }
    else if ( identifier == "itkDataImageFloat" )
    {
        d->dataTypeValue->setText ( "Float" );
    }
    else if ( identifier == "itkDataImageDouble" )
    {
        d->dataTypeValue->setText ( "Double" );
    }
    else
    {
        qWarning() << "Error : pixel type not yet implemented ("
        << identifier
        << ")";
    }
}

dtkPlugin* animaNonLocalMeansFilterToolBox::plugin()
{
    medPluginManager* pm = medPluginManager::instance();
    dtkPlugin* plugin = pm->plugin ( "animaNonLocalMeansFilterPlugin" );
    return plugin;
}
