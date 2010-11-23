#ifndef _med_VistalDataImageConverterMacros_h_
#define _med_VistalDataImageConverterMacros_h_

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
	d->output = dtkAbstractDataFactory::instance()->create("itkDataImage"#suffix); \
  d->vistalConverter = NULL; \
} \
vistalDataImageToItkDataImage##suffix##Converter::~vistalDataImageToItkDataImage##suffix##Converter(void) \
{ \
} \
bool vistalDataImageToItkDataImage##suffix##Converter::registered(void) \
{ \
	return dtkAbstractDataFactory::instance()->registerDataConverterType(QString("vistalDataImageToItkDataImage") + QString(""#suffix) + QString("Converter"), QStringList() << "vistalDataImage"#suffix, "itkDataImage"#suffix, createVistalDataImageToItkDataImage##suffix##Converter); \
} \
QString vistalDataImageToItkDataImage##suffix##Converter::description(void) const \
{ \
	return QString("vistalDataImageToItkDataImage") + QString(""#suffix) + QString("Converter"); \
} \
QStringList vistalDataImageToItkDataImage##suffix##Converter::fromTypes(void) const \
{ \
	return QStringList() << "vistalDataImage"#suffix; \
} \
QString vistalDataImageToItkDataImage##suffix##Converter::toType(void) const \
{ \
	return "itkDataImage"#suffix; \
} \
dtkAbstractData *vistalDataImageToItkDataImage##suffix##Converter::convert(void) \
{ \
	if (!d->output) \
		return NULL; \
	dtkAbstractData *data = this->data(); \
	if (!data) \
		return NULL; \
	if (data->description() == "vistalDataImage"#suffix) { \
		if ( vistal::Image3D<type>* image = static_cast<vistal::Image3D<type>*>( data->data() ) ) { \
			if (d->vistalConverter == NULL) \
				d->vistalConverter = new itkImage3D<type> ; \
			d->vistalConverter->SetImage3D(*image); \
			d->output->setData(d->vistalConverter->GetOutput()); \
		} \
	} \
	return d->output; \
} \
dtkAbstractDataConverter *createVistalDataImageToItkDataImage##suffix##Converter(void) \
{ \
	return new vistalDataImageToItkDataImage##suffix##Converter; \
}

#endif
