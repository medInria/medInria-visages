#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkPluginManager.h>

#include <QtCore>
#include <QtGui>
#include <QtDebug>

int main(int argc, char **argv)
{
        QApplication application(argc, argv);
        application.setApplicationName("vistalProcessSegmentationTesting");
        application.setApplicationVersion("0.0.1");
        application.setOrganizationName("INRIA");
        application.setOrganizationDomain("FR");

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
