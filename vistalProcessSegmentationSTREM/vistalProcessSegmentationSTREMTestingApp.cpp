#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkPluginManager.h>

#include <QtCore>
#include <QtDebug>

#include <iostream>

#include "Image3D.hh"
#include "loadImg.hh"

#include "Arguments.hh"

/*
initMethod(HierarchicalFLAIR), approachEM(GaussianREM),
rejectionRatio(0.2),  minDistance(1e-4), emIter(10), strem(0),
mahalanobisThreshold(.4), rulesThreshold(3.),
minsize(6), wmneighbor(0.05), output(0)
*/

class LSArguments: public GenericArguments
{
        //	MANDATORY(1,std::string, i1, "", "", "Reference Image (4D volume)", InputArgument, "Image4D");
        OPTIONAL(1, std::string, t1, "t", "t1-image", "T1 Weighted Image", "/Users/nwiestda/Data/USPIO-6/01011/M0/unbias_3DMPRAGEs005a001", InputArgument, "Image3D");
        OPTIONAL(2, std::string, pd, "pd", "pd-image", "Proton Density Weighted image", "/Users/nwiestda/Data/USPIO-6/01011/M0/DP_3D", InputArgument, "Image3D");

        OPTIONAL(3, std::string, t2, "t2", "t2-image", "T2 Weighted image", "", InputArgument, "Image3D");

        OPTIONAL(4, std::string, flair, "flair", "flair-image", "FLAIR image", "/Users/nwiestda/Data/USPIO-6/01011/M0/unbias_3DFLAIRs007a001", InputArgument, "Image3D");

        ENUM(5, initMethod, "I", "init-method", "Method for initialisation", (StraInit)(HierarchicalPD)(HierarchicalFLAIR), HierarchicalFLAIR);

        OPTIONAL(6, double, rejectionRatio, "rej", "rejectionRatio", "Robust estimation rejection Ratio", ".2", InputArgument, "Image3D");

        ENUM(7, EMAlgorithm, "EM", "EM-Algorithm", "EM Algorithm", (GaussianEM)(GaussianCeleuxREM)(GaussianREM), GaussianREM);

        OPTIONAL(8, double, minDistance, "minD", "minDistance", "Minimum distance in EM (stoping criteria)", "1e-4", InputArgument, "");

        OPTIONAL(9, int, emIter, "eit", "emIter", "Iterations of the EM Algorithm", "1e-4", InputArgument, "");

        FLAG(10, strem, "st", "Strem", "Start the first iteration with STREM?", false);

        //OPTIONAL(11, float, emIter, "eit", "emIter", "Iterations of the EM Algorithm", "10", InputArgument, "");


        OPTIONAL(11, double, mahalanobisThreshold, "mTh", "mahalanobisThreshold", "Threshold in the Mahalanobis distance", ".4", InputArgument, "");
        OPTIONAL(12, double, rulesThreshold, "rTh", "rulesThreshold", "Threshold to apply rules (in times of SD)", "3.", InputArgument, "");
        OPTIONAL(13, double, minsize, "msize", "minsize", "minimum lesion size", "6", InputArgument, "");
        OPTIONAL(14, double, wmneighbor, "wm", "wmneighbor", "neighborhing ratio", "0.05", InputArgument, "");

        OPTIONAL(15, std::string, output, "out", "output-image", "output image", "", OutputArgument, "Image3D");
        OPTIONAL(16, std::string, mask, "m", "brain-mask", "brain mask (CSF+WM+GM+Lesions)", "/Users/nwiestda/Data/USPIO-6/01011/M0/BrainMaskCon", InputArgument, "Image3D");


        //	FLAG(11, nonlinear, "n", "non-linear", "Perform non linear estimation (if available)", false);
        FLAG(17, help, "h", "help", "Call this help", false);

        CONSTRUCTORS(LSArguments, 17);
};




int main(int argc, char **argv)
{
        QCoreApplication application(argc, argv);
        application.setApplicationName("vistalProcessSegmentationSTREMTesting");
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

        dtkAbstractProcess *process = dynamic_cast <dtkAbstractProcess *>(dtkAbstractProcessFactory::instance()->create("vistalProcessSegmentationSTREM"));
        if (!process) {
                qDebug() << "I am not able to find myself!!! ouiiiiiiiiiiinnnnnnnnnn !!!!!!!!";
                return -1;
        }

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
//        dtkAbstractData *outputImage = process->output();
//        outputImage->enableWriter("vistalDataImageWriter");
//        outputImage->write(arg.getoutput().c_str());
        }




        dtkPluginManager::instance()->uninitialize();


        delete inputImage;
        delete PD;
        delete Third;
        delete mask;


        return DTK_SUCCEED;
}
