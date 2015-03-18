// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalProcessSegmentationSTREM.h"

#include <dtkCore/dtkAbstractProcessFactory.h>
#include <medAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>

#include <QDebug>

#include "mstoolsFiniteModel.h"
#include "Matrice.hh"
#include "Image3D.hh"
#include "GIS.hh"
#include "mstoolsGaussian.h"
#include "mstoolsStraInitializer.h"
#include "mstoolsHierarchicalInitializer.h"

#include "mstoolsClassificationFunctions.h"

#include "mstoolsAtlasRandomInitializer.h"
#include "mstoolsModelInitializer.h"
#include "mstoolsJointHistogramNdims.h"

#include "mstoolsClassEstimator.h"
#include "mstoolsGaussian.h"
#include "mstoolsGaussianREMEstimator.h"
#include "mstoolsGaussianEMEstimator.h"
#include "mstoolsGaussianCeleuxREMEstimator.h"
#include "mstoolsGaussianCeleuxEMEstimator.h"
#include "mstoolsImageClassifier.h"
#include "mstoolsRulesLesionClassifier.h"

#include "mstoolsClassificationStrategy.h"
#include "Labelize.hh"
#include "mstoolsRulesLesionClassifier.h"
#include "mstoolsMahalanobisThreshold.h"
#include "mstoolsChi2.h"

#include <medMetaDataKeys.h>


//#include "mstoolsIO.h"


// /////////////////////////////////////////////////////////////////
// vistalProcessSegmentationSTREMPrivate
// /////////////////////////////////////////////////////////////////

class vistalProcessSegmentationSTREMPrivate
{
public:
    vistalProcessSegmentationSTREMPrivate();
    ~vistalProcessSegmentationSTREMPrivate();
    // Channel 0 to 2
    QList < dtkSmartPointer <medAbstractData> > input; // Expected Input image to segment (T1, PD , {T2, FLAIR} )
    // Channel 3
    dtkSmartPointer <medAbstractData> mask;
    int imported;

    enum InitialisationMethod { StraInit, HierarchicalPD, HierarchicalFLAIR } initMethod; // Type of initialisation for the EM, D. Garcia used Hierachical PD or FLAIR depending on the input

    enum ApproachEM { GaussianEM, GaussianCeleuxREM, GaussianREM } approachEM;
    // Rejection Ratio
    double rejectionRatio;

    double minDistance; // = 1e-4;
    int emIter;
    int strem;

    /* nlesions parameterts*/
    double mahalanobisThreshold, rulesThreshold;
    int minsize;
    double wmneighbor;


    dtkSmartPointer <medAbstractData> output;

};

vistalProcessSegmentationSTREMPrivate::vistalProcessSegmentationSTREMPrivate(): imported(0),
    initMethod(HierarchicalFLAIR), approachEM(GaussianREM),
    rejectionRatio(0.2),  minDistance(1e-4), emIter(10), strem(0),
    mahalanobisThreshold(.4), rulesThreshold(3.),
    minsize(6), wmneighbor(0.05), output(0)

  // -0 -iter 200 dist 1e-3
  // show outliers, set iteration to 200, mindistance 1e-3,
{
}

vistalProcessSegmentationSTREMPrivate::~vistalProcessSegmentationSTREMPrivate()
{
}






// /////////////////////////////////////////////////////////////////
// vistalProcessSegmentationSTREM
// /////////////////////////////////////////////////////////////////

vistalProcessSegmentationSTREM::vistalProcessSegmentationSTREM(void) : dtkAbstractProcess(), d(new vistalProcessSegmentationSTREMPrivate)
{
}

vistalProcessSegmentationSTREM::~vistalProcessSegmentationSTREM(void)
{
    delete d;
}

bool vistalProcessSegmentationSTREM::registered(void)
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("vistalProcessSegmentationSTREM", createVistalProcessSegmentationSTREM);
}

QString vistalProcessSegmentationSTREM::description(void) const
{
    return "vistalProcessSegmentationSTREM";
}

void vistalProcessSegmentationSTREM::setInputImage(medAbstractData *data, int channel)
{
    if (!data)	return;

    if (!d) return;
    if (d->input.size() != 3)
    {
        d->input.push_back(NULL);
        d->input.push_back(NULL);
        d->input.push_back(NULL);
    }

    medAbstractData *dU8 = data->convert("vistalDataImageUChar3");

    if (!dU8)
    {
        qDebug() << "DataType conversion error";
        return;
    }
    
    if (channel >= 0 && channel < 3)
    {
        d->input[channel] = dU8;
    }
    if (channel == 3)
        d->mask = dU8;

    d->imported |= (1<< channel);
}


