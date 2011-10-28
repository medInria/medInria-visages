#ifndef _med_VistalDataImageConverterMacros_h_
#define _med_VistalDataImageConverterMacros_h_

#include "VistalConverters.h"
// The function taking medinria internal vistal names and converts to desired name

#include "boost/function.hpp"




// The converter toward Itk image data


#define medImplementVistalDataImageConverter(type, suffix)		\
vistalDataImageToItkDataImage##suffix##Converter::vistalDataImageToItkDataImage##suffix##Converter(void) : \
dtkAbstractDataConverter()\
{} \
vistalDataImageToItkDataImage##suffix##Converter::~vistalDataImageToItkDataImage##suffix##Converter(void) \
{} \
bool vistalDataImageToItkDataImage##suffix##Converter::registered(void) \
{ \
return dtkAbstractDataFactory::instance()->registerDataConverterType(QString("vistalDataImageToItkDataImage") + QString(""#suffix) + QString("Converter"), \
																	QStringList()	<< "vistalDataImageChar3" <<  "vistalDataImageUChar3" \
																					<<  "vistalDataImageShort3" <<  "vistalDataImageUShort3" \
																					<<  "vistalDataImageInt3" <<  "vistalDataImageUInt3"  \
																					<< "vistalDataImageFloat3" <<  "vistalDataImageDouble3",\
																	"itkDataImage"#suffix, createVistalDataImageToItkDataImage##suffix##Converter); \
} \
QString vistalDataImageToItkDataImage##suffix##Converter::identifier(void) const \
{ \
        return QString("vistalDataImageToItkDataImage") + QString(""#suffix) + QString("Converter"); \
} \
QString vistalDataImageToItkDataImage##suffix##Converter::description(void) const \
{ \
        return QString("vistalDataImageToItkDataImage") + QString(""#suffix) + QString("Converter"); \
} \
QStringList vistalDataImageToItkDataImage##suffix##Converter::fromTypes(void) const \
{ \
 return QStringList() << "vistalDataImageChar3" <<  "vistalDataImageUChar3" \
	<<  "vistalDataImageShort3" <<  "vistalDataImageUShort3" \
	<<  "vistalDataImageInt3" <<  "vistalDataImageUInt3"  \
	<< "vistalDataImageFloat3" <<  "vistalDataImageDouble3"; \
} \
QString vistalDataImageToItkDataImage##suffix##Converter::toType(void) const \
{ \
	return "itkDataImage"#suffix; \
} \
dtkAbstractData *vistalDataImageToItkDataImage##suffix##Converter::convert(void) \
{ \
	dtkAbstractData *data = this->data(); \
	if (!data) \
		return NULL; \
	dtkAbstractData * output;\
	vistal::medinria::convertToItk(data->identifier(), ""#suffix, data, output);\
	return output; \
} \
dtkAbstractDataConverter *createVistalDataImageToItkDataImage##suffix##Converter(void) \
{ \
	return new vistalDataImageToItkDataImage##suffix##Converter; \
}

// Converter from Itk to vistal format

#define medImplementItkToVistalDataImageConverter(type, suffix)		\
itkDataImageToVistalDataImage##suffix##Converter::itkDataImageToVistalDataImage##suffix##Converter(void) : \
	dtkAbstractDataConverter()\
{ } \
itkDataImageToVistalDataImage##suffix##Converter::~itkDataImageToVistalDataImage##suffix##Converter(void) \
{ } \
bool itkDataImageToVistalDataImage##suffix##Converter::registered(void) \
{ \
return dtkAbstractDataFactory::instance()->registerDataConverterType(QString("itkDataImageToVistalDataImage") + QString(""#suffix) + QString("Converter"), \
																	 QStringList()  << "itkDataImageChar3" <<  "itkDataImageUChar3" \
																					<<  "itkDataImageShort3" <<  "itkDataImageUShort3" \
																					<<  "itkDataImageInt3" <<  "itkDataImageUInt3"  \
																					<< "itkDataImageFloat3" <<  "itkDataImageDouble3" ,\
																	"vistalDataImage"#suffix, createItkDataImageToVistalDataImage##suffix##Converter); \
} \
QString itkDataImageToVistalDataImage##suffix##Converter::identifier(void) const \
{ \
        return QString("itkDataImageToVistalDataImage") + QString(""#suffix) + QString("Converter"); \
} \
QString itkDataImageToVistalDataImage##suffix##Converter::description(void) const \
{ \
        return QString("itkDataImageToVistalDataImage") + QString(""#suffix) + QString("Converter"); \
} \
QStringList itkDataImageToVistalDataImage##suffix##Converter::fromTypes(void) const \
{ \
	return QStringList() << "itkDataImageChar3" <<  "itkDataImageUChar3" \
						 <<  "itkDataImageShort3" <<  "itkDataImageUShort3" \
						 <<  "itkDataImageInt3" <<  "itkDataImageUInt3"  \
						 << "itkDataImageFloat3" <<  "itkDataImageDouble3"; \
} \
QString itkDataImageToVistalDataImage##suffix##Converter::toType(void) const \
{ \
	return "vistalDataImage"#suffix; \
} \
dtkAbstractData *itkDataImageToVistalDataImage##suffix##Converter::convert(void) \
{ \
	dtkAbstractData *data = this->data(); \
	if (!data) \
		return NULL; \
	dtkAbstractData * output;\
	vistal::medinria::convertFromItk(data->identifier(), ""#suffix, data, output);\
	return output; \
} \
dtkAbstractDataConverter *createItkDataImageToVistalDataImage##suffix##Converter(void) \
{ \
	return new itkDataImageToVistalDataImage##suffix##Converter; \
}



#define medImplementVistaltoVistalDataImageConverter(type, suffix)		\
VistalToVistal##suffix##Converter::VistalToVistal##suffix##Converter(void) : \
dtkAbstractDataConverter()\
{ \
} \
VistalToVistal##suffix##Converter::~VistalToVistal##suffix##Converter(void) \
{ \
} \
bool VistalToVistal##suffix##Converter::registered(void) \
{ \
return dtkAbstractDataFactory::instance()->registerDataConverterType(QString("VistalToVistal") + QString(""#suffix) + QString("Converter"), \
																	 QStringList()	<< "vistalDataImageChar3" <<  "vistalDataImageUChar3" \
																					<<  "vistalDataImageShort3" <<  "vistalDataImageUShort3" \
																					<<  "vistalDataImageInt3" <<  "vistalDataImageUInt3"  \
																					<< "vistalDataImageFloat3" <<  "vistalDataImageDouble3",\
																					"vistalDataImage"#suffix, createVistalToVistal##suffix##Converter); \
} \
QString VistalToVistal##suffix##Converter::identifier(void) const \
{ \
return QString("VistalToVistal") + QString(""#suffix) + QString("Converter"); \
} \
QString VistalToVistal##suffix##Converter::description(void) const \
{ \
return QString("VistalToVistal") + QString(""#suffix) + QString("Converter"); \
} \
QStringList VistalToVistal##suffix##Converter::fromTypes(void) const \
{ \
return QStringList() << "vistalDataImageChar3" <<  "vistalDataImageUChar3" \
<<  "vistalDataImageShort3" <<  "vistalDataImageUShort3" \
<<  "vistalDataImageInt3" <<  "vistalDataImageUInt3"  \
<< "vistalDataImageFloat3" <<  "vistalDataImageDouble3"; \
} \
QString VistalToVistal##suffix##Converter::toType(void) const \
{ \
return "vistalDataImage"#suffix; \
} \
dtkAbstractData *VistalToVistal##suffix##Converter::convert(void) \
{ \
qDebug() << "Vistal self Conversion to "#suffix << "from"<< this->data();\
dtkAbstractData *data = this->data(); \
dtkAbstractData *output; \
if (!data) \
return NULL; \
if (data->identifier() == "vistalDataImage"#suffix) { output = data; return output; } \
vistal::medinria::convert(data->identifier(), ""#suffix, data, output);\
return output; \
} \
dtkAbstractDataConverter *createVistalToVistal##suffix##Converter(void) \
{ \
return new VistalToVistal##suffix##Converter; \
}





#endif
