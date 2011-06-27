
#include "itkImage3D.hh"
#include "Image3D.hh"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include "VistalConverters.hh"


namespace vistal
{
	namespace medinria	
	{		
		
#define TryVistalConvertDetailsCopy(suffix, TypeIn, suffixOut, TypeOut) \
if (typeOut == ""#suffixOut ) \
{ \
vistal::Image3D<TypeIn>* image = static_cast<vistal::Image3D<TypeIn>*>( imageIn->data() ); \
if (!image) return; \
vistal::Image3D<TypeOut> conv;\
vistal::converters::Parameters parameters; /* conversion parameters */ \
parameters.copy = true; \
vistal::converters::ConvertImages(*image, conv, parameters); \
itkImage3D<TypeOut> * vistalConverter = new itkImage3D<TypeOut> (conv); \
if (vistalConverter) imageOut = dtkAbstractDataFactory::instance()->create("itkDataImage"#suffixOut); \
if (imageOut) imageOut->setData(vistalConverter->GetOutput()); \
return; \
} 
		
#define TryVistalConvertDetails(suffix, TypeIn, suffixOut, TypeOut) \
if (typeOut == ""#suffixOut ) \
{ \
vistal::Image3D<TypeIn>* image = static_cast<vistal::Image3D<TypeIn>*>( imageIn->data() ); \
if (!image) return; \
vistal::Image3D<TypeOut> conv;\
vistal::converters::Parameters parameters; /* conversion parameters */ \
vistal::converters::ConvertImages(*image, conv, parameters); \
itkImage3D<TypeOut> * vistalConverter = new itkImage3D<TypeOut> (conv); \
if (vistalConverter) imageOut = dtkAbstractDataFactory::instance()->create("itkDataImage"#suffixOut); \
if (imageOut) imageOut->setData(vistalConverter->GetOutput()); \
return; \
} 
		
#define TryVistalConvert(suffix, TypeIn)\
if (typeIn == "vistalDataImage"#suffix)\
{\
TryVistalConvertDetails(suffix, TypeIn, "Char3", char);\
TryVistalConvertDetails(suffix, TypeIn, "UChar3", unsigned char);\
\
TryVistalConvertDetails(suffix, TypeIn, "Short3", short);\
TryVistalConvertDetails(suffix, TypeIn, "UShort3", unsigned short);\
\
TryVistalConvertDetails(suffix, TypeIn, "Int3", int);\
TryVistalConvertDetails(suffix, TypeIn, "UInt3", unsigned);\
\
TryVistalConvertDetails(suffix, TypeIn, "Float3", float);\
TryVistalConvertDetails(suffix, TypeIn, "Double3", double);\
}		
		
		
		 void convertToItk(QString typeIn, QString typeOut, dtkAbstractData* imageIn, dtkAbstractData* imageOut)
		{
			
			// if output type can handle larger datatype compared to output set parameters to copy
			
			TryVistalConvertDetailsCopy("Char3", char, "Short3", short);
			TryVistalConvertDetailsCopy("Char3", char, "Int3", int);
			TryVistalConvertDetailsCopy("Char3", char, "Float3", float);
			TryVistalConvertDetailsCopy("Char3", char, "Double3", double);

			TryVistalConvertDetailsCopy("Short3", short, "Int3", int);
			TryVistalConvertDetailsCopy("Short3", short, "Float3", float);
			TryVistalConvertDetailsCopy("Short3", short, "Double3", double);
			
			TryVistalConvertDetailsCopy("Int3", int, "Float3", float);
			TryVistalConvertDetailsCopy("Int3", int, "Double3", double);
			
			TryVistalConvertDetailsCopy("Float3", float, "Double3", double);
			
			TryVistalConvertDetailsCopy("UChar3",unsigned char, "Short3", short);
			TryVistalConvertDetailsCopy("UChar3", unsigned char, "UShort3", unsigned short);
			
			TryVistalConvertDetailsCopy("UChar3",unsigned char, "Int3", int);
			TryVistalConvertDetailsCopy("UChar3",unsigned char, "UInt3", unsigned int);

			TryVistalConvertDetailsCopy("UChar3",unsigned char, "Float3", float);
			TryVistalConvertDetailsCopy("UChar3",unsigned char, "Double3", double);
			
			TryVistalConvertDetailsCopy("UShort3",unsigned short, "Int3", int);
			TryVistalConvertDetailsCopy("UShort3",unsigned short, "UInt3",unsigned int);
			TryVistalConvertDetailsCopy("UShort3",unsigned short, "Float3", float);
			TryVistalConvertDetailsCopy("UShort3",unsigned short, "Double3", double);
			
			TryVistalConvertDetailsCopy("UInt3", unsigned, "Float3", float);
			TryVistalConvertDetailsCopy("UInt3", unsigned, "Double3", double);										
			
			TryVistalConvert("Char3", char);			
			TryVistalConvert("UChar3", unsigned char);
			
			TryVistalConvert("Short3", short);
			TryVistalConvert("UShort3", unsigned short);			
			
			TryVistalConvert("Int3", int);
			TryVistalConvert("UInt3", unsigned);
			
			TryVistalConvert("Float3", float);
			
			TryVistalConvert("Double3", double);
			
			
		}
		
		
		
		
		
		
#define TryVistalConvertFromITKDetailsCopy(suffix, TypeIn, suffixOut, TypeOut) \
if (typeOut == ""#suffixOut ) \
{ \
itk::Image<TypeIn, 3>::Pointer image = static_cast<itk::Image<TypeIn, 3> *>( imageIn->data() );\
if (!image) return; \
itkImage3D<TypeIn> * vistalConverter = new itkImage3D<TypeIn> (image); \
vistal::Image3D<TypeIn> conv = vistalConverter->GetImage3D(); \
vistal::converters::Parameters parameters; /* conversion parameters */ \
parameters.copy = true; \
vistal::Image3D<TypeOut>* res = new vistal::Image3D<TypeOut>(conv, 0); \
vistal::converters::ConvertImages(conv, *res, parameters); \
if (res) imageOut = dtkAbstractDataFactory::instance()->create("vistalDataImage"#suffixOut); \
if (imageOut) imageOut->setData(res); \
return; \
} 
		
		
		
		
#define TryVistalConvertFromITKDetails(suffix, TypeIn, suffixOut, TypeOut) \
if (typeOut == ""#suffixOut ) \
{ \
	itk::Image<TypeIn, 3>::Pointer image = static_cast<itk::Image<TypeIn, 3> *>( imageIn->data() );\
	if (!image) return; \
	itkImage3D<TypeIn> * vistalConverter = new itkImage3D<TypeIn> (image); \
	vistal::Image3D<TypeIn> conv = vistalConverter->GetImage3D(); \
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
TryVistalConvertFromITKDetails(suffix, TypeIn, "Char3", char);\
TryVistalConvertFromITKDetails(suffix, TypeIn, "UChar3", unsigned char);\
\
TryVistalConvertFromITKDetails(suffix, TypeIn, "Short3", short);\
TryVistalConvertFromITKDetails(suffix, TypeIn, "UShort3", unsigned short);\
\
TryVistalConvertFromITKDetails(suffix, TypeIn, "Int3", int);\
TryVistalConvertFromITKDetails(suffix, TypeIn, "UInt3", unsigned);\
\
TryVistalConvertFromITKDetails(suffix, TypeIn, "Float3", float);\
TryVistalConvertFromITKDetails(suffix, TypeIn, "Double3", double);\
}		
		
		
		// 		
		void convertFromItk(QString typeIn, QString typeOut, dtkAbstractData* imageIn, dtkAbstractData* imageOut)
		{
			TryVistalConvertFromITKDetailsCopy("Char3", char, "Short3", short);
			TryVistalConvertFromITKDetailsCopy("Char3", char, "Int3", int);
			TryVistalConvertFromITKDetailsCopy("Char3", char, "Float3", float);
			TryVistalConvertFromITKDetailsCopy("Char3", char, "Double3", double);
			
			TryVistalConvertFromITKDetailsCopy("Short3", short, "Int3", int);
			TryVistalConvertFromITKDetailsCopy("Short3", short, "Float3", float);
			TryVistalConvertFromITKDetailsCopy("Short3", short, "Double3", double);
			
			TryVistalConvertFromITKDetailsCopy("Int3", int, "Float3", float);
			TryVistalConvertFromITKDetailsCopy("Int3", int, "Double3", double);
			
			TryVistalConvertFromITKDetailsCopy("Float3", float, "Double3", double);
			
			TryVistalConvertFromITKDetailsCopy("UChar3",unsigned char, "Short3", short);
			TryVistalConvertFromITKDetailsCopy("UChar3", unsigned char, "UShort3", unsigned short);
			
			TryVistalConvertFromITKDetailsCopy("UChar3",unsigned char, "Int3", int);
			TryVistalConvertFromITKDetailsCopy("UChar3",unsigned char, "UInt3", unsigned int);
			
			TryVistalConvertFromITKDetailsCopy("UChar3",unsigned char, "Float3", float);
			TryVistalConvertFromITKDetailsCopy("UChar3",unsigned char, "Double3", double);
			
			TryVistalConvertFromITKDetailsCopy("UShort3",unsigned short, "Int3", int);
			TryVistalConvertFromITKDetailsCopy("UShort3",unsigned short, "UInt3",unsigned int);
			TryVistalConvertFromITKDetailsCopy("UShort3",unsigned short, "Float3", float);
			TryVistalConvertFromITKDetailsCopy("UShort3",unsigned short, "Double3", double);
			
			TryVistalConvertFromITKDetailsCopy("UInt3", unsigned, "Float3", float);
			TryVistalConvertFromITKDetailsCopy("UInt3", unsigned, "Double3", double);										
			
			
			
			
			TryVistalConvertFromITK("Char3", char);			
			TryVistalConvertFromITK("UChar3", unsigned char);
			
			TryVistalConvertFromITK("Short3", short);
			TryVistalConvertFromITK("UShort3", unsigned short);			
			
			TryVistalConvertFromITK("Int3", int);
			TryVistalConvertFromITK("UInt3", unsigned);
			
			TryVistalConvertFromITK("Float3", float);
			
			TryVistalConvertFromITK("Double3", double);
			
			
			
		}
		
		
		
#define TryVistalVistalConvertDetailsCopy(suffix, TypeIn, suffixOut, TypeOut) \
if (typeOut == ""#suffixOut ) \
{ \
vistal::Image3D<TypeIn>* image = static_cast<vistal::Image3D<TypeIn>*>( imageIn->data() ); \
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
if (typeOut == ""#suffixOut ) \
{ \
vistal::Image3D<TypeIn>* image = static_cast<vistal::Image3D<TypeIn>*>( imageIn->data() ); \
if (!image) return; \
vistal::Image3D<TypeOut>* res = new vistal::Image3D<TypeOut>(*image, 0); \
if (!res) return; \
vistal::converters::Parameters parameters; /* conversion parameters */ \
vistal::converters::ConvertImages(*image, *res, parameters); \
if (res) imageOut = dtkAbstractDataFactory::instance()->create("vistalDataImage"#suffixOut); \
if (imageOut) imageOut->setData(res); \
return; \
} 
		
		
		
#define TryVistalVistalConvert(suffix, TypeIn)\
if (typeIn == "vistalDataImage"#suffix)\
{\
TryVistalConvertFromITKDetails(suffix, TypeIn, "Char3", char);\
TryVistalConvertFromITKDetails(suffix, TypeIn, "UChar3", unsigned char);\
\
TryVistalConvertFromITKDetails(suffix, TypeIn, "Short3", short);\
TryVistalConvertFromITKDetails(suffix, TypeIn, "UShort3", unsigned short);\
\
TryVistalConvertFromITKDetails(suffix, TypeIn, "Int3", int);\
TryVistalConvertFromITKDetails(suffix, TypeIn, "UInt3", unsigned);\
\
TryVistalConvertFromITKDetails(suffix, TypeIn, "Float3", float);\
TryVistalConvertFromITKDetails(suffix, TypeIn, "Double3", double);\
}		
		
		// Simple vistal converter
		void convert(QString typeIn, QString typeOut, dtkAbstractData* imageIn, dtkAbstractData* imageOut)
		{
			
			TryVistalVistalConvertFromCopy("Char3", char, "Short3", short);
			TryVistalVistalConvertFromCopy("Char3", char, "Int3", int);
			TryVistalVistalConvertFromCopy("Char3", char, "Float3", float);
			TryVistalVistalConvertFromCopy("Char3", char, "Double3", double);
			
			TryVistalVistalConvertFromCopy("Short3", short, "Int3", int);
			TryVistalVistalConvertFromCopy("Short3", short, "Float3", float);
			TryVistalVistalConvertFromCopy("Short3", short, "Double3", double);
			
			TryVistalVistalConvertFromCopy("Int3", int, "Float3", float);
			TryVistalVistalConvertFromCopy("Int3", int, "Double3", double);
			
			TryVistalVistalConvertFromCopy("Float3", float, "Double3", double);
			
			TryVistalVistalConvertFromCopy("UChar3",unsigned char, "Short3", short);
			TryVistalVistalConvertFromCopy("UChar3", unsigned char, "UShort3", unsigned short);
			
			TryVistalVistalConvertFromCopy("UChar3",unsigned char, "Int3", int);
			TryVistalVistalConvertFromCopy("UChar3",unsigned char, "UInt3", unsigned int);
			
			TryVistalVistalConvertFromCopy("UChar3",unsigned char, "Float3", float);
			TryVistalVistalConvertFromCopy("UChar3",unsigned char, "Double3", double);
			
			TryVistalVistalConvertFromCopy("UShort3",unsigned short, "Int3", int);
			TryVistalVistalConvertFromCopy("UShort3",unsigned short, "UInt3",unsigned int);
			TryVistalVistalConvertFromCopy("UShort3",unsigned short, "Float3", float);
			TryVistalVistalConvertFromCopy("UShort3",unsigned short, "Double3", double);
			
			TryVistalVistalConvertFromCopy("UInt3", unsigned, "Float3", float);
			TryVistalVistalConvertFromCopy("UInt3", unsigned, "Double3", double);										
			
			
			
			
			
			TryVistalVistalConvert("Char3", char);			
			TryVistalVistalConvert("UChar3", unsigned char);
			
			TryVistalVistalConvert("Short3", short);
			TryVistalVistalConvert("UShort3", unsigned short);			
			
			TryVistalVistalConvert("Int3", int);
			TryVistalVistalConvert("UInt3", unsigned);
			
			TryVistalVistalConvert("Float3", float);
			
			TryVistalVistalConvert("Double3", double);									
			
		}
		
		
		
		
	}
}