void vistalProcessSegmentationSTREM::setParameter(double  data, int channel)
{
    switch(channel){

    case(0):
        //if (data == 0)
        //					d->initMethod = vistalProcessSegmentationSTREMPrivate::Unset;
        //				else
        if (data == 0)
            d->initMethod = vistalProcessSegmentationSTREMPrivate::StraInit;
        else if (data == 1)
            d->initMethod = vistalProcessSegmentationSTREMPrivate::HierarchicalPD;
        else if (data == 2)
            d->initMethod = vistalProcessSegmentationSTREMPrivate::HierarchicalFLAIR;
        break;

    case 1:
        if (data > 0 && data < 1)
            d->rejectionRatio = data;
        else d->rejectionRatio = 0;

        break;

    case 2:
        if (data == 0)
            d->approachEM = vistalProcessSegmentationSTREMPrivate::GaussianEM;
        else if (data == 1)
            d->approachEM = vistalProcessSegmentationSTREMPrivate::GaussianCeleuxREM;
        else if (data == 2)
            d->approachEM = vistalProcessSegmentationSTREMPrivate::GaussianREM  ;
        break;

    case 3:
        d->minDistance = data;//1e-4;
        break;

    case 4:
        d->emIter = data;
        break;

    case 5:
        d->strem = data;
        break;
    case 6:
        d->mahalanobisThreshold = data;
        break;
    case 7:
        d->rulesThreshold = data;
        break;
    case 8:
        d->minsize = data;
        break;
    case 9:
        d->wmneighbor = data;
        break;
    default:
        return;
    }
}

