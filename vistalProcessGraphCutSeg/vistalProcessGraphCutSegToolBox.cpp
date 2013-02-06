#include "vistalProcessGraphCutSegToolBox.h"
#include "vistalProcessGraphCutSeg.h"

#include <dtkCore/dtkSmartPointer.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>

#include <medToolBoxFactory.h>
#include <medToolBoxSegmentation.h>
#include <medToolBoxSegmentationCustom.h>
#include <medPluginManager.h>
#include <medDropSite.h>
#include <medMultipleImageSelectionWidget.h>
#include <medDataManager.h>
#include <medDatabaseModel.h>
#include <medDatabaseProxyModel.h>
#include <medProgressionStack.h>
#include <medRunnableProcess.h>
#include <medJobManager.h>

#include <QtGui>

class vistalProcessGraphCutSegToolBoxPrivate
{

public:

    medDropSite *maskDropSite;
    medMultipleImageSelectionWidget *inputImageSelection;
    QPushButton *runButton;
    medProgressionStack * progression_stack;
    QDoubleSpinBox *alpha;
    QDoubleSpinBox *beta;
    QDoubleSpinBox *sigma;
    QComboBox *mode;
    QCheckBox *useSpectralGradient;

    dtkSmartPointer<dtkAbstractData> maskData;
    dtkSmartPointer<vistalProcessGraphCutSeg> process;
    QList< dtkSmartPointer<dtkAbstractData> > imageDataList;
};


vistalProcessGraphCutSegToolBox::vistalProcessGraphCutSegToolBox(QWidget *parent) : medToolBoxSegmentationCustom(parent), d(new vistalProcessGraphCutSegToolBoxPrivate)
{
    d->process = NULL;
    
    //Mask :
    d->maskDropSite = new medDropSite();
    d->maskDropSite->setToolTip("Drop your mask here. Your mask must contain 2 different labels: Label1 for target, label2 for background.");

    //Input image selection :
    QPushButton *inputSelectionButton = new QPushButton(tr("Select images"));

    // Parameters :
    d->mode = new QComboBox();
    QStringList modes;
    modes  << "SingleGaussian" << "STREM" << "Parzen" << "Density";
    d->mode->addItems(modes);
    //"Density by default"
    d->mode->setCurrentIndex(3);
    
    d->alpha = new QDoubleSpinBox();
    d->alpha->setValue(1); //default 1
    d->beta = new QDoubleSpinBox();
    d->beta->setValue(0); //default 0
    d->sigma = new QDoubleSpinBox();
    d->sigma->setValue(0.6); //default 0.6
    d->useSpectralGradient = new QCheckBox(tr("Use Spectral Gradient"));

    // Run :
    d->runButton = new QPushButton(tr("Run"));
    
    QLabel * maskLabel = new QLabel(tr("Drop mask"));
    QHBoxLayout *maskBoxLayout = new QHBoxLayout();
    maskBoxLayout->addWidget(maskLabel);
    maskBoxLayout->addWidget(d->maskDropSite);
    
    QLabel * inputSelectionLabel = new QLabel(tr("Select input images"));
    QHBoxLayout *imagesBoxLayout = new QHBoxLayout();
    imagesBoxLayout->addWidget(inputSelectionLabel);
    imagesBoxLayout->addWidget(inputSelectionButton);
    
    QLabel *modeLabel = new QLabel(tr("Mode:"));
    QHBoxLayout *modeLayout = new QHBoxLayout;
    modeLayout->addWidget(modeLabel);
    modeLayout->addWidget(d->mode);
    
    QLabel *alphaLabel = new QLabel(tr("Alpha:"));
    QHBoxLayout *alphaLayout = new QHBoxLayout;
    alphaLayout->addWidget(alphaLabel);
    alphaLayout->addWidget(d->alpha);
    
    QLabel *betaLabel = new QLabel(tr("Beta:"));
    QHBoxLayout *betaLayout = new QHBoxLayout;
    betaLayout->addWidget(betaLabel);
    betaLayout->addWidget(d->beta);
    
    QLabel *sigmaLabel = new QLabel(tr("Sigma:"));
    QHBoxLayout *sigmaLayout = new QHBoxLayout;
    sigmaLayout->addWidget(sigmaLabel);
    sigmaLayout->addWidget(d->sigma);
    
    d->progression_stack = new medProgressionStack;

    // layout
    QVBoxLayout *toolboxLayout = new QVBoxLayout();
    toolboxLayout->addLayout(maskBoxLayout);
    toolboxLayout->addLayout(imagesBoxLayout);
    toolboxLayout->addWidget(d->useSpectralGradient);
    toolboxLayout->addLayout(modeLayout);
    toolboxLayout->addLayout(alphaLayout);
    toolboxLayout->addLayout(betaLayout);
    toolboxLayout->addLayout(sigmaLayout);
    toolboxLayout->addWidget(d->runButton);
    toolboxLayout->addWidget(d->progression_stack);

    // connects
    connect(d->maskDropSite, SIGNAL(objectDropped(const medDataIndex &)),this,SLOT(onMaskDropped(const medDataIndex &)));
    connect(inputSelectionButton,SIGNAL(clicked()),this,SLOT(onMultipleImageSelectionClicked()));
    connect(d->runButton, SIGNAL(clicked()), this, SLOT(run()));

    QWidget *widget = new QWidget(this);
    widget->setLayout(toolboxLayout);
    this->setTitle("Graph Cuts : settings");
    this->addWidget(widget);

    // Add about plugin
    medPluginManager* pm = medPluginManager::instance();
    dtkPlugin* plugin = pm->plugin ( "vistalProcessGraphCutSegPlugin" );
    setAboutPluginButton ( plugin );
    setAboutPluginVisibility( true );
}


