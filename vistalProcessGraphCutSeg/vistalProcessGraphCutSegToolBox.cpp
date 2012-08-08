#include "vistalProcessGraphCutSegToolBox.h"

#include <medToolBoxFactory.h>
#include <medToolBoxSegmentationCustom.h>
#include <medPluginManager.h>
#include <medDropSite.h>
#include <medMultipleImageSelectionWidget.h>
#include <medDatabaseModel.h>


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

    QList<medDataIndex> selectedIndexes;
};


vistalProcessGraphCutSegToolBox::vistalProcessGraphCutSegToolBox(QWidget *parent) : medToolBoxSegmentationCustom, d(new vistalProcessGraphCutSegToolBoxPrivate)
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
    toolboxLayout->addWidget(imagesBoxLayout);
    toolboxLayout->addWidget(d->alpha);
    toolboxLayout->addWidget(d->beta);
    toolboxLayout->addWidget(d->sigma);
    toolboxLayout->addWidget(d->run);

    // connects
    connect(inputSelectionButton,SIGNAL(clicked),this,SLOT(onMultipleImageSelectionClicked()));
    connect(d->runButton, SIGNAL(clicked()), this, SLOT(run()));

    QWidget *widget = new QWidget(this);
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
    d->inputImageSelection = new medMultipleImageSelectionWidget(d->selectedIndexes, this);

    bool justBringStudies = true;

    medDatabaseModel* model = new medDatabaseModel(this, justBringStudies);

    medDatabaseProxyModel* proxy = new medDatabaseProxyModel(this);

    proxy->setSourceModel(model);

    d->inputImageSelection->setModel(proxy);

    if(!d->inputImageSelection->exec())
        d->selectedIndexes = d->inputImageSelection->getSelectedIndexes();
}


bool vistalProcessGraphCutSegToolBox::registered(void)
{
    return medToolBoxFactory::instance()->registerToolBox
                            <vistalProcessGraphCutSegToolBox>("graphcutSegmentation",
                                                            "Graph cut segmentation",
                                                            "Applies a graph cut segementation",
                                                            QStringList()<<"segmentation");
}

void vistalProcessGraphCutSegToolBox::run()
{
    if (!this->segmentationToolBox())
        return;


}
