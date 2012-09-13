
#include "vistalProcessBiasRemoval.h"
#include "vistalProcessBiasRemovalToolBox.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewInteractor.h>
#include <dtkCore/dtkSmartPointer.h>

#include <medAbstractDataImage.h>
#include <medToolBoxFactory.h>
#include <medToolBoxFiltering.h>
#include <medToolBoxFilteringCustom.h>

#include <QtGui>

class vistalProcessBiasRemovalToolBoxPrivate
{
public:
    QDoubleSpinBox *cutoff;
    QSpinBox *bins;
    QDoubleSpinBox *regularization;

    QComboBox *basistype;
    QCheckBox *random;
    QCheckBox *skip0;

    QDoubleSpinBox *threshold;

    QSpinBox *iter;
    QDoubleSpinBox *optThresh;

    QCheckBox *biasOutput;


    dtkSmartPointer <dtkAbstractProcess> process;
};

vistalProcessBiasRemovalToolBox::vistalProcessBiasRemovalToolBox(QWidget *parent) : medToolBoxFilteringCustom(parent), d(new vistalProcessBiasRemovalToolBoxPrivate)
{
    // Parameters:

    QLabel *cutoffLbl = new QLabel("Cut off Freq. :");
    d->cutoff = new QDoubleSpinBox();
    d->cutoff->setRange(5, 200);

    d->cutoff->setValue(30);

    QHBoxLayout *cutoffBox = new QHBoxLayout();
    cutoffBox->addWidget(cutoffLbl);
    cutoffBox->addWidget(d->cutoff);

    QLabel *binsLbl = new QLabel("Number of Bins :");
    d->bins = new QSpinBox();
    d->bins->setRange(1, 2048);
    d->bins->setValue(1024);

    QHBoxLayout *binsBox = new QHBoxLayout();
    binsBox->addWidget(binsLbl);
    binsBox->addWidget(d->bins);

    QLabel *regLbl = new QLabel("Regularization parameter :");
    d->regularization = new QDoubleSpinBox();
    d->regularization->setRange(1e-9, 1);
    d->regularization->setDecimals(8);
    d->regularization->setValue(1e-5);

    QHBoxLayout *regBox = new QHBoxLayout();
    regBox->addWidget(regLbl);
    regBox->addWidget(d->regularization);

    QLabel *basLbl = new QLabel("Type of Basis :");
    d->basistype = new QComboBox();
    d->basistype->addItems(QStringList() << "Discrete Cosines" << "Legendre Polynomials" << "Hermite Polynomials");

    QHBoxLayout *basBox = new QHBoxLayout();
    basBox->addWidget(basLbl);
    basBox->addWidget(d->basistype);

    d->random = new QCheckBox("Noisy input");
    d->random->setChecked(true);

    d->skip0 = new QCheckBox("Skip null values");
    d->skip0->setChecked(false);

    QLabel *thrLbl = new QLabel("Background removal:");
    d->threshold = new QDoubleSpinBox();
    d->threshold->setValue(-1);
    d->threshold->setRange(-1, 10000);

    QHBoxLayout *thBox = new QHBoxLayout();
    thBox->addWidget(thrLbl);
    thBox->addWidget(d->threshold);

    QLabel *iterLbl = new QLabel("Number of Iterations:");
    d->iter = new QSpinBox();
    d->iter->setRange(1, 1000);
    d->iter->setValue(128);

    QHBoxLayout *iterBox = new QHBoxLayout();
    iterBox->addWidget(iterLbl);
    iterBox->addWidget(d->iter);

    QLabel *optThLbl = new QLabel("Optimisation End:");
    d->optThresh = new QDoubleSpinBox();
    d->optThresh->setRange(1e-9, 1);
    d->optThresh->setDecimals(8);
    d->optThresh->setValue(1e-5);

    QHBoxLayout *optThBox = new QHBoxLayout();
    optThBox->addWidget(optThLbl);
    optThBox->addWidget(d->optThresh);

    d->biasOutput = new QCheckBox("Bias field");
    d->biasOutput->setChecked(false);

    QVBoxLayout *parametersLayout = new QVBoxLayout();
    parametersLayout->addLayout(cutoffBox);
    parametersLayout->addLayout(binsBox);
    parametersLayout->addLayout(regBox);
    parametersLayout->addLayout(basBox);
    parametersLayout->addWidget(d->random);
    parametersLayout->addWidget(d->skip0);
    parametersLayout->addLayout(thBox);
    parametersLayout->addLayout(iterBox);
    parametersLayout->addLayout(optThBox);

    parametersLayout->addWidget(d->biasOutput);

//    QGroupBox *groupParameters = new QGroupBox("Mandatory");
//    groupParameters->setLayout(parametersLayout);

    // Options:

    // Run button:

    QPushButton *runButton = new QPushButton(tr("Run"));

    // Principal layout:

    QVBoxLayout *layprinc = new QVBoxLayout();
//    layprinc->addWidget(groupParameters);
//    layprinc->addWidget(groupOptions);
    layprinc->addLayout(parametersLayout);
    layprinc->addWidget(runButton);

    QWidget *widget = new QWidget(this);
    widget->setLayout(layprinc);

    // Main toolbox:
    this->setTitle("Intensity Non Uniformity Settings");
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
    return medToolBoxFactory::instance()->registerToolBox
                            <vistalProcessBiasRemovalToolBox>("BiasRemovalFilter",
                                                              "Bias removal",
                                                              "Applies bias removal filter",
                                                              QStringList()<<"filtering");
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

    d->process = dtkAbstractProcessFactory::instance()->createSmartPointer("vistalProcessBiasRemoval");

    if(!this->parentToolBox()->data())
        return;

    d->process->setInput(this->parentToolBox()->data());

    d->process->setParameter((double)d->cutoff->value(), 0);
    d->process->setParameter((double)d->bins->value(), 1);
    d->process->setParameter((double)d->regularization->value(),2);
    d->process->setParameter((double)d->basistype->currentIndex(), 3);
    d->process->setParameter((double)d->random->isChecked(),4);
    d->process->setParameter((double)d->skip0->isChecked(),5);
    d->process->setParameter((double)d->threshold->value(), 6);
    d->process->setParameter((double)d->iter->value(), 7);
    d->process->setParameter((double)d->optThresh->value(), 8);
    d->process->setParameter((double)d->biasOutput->isChecked(), 9);


    if(d->process->update()==0)
        emit success();
    else
        emit failure();

}

medToolBoxFilteringCustom *createVistalProcessBiasRemovalToolBox(QWidget *parent)
{
    return new vistalProcessBiasRemovalToolBox(parent);
}
