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


template <class D1, class D2>
bool compareCast(vistal::Image3D<D1>& im1, vistal::Image3D<D2>& im2)
{
    // Image should be cast comparable
    typename vistal::Image3D<D1>::iterator it1 = im1.begin();
    typename vistal::Image3D<D2>::iterator it2 = im2.begin();


    for (; it1 != im1.end(); ++it1, ++it2)
        if ((D2)*it1 != *it2) return false;

    return true;
}


#define CAST_COMPARE(FromType, ToType, FromStr, ToStr)\
{ vistal::Image3D<FromType> *im1 = new 	vistal::Image3D<FromType>(8, 8, 4, 0);\
    qDebug() << "Testing conversion from " # FromType << "to " # ToType;\
    FromType val = 0;\
for (vistal::Image3D<FromType>::iterator it = im1->begin(); it != im1->end(); ++it)\
    *it = val++;\
dtkAbstractData *inputImage = dynamic_cast <dtkAbstractData *>(dtkAbstractDataFactory::instance()->create("vistalDataImage"#FromStr));\
inputImage->setData(im1);\
dtkAbstractData *converted = inputImage->convert("vistalDataImage"#ToStr);\
if (!converted)\
{\
    qDebug() << "Conversion failed";\
    return DTK_FAILURE;\
}\
if (!compareCast(*im1, *((vistal::Image3D<ToType>*)converted->data())))        {\
    qDebug() << "Comparison failed";\
    return DTK_FAILURE;\
}\
}

int main(int argc, char **argv)
{
        QApplication application(argc, argv);
        application.setApplicationName("vistalProcessSegmentationGCEMTesting");
        application.setApplicationVersion("0.0.1");
        application.setOrganizationName("INRIA");
        application.setOrganizationDomain("FR");

        dtkPluginManager::instance()->initialize();

        // Build an image
        CAST_COMPARE(unsigned char, unsigned char, UChar3, UChar3);

        CAST_COMPARE(unsigned char, short, UChar3, Short3);
        CAST_COMPARE(unsigned char, unsigned short, UChar3, UShort3);

        CAST_COMPARE(unsigned char, int, UChar3, Int3);
        CAST_COMPARE(unsigned char, unsigned int, UChar3, UInt3);

        CAST_COMPARE(unsigned char, float, UChar3, Float3);
        CAST_COMPARE(unsigned char, double, UChar3, Double3);

        CAST_COMPARE(unsigned short, unsigned short, UShort3, UShort3);

        CAST_COMPARE(unsigned short, int, UShort3, Int3);
        CAST_COMPARE(unsigned short, unsigned int, UShort3, UInt3);

        CAST_COMPARE(unsigned short, float, UShort3, Float3);
        CAST_COMPARE(unsigned short, double, UShort3, Double3);

        CAST_COMPARE(unsigned int, unsigned int, UInt3, UInt3);

        CAST_COMPARE(unsigned int, float, UInt3, Float3);
        CAST_COMPARE(unsigned int, double, UInt3, Double3);
        //




        qDebug() << "Testing finished, everything is fine then";
        return DTK_SUCCEED;
}
