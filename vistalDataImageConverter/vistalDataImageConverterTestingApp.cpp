#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkPluginManager.h>

#include <QtCore>
#include <QtGui>
#include <QtDebug>

#include <iostream>

#include "Image3D.hh"
#include "loadImg.hh"

#include "Arguments.hh"




int main(int argc, char **argv)
{
        QApplication application(argc, argv);
        application.setApplicationName("vistalProcessSegmentationGCEMTesting");
        application.setApplicationVersion("0.0.1");
        application.setOrganizationName("INRIA");
        application.setOrganizationDomain("FR");

        LSArguments arg(argc, (const char**)argv);

        if (!arg.parsed) return -1;
        if (arg.gethelp()) { arg.usage(argv[0]); return -2; }



        dtkPluginManager::instance()->initialize();


        QString t1 = arg.gett1().c_str();
        QString pd = arg.getpd().c_str();

        QString t2 = arg.gett2().c_str();

        QString flair = arg.getflair().c_str();


        if (t1 == "")
                std::cerr << "Expecting T1 input" << std::endl;
        if (pd == "")
                std::cerr << "Expecting PD input" << std::endl;
        if (t2 == "" && flair == "")
                std::cerr << "Expecting T2 or FLAIR input image" << std::endl;

        if (t1== "" || pd == "" && (flair == "" || t2 == ""))
                abort();

        vistal::Image3D<unsigned char> *im1 = new 	vistal::Image3D<unsigned char>;
        loadImage(arg.gett1(), *im1, 0);

        dtkAbstractData *inputImage = dynamic_cast <dtkAbstractData *>(dtkAbstractDataFactory::instance()->create("vistalDataImageUChar3"));
        inputImage->setData(im1);

        vistal::Image3D<unsigned char>* im2 = new 	vistal::Image3D<unsigned char>;
        loadImage(arg.getpd(), *im2, 0);

        dtkAbstractData *PD = dynamic_cast <dtkAbstractData *>(dtkAbstractDataFactory::instance()->create("vistalDataImageUChar3"));
        PD->setData(im2);


        vistal::Image3D<unsigned char> *im3 = new 	vistal::Image3D<unsigned char>;
        if (t2 == "" && flair != "")
                loadImage(arg.getflair(), *im3, 0);
        else
                loadImage(arg.gett2(), *im3, 0);

        dtkAbstractData *Third = dynamic_cast <dtkAbstractData *>(dtkAbstractDataFactory::instance()->create("vistalDataImageUChar3"));
        Third->setData(im3);

        vistal::Image3D<unsigned char>* msk = new 	vistal::Image3D<unsigned char>;
        loadImage(arg.getmask(), *msk, 0);

        dtkAbstractData *mask = dynamic_cast <dtkAbstractData *>(dtkAbstractDataFactory::instance()->create("vistalDataImageUChar3"));
        mask->setData(msk);

        dtkAbstractProcess *process = dynamic_cast <dtkAbstractProcess *>(dtkAbstractProcessFactory::instance()->create("vistalProcessSegmentationGCEM"));
        if (!process) {
                qDebug() << "I am not able to find myself!!! ouiiiiiiiiiiinnnnnnnnnn !!!!!!!!";
                return -1;
        }


        /* Set Options  */

        process->setParameter((double)arg.getinitMethod(), 0);
        process->setParameter((double)arg.getrejectionRatio(), 1);
        process->setParameter((double)arg.getEMAlgorithm(), 2);
        process->setParameter((double)arg.getminDistance(), 3 );
        process->setParameter((double)arg.getemIter(), 4);
        process->setParameter((double)arg.getstrem(), 5);
        process->setParameter((double)arg.getmahalanobisThreshold(), 6);
        process->setParameter((double)arg.getrulesThreshold(), 7);
        process->setParameter((double)arg.getminsize(), 8);
        process->setParameter((double)arg.getwmneighbor(), 9);

        process->setParameter((double)arg.getrulesMin(), 10);
        process->setParameter((double)arg.getrulesMax(), 11);
        process->setParameter((double)arg.getalphap(), 12);



/* Set algorithm input images
 */

        process->setInput(inputImage,0);

        process->setInput(PD,1);

        process->setInput(Third,2);

        process->setInput(mask,3);

        process->update();

        if (!process->output())
        {
                qDebug() << "Warning output not available";

        }
        else {


        vistal::Image3D<unsigned char>* ima = dynamic_cast<vistal::Image3D<unsigned char>* >((vistal::Image3D<unsigned char>* )process->output()->data());

        vistal::gis::saveVolume(arg.getoutput().c_str(), *ima, 0);
        dtkAbstractData *outputImage = process->output();
        outputImage->enableWriter("vistalDataImageWriter");
        outputImage->write(arg.getoutput().c_str());
        }




        dtkPluginManager::instance()->uninitialize();


        delete inputImage;
        delete PD;
        delete Third;
        delete mask;


        return DTK_SUCCEED;
}
