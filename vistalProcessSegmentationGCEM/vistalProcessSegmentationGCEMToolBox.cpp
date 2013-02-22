
#include "vistalProcessSegmentationGCEM.h"
#include "vistalProcessSegmentationGCEMToolBox.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewInteractor.h>

#include <medRunnableProcess.h>
#include <medJobManager.h>
#include <medAbstractDataImage.h>

#include <medToolBoxFactory.h>
#include <medSegmentationSelectorToolBox.h>
#include <medProgressionStack.h>
#include <medDropSite.h>
#include <medDataManager.h>

#include <QtGui>

class vistalProcessSegmentationGCEMToolBoxPrivate
{
public:
    vistalProcessSegmentationGCEMToolBoxPrivate();

    medDropSite *dropSiteT1;
    medDropSite *dropSitePD;
    medDropSite *dropSiteT2;
    medDropSite *dropSiteMask;

    QComboBox* InitMethod;

    QDoubleSpinBox* rejRatio;
    QComboBox* emAlgo;
    QDoubleSpinBox* minDistance;
    QSpinBox* emIter;

    QCheckBox* GCEM;

    QDoubleSpinBox* mahalanobisDist;
    QDoubleSpinBox* rulesThreshold;
    QDoubleSpinBox* minSize;
    QDoubleSpinBox* wmneighb;

    QDoubleSpinBox* rmin;
    QDoubleSpinBox* rmax;
    QDoubleSpinBox* alphap;

    QPushButton *runButton;

    int startLock;

    dtkSmartPointer <dtkAbstractProcess> process;
    medProgressionStack * progression_stack;

    /* Pointer to the data to be processed*/
    dtkSmartPointer< dtkAbstractData > dataT1;
    dtkSmartPointer< dtkAbstractData > dataPD;
    dtkSmartPointer< dtkAbstractData > dataT2;
    dtkSmartPointer< dtkAbstractData > dataMask;
};


vistalProcessSegmentationGCEMToolBoxPrivate::vistalProcessSegmentationGCEMToolBoxPrivate():

    runButton(0), startLock(0),
    process(0), progression_stack(0),
    dataT1(0), dataPD(0), dataT2(0), dataMask(0)
{
}


