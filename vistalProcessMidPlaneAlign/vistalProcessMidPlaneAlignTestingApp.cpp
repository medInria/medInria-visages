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


class LSArguments: public GenericArguments
{
    MANDATORY(1,std::string, input, "", "", "Image to Realign", InputArgument, "Image3D");
    MANDATORY(2,std::string, res, "", "", "Realigned Image", OutputArgument, "Image3D");

    OPTIONAL(3, int, maxFun, "m", "maxfun", "Maximum number of similarity function call", 500, InputArgument, "");
    OPTIONAL(4, float, rhobeg, "R", "rho-beg", "Initial Search Radius", 5, InputArgument, "");
    OPTIONAL(5, float, rhoend, "r", "rho-end", "Final radius", 1e-3, InputArgument, "");

    FLAG(6, help, "h", "help", "Call this help", false);

    CONSTRUCTORS(LSArguments, 6);
};




int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    application.setApplicationName("vistalProcessMidPlaneRealignTesting");
    application.setApplicationVersion("0.0.1");
    application.setOrganizationName("INRIA");
    application.setOrganizationDomain("FR");

    LSArguments arg(argc, (const char**)argv);

    if (!arg.parsed) return -1;
    if (arg.gethelp()) { arg.usage(argv[0]); return -2; }



    dtkPluginManager::instance()->initialize();


    vistal::Image3D<float> *input = new 	vistal::Image3D<float>;
    loadImage(arg.getinput(), *input, 0);

    dtkAbstractData *inputImage = dynamic_cast <dtkAbstractData *>(dtkAbstractDataFactory::instance()->create("vistalDataImageFloat3"));
    inputImage->setData(input);


    dtkAbstractProcess *process = dynamic_cast <dtkAbstractProcess *>(dtkAbstractProcessFactory::instance()->create("vistalProcessMidPlaneAlign"));
    if (!process) {
        qDebug() << "I am not able to find myself!!! ouiiiiiiiiiiinnnnnnnnnn !!!!!!!!";
        return -1;
    }


    process->setParameter((double)arg.getmaxFun(), 0);
    process->setParameter((double)arg.getrhobeg(), 1);
    process->setParameter((double)arg.getrhoend(), 2);

    process->setInput(inputImage);


    process->update();

    if (!process->output())
    {
        qDebug() << "Warning output not available";

    }
    else {

        vistal::Image3D<float>* ima = dynamic_cast<vistal::Image3D<float>* >((vistal::Image3D<float>* )process->output()->data());
        vistal::gis::saveVolume(arg.getres().c_str(), *ima, 0);
    }




    dtkPluginManager::instance()->uninitialize();


    delete inputImage;



    return DTK_SUCCEED;
}