vistalProcessGraphCutSegToolBox::~vistalProcessGraphCutSegToolBox()
{
    delete d;
    d = NULL;
}

void vistalProcessGraphCutSegToolBox::onMultipleImageSelectionClicked()
{
    d->inputImageSelection = new medMultipleImageSelectionWidget(QList<medDataIndex>(), this);

    bool justBringStudies = true;

    medDatabaseModel* model = new medDatabaseModel(this, justBringStudies);

    medDatabaseProxyModel* proxy = new medDatabaseProxyModel(this);

    proxy->setSourceModel(model);

    d->inputImageSelection->setModel(proxy);

    if(d->inputImageSelection->exec()){

        d->imageDataList.clear();

        foreach(medDataIndex index,  d->inputImageSelection->getSelectedIndexes()){
                d->imageDataList.append(medDataManager::instance()->data(index));
        }
    }
}

void vistalProcessGraphCutSegToolBox::onMaskDropped(const medDataIndex& index)
{
    if (!index.isValid())
            return;

    d->maskData = medDataManager::instance()->data(index);
}



bool vistalProcessGraphCutSegToolBox::registered(void)
{
    return medToolBoxFactory::instance()->registerToolBox
                            <vistalProcessGraphCutSegToolBox>("graphcutSegmentation",
                                                            "Graph cut segmentation",
                                                            "Computes a graph cut segmentation",
                                                            QStringList()<<"segmentation");
}

void vistalProcessGraphCutSegToolBox::run()
{
    if (!this->segmentationToolBox() && d->imageDataList.size() && (!d->maskData))
        return;

    d->process = dtkAbstractProcessFactory::instance()->createSmartPointer("vistalProcessGraphCutSeg");

    d->process->setParameter(d->imageDataList.size(),0); //first parameter : number of images
    d->process->setParameter(d->alpha->value(),1);
    d->process->setParameter(d->beta->value(),2);
    d->process->setParameter(d->sigma->value(),3);
    d->process->setParameter(d->mode->currentIndex(),4);
    d->process->setParameter(d->useSpectralGradient->isChecked(),5);

    d->process->setInput( d->maskData,0); //setInput : mask then images

    for(int image_nb = 0 ; image_nb < d->imageDataList.size() ; image_nb ++)
        d->process->setInput(d->imageDataList[image_nb], 1);

    this->segmentationToolBox()->run( d->process );

}