vistalProcessSegmentationGCEMToolBox::vistalProcessSegmentationGCEMToolBox(QWidget *parent) : medSegmentationAbstractToolBox(parent), d(new vistalProcessSegmentationGCEMToolBoxPrivate)
{
    /* Image Input */
    d->dropSiteT1 = new medDropSite;
    d->dropSitePD = new medDropSite;
    d->dropSiteT2 = new medDropSite;
    d->dropSiteMask = new medDropSite;

    QGridLayout* imgL = new QGridLayout;
    imgL->addWidget(new QLabel("T1w Image"), 0,0);
    imgL->addWidget(d->dropSiteT1, 1,0);

    imgL->addWidget(new QLabel("PDw Image"), 0, 1);
    imgL->addWidget(d->dropSitePD, 1,1);

    imgL->addWidget(new QLabel("T2 or FLAIR"), 2, 0);
    imgL->addWidget(d->dropSiteT2, 3,0);

    imgL->addWidget(new QLabel("Brain Mask"), 2,1);
    imgL->addWidget(d->dropSiteMask, 3,1);

    QGroupBox* groupInput = new QGroupBox("Images Input");
    groupInput->setLayout(imgL);

    /* Algorithm Option */
    d->InitMethod = new QComboBox();
    d->InitMethod->addItems(QStringList() << "StraInit" << "HierarchicalPD" << "HierarchicalFLAIR");
    QHBoxLayout* iniL = new QHBoxLayout();
    iniL->addWidget(new QLabel("Initialisation Method"));
    iniL->addWidget(d->InitMethod);

    d->rejRatio  = new QDoubleSpinBox;
    d->rejRatio->setRange(0, 1);
    d->rejRatio->setDecimals(4);
    d->rejRatio->setValue(.2);

    QHBoxLayout *rejL = new QHBoxLayout;
    rejL->addWidget(new QLabel("Rejection Ratio"));
    rejL->addWidget(d->rejRatio);


    d->emAlgo = new QComboBox();
    d->emAlgo->addItems(QStringList() << "GaussianEM" << "Gaussian \"Celeux\" Robust EM" << "Gaussian Robust EM");
    d->emAlgo->setCurrentIndex(2);

    QHBoxLayout* emAlL = new QHBoxLayout;
    emAlL->addWidget(new QLabel("EM Approach"));
    emAlL->addWidget(d->emAlgo);

    d->minDistance = new QDoubleSpinBox;
    d->minDistance->setRange(0, 1);
    d->minDistance->setDecimals(7);
    d->minDistance->setValue(1e-4);

    QHBoxLayout* mdL = new QHBoxLayout;
    mdL->addWidget(new QLabel("Convergence Dist."));
    mdL->addWidget(d->minDistance);

    d->emIter = new QSpinBox;
    d->emIter->setRange(0, 1000);
    d->emIter->setValue(100);

    QHBoxLayout* emIL = new QHBoxLayout;
    emIL->addWidget(new QLabel("Iterations in EM:"));
    emIL->addWidget(d->emIter);

    d->GCEM = new QCheckBox;
    d->GCEM->setText("First iteration with STREM?");
    d->GCEM->setChecked(false);

    QVBoxLayout* optAlg = new QVBoxLayout;
    optAlg->addLayout(iniL);
    optAlg->addLayout(rejL);
    optAlg->addLayout(emAlL);
    optAlg->addLayout(mdL);
    optAlg->addLayout(emIL);
    optAlg->addWidget(d->GCEM);


    QGroupBox* Algo = new QGroupBox("EM Options");
    Algo->setLayout(optAlg);


    /* Lesion Options */
    d->mahalanobisDist = new QDoubleSpinBox;
    d->mahalanobisDist->setRange(0,4);
    d->mahalanobisDist->setDecimals(4);
    d->mahalanobisDist->setValue(.4);

    QHBoxLayout* mahaL = new QHBoxLayout;
    mahaL->addWidget(new QLabel("mahalanobis Distance:"));
    mahaL->addWidget(d->mahalanobisDist);

    d->rulesThreshold = new QDoubleSpinBox;
    d->rulesThreshold->setRange(0, 10);
    d->rulesThreshold->setDecimals(4);
    d->rulesThreshold->setValue(3);


    QHBoxLayout* rtL = new QHBoxLayout;
    rtL->addWidget(new QLabel("rules Threshold:"));
    rtL->addWidget(d->rulesThreshold);

    d->minSize = new QDoubleSpinBox;

    d->minSize->setRange(0,100);
    d->minSize->setDecimals(2);
    d->minSize->setValue(6);

    QHBoxLayout* msL = new QHBoxLayout;
    msL->addWidget(new QLabel("min Lesion size:"));
    msL->addWidget(d->minSize);

    d->wmneighb = new QDoubleSpinBox;
    d->wmneighb->setRange(0, 1);
    d->wmneighb->setDecimals(4);
    d->wmneighb->setValue(.05);
    QHBoxLayout* wmnL = new QHBoxLayout;
    wmnL->addWidget(new QLabel("WM neighbors:"));
    wmnL->addWidget(d->wmneighb);

    // 2,3, 10
    d->rmin = new QDoubleSpinBox;
    d->rmin->setRange(0, 10);
    d->rmin->setValue(2.);
    QHBoxLayout* rmiL = new QHBoxLayout;
    rmiL->addWidget(new QLabel("rules Min"));
    rmiL->addWidget(d->rmin);

    d->rmax = new QDoubleSpinBox;
    d->rmax->setRange(0, 10);
    d->rmax->setValue(3.);
    QHBoxLayout* rmaL = new QHBoxLayout;
    rmaL->addWidget(new QLabel("rules Max"));
    rmaL->addWidget(d->rmax);

    d->alphap = new QDoubleSpinBox;
    d->alphap->setRange(0, 1000);
    d->alphap->setValue(10);
    QHBoxLayout* alL = new QHBoxLayout;
    alL->addWidget(new QLabel("Graphcut Threshold"));
    alL->addWidget(d->alphap);

    QVBoxLayout* lesL = new QVBoxLayout;
    lesL->addLayout(mahaL);
    lesL->addLayout(rtL);
    lesL->addLayout(msL);
    lesL->addLayout(wmnL);
    lesL->addLayout(rmiL);
    lesL->addLayout(rmaL);
    lesL->addLayout(alL);

    QGroupBox* les = new QGroupBox("MS Lesions Options");
    les->setLayout(lesL);


    // Run button:
    d->runButton = new QPushButton(tr("Run"));

    // Principal layout:

    QWidget *widget = new QWidget;
    d->progression_stack = new medProgressionStack(widget);

    QVBoxLayout *layprinc = new QVBoxLayout();
    layprinc->addWidget(groupInput); // Image input
    layprinc->addWidget(Algo); // Algorithm option input
    layprinc->addWidget(les); // lesion seg input
    layprinc->addWidget(d->runButton);
    layprinc->addWidget(d->progression_stack);

    widget->setLayout(layprinc);

    // Main toolbox:
    this->setTitle("Segmentation settings");
    this->addWidget(widget);


    d->runButton->setDisabled(true); // Need to add all the data prior to start

    // Connect the created dropsite
    connect(d->dropSiteT1, SIGNAL(objectDropped(const medDataIndex &)), this, SLOT(onT1ImageDropped(const medDataIndex &)));

    connect(d->dropSiteT2, SIGNAL(objectDropped(const medDataIndex &)), this, SLOT(onT2orFLAIRImageDropped(const medDataIndex &)));
    connect(d->dropSitePD, SIGNAL(objectDropped(const medDataIndex &)), this, SLOT(onPDImageDropped(const medDataIndex &)));
    connect(d->dropSiteMask, SIGNAL(objectDropped(const medDataIndex &)), this, SLOT(onMaskImageDropped(const medDataIndex &)));

    connect(d->runButton, SIGNAL(clicked()), this, SLOT(run()));
}

