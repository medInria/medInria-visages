// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalProcessDenoising.h"

#include <dtkCore/dtkAbstractProcessFactory.h>

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

void setInput(dtkAbstractData *data)
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
        itkDataImageToVistalDataImageUChar3Converter *converter = new itkDataImageToVistalDataImageUChar3Converter;
        if(converter == NULL)
            return;

        converter->setData(data);
        d->input = converter->convert();

        delete converter;
    }

    else if (data->description() == "itkDataImageUShort3")
    {
        itkDataImageToVistalDataImageUShort3Converter *converter = new itkDataImageToVistalDataImageUShort3Converter;
        if(converter == NULL)
            return;

        converter->setData(data);
        d->input = converter->convert();

        delete converter;
    }

    else if (data->description() == "itkDataImageFloat3")
    {
        itkDataImageToVistalDataImageFloat3Converter *converter = new itkDataImageToVistalDataImageFloat3Converter;
        if(converter == NULL)
            return;

        converter->setData(data);
        d->input = converter->convert();

        delete converter;
    }

    else if (data->description() == "itkDataImageDouble3")
    {
        itkDataImageToVistalDataImageDouble3Converter *converter = new itkDataImageToVistalDataImageDouble3Converter;
        if(converter == NULL)
            return;

        converter->setData(data);
        d->input = converter->convert();

        delete converter;
    }

    else if (data->description() == "itkDataImageShort3")
    {
        itkDataImageToVistalDataImageShort3Converter *converter = new itkDataImageToVistalDataImageShort3Converter;
        if(converter == NULL)
            return;

        converter->setData(data);
        d->input = converter->convert();

        delete converter;
    }

    else if (data->description() == "itkDataImageInt3")
    {
        itkDataImageToVistalDataImageInt3Converter *converter = new itkDataImageToVistalDataImageInt3Converter;
        if(converter == NULL)
            return;

        converter->setData(data);
        d->input = converter->convert();

        delete converter;
    }

    else if (data->description() == "itkDataImageUInt3")
    {
        itkDataImageToVistalDataImageUInt3Converter *converter = new itkDataImageToVistalDataImageUInt3Converter;
        if(converter == NULL)
            return;

        converter->setData(data);
        d->input = converter->convert();

        delete converter;
    }
    else
        return;
}



void setParameter(double  data, int channel)
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


int update (void)
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
            NLMeansDenoising<unsigned char> *nlmeans = new NLMeansDenoising<unsigned char>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(d->input->data());
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
        else if (d->input->description() == "vistalDataImageUShort3")
        {
            NLMeansDenoising<unsigned short> *nlmeans = new NLMeansDenoising<unsigned short>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(d->input->data());
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
            NLMeansDenoising<float> *nlmeans = new NLMeansDenoising<float>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(d->input->data());
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
            NLMeansDenoising<double> *nlmeans = new NLMeansDenoising<double>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(d->input->data());
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

            if(d->output->data() == NULL)
                return -1;

            delete nlmeans;

        }
        else if (d->input->description() == "vistalDataImageShort3")
        {
            NLMeansDenoising<short> *nlmeans = new NLMeansDenoising<short>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(d->input->data());
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
            NLMeansDenoising<int> *nlmeans = new NLMeansDenoising<int>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(d->input->data());
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
            NLMeansDenoising<unsigned int> *nlmeans = new NLMeansDenoising<unsigned int>;

            if(nlmeans == NULL)
                return -1;

            nlmeans->setInput(d->input->data());
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

        return EXIT_SUCCESS;

}

dtkAbstractData *output(void)
{
        // TO DO : what if: output == NULL ? (error, warning, message, signal, etc.)
        // TO DO : call d->output
        // TO DO : convert into type itkDataImage

        if (d->output == NULL)
            return -1;

        return (d->output->data());

}


// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess *createVistalProcessDenoising(void)
{
    return new vistalProcessDenoising;
}