// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalProcessSegmentationSTREM.h"

#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>

#include "gcTlinks.h"
#include "gcGraph3D.h"

// /////////////////////////////////////////////////////////////////
// vistalProcessSegmentationSTREMPrivate
// /////////////////////////////////////////////////////////////////

class vistalProcessSegmentationSTREMPrivate
{
public:
          QVector< vistal::Image3D<float>* > input;
//        vistal::Image3D<unsigned char> *target;
//        vistal::Image3D<unsigned char> *sink;
//        vistal::Image3D<char> *mask;
//        float alpha;
//        vistal::Tlinks::e_mode tlinkMode;
//        vistal::Image3D<float> *targetProba;
//        vistal::Image3D<float> *sinkProba;
////        dtkAbstractData *seedMask;
//        vistal::Image3D<float> *atlas;
//        float beta;
//        bool useSpecGrad;
//        float sigma;
//        dtkAbstractData *output;

//        QVector < dtkAbstractData *> input;
          dtkAbstractData *target;
          dtkAbstractData *sink;

          dtkAbstractData *mask;
          float alpha;
          vistal::Tlinks::e_mode tlinkMode;
          dtkAbstractData *targetProba;
          dtkAbstractData *sinkProba;
////        dtkAbstractData *seedMask;

          dtkAbstractData *atlas;
          float beta;
          bool useSpecGrad;
          float sigma;
          dtkAbstractData *output;
};

// /////////////////////////////////////////////////////////////////
// vistalProcessSegmentationSTREM
// /////////////////////////////////////////////////////////////////

vistalProcessSegmentationSTREM::vistalProcessSegmentationSTREM(void) : dtkAbstractProcess(), d(new vistalProcessSegmentationSTREMPrivate)
{
        d->target = NULL;
        d->sink = NULL;
        d->mask = NULL;
        d->alpha = 1;
        d->tlinkMode = vistal::Tlinks::Density;
        d->targetProba = NULL;
        d->sinkProba = NULL;
//        d->seedMask = NULL;
        d->atlas = NULL;
        d->beta = 0;
        d->useSpecGrad = false;
        d->sigma = 0.6;
        d->output = NULL;
}

vistalProcessSegmentationSTREM::~vistalProcessSegmentationSTREM(void)
{
//        for(int i=0; i < d->input.size();i++)
//        {
//          remove d->input(i);
//        }

        delete d->target;
        d->target = NULL;

        delete d->sink;
        d->sink = NULL;

        delete d->mask;
        d->mask = NULL;

        delete d->targetProba;
        d->targetProba = NULL;

        delete d->sinkProba;
        d->sinkProba = NULL;

//        delete d->seedMask;
//        d->seedMask = NULL;

        delete d->atlas;
        d->atlas = NULL;

        delete d->output;
        d->output = NULL;
}

bool vistalProcessSegmentationSTREM::registered(void)
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("vistalProcessSegmentationSTREM", createVistalProcessSegmentationSTREM);
}

QString vistalProcessSegmentationSTREM::description(void) const
{
    return "vistalProcessSegmentationSTREM";
}

void vistalProcessSegmentationSTREM::setInput(dtkAbstractData *data, int channel)
{
        switch (channel){

            case(0):
                    if(!data)
                        return;
                    qDebug() << "method setInput, entering case 0";
//                    d->input.append(static_cast<vistal::Image3D<float>* > (data->convert("vistalDataImageFloat3")->data()) );
                      d->input.append(static_cast<vistal::Image3D<float>* > (data->data()) );
//                    d->input.append(data);
                    qDebug() << "after append new input image to vector, size is " << d->input.size();
                    break;

            case(1):
                    if (!data)
                        return;
                    qDebug() << "entering setInput, case 1";
                    //d->target = static_cast<vistal::Image3D<unsigned char>* >(data->convert("vistalDataImageUChar3")->data());
                    //d->target = static_cast<vistal::Image3D<unsigned char>* > (data->data());
                    d->target = data;
                    qDebug() << "after setting target";
                    break;

            case(2):
                    if (!data)
                        return;
                    qDebug() << "entering setInput, case 2";
                    //d->sink = static_cast<vistal::Image3D<unsigned char>* > (data->convert("vistalDataImageUChar3")->data());
                    //d->sink = static_cast<vistal::Image3D<unsigned char>* > (data->data());
                    d->sink = data;
                    qDebug() << "after setting sink";
                    break;

//            case(3):
//                    if (!data)
//                        return;
//                    d->mask = static_cast<vistal::Image3D<char>* > (data->convert("vistalDataImageChar3")->data());
//                    break;
//            case(4):
//                    if (!data)
//                        return;
//                    d->targetProba = static_cast<vistal::Image3D<float>* > (data->convert("vistalDataImageFloat3")->data());
//                    break;
//
//            case(5):
//                    if (!data)
//                        return;
//                    d->sinkProba = static_cast<vistal::Image3D<float>* > (data->convert("vistalDataImageFloat3")->data());
//                    break;
//
//            case(6):
//                    if (!data)
//                        return;
//                    d->atlas = static_cast<vistal::Image3D<float>* > (data->convert("vistalDataImageFloat3")->data());
//                    break;


//            case(7):
//                    if (!data)
//                        return;
//                    d->seedMask = data;
//                    break;

            default:
                return;
        }
}


