#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkPluginManager.h>

#include <QtCore>
#include <QtGui>
#include <QtDebug>



#include <Arguments.hh>


#include <Image3D.hh>
#include "loadImg.hh"

struct CLArguments: public GenericArguments
{
        // Positional arguments, inputfile
        MANDATORY(1,std::string, inputfile, "", "", "input GIS file", InputArgument, "Image3D");


        MANDATORY(2, std::string, result, "", "", "result", OutputArgument, "Image3D<float>");

        OPTIONAL(3, float, cutoff, "c", "cutoff", "Cut off frequency of the DCT Basis",  "30", InputArgument, "");
        OPTIONAL(4, int , bins, "b", "bins", "Size of the bin", "1024", InputArgument, "");
        OPTIONAL(5, float , reg, "r", "regularization", "regularization parameter", "1e-3", InputArgument, "");

        //  OPTIONAL(3, float , threshold, "t", "threshold", "Threshold for masking", -1,InputArgument, "");
        OPTIONAL(6, std::string , mask, "m", "mask", "Object's mask","",InputArgument, "");
        ENUM(7, basistype, "T", "type", "Type of the employed basis", (DiscretCosines)(LegendrePolynomials)(HermitePolynomials), DiscretCosines);

        FLAG(8, bias, "B", "bias", "Save the bias field (result name + _bias)", false);
        FLAG(9, random, "R", "random", "Add Random seed to the data (mimic the real spm tool)", true);
        FLAG(10, skip0, "s", "skip0", "skip the 0 value from the image", false);


        OPTIONAL(11, float , threshold, "t", "threshold", "Threshold for skiping background", "0", InputArgument, "");

        OPTIONAL(12, int , iter, "it", "iterations", "max number of iteration", "128", InputArgument, "");
        OPTIONAL(13, float , lowest, "l", "low", "Optimisation threshold", "1e-5", InputArgument, "");

        FLAG(14, help, "h", "help", "Call this help", false);

        CONSTRUCTORS(CLArguments, 14);
};



int main(int argc,  char **argv)
{
        QApplication application(argc, argv);
        application.setApplicationName("vistalProcessBiasRemovalTesting");
        application.setApplicationVersion("0.0.1");
        application.setOrganizationName("INRIA");
        application.setOrganizationDomain("FR");

        dtkPluginManager::instance()->initialize();

        CLArguments args(argc, (const char**)argv); // We are sure we've got our mandatory arguments

        if (!args.parsed) return 1;
        if (args.gethelp()) { args.usage(argv[0]); exit(0); }


        vistal::Image3D<float> image;
        loadImage(args.getinputfile().c_str(), image, 0);

        dtkAbstractData*  input = dtkAbstractDataFactory::instance()->create("vistalDataImageFloat3");
        input->setData(&image);

        dtkAbstractProcess *worker = dynamic_cast <dtkAbstractProcess *>(dtkAbstractProcessFactory::instance()->create("vistalProcessBiasRemoval"));

        if (!worker)
        {
                std::cerr << "Instance creation error" << std::endl;
                abort();
        }

        worker->setInput(input);

        worker->setParameter((double)args.getcutoff(), 0);
        worker->setParameter((double)args.getbins()  , 1);
        worker->setParameter((double)args.getreg()   , 2);
        worker->setParameter((double)args.getbasistype()  , 3);
        worker->setParameter((double)args.getrandom(), 4);
        worker->setParameter((double)args.getskip0() , 5);
        worker->setParameter((double)args.getthreshold(), 6);
        worker->setParameter((double)args.getiter(), 7);
        worker->setParameter((double)args.getlowest(), 8);
        worker->setParameter((double)args.getbias(), 9);

        int r = worker->run();

        input = worker->output();

        if (r != 0)
        {
                std::cerr << "Instance execution error" << std::endl;
                abort();
        }

        if (input)
                vistal::gis::saveVolume(args.getresult().c_str(), *(vistal::Image3D<float>*)input->data(), 0);


        dtkPluginManager::instance()->uninitialize();

        return DTK_SUCCEED;
}
