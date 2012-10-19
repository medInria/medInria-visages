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

#include <QtGui>

class vistalProcessGraphCutSegToolBoxPrivate
{

public:

    medDropSite *maskDropSite;
    medMultipleImageSelectionWidget *inputImageSelection;
    QPushButton *runButton;
    QDoubleSpinBox *alpha;
    QDoubleSpinBox *beta;
    QDoubleSpinBox *sigma;

    dtkSmartPointer<dtkAbstractData> maskData;
    dtkSmartPointer<vistalProcessGraphCutSeg> process;
    QList< dtkSmartPointer<dtkAbstractData> > imageDataList;
    dtkSmartPointer<dtkAbstractData> outputData;
};


vistalProcessGraphCutSegToolBox::vistalProcessGraphCutSegToolBox(QWidget *parent) : medToolBoxSegmentationCustom(parent), d(new vistalProcessGraphCutSegToolBoxPrivate)
{
    //Mask :
    QLabel * maskLabel = new QLabel("Drop mask");
    d->maskDropSite = new medDropSite();

    QHBoxLayout *maskBoxLayout = new QHBoxLayout();
    maskBoxLayout->addWidget(maskLabel);
    maskBoxLayout->addWidget(d->maskDropSite);

    //Input image selection :

    QLabel * inputSelectionLabel = new QLabel("Select input images");
    QPushButton *inputSelectionButton = new QPushButton(tr("Select images"));

    QHBoxLayout *imagesBoxLayout = new QHBoxLayout();
    imagesBoxLayout->addWidget(inputSelectionLabel);
    imagesBoxLayout->addWidget(inputSelectionButton);

    // Parameters :

    d->alpha = new QDoubleSpinBox();
    d->alpha->setValue(1); //default 1
    d->beta = new QDoubleSpinBox();
    d->beta->setValue(0); //default 0
    d->sigma = new QDoubleSpinBox();
    d->sigma->setValue(0.6); //default 0.6

    // Run :

    d->runButton = new QPushButton(tr("Run"));

    // layout, this->Widget ...
    QVBoxLayout *toolboxLayout = new QVBoxLayout();
    toolboxLayout->addLayout(maskBoxLayout);
    toolboxLayout->addLayout(imagesBoxLayout);
    toolboxLayout->addWidget(d->alpha);
    toolboxLayout->addWidget(d->beta);
    toolboxLayout->addWidget(d->sigma);
    toolboxLayout->addWidget(d->runButton);

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

    d->process->setInput( d->maskData,0); //setInput : mask then images

    qDebug() << d->imageDataList.size();
    for(int image_nb = 0 ; image_nb < d->imageDataList.size() ; image_nb ++)
        d->process->setInput(d->imageDataList[image_nb], 1);

    this->segmentationToolBox()->run( d->process );

    d->outputData = d->process->output();
}