// Run the STREM Algorithm
int vistalProcessSegmentationSTREM::update(void)
{
    using namespace mstools;
    // Starting  strainit binary code

    if (!(d->imported & 15))
    {
        qDebug() << "Error data not properly imported";
        return -1;
    }

    std::vector<vistal::Image3D<unsigned char> > input;
    vistal::Image3D <unsigned char> mask;
    
    foreach (dtkAbstractData *image, d->input)
    {
        vistal::Image3D<unsigned char>* ima = dynamic_cast<vistal::Image3D<unsigned char>* >((vistal::Image3D<unsigned char>* )image->data());
        if (!ima) { qDebug() << "What the fuck the image is fucked up here!!!"; return -1; }
        
        input.push_back(*ima);
    }
    
    mask = * (dynamic_cast<vistal::Image3D<unsigned char>* >((vistal::Image3D<unsigned char>* )d->mask->data()));

    FiniteModel initia;

    for(unsigned int i=0; i<3; i++)
    {
        Distribution::Pointer p=Gaussian::New( 3);
        initia.push_back(p);
    }


    switch (d->initMethod)
    {
    case vistalProcessSegmentationSTREMPrivate::StraInit:
    {
        qDebug() << "Stra Init";
        StraInitializer init(input,mask);


        if(!init. getInitialization(initia))
        {
            qDebug() << "Error in initialisation";
            return -1;
        }
        break;
    }
    case vistalProcessSegmentationSTREMPrivate::HierarchicalPD: // If third image is T2 use this init
    {
        qDebug() << "Hierarch PD";

        std::vector<std::string> seq;
        HierarchicalInitializer init(input,mask,seq,false,0.01, 0);
        if(!init. getInitialization(initia))
        {
            qDebug() << "Error in initialisation";
            return -1;
        }
        break;
    }
    case vistalProcessSegmentationSTREMPrivate::HierarchicalFLAIR: // If third image is FLAIR use this init
    {
        qDebug() << "Hierarch init FLAIR";

        std::vector<std::string> seq;
        HierarchicalInitializer init(input, mask, seq, true, 0.01, 0);
        qDebug() << "init loaded";
        if(!init. getInitialization(initia))
        {
            qDebug() << "Error in initialisation";
            return -1;
        }
        break;
    }
    default:
    {
        qDebug() << "Error in initialisation";

        return -1;
    }
    }

    // Starting Classification binary code

    int modalities = 3;

    JointHistogramNdims jointHistogram;
    std::vector<double> min( modalities, 255.0 ); //min values for random initialization
    std::vector<double> max( modalities, 0.0 ); //max values for random initialization

    for (unsigned i = 0; i < 3; ++i) min[i] = vistal::stats::GetMinPixelValue( input[ i ] , mask );
    for (unsigned i = 0; i < 3; ++i) max[i] = vistal::stats::GetMaxPixelValue( input[ i ] , mask );

    if (! jointHistogram.createJointHistogram( input, mask, false ))
    {
        qDebug() << "Error in Joint Histogram creation";
        return -1;  // Joint histogram construction failure
    }

    std::vector<unsigned int> emSteps( 1, 1 );
    std::vector<unsigned int> iterSteps( 1, 100 );

    ClassEstimator *estimator = NULL;

    switch (d->approachEM)
    {
    case vistalProcessSegmentationSTREMPrivate::GaussianCeleuxREM:
        estimator = new GaussianCeleuxREMEstimator( iterSteps[ 0 ], d->minDistance, d->emIter, d->strem );
        dynamic_cast<GaussianCeleuxREMEstimator *>( estimator ) ->setRejectionRatio( d->rejectionRatio );
        break;
    case vistalProcessSegmentationSTREMPrivate::GaussianEM:
        estimator = new GaussianEMEstimator( iterSteps[ 0 ], d->minDistance );
        break;
    case vistalProcessSegmentationSTREMPrivate::GaussianREM:
        estimator = new GaussianREMEstimator( iterSteps[ 0 ], d->minDistance, d->emIter, d->strem );
        dynamic_cast<GaussianREMEstimator *>( estimator ) ->setRejectionRatio( d->rejectionRatio );

        break;
    }

    estimator->setJointHistogram(jointHistogram);

    estimator->setModel(initia);

    unsigned iterations = 0;

    estimator->run(iterations);

    FiniteModel solution = estimator->getModel();

    // Got the segmentation ....

    if (solution.size() != 0)
    {
        ImageClassifier classifier;
        //Create classification output
        classifier.setModel( solution );

        vistal::Image3D<unsigned char> outima;

        classifier.getOutputImage( input , mask, outima );

        // Fixme tell medINRIA that outima is the output....

        //	if (d->showOutliers)
        //		{
        //		}
        //


    }

    delete estimator;


    // Now apply the nlesions binary


    vistal::Image3D<unsigned char> thImage;
    MahalanobisThreshold threshold;
    threshold.setModel( solution );
    threshold.setThreshold( d->mahalanobisThreshold );

    threshold.getThresholdImage( input, mask, thImage );

    vistal::Image3D<unsigned char> rulesIma;
    double rules3[3];
    rules3[0]=d->rulesThreshold;
    rules3[1]=d->rulesThreshold;
    rules3[2]=d->rulesThreshold;

    // Lesions in rules Ima are ==5
    if(!rulesT2lesions(rulesIma, thImage, input, solution, rules3, false /* verbose*/ ))
    {
        qDebug() << "Error in Lesions Rules application";

        return -1;
    }
    vistal::Image3D<unsigned int > labels;
    int numLabels=0;
    vistal::Image3D<unsigned int> tmpIma(mask, 0);
    for (vistal::Image3D<unsigned>::iterator it = tmpIma.begin(); it != tmpIma.end(); ++it)
        if (rulesIma(it.Position()) == 5)
            *it = 1;

    numLabels = Labelize( tmpIma, labels, 0 );

    vistal::Image3D<unsigned int> biglesions(tmpIma);
    rulesLesionSize(biglesions,mask,labels, d->minsize,/* verbose = */ false);

    // Removing border lesions
    //////////////////////////////
    vistal::Image3D<unsigned int> noborderlesions;

    if(!rulesBorder( noborderlesions, mask, biglesions,/* verbose = */false ))
    {
        std::cout<<" ** ERROR in rulesBorder"<<std::endl;
        return -1;
    }

    vistal::Image3D<unsigned char> classifIma;
    ImageClassifier classifier;
    classifier.setModel( solution );
    classifier.getOutputImage( input , mask, classifIma );


    vistal::Image3D<unsigned char> classifplus(classifIma);
    Voxel p;


    for (vistal::Image3D<unsigned char>::iterator it = classifplus.begin(); it != classifplus.end(); ++it)
        if(noborderlesions(it.Position()))
            *it = solution.size()+1;
    // Choose and remove small GM regions

    vistal::Image3D<unsigned char> nclassif;
    int minGMsize=15;
    //			std::cout<<" -- Cleaning GM in classification: minsize: "<<minGMsize<<std::endl;
    rules4GM(nclassif,classifplus,minGMsize,solution.size()-1,/*verbose=*/false);


    //			std::cout<<" -- Cleaning lesions that are not neighbors to the WM!"<<std::endl;
    vistal::Image3D<unsigned char> *fclassif = new vistal::Image3D<unsigned char>;
    rulesWM4lesions(*fclassif,noborderlesions,nclassif,solution.size()+1,d->wmneighbor,/*verbose=*/false);

    medAbstractData *tmpData = medAbstractDataFactory::instance()->create("vistalDataImageUChar3");
    tmpData->setData(fclassif);
    d->output = tmpData->convert("itkDataImageUChar3");

    foreach(QString list, d->input[0]->metaDataList())
        d->output->addMetaData(list, d->input[0]->metaDataValues(list));

    QString newSeriesDescription = d->output->metadata(medMetaDataKeys::SeriesDescription.key());
    newSeriesDescription += " STREM lesions segmentation";

    d->output->setMetaData(medMetaDataKeys::SeriesDescription.key(),newSeriesDescription);

    return EXIT_SUCCESS;
}

dtkAbstractData * vistalProcessSegmentationSTREM::output(void)
{
    return d->output;
}

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess *createVistalProcessSegmentationSTREM(void)
{
    return new vistalProcessSegmentationSTREM;
}
