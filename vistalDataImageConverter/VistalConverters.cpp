
#include "itkImage3D.hh"
#include "Image3D.hh"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include "VistalConverters.hh"
//casting and intensity mapping
#include "itkCastImageFilter.h"


namespace vistal
{
	namespace medinria	
	{		
		
		// MACRO to convert from vistal image with type TypeIn to itk image of type TypeOut
		// this does just copy data to the desired type (hence the "Copy" in name)
		
#define TryVistalConvertDetailsCopy(suffix, TypeIn, suffixOut, TypeOut) \
if (typeOut == ""#suffixOut && typeIn == "vistalDataImage"#suffix ) \
{ \
vistal::Image3D<TypeIn>* image = dynamic_cast<vistal::Image3D<TypeIn>*>( (vistal::Image3D<TypeIn>*)imageIn->data() ); \
if (!image) return; \
vistal::Image3D<TypeOut> conv;\
vistal::converters::Parameters parameters; /* conversion parameters */ \
parameters.copy = true; \
vistal::converters::ConvertImages(*image, conv, parameters); \
itkImage3D<TypeOut> vistalConverter(conv); \
imageOut = dtkAbstractDataFactory::instance()->create("itkDataImage"#suffixOut); \
if (imageOut) imageOut->setData(vistalConverter.GetOutput()); \
return; \
} 

		/*
		 itkImage3D<TypeOut>::imT* itp;\
		 typedef  itk::CastImageFilter<itkImage3D<TypeOut>::imT, itkImage3D<TypeOut>::imT>  NullFilterType; \
		 NullFilterType::Pointer myNullFilter = NullFilterType::New(); \
		 myNullFilter->SetInput(vistalConverter.GetOutput());\
		 myNullFilter->Update();\
		 itp = myNullFilter->GetOutput();\
		 if (imageOut) imageOut->setData(itp); \
*/		 
		
		// MACRO to convert from vistal image with type TypeIn to itk image of type TypeOut
#define TryVistalConvertDetails(suffix, TypeIn, suffixOut, TypeOut) \
if (typeOut == ""#suffixOut && typeIn == "vistalDataImage"#suffix ) \
{ \
vistal::Image3D<TypeIn>* image = dynamic_cast<vistal::Image3D<TypeIn>*>( (vistal::Image3D<TypeIn>*)imageIn->data() ); \
if (!image) return; \
vistal::Image3D<TypeOut> conv;\
vistal::converters::Parameters parameters; /* conversion parameters */ \
vistal::converters::ConvertImages(*image, conv, parameters); \
itkImage3D<TypeOut> vistalConverter(conv); \
imageOut = dtkAbstractDataFactory::instance()->create("itkDataImage"#suffixOut); \
if (imageOut) imageOut->setData(vistalConverter.GetOutput()); \
return; \
} 
		
		
// MACRO to dispatch conversion from suffix type to any scalar type (vistal to ITK conversion)
#define TryVistalConvert(suffix, TypeIn)\
if (typeIn == "vistalDataImage"#suffix)\
{\
TryVistalConvertDetails(suffix, TypeIn, Char3, char);\
TryVistalConvertDetails(suffix, TypeIn, UChar3, unsigned char);\
\
TryVistalConvertDetails(suffix, TypeIn, Short3, short);\
TryVistalConvertDetails(suffix, TypeIn, UShort3, unsigned short);\
\
TryVistalConvertDetails(suffix, TypeIn, Int3, int);\
TryVistalConvertDetails(suffix, TypeIn, UInt3, unsigned);\
\
TryVistalConvertDetails(suffix, TypeIn, Float3, float);\
TryVistalConvertDetails(suffix, TypeIn, Double3, double);\
}		
		
		
		 void convertToItk(QString typeIn, QString typeOut, dtkAbstractData* imageIn, dtkAbstractData*& imageOut)
		{
			//qDebug() << "Converting from" << typeIn << "to" << typeOut;
			
			// Bunch of function to distribute over types going from short type to larger one,
			// Avoiding the rescaling of input to the output, does just a copy of data in the new type
			
			
			TryVistalConvertDetailsCopy(Char3, char, Short3, short);
			TryVistalConvertDetailsCopy(Char3, char, Int3, int);
			TryVistalConvertDetailsCopy(Char3, char, Float3, float);
			TryVistalConvertDetailsCopy(Char3, char, Double3, double);

			TryVistalConvertDetailsCopy(Short3, short, Int3, int);
			TryVistalConvertDetailsCopy(Short3, short, Float3 , float);
			TryVistalConvertDetailsCopy(Short3, short, Double3, double);
			
			TryVistalConvertDetailsCopy(Int3, int, Float3, float);
			TryVistalConvertDetailsCopy(Int3, int, Double3, double);
			
			TryVistalConvertDetailsCopy(Float3, float, Float3, float);
			TryVistalConvertDetailsCopy(Float3, float, Double3, double);
			
			TryVistalConvertDetailsCopy(UChar3,unsigned char, Short3, short);
			TryVistalConvertDetailsCopy(UChar3, unsigned char, UShort3, unsigned short);
			
			TryVistalConvertDetailsCopy(UChar3,unsigned char, Int3, int);
			TryVistalConvertDetailsCopy(UChar3,unsigned char, UInt3, unsigned int);

			TryVistalConvertDetailsCopy(UChar3,unsigned char, Float3, float);
			TryVistalConvertDetailsCopy(UChar3,unsigned char, Double3, double);
			
			TryVistalConvertDetailsCopy(UShort3,unsigned short, Int3, int);
			TryVistalConvertDetailsCopy(UShort3,unsigned short, UInt3,unsigned int);
			TryVistalConvertDetailsCopy(UShort3,unsigned short, Float3, float);
			TryVistalConvertDetailsCopy(UShort3,unsigned short, Double3, double);
			
			TryVistalConvertDetailsCopy(UInt3, unsigned, Float3, float);
			TryVistalConvertDetailsCopy(UInt3, unsigned, Double3, double);										
						
			// Use dispatcher to any type, this generate all the conversion (code with scaling)
	
			TryVistalConvert(Char3, char);			
			TryVistalConvert(UChar3, unsigned char);
			
			TryVistalConvert(Short3, short);
			TryVistalConvert(UShort3, unsigned short);			
			
			TryVistalConvert(Int3, int);
			TryVistalConvert(UInt3, unsigned);
			
			TryVistalConvert(Float3, float);
			
			TryVistalConvert(Double3, double);
			
			
		}
		
		
		
		
		
		
#define TryVistalConvertFromITKDetailsCopy(suffix, TypeIn, suffixOut, TypeOut) \
if (typeOut == ""#suffixOut &&typeIn == "itkDataImage"#suffix) \
{ \
itk::Image<TypeIn, 3>::Pointer image = dynamic_cast<itk::Image<TypeIn, 3> *>( (itk::Image<TypeIn, 3> *)imageIn->data() );\
if (!image) return; \
itkImage3D<TypeIn> vistalConverter(image); \
vistal::Image3D<TypeIn> conv = vistalConverter.GetImage3D(); \
vistal::converters::Parameters parameters; /* conversion parameters */ \
parameters.copy = true; \
vistal::Image3D<TypeOut>* res = new vistal::Image3D<TypeOut>(conv, 0); \
vistal::converters::ConvertImages(conv, *res, parameters); \
if (res) imageOut = dtkAbstractDataFactory::instance()->create("vistalDataImage"#suffixOut); \
if (imageOut) imageOut->setData(res); \
return; \
} 
		
		
		
		
#define TryVistalConvertFromITKDetails(suffix, TypeIn, suffixOut, TypeOut) \
if (typeOut == ""#suffixOut &&typeIn == "itkDataImage"#suffix) \
{ \
	itk::Image<TypeIn, 3>::Pointer image = dynamic_cast<itk::Image<TypeIn, 3> *>((itk::Image<TypeIn, 3> *) imageIn->data() );\
	if (!image) return; \
	itkImage3D<TypeIn>  vistalConverter(image); \
	vistal::Image3D<TypeIn> conv = vistalConverter.GetImage3D(); \
	vistal::converters::Parameters parameters; /* conversion parameters */ \
	vistal::Image3D<TypeOut>* res = new vistal::Image3D<TypeOut>(conv, 0); \
	vistal::converters::ConvertImages(conv, *res, parameters); \
	if (res) imageOut = dtkAbstractDataFactory::instance()->create("vistalDataImage"#suffixOut); \
	if (imageOut) imageOut->setData(res); \
	return; \
} 
		
		
		
#define TryVistalConvertFromITK(suffix, TypeIn)\
if (typeIn == "itkDataImage"#suffix)\
{\
TryVistalConvertFromITKDetails(suffix, TypeIn, Char3, char);\
TryVistalConvertFromITKDetails(suffix, TypeIn, UChar3, unsigned char);\
\
TryVistalConvertFromITKDetails(suffix, TypeIn, Short3, short);\
TryVistalConvertFromITKDetails(suffix, TypeIn, UShort3, unsigned short);\
\
TryVistalConvertFromITKDetails(suffix, TypeIn, Int3, int);\
TryVistalConvertFromITKDetails(suffix, TypeIn, UInt3, unsigned);\
\
TryVistalConvertFromITKDetails(suffix, TypeIn, Float3, float);\
TryVistalConvertFromITKDetails(suffix, TypeIn, Double3, double);\
}		
		
		
		// 		
		void convertFromItk(QString typeIn, QString typeOut, dtkAbstractData* imageIn, dtkAbstractData*& imageOut)
		{
			// Bunch of function to distribute over types going from short type to larger one,
			// Avoiding the rescaling of input to the output, does just a copy of data in the new type

			TryVistalConvertFromITKDetailsCopy(Char3, char, Short3, short);
			TryVistalConvertFromITKDetailsCopy(Char3, char, Int3, int);
			TryVistalConvertFromITKDetailsCopy(Char3, char, Float3, float);
			TryVistalConvertFromITKDetailsCopy(Char3, char, Double3, double);
			
			TryVistalConvertFromITKDetailsCopy(Short3, short, Int3, int);
			TryVistalConvertFromITKDetailsCopy(Short3, short, Float3, float);
			TryVistalConvertFromITKDetailsCopy(Short3, short, Double3, double);
			
			TryVistalConvertFromITKDetailsCopy(Int3, int, Float3, float);
			TryVistalConvertFromITKDetailsCopy(Int3, int, Double3, double);
			
			TryVistalConvertFromITKDetailsCopy(Float3, float, Float3, float);			
			TryVistalConvertFromITKDetailsCopy(Float3, float, Double3, double);
			
			TryVistalConvertFromITKDetailsCopy(UChar3,unsigned char, Short3, short);
			TryVistalConvertFromITKDetailsCopy(UChar3, unsigned char, UShort3, unsigned short);
			
			TryVistalConvertFromITKDetailsCopy(UChar3,unsigned char, Int3, int);
			TryVistalConvertFromITKDetailsCopy(UChar3,unsigned char, UInt3, unsigned int);
			
			TryVistalConvertFromITKDetailsCopy(UChar3,unsigned char, Float3, float);
			TryVistalConvertFromITKDetailsCopy(UChar3,unsigned char, Double3, double);
			
			TryVistalConvertFromITKDetailsCopy(UShort3,unsigned short, Int3, int);
			TryVistalConvertFromITKDetailsCopy(UShort3,unsigned short, UInt3,unsigned int);
			TryVistalConvertFromITKDetailsCopy(UShort3,unsigned short, Float3, float);
			TryVistalConvertFromITKDetailsCopy(UShort3,unsigned short, Double3, double);
			
			TryVistalConvertFromITKDetailsCopy(UInt3, unsigned, Float3, float);
			TryVistalConvertFromITKDetailsCopy(UInt3, unsigned, Double3, double);										
			
				// Use dispatcher to any type, this generate all the conversion (code with scaling)
			
			
			TryVistalConvertFromITK(Char3, char);			
			TryVistalConvertFromITK(UChar3, unsigned char);
			
			TryVistalConvertFromITK(Short3, short);
			TryVistalConvertFromITK(UShort3, unsigned short);			
			
			TryVistalConvertFromITK(Int3, int);
			TryVistalConvertFromITK(UInt3, unsigned);
			
			TryVistalConvertFromITK(Float3, float);
			
			TryVistalConvertFromITK(Double3, double);
			
			
			
		}
		
		
		
#define TryVistalVistalConvertDetailsCopy(suffix, TypeIn, suffixOut, TypeOut) \
if (typeOut == ""#suffixOut &&typeIn == "vistalDataImage"#suffix ) \
{ \
vistal::Image3D<TypeIn>* image = dynamic_cast<vistal::Image3D<TypeIn>*>( (vistal::Image3D<TypeIn>*)imageIn->data() ); \
if (!image) return; \
vistal::Image3D<TypeOut>* res = new vistal::Image3D<TypeOut>(*image, 0); \
if (!res) return; \
vistal::converters::Parameters parameters; /* conversion parameters */ \
parameters.copy = true; \
vistal::converters::ConvertImages(*image, *res, parameters); \
if (res) imageOut = dtkAbstractDataFactory::instance()->create("vistalDataImage"#suffixOut); \
if (imageOut) imageOut->setData(res); \
return; \
} 		
		
		
		
#define TryVistalVistalConvertDetails(suffix, TypeIn, suffixOut, TypeOut) \
if (typeOut == ""#suffixOut&&typeIn == "vistalDataImage"#suffix ) \
{ \
vistal::Image3D<TypeIn>* image = dynamic_cast<vistal::Image3D<TypeIn>*>( (vistal::Image3D<TypeIn>*)imageIn->data() ); \
if (!image) return; \
vistal::Image3D<TypeOut>* res = new vistal::Image3D<TypeOut>(*image, 0); \
if (!res) return; \
vistal::converters::Parameters parameters; /* conversion parameters */ \
vistal::converters::ConvertImages(*image, *res, parameters); \
if (res) imageOut = dtkAbstractDataFactory::instance()->create("vistalDataImage"#suffixOut); \
if (imageOut) imageOut->setData(res); \
return; \
} 
		
		
		
#define TryVistalVistalConvert(suffix, TypeIn) \
if (typeIn == "vistalDataImage"#suffix)\
{ \
TryVistalVistalConvertDetails(suffix, TypeIn, Char3, char);\
TryVistalVistalConvertDetails(suffix, TypeIn, UChar3, unsigned char);\
\
TryVistalVistalConvertDetails(suffix, TypeIn, Short3, short);\
TryVistalVistalConvertDetails(suffix, TypeIn, UShort3, unsigned short);\
\
TryVistalVistalConvertDetails(suffix, TypeIn, Int3, int);\
TryVistalVistalConvertDetails(suffix, TypeIn, UInt3, unsigned);\
\
TryVistalVistalConvertDetails(suffix, TypeIn, Float3, float);\
TryVistalVistalConvertDetails(suffix, TypeIn, Double3, double);\
}		
		
		// Simple vistal converter
		void convert(QString typeIn, QString typeOut, dtkAbstractData* imageIn, dtkAbstractData*& imageOut)
		{
			//qDebug() << "Vistal Converter " << typeIn << " to " << typeOut;
			// Bunch of function to distribute over types going from short type to larger one,
			// Avoiding the rescaling of input to the output, does just a copy of data in the new type

			TryVistalVistalConvertDetailsCopy(Char3, char, Short3, short);
			TryVistalVistalConvertDetailsCopy(Char3, char, Int3, int);
			TryVistalVistalConvertDetailsCopy(Char3, char, Float3, float);
			TryVistalVistalConvertDetailsCopy(Char3, char, Double3, double);
			
			TryVistalVistalConvertDetailsCopy(Short3, short, Int3, int);
			TryVistalVistalConvertDetailsCopy(Short3, short, Float3, float);
			TryVistalVistalConvertDetailsCopy(Short3, short, Double3, double);
			
			TryVistalVistalConvertDetailsCopy(Int3, int, Float3, float);
			TryVistalVistalConvertDetailsCopy(Int3, int, Double3, double);
			
			TryVistalVistalConvertDetailsCopy(Float3, float, Float3, float);
			TryVistalVistalConvertDetailsCopy(Float3, float, Double3, double);
			
			TryVistalVistalConvertDetailsCopy(UChar3,unsigned char, Short3, short);
			TryVistalVistalConvertDetailsCopy(UChar3, unsigned char, UShort3, unsigned short);
			
			TryVistalVistalConvertDetailsCopy(UChar3,unsigned char, Int3, int);
			TryVistalVistalConvertDetailsCopy(UChar3,unsigned char, UInt3, unsigned int);
			
			TryVistalVistalConvertDetailsCopy(UChar3,unsigned char, Float3, float);
			TryVistalVistalConvertDetailsCopy(UChar3,unsigned char, Double3, double);
			
			TryVistalVistalConvertDetailsCopy(UShort3,unsigned short, Int3, int);
			TryVistalVistalConvertDetailsCopy(UShort3,unsigned short, UInt3,unsigned int);
			TryVistalVistalConvertDetailsCopy(UShort3,unsigned short, Float3, float);
			TryVistalVistalConvertDetailsCopy(UShort3,unsigned short, Double3, double);
			
			TryVistalVistalConvertDetailsCopy(UInt3, unsigned, Float3, float);
			TryVistalVistalConvertDetailsCopy(UInt3, unsigned, Double3, double);																			
			
				// Use dispatcher to any type, this generate all the conversion (code with scaling)
			
			TryVistalVistalConvert(Char3, char);			
			TryVistalVistalConvert(UChar3, unsigned char);
			
			TryVistalVistalConvert(Short3, short);
			TryVistalVistalConvert(UShort3, unsigned short);			
			
			TryVistalVistalConvert(Int3, int);
			TryVistalVistalConvert(UInt3, unsigned);
			
			TryVistalVistalConvert(Float3, float);
			
			TryVistalVistalConvert(Double3, double);									
			
		}
		
		
		
		
	}
}

