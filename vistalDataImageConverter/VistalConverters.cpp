
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
	}
}

