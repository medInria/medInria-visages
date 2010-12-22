// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalProcessDenoising.h"

#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include "itkDataImageToVistalDataImageDouble3Converter.h"
#include "itkDataImageToVistalDataImageFloat3Converter.h"
#include "itkDataImageToVistalDataImageInt3Converter.h"
#include "itkDataImageToVistalDataImageShort3Converter.h"
#include "itkDataImageToVistalDataImageChar3Converter.h"
#include "itkDataImageToVistalDataImageUInt3Converter.h"
#include "itkDataImageToVistalDataImageUShort3Converter.h"
#include "itkDataImageToVistalDataImageUChar3Converter.h"

#include "NLMeans_class.hh"
#include <cstdlib>

// /////////////////////////////////////////////////////////////////
// vistalProcessDenoisingPrivate
// /////////////////////////////////////////////////////////////////

class vistalProcessDenoisingPrivate
{
public:
        dtkAbstractData *input;
        dtkAbstractData *output;

        double seuil;
        double beta;
        int seuil_adapt;
        int isotropic;
        double S;
        double M;
        int testmean;
        int testvar;
        double m_min;
        double v_min;
        int weight_method;
        int block;
        int b_space;
        //char* temp;

        // TO DO : parameters and options
        // TO DO : input and output images
        // TO DO : temp: directory for slice preview
        // TO DO : use QSettings to store parameters ? or not
};

// /////////////////////////////////////////////////////////////////
// vistalProcessDenoising
// /////////////////////////////////////////////////////////////////

vistalProcessDenoising::vistalProcessDenoising(void) : dtkAbstractProcess(), d(new vistalProcessDenoisingPrivate)
{
        d->seuil = 0;
        d->beta = 1;
        d->seuil_adapt = 0;
        d->isotropic = 0;
        d->S = 1;
        d->M = 5;
        d->testmean = 1;
        d->testvar = 1;
        d->m_min = 0.95;
        d->v_min = 0.5;
        d->weight_method = 0;
        d->block = 1;
        d->b_space = 2;
        //temp = NULL;
}

vistalProcessDenoising::~vistalProcessDenoising(void)
{
        // TO DO: useless ?
        delete d->input;
        delete d->output;
}

bool vistalProcessDenoising::registered(void)
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("vistalProcessDenoising", createVistalProcessDenoising);
}

QString vistalProcessDenoising::description(void) const
{
    return "vistalProcessDenoising";
}

void vistalProcessDenoising::setInput(dtkAbstractData *data)
{

    // TO DO : convert and store converted data into d->input (private)
    // TO DO : Should we expect itkDataImages only ? (answer: no, but we'll see later)
    // TO DO : warning or similar action to handle incompatible input types
    // TO DO : what if: input == NULL ?
    // TO DO : correct : D->INPUT
    // TO DO : D->INPUT (test NULL after new and convert)
    // TO DO : correct use of converter: see AbstractDataConverter

    if (!data)
        return;

    if (data->description() == "itkDataImageUChar3")
    {
        //itkDataImageToVistalDataImageUChar3Converter *converter = new itkDataImageToVistalDataImageUChar3Converter;
        //if(converter == NULL)
        //    return;

        //converter->setData(data);
        //d->input = converter->convert();
        
        d->input = data->convert("vistalDataImageUChar3");	

	if (!d->input)
	  return;
	  


        //delete converter;
    }

    else if (data->description() == "itkDataImageUShort3")
    {
        //itkDataImageToVistalDataImageUShort3Converter *converter = new itkDataImageToVistalDataImageUShort3Converter;
        //if(converter == NULL)
        //    return;

        //converter->setData(data);
        //d->input = converter->convert();
        
        d->input = data->convert("vistalDataImageUShort3");
	if (!d->input)
	  return;
	

        //delete converter;
    }

    else if (data->description() == "itkDataImageFloat3")
    {
        //itkDataImageToVistalDataImageFloat3Converter *converter = new itkDataImageToVistalDataImageFloat3Converter;
        //if(converter == NULL)
        //    return;

        //converter->setData(data);
        //d->input = converter->convert();
        
        d->input = data->convert("vistalDataImageFloat3");
	if (!d->input)
	  return;
               

        //delete converter;
    }

    else if (data->description() == "itkDataImageDouble3")
    {
        /*itkDataImageToVistalDataImageDouble3Converter *converter = new itkDataImageToVistalDataImageDouble3Converter;
        if(converter == NULL)
            return;

        converter->setData(data);
        d->input = converter->convert();

        delete converter;*/
	
	d->input = data->convert("vistalDataImageDouble3");
	if (!d->input)
	  return;
	
	
    }

    else if (data->description() == "itkDataImageShort3")
    {
        /*itkDataImageToVistalDataImageShort3Converter *converter = new itkDataImageToVistalDataImageShort3Converter;
        if(converter == NULL)
            return;

        converter->setData(data);
        d->input = converter->convert();

        delete converter;*/
	
	d->input = data->convert("vistalDataImageShort3");
	if (!d->input)
	  return;
	
	
	
    }

    else if (data->description() == "itkDataImageInt3")
    {
        /*itkDataImageToVistalDataImageInt3Converter *converter = new itkDataImageToVistalDataImageInt3Converter;
        if(converter == NULL)
            return;

        converter->setData(data);
        d->input = converter->convert();

        delete converter;*/
	
	d->input = data->convert("vistalDataImageInt3");
	if (!d->input)
	  return;
	
    }

    else if (data->description() == "itkDataImageUInt3")
    {
        /*itkDataImageToVistalDataImageUInt3Converter *converter = new itkDataImageToVistalDataImageUInt3Converter;
        if(converter == NULL)
            return;

        converter->setData(data);
        d->input = converter->convert();

        delete converter;*/
	
	d->input = data->convert("vistalDataImageUInt3");
	if (!d->input)
	  return;
    }
    else
        return;
}



