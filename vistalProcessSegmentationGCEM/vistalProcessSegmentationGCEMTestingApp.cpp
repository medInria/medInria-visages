
#include <dtkCore/dtkAbstractData.h>

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractDataReader.h>
#include <dtkCore/dtkAbstractDataWriter.h>

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
        OPTIONAL(1, std::string, t1, "t", "t1-image", "T1 Weighted Image", "/Users/nwiestda/Data/USPIO-6/01011/M0/unbias_3DMPRAGEs005a001.nii.gz", InputArgument, "Image3D");
        OPTIONAL(2, std::string, pd, "pd", "pd-image", "Proton Density Weighted image", "/Users/nwiestda/Data/USPIO-6/01011/M0/DP_3D.nii.gz", InputArgument, "Image3D");

        OPTIONAL(3, std::string, t2, "t2", "t2-image", "T2 Weighted image", "", InputArgument, "Image3D");

        OPTIONAL(4, std::string, flair, "flair", "flair-image", "FLAIR image", "/Users/nwiestda/Data/USPIO-6/01011/M0/unbias_3DFLAIRs007a001.nii.gz", InputArgument, "Image3D");

        ENUM(5, initMethod, "I", "init-method", "Method for initialisation", (StraInit)(HierarchicalPD)(HierarchicalFLAIR), StraInit);

        OPTIONAL(6, float, rejectionRatio, "rej", "rejectionRatio", "Robust estimation rejection Ratio", .2, InputArgument, "Image3D");

        ENUM(7, EMAlgorithm, "EM", "EM-Algorithm", "EM Algorithm", (GaussianEM)(GaussianCeleuxREM)(GaussianREM), GaussianREM);

        OPTIONAL(8, float, minDistance, "minD", "minDistance", "Minimum distance in EM (stoping criteria)", 1e-4, InputArgument, "");

        OPTIONAL(9, int, emIter, "eit", "emIter", "Iterations of the EM Algorithm", 1e-4, InputArgument, "");

        FLAG(10, strem, "st", "Strem", "Start the first iteration with GCEM?", false);

        //OPTIONAL(11, float, emIter, "eit", "emIter", "Iterations of the EM Algorithm", 10, InputArgument, "");


        OPTIONAL(11, float, mahalanobisThreshold, "mTh", "mahalanobisThreshold", "Iterations of the EM Algorithm", .4, InputArgument, "");
        OPTIONAL(12, float, rulesThreshold, "rTh", "rulesThreshold", "Iterations of the EM Algorithm", 3., InputArgument, "");
        OPTIONAL(13, float, minsize, "msize", "minsize", "Iterations of the EM Algorithm", 6, InputArgument, "");
        OPTIONAL(14, float, wmneighbor, "wm", "wmneighbor", "Iterations of the EM Algorithm", 0.05, InputArgument, "");

        OPTIONAL(15, std::string, output, "out", "output-image", "output image", "/tmp/GCEM.nii.gz", OutputArgument, "Image3D");
        OPTIONAL(16, std::string, mask, "m", "brain-mask", "brain mask (CSF+WM+GM+Lesions)", "/Users/nwiestda/Data/USPIO-6/01011/M0/BrainMaskCon.nii.gz", InputArgument, "Image3D");

        OPTIONAL(17, float, rulesMin, "rmin", "rulesMin", " Rules Min Threshold (in SD times)", 2, InputArgument, "Image3D");
        OPTIONAL(18, float, rulesMax, "rmax", "rulesMax", " Rules Max Threshold (in SD times)", 3, InputArgument, "Image3D");
        OPTIONAL(19, float, alphap, "al", "Alpha", "Mixing energy parameter", 10, InputArgument, "Image3D");


        //	FLAG(11, nonlinear, "n", "non-linear", "Perform non linear estimation (if available)", false);
        FLAG(20, help, "h", "help", "Call this help", false);

        CONSTRUCTORS(LSArguments, 20);
};



dtkAbstractDataReader* getSuitableReader( QString filename )
{
    QList<QString> readers = dtkAbstractDataFactory::instance()->readers();

    // cycle through readers to see if the last used reader can handle the file
    for (int i=0; i<readers.size(); i++) {
        dtkAbstractDataReader* dataReader = dtkAbstractDataFactory::instance()->reader(readers[i]);
//        qDebug() << dataReader->description();
        if (dataReader->canRead( filename ))
            return dataReader;
        else
            delete dataReader;
    }

    qWarning() << "No suitable reader found!";
    return NULL;
}

dtkAbstractDataWriter* getSuitableWriter( QString filename, dtkAbstractData* dtkdata )
{
    if (!dtkdata)
        return NULL;

    QList<QString> writers = dtkAbstractDataFactory::instance()->writers();

    for (int i=0; i<writers.size(); i++) {
        dtkAbstractDataWriter *dataWriter = dtkAbstractDataFactory::instance()->writer(writers[i]);

        if ( dataWriter->handled().contains(dtkdata->description()) &&
             dataWriter->canWrite( filename ) ) {
            return dataWriter;
        }
        else
            delete dataWriter;
    }

    return NULL;
}



dtkAbstractData* load(QString t1)
{
    dtkAbstractData *inputImage;
    dtkAbstractDataReader* dataReader = getSuitableReader(t1);
    if (dataReader){
        dataReader->readInformation( t1 );
        inputImage = dataReader->data();
        delete dataReader;
    }
    else {
        qWarning() << "No suitable reader found for file: " << t1 << " unable to import!";
        exit(-1);
    }

    if (!inputImage) {
        qWarning() << "Reader was unable to read: " << t1;
        exit(-1);
    }
    return inputImage;
}

void Write(QString file, dtkAbstractData* imData)
{
    dtkAbstractDataWriter *dataWriter = getSuitableWriter(file, imData);
    if( dataWriter) {
        dataWriter->setData (imData);
        if (!dataWriter->write( file))
            qDebug() << "Could not save data file: " + file;

        delete dataWriter;
    }

}




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

          dtkAbstractData *inputImage = load(arg.gett1().c_str());
          dtkAbstractData *PD = load(arg.getpd().c_str());


          dtkAbstractData *Third =0;
          if (t2 == "" && flair != "")
              Third = load(flair);
          else
              Third = load(t2);

          dtkAbstractData *mask = load(arg.getmask().c_str());

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
               Write(arg.getoutput().c_str(), process->output());
           }



        dtkPluginManager::instance()->uninitialize();

        return DTK_SUCCEED;
}
