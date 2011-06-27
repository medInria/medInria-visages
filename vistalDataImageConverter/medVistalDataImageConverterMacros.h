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
	return dtkAbstractDataFactory::instance()->registerDataConverterType(QString("itkDataImageToVistalDataImage") + QString(""#suffix) + QString("Converter"), QStringList() << "itkDataImage"#suffix, "vistalDataImage"#suffix, createItkDataImageToVistalDataImage##suffix##Converter); \
} \
QString itkDataImageToVistalDataImage##suffix##Converter::description(void) const \
{ \
	return QString("itkDataImageToVistalDataImage") + QString(""#suffix) + QString("Converter"); \
} \
QStringList itkDataImageToVistalDataImage##suffix##Converter::fromTypes(void) const \
{ \
	return QStringList() << "itkDataImage"#suffix; \
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
	if (data->description() == "itkDataImage"#suffix) { \
		if ( itk::Image<type, 3>::Pointer image = static_cast<itk::Image<type, 3> *>( data->data() ) ) { \
			if (d->vistalConverter == NULL) \
      { \
				d->vistalConverter = new itkImage3D<type> (image); \
      } \
			if (!d->output) \
				d->output = dtkAbstractDataFactory::instance()->create("vistalDataImage"#suffix); \
			if (!d->output) \
				return NULL; \
			if (d->tmpOut) \
				delete d->tmpOut; \
			d->tmpOut = new vistal::Image3D <type>(d->vistalConverter->GetImage3D()); \
			d->output->setData(d->tmpOut); \
		} \
	} \
	return d->output; \
} \
dtkAbstractDataConverter *createItkDataImageToVistalDataImage##suffix##Converter(void) \
{ \
	return new itkDataImageToVistalDataImage##suffix##Converter; \
}

#endif