void vistalProcessSegmentationSTREM::setParameter(double  data, int channel)
{
        switch(channel){

            case(0):
                    d->alpha = data;
                    break;
            case(1):
                    if(data == 0)
                        d->tlinkMode = vistal::Tlinks::Gaussian;
                    else if(data == 1)
                        d->tlinkMode = vistal::Tlinks::Strem;
                    else if(data == 2)
                        d->tlinkMode = vistal::Tlinks::Parzen;
                    else if(data ==3)
                        d->tlinkMode = vistal::Tlinks::Density;
                    else
                        return;

                    break;

            case(2):
                    d->beta = data;
                    break;

            case(3):
                    d->useSpecGrad = data;
                    break;

            case(4):
                    d->sigma = data;
                    break;

            default:
                return;
        }
}


int vistalProcessSegmentationSTREM::update(void)
{
  bool ok;

  if(d->input.isEmpty() || !d->target || !d->sink)
      return -1;

  if ((!d->targetProba) && (!d->sinkProba))
  {
    qDebug() << "Computing t-links";

    d->targetProba->setData(static_cast<vistal::Image3D<float> *>(d->input[0]));
    d->sinkProba->setData(static_cast<vistal::Image3D<float> *>(d->input[0]));

    // targetProba and sinkProba initialization (IS IT REQUIRED to prevent SEGFAULT ?)
//    d->targetProba = new vistal::Image3D<float> (*d->input[0],0.5);
//    d->sinkProba = new vistal::Image3D<float> (*d->input[0],0.5);


    vistal::Tlinks *probaMaps = new vistal::Tlinks( (vistal::Tlinks::e_mode)d->tlinkMode, d->alpha, d->input.toStdVector());

    if ((!d->target) && (!d->sink))
      probaMaps -> addSeeds( static_cast<vistal::Image3D<unsigned char>* > (d->target->data()), static_cast<vistal::Image3D<unsigned char>* > (d->sink->data()));

    qDebug() << "OK 1 ?";

    if (d->atlas)
      probaMaps -> addAtlas( static_cast<vistal::Image3D<float>* > (d->atlas->data()), d->beta);

    qDebug() << "OK 2 ?";

    ok = probaMaps -> generateProbaMaps( static_cast<vistal::Image3D<float> * > (d->targetProba->data()), static_cast<vistal::Image3D<float>* > (d->sinkProba->data()));

    qDebug() << "OK 3 ?";

    if(!ok)
        return -1;

    delete probaMaps;
  }

  qDebug() << " -- Computing Graph Cuts ";

  vistal::Graph3D *graphSeg = new vistal::Graph3D( d->useSpecGrad, d->sigma, static_cast<vistal::Image3D<float>* > (d->targetProba->data()), static_cast<vistal::Image3D<float>* > (d->sinkProba->data()), static_cast<vistal::Image3D<char>* > (d->mask->data()), d->input.toStdVector() );

  ok = graphSeg->createGraph();

  if(!ok)
  {
    qDebug() << "error : graph creation failed";
    return -1;
  }

  graphSeg->computeGraphCut(*static_cast<vistal::Image3D<unsigned char> *>(d->output->data()), false);

  if(!ok)
  {
    qDebug() << "error : graphcut computation failed";
    return -1;
  }

  delete graphSeg;

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