vistalProcessSegmentationGCEMToolBox::~vistalProcessSegmentationGCEMToolBox(void)
{
    delete d;
    d = NULL;
}

bool vistalProcessSegmentationGCEMToolBox::registered(void)
{
    return medToolBoxFactory::instance()->registerToolBox <vistalProcessSegmentationGCEMToolBox>
                            ("gcemSegmentation", "GCEM MS lesions segmentation",
                             "GraphCut w. EM init + outliers",
                             QStringList() << "segmentation");
}

void vistalProcessSegmentationGCEMToolBox::run(void)
{
    if(!this->segmentationToolBox())
        return;

    d->process = dtkAbstractProcessFactory::instance()->createSmartPointer("vistalProcessSegmentationGCEM");

    //    if(!this->parent()->data())
    //        return;

    d->process->setInput(d->dataT1.data(), 0);
    d->process->setInput(d->dataPD.data(), 1);
    d->process->setInput(d->dataT2.data(), 2);
    d->process->setInput(d->dataMask.data(), 3);

    d->process->setParameter((double)d->InitMethod->currentIndex(), 0);
    d->process->setParameter((double)d->rejRatio ->value(), 1);
    d->process->setParameter((double)d->emAlgo->currentIndex(), 2);

    d->process->setParameter((double)d->minDistance->value(), 3);
    d->process->setParameter((double)d->emIter->value(), 4);
    d->process->setParameter((double)d->GCEM->isChecked(), 5);

    d->process->setParameter((double)d->mahalanobisDist->value(), 6);
    d->process->setParameter((double)d->rulesThreshold ->value(), 7);
    d->process->setParameter((double)d->minSize->value(), 8);
    d->process->setParameter((double)d->wmneighb->value(), 9);

    this->segmentationToolBox()->run( d->process );
}

void vistalProcessSegmentationGCEMToolBox::onT1ImageDropped(const medDataIndex &index)
{
    if (!index.isValid())
        return;

    d->dataT1 = medDataManager::instance()->data (index);

    if (!d->dataT1)
        return;

    d->startLock |= 1;

    if (d->startLock & 15)
        d->runButton->setEnabled(true);

    //emit dataSelected(d->data);
}


void vistalProcessSegmentationGCEMToolBox::onPDImageDropped(const medDataIndex &index)
{
    if (!index.isValid())
        return;

    d->dataPD = medDataManager::instance()->data (index);

    if (!d->dataPD)
        return;

    d->startLock |= 2;
    
    if (d->startLock & 15)
        d->runButton->setEnabled(true);


    //emit dataSelected(d->data);
}

void vistalProcessSegmentationGCEMToolBox::onT2orFLAIRImageDropped(const medDataIndex &index)
{
    if (!index.isValid())
        return;

    d->dataT2 = medDataManager::instance()->data (index);


    if (!d->dataT2)
        return;
    d->startLock |= 4;
    
    if (d->startLock & 15)
        d->runButton->setEnabled(true);

    //emit dataSelected(d->data);
}

void vistalProcessSegmentationGCEMToolBox::onMaskImageDropped(const medDataIndex &index)
{
    if (!index.isValid())
        return;

    d->dataMask = medDataManager::instance()->data (index);

    if (!d->dataMask)
        return;

    d->startLock |= 6;

    if (d->startLock & 15)
        d->runButton->setEnabled(true);
    //emit dataSelected(d->data);
}
