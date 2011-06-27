#ifndef _med_VistalDataImageConverterMacros_h_
#define _med_VistalDataImageConverterMacros_h_

#include "VistalConverters.hh"
// The function taking medinria internal vistal names and converts to desired name

#include "boost/function.hpp"




// The converter toward Itk image data


#define medImplementVistalDataImageConverter(type, suffix)		\
class vistalDataImageToItkDataImage##suffix##ConverterPrivate \
{ \
public: \
	itkImage3D<type> * vistalConverter; \
	dtkAbstractData * output; \
}; \
vistalDataImageToItkDataImage##suffix##Converter::vistalDataImageToItkDataImage##suffix##Converter(void) : \
dtkAbstractDataConverter(), d(new vistalDataImageToItkDataImage##suffix##ConverterPrivate) \
{ \
	d->output = NULL; \
  d->vistalConverter = NULL; \
} \
vistalDataImageToItkDataImage##suffix##Converter::~vistalDataImageToItkDataImage##suffix##Converter(void) \
{ \
	if (d->vistalConverter) \
		delete d->vistalConverter; \
} \
bool vistalDataImageToItkDataImage##suffix##Converter::registered(void) \
{ \
return dtkAbstractDataFactory::instance()->registerDataConverterType(QString("vistalDataImageToItkDataImage") + QString(""#suffix) + QString("Converter"), \
																	QStringList()	<< "vistalDataImageChar3" <<  "vistalDataImageUChar3" \
																					<<  "vistalDataImageShort3" <<  "vistalDataImageUShort3" \
																					<<  "vistalDataImageInt3" <<  "vistalDataImageUInt3"  \
																					<< "vistalDataImageFloat3" <<  "vistalDataImageDouble3",\
																	"itkDataImage"#suffix, createVistalDataImageToItkDataImage##suffix##Converter); \
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
	vistal::medinria::convertToItk(data->description(), ""#suffix, data, d->output);\
	return d->output; \
} \
dtkAbstractDataConverter *createVistalDataImageToItkDataImage##suffix##Converter(void) \
{ \
	return new vistalDataImageToItkDataImage##suffix##Converter; \
}

// Converter from Itk to vistal format

#define medImplementItkToVistalDataImageConverter(type, suffix)		\
class itkDataImageToVistalDataImage##suffix##ConverterPrivate \
{ \
public: \
	itkImage3D<type> * vistalConverter; \
	vistal::Image3D<type> * tmpOut; \
	dtkAbstractData * output; \
}; \
itkDataImageToVistalDataImage##suffix##Converter::itkDataImageToVistalDataImage##suffix##Converter(void) : \
	dtkAbstractDataConverter(), d(new itkDataImageToVistalDataImage##suffix##ConverterPrivate) \
{ \
	d->output = NULL; \
	d->tmpOut = NULL; \
	d->vistalConverter = NULL; \
} \
itkDataImageToVistalDataImage##suffix##Converter::~itkDataImageToVistalDataImage##suffix##Converter(void) \
{ \
	if (d->vistalConverter) \
		delete d->vistalConverter; \
} \
bool itkDataImageToVistalDataImage##suffix##Converter::registered(void) \
{ \
return dtkAbstractDataFactory::instance()->registerDataConverterType(QString("itkDataImageToVistalDataImage") + QString(""#suffix) + QString("Converter"), \
																	 QStringList()  << "itkDataImageChar3" <<  "itkDataImageUChar3" \
																					<<  "itkDataImageShort3" <<  "itkDataImageUShort3" \
																					<<  "itkDataImageInt3" <<  "itkDataImageUInt3"  \
																					<< "itkDataImageFloat3" <<  "itkDataImageDouble3" ,\
																	"vistalDataImage"#suffix, createItkDataImageToVistalDataImage##suffix##Converter); \
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
	vistal::medinria::convertFromItk(data->description(), ""#suffix, data, d->output);\
	return d->output; \
} \
dtkAbstractDataConverter *createItkDataImageToVistalDataImage##suffix##Converter(void) \
{ \
	return new itkDataImageToVistalDataImage##suffix##Converter; \
}



#define medImplementVistaltoVistalDataImageConverter(type, suffix)		\
class VistalToVistal##suffix##ConverterPrivate \
{ \
public: \
	vistal::Image3D<type> * tmpOut; \
	dtkAbstractData * output; \
}; \
VistalToVistal##suffix##Converter::VistalToVistal##suffix##Converter(void) : \
dtkAbstractDataConverter(), d(new VistalToVistal##suffix##ConverterPrivate) \
{ \
d->output = NULL; \
d->tmpOut = NULL; \
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
dtkAbstractData *data = this->data(); \
if (!data) \
return NULL; \
vistal::medinria::convert(data->description(), ""#suffix, data, d->output);\
return d->output; \
} \
dtkAbstractDataConverter *createVistalToVistal##suffix##Converter(void) \
{ \
return new VistalToVistal##suffix##Converter; \
}





#endif
