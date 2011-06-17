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
	MANDATORY(1,std::string, i1, "", "", "Reference Image (4D volume)", InputArgument, "Image4D");
	OPTIONAL(2, std::string, pars, "p", "parameters", "Parameters for computing the mapping \n\t-flip angles\n\t-multiple TR", "", InputArgument, "");
	
	MANDATORY(3,std::string, output, "", "", "Result", OutputArgument, "Image3D");
	
	ENUM(4, map, "m", "map", "Mapping to perform",
		 (T1)(T1TR)(T2)(MTR), T1);
	
	OPTIONAL(5, std::string, mask, "M", "mask", "Mask for computation", "", InputArgument, "Image3D");
	OPTIONAL(6, std::string, priorT1, "P", "prior-t1", "Prior knowledge for T2 computation (Map of T1)", "", InputArgument, "Image3D");
	OPTIONAL(7, float, TR, "TR", "TR", "TR of acquisition if using prior T1 knowledge", "", InputArgument, "");
	
	OPTIONAL(8, int, skipEcho, "s", "skip", "Skip echoes", 0, InputArgument, "");
	
	FLAG(9, offset, "o", "offset", "Compute with offset correction", false);
	OPTIONAL(10, float, threshold, "t", "threshold", "Apply a threshold at  0 ms, and at specified value (or default if 0, and not used if == -1)", -1, InputArgument, "");
	OPTIONAL(11, std::list<int>, pickedImages, "S", "selected-images", "Select a subset of input images (default none)", "", InputArgument, "");
	
	//	FLAG(11, nonlinear, "n", "non-linear", "Perform non linear estimation (if available)", false);
	FLAG(12, help, "h", "help", "Call this help", false);
	
	CONSTRUCTORS(LSArguments, 11);
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

        dtkAbstractProcess *process = dynamic_cast <dtkAbstractProcess *>(dtkAbstractProcessFactory::instance()->create("vistalProcessSegmentation"));

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
