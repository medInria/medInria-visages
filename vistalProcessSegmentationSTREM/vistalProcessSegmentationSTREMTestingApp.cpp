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
#include "Arguments.hh"


class LSArguments: public GenericArguments
{
//	MANDATORY(1,std::string, i1, "", "", "Reference Image (4D volume)", InputArgument, "Image4D");
	OPTIONAL(1, std::string, t1, "t", "t1-image", "T1 Weighted Image", "", InputArgument, "Image3D");
	OPTIONAL(2, std::string, pd, "pd", "pd-image", "Proton Density Weighted image", "", InputArgument, "Image3D");

	OPTIONAL(3, std::string, t2, "t2", "t2-image", "T2 Weighted image", "", InputArgument, "Image3D");

	OPTIONAL(4, std::string, flair, "flair", "flair-image", "FLAIR image", "", InputArgument, "Image3D");

	ENUM(5, initMethod, "I", "init-method", "Method for initialisation", (StraInit)(HierarchicalPD)(HierarchicalFLAIR), StraInit);
	
	OPTIONAL(6, float, rejectionRatio, "rej", "rejectionRatio", "Robust estimation rejection Ratio", .2, InputArgument, "Image3D");

	ENUM(7, EMAlgorithm, "EM", "EM-Algorithm", "EM Algorithm", (GaussianEM)(GaussianCeleuxREM)(GaussianREM), GaussianREM);
	
	OPTIONAL(8, float, minDistance, "minD", "minDistance", "Minimum distance in EM (stoping criteria)", 1e-4, InputArgument, "");

	OPTIONAL(9, int, emIter, "eit", "emIter", "Iterations of the EM Algorithm", 1e-4, InputArgument, "");
	
	FLAG(10, strem, "st", "Strem", "Start the first iteration with STREM?", false);
	
	//OPTIONAL(11, float, emIter, "eit", "emIter", "Iterations of the EM Algorithm", 10, InputArgument, "");
	
	
	OPTIONAL(11, float, mahalanobisThreshold, "mTh", "mahalanobisThreshold", "Iterations of the EM Algorithm", .4, InputArgument, "");
	OPTIONAL(12, float, rulesThreshold, "rTh", "rulesThreshold", "Iterations of the EM Algorithm", 3., InputArgument, "");
	OPTIONAL(13, float, minsize, "msize", "minsize", "Iterations of the EM Algorithm", 6, InputArgument, "");
	OPTIONAL(14, float, wmneighbor, "wm", "wmneighbor", "Iterations of the EM Algorithm", 0.05, InputArgument, "");

	OPTIONAL(15, std::string, output, "out", "output-image", "output image", "", OutputArgument, "Image3D");


	//	FLAG(11, nonlinear, "n", "non-linear", "Perform non linear estimation (if available)", false);
	FLAG(16, help, "h", "help", "Call this help", false);
	
	CONSTRUCTORS(LSArguments, 16);
};




int main(int argc, char **argv)
{
        QApplication application(argc, argv);
        application.setApplicationName("vistalProcessSegmentationSTREMTesting");
        application.setApplicationVersion("0.0.1");
        application.setOrganizationName("INRIA");
        application.setOrganizationDomain("FR");

	LSArguments arg(argc, (const char**)argv);
	
	if (!arg.parsed) return -1;
	if (arg.gethelp()) { arg.usage(argv[0]); return -2; }
	
	
	
//        if(argc < 4)
//        {
//            qDebug() << "Invalid number of arguments (input / output names are necessary)" << endl;
//            qDebug() << "Mandatory arguments are :\n-input image\n-output image\n-target\n-sink";
//            application.exit(-1);
//        }

        dtkPluginManager::instance()->initialize();


        QString input = "/home/cphilipo/Pictures/masques/t1_float.dim";
        QString output = "/home/cphilipo/Pictures/masques/result.dim";
        QString target = "/home/cphilipo/Pictures/masques/puits_u8.dim";
        QString sink = "/home/cphilipo/Pictures/masques/source_u8.dim";


        dtkAbstractData *inputImage = dynamic_cast <dtkAbstractData *>(dtkAbstractDataFactory::instance()->create("vistalDataImageFloat3"));
        qDebug() << "inputImage->data() = "<< inputImage->data() ;
        inputImage->enableReader("vistalDataImageReader");
        inputImage->read(input);
        qDebug() << "inputImage->data() = "<< inputImage->data() ;

//        dtkAbstractData *outputImage = dynamic_cast <dtkAbstractData *>(dtkAbstractDataFactory::instance()->create("vistalDataImageFloat3"));
//        inputImage->enableWriter("vistalDataImageWriter");
//        inputImage->read(argv[2]);

        dtkAbstractData *targetImage = dynamic_cast <dtkAbstractData *>(dtkAbstractDataFactory::instance()->create("vistalDataImageUChar3"));
        targetImage->enableReader("vistalDataImageReader");
        targetImage->read(target);

        dtkAbstractData *sinkImage = dynamic_cast <dtkAbstractData *>(dtkAbstractDataFactory::instance()->create("vistalDataImageUChar3"));
        sinkImage->enableReader("vistalDataImageReader");
        sinkImage->read(sink);

        dtkAbstractProcess *process = dynamic_cast <dtkAbstractProcess *>(dtkAbstractProcessFactory::instance()->create("vistalProcessSegmentationSTREM"));

        process->setInput(inputImage,0); // input image

        process->setInput(targetImage,1); // target

        process->setInput(sinkImage,2); // sink

        process->update();

        dtkAbstractData *outputImage = process->output();
        outputImage->enableWriter("vistalDataImageWriter");

        outputImage->write(output);

        dtkPluginManager::instance()->uninitialize();

        return DTK_SUCCEED;
}