void vistalProcessDenoising::setParameter(double  data, int channel)
{
        // TO DO : handle wrong channel id
        // TO DO : store parameters in vistalProcessDenoisingPrivate

    switch (channel){

        case (0):
                d->seuil = data;
                break;
        case (1):
                d->beta = data;
                break;
        case (2):
                d->seuil_adapt = data;
                break;
        case (3):
                d->isotropic =data;
                break;
        case (4):
                d->S = data;
                break;
        case (5):
                d->M =data;
                break;
        case (6):
                d->testmean = data;
                break;
        case (7):
                d->testvar = data;
                break;
        case (8):
                d->m_min = data;
                break;
        case (9):
                d->v_min = data;
                break;
        case (10):
                d->weight_method = data;
                break;
        case (11):
                d->block = data;
                break;
        case (12):
                d->b_space = data;
                break;
        default :
                return;
        }
}


int vistalProcessDenoising::update (void)
{
        // TO DO : construct NLMeansDenoising<> according to data->description (if...else if..)
        // TO DO : setInput, set{parameters}, run, output
        // TO DO : delete nlmeans after process
        // TO DO : unresolved input descriptions
        // TO DO : output stored in d->output
        // TO DO : see again: *output allocation

        if (d->input == NULL)
            return -1;

        if (d->input->description() == "vistalDataImageUChar3")
        {
            vistal::NLMeansDenoising<unsigned char> *nlmeans = new vistal::NLMeansDenoising<unsigned char>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(static_cast<vistal::Image3D<unsigned char> * > (d->input->data()));
            nlmeans->setAdaptiveSlope(d->seuil_adapt);
            nlmeans->setSigma(d->seuil);
            nlmeans->setBeta(d->beta);
            nlmeans->setIsotropicNeighborhood(d->isotropic);
            nlmeans->setNeighborhoodSize(d->S);
            nlmeans->setSearchVolumeSize(d->M);
            nlmeans->setBlockApproach(d->block);
            nlmeans->setTestOnMean(d->testmean);
            nlmeans->setTestOnVar(d->testvar);
            nlmeans->setMeanMinRatio(d->m_min);
            nlmeans->setVarMinRatio(d->v_min);
            nlmeans->setWeightingMethod(d->weight_method);
            nlmeans->setDistanceBetweenBlocks(d->b_space);

            nlmeans->run();

            d->output = dtkAbstractDataFactory::instance()->create("vistalDataImageUChar3");
            if (d->output == NULL)
                return -1;

            d->output->setData(nlmeans->getOutput());

            if(d->output->data() == NULL)
                return -1;

            delete nlmeans;

        }
/*        else if (d->input->description() == "vistalDataImageUShort3")
        {
            vistal::NLMeansDenoising<unsigned short> *nlmeans = new vistal::NLMeansDenoising<unsigned short>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(static_cast<vistal::Image3D<unsigned short> * > (d->input->data()));
            nlmeans->setAdaptiveSlope(d->seuil_adapt);
            nlmeans->setSigma(d->seuil);
            nlmeans->setBeta(d->beta);
            nlmeans->setIsotropicNeighborhood(d->isotropic);
            nlmeans->setNeighborhoodSize(d->S);
            nlmeans->setSearchVolumeSize(d->M);
            nlmeans->setBlockApproach(d->block);
            nlmeans->setTestOnMean(d->testmean);
            nlmeans->setTestOnVar(d->testvar);
            nlmeans->setMeanMinRatio(d->m_min);
            nlmeans->setVarMinRatio(d->v_min);
            nlmeans->setWeightingMethod(d->weight_method);
            nlmeans->setDistanceBetweenBlocks(d->b_space);

            nlmeans->run();

            d->output = dtkAbstractDataFactory::instance()->create("vistalDataImageUShort3");
            if (d->output == NULL)
                return -1;

            d->output->setData(nlmeans->getOutput());

            if(d->output->data() == NULL)
                return -1;

            delete nlmeans;

        }
        else if (d->input->description() == "vistalDataImageFloat3")
        {
            vistal::NLMeansDenoising<float> *nlmeans = new vistal::NLMeansDenoising<float>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(static_cast<vistal::Image3D<float> * > (d->input->data()));
            nlmeans->setAdaptiveSlope(d->seuil_adapt);
            nlmeans->setSigma(d->seuil);
            nlmeans->setBeta(d->beta);
            nlmeans->setIsotropicNeighborhood(d->isotropic);
            nlmeans->setNeighborhoodSize(d->S);
            nlmeans->setSearchVolumeSize(d->M);
            nlmeans->setBlockApproach(d->block);
            nlmeans->setTestOnMean(d->testmean);
            nlmeans->setTestOnVar(d->testvar);
            nlmeans->setMeanMinRatio(d->m_min);
            nlmeans->setVarMinRatio(d->v_min);
            nlmeans->setWeightingMethod(d->weight_method);
            nlmeans->setDistanceBetweenBlocks(d->b_space);

            nlmeans->run();

            d->output = dtkAbstractDataFactory::instance()->create("vistalDataImageFloat3");
            if (d->output == NULL)
                return -1;

            d->output->setData(nlmeans->getOutput());

            if(d->output->data() == NULL)
                return -1;

            delete nlmeans;

        }
        else if (d->input->description() == "vistalDataImageDouble3")
        {
            vistal::NLMeansDenoising<double> *nlmeans = new vistal::NLMeansDenoising<double>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(static_cast<vistal::Image3D<double> * > (d->input->data()));
            nlmeans->setAdaptiveSlope(d->seuil_adapt);
            nlmeans->setSigma(d->seuil);
            nlmeans->setBeta(d->beta);
            nlmeans->setIsotropicNeighborhood(d->isotropic);
            nlmeans->setNeighborhoodSize(d->S);
            nlmeans->setSearchVolumeSize(d->M);
            nlmeans->setBlockApproach(d->block);
            nlmeans->setTestOnMean(d->testmean);
            nlmeans->setTestOnVar(d->testvar);
            nlmeans->setMeanMinRatio(d->m_min);
            nlmeans->setVarMinRatio(d->v_min);
            nlmeans->setWeightingMethod(d->weight_method);
            nlmeans->setDistanceBetweenBlocks(d->b_space);

            nlmeans->run();

            d->output = dtkAbstractDataFactory::instance()->create("vistalDataImageDouble3");
            if (d->output == NULL)
                return -1;

             d->output->setData(nlmeans->getOutput());
	    //d->output = static_cast<dtkAbstractData *> (nlmeans->getOutput());

            if(d->output->data() == NULL)
                return -1;

            delete nlmeans;

        }
        else if (d->input->description() == "vistalDataImageShort3")
        {
            vistal::NLMeansDenoising<short> *nlmeans = new vistal::NLMeansDenoising<short>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(static_cast<vistal::Image3D<short> * > (d->input->data()));
            nlmeans->setAdaptiveSlope(d->seuil_adapt);
            nlmeans->setSigma(d->seuil);
            nlmeans->setBeta(d->beta);
            nlmeans->setIsotropicNeighborhood(d->isotropic);
            nlmeans->setNeighborhoodSize(d->S);
            nlmeans->setSearchVolumeSize(d->M);
            nlmeans->setBlockApproach(d->block);
            nlmeans->setTestOnMean(d->testmean);
            nlmeans->setTestOnVar(d->testvar);
            nlmeans->setMeanMinRatio(d->m_min);
            nlmeans->setVarMinRatio(d->v_min);
            nlmeans->setWeightingMethod(d->weight_method);
            nlmeans->setDistanceBetweenBlocks(d->b_space);

            nlmeans->run();

            d->output = dtkAbstractDataFactory::instance()->create("vistalDataImageShort3");
            if (d->output == NULL)
                return -1;

            d->output->setData(nlmeans->getOutput());

            if(d->output->data() == NULL)
                return -1;

            delete nlmeans;

        }
        else if (d->input->description() == "vistalDataImageInt3")
        {
            vistal::NLMeansDenoising<int> *nlmeans = new vistal::NLMeansDenoising<int>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(static_cast<vistal::Image3D<int> * > (d->input->data()));
            nlmeans->setAdaptiveSlope(d->seuil_adapt);
            nlmeans->setSigma(d->seuil);
            nlmeans->setBeta(d->beta);
            nlmeans->setIsotropicNeighborhood(d->isotropic);
            nlmeans->setNeighborhoodSize(d->S);
            nlmeans->setSearchVolumeSize(d->M);
            nlmeans->setBlockApproach(d->block);
            nlmeans->setTestOnMean(d->testmean);
            nlmeans->setTestOnVar(d->testvar);
            nlmeans->setMeanMinRatio(d->m_min);
            nlmeans->setVarMinRatio(d->v_min);
            nlmeans->setWeightingMethod(d->weight_method);
            nlmeans->setDistanceBetweenBlocks(d->b_space);
            nlmeans->run();

            d->output = dtkAbstractDataFactory::instance()->create("vistalDataImageInt3");
            if (d->output == NULL)
                return -1;

            d->output->setData(nlmeans->getOutput());

            if(d->output->data() == NULL)
                return -1;

            delete nlmeans;

        }
        else if (d->input->description() == "vistalDataImageUInt3")
        {
            vistal::NLMeansDenoising<unsigned int> *nlmeans = new vistal::NLMeansDenoising<unsigned int>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(static_cast<vistal::Image3D<unsigned int> * > (d->input->data()));
            nlmeans->setAdaptiveSlope(d->seuil_adapt);
            nlmeans->setSigma(d->seuil);
            nlmeans->setBeta(d->beta);
            nlmeans->setIsotropicNeighborhood(d->isotropic);
            nlmeans->setNeighborhoodSize(d->S);
            nlmeans->setSearchVolumeSize(d->M);
            nlmeans->setBlockApproach(d->block);
            nlmeans->setTestOnMean(d->testmean);
            nlmeans->setTestOnVar(d->testvar);
            nlmeans->setMeanMinRatio(d->m_min);
            nlmeans->setVarMinRatio(d->v_min);
            nlmeans->setWeightingMethod(d->weight_method);
            nlmeans->setDistanceBetweenBlocks(d->b_space);

            nlmeans->run();

            d->output = dtkAbstractDataFactory::instance()->create("vistalDataImageUInt3");
            if (d->output == NULL)
                return -1;

            d->output->setData(nlmeans->getOutput());

            if(d->output->data() == NULL)
                return -1;

            delete nlmeans;

        }
        else
            return -1;

*/        return EXIT_SUCCESS;

}

dtkAbstractData * vistalProcessDenoising::output(void)
{
        // TO DO : what if: output == NULL ? (error, warning, message, signal, etc.)
        // TO DO : call d->output
        // TO DO : convert into type itkDataImage

//         if (!d->output)
//             return;
        return (static_cast<dtkAbstractData *> (d->output->data()));

}


// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess * createVistalProcessDenoising(void)
{
    return new vistalProcessDenoising;
}
