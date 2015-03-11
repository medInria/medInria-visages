#ifndef _med_VistalDataImageMacros_h_
#define _med_VistalDataImageMacros_h_

#include <Image3D.hh>
#include <Stats.hh>

template<typename DataType>
    void
    generateThumbnails(typename vistal::Image3D<DataType> * ima, QList<QImage> & thumbnails)
    {
        if (ima == NULL)
            return;

        thumbnails.clear();

        qDebug() << "generating thumbnails... ";

        DataType max = vistal::stats::GetMaxPixelValue(*ima);
        DataType min = vistal::stats::GetMinPixelValue(*ima);

        for (short k = 0; k < ima->nbz; k++) {
            QImage *qImage = new QImage(ima->nbx, ima->nby, QImage::Format_ARGB32);
            uchar *buffer = qImage->bits();
            for (short j = ima->nby - 1; j >= 0; j--)
                for (short i = 0; i < ima->nbx; i++) {
                    float val = floor((ima->ptr[k][j][i] - min) * 255.0 / (max - min));
                    for (short a = 0; a < 3; ++a)
                        *buffer++ = (uchar) val;
                    *buffer++ = 0xFF;
                }

            *qImage = qImage->scaled(128, 128, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            //qImage->fill(128);
            thumbnails.push_back(*qImage);
        }

        qDebug() << "...generated " << thumbnails.length() << " thumbnails";
    }

template<typename DataType>
    void
    getThumbnail(typename vistal::Image3D<DataType> * ima, QImage & thumbnail)
    {
        if (ima == NULL)
            return;

        DataType max = vistal::stats::GetMaxPixelValue(*ima);
        DataType min = vistal::stats::GetMinPixelValue(*ima);

        QImage *qImage = new QImage(ima->nbx, ima->nby, QImage::Format_ARGB32);
        uchar *buffer = qImage->bits();

        short index = ima->nbz / 2;

        for (short j = ima->nby - 1; j >= 0; j--)
            for (short i = 0; i < ima->nbx; i++) {
                float val = floor((ima->ptr[index][j][i] - min) * 255.0 / (max - min));
                for (short a = 0; a < 3; ++a)
                    *buffer++ = (uchar) val;
                *buffer++ = 0xFF;
            }

        *qImage = qImage->scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        thumbnail = *qImage;
    }

#define medImplementVistalDataImage(type, suffix)		\
	class vistalDataImage##suffix##Private \
	{ \
	public: \
		vistal::Image3D< type > * image; \
		QList<QImage> thumbnails;	\
		QImage defaultThumbnail; \
		type range_min, range_max; \
	}; \
    vistalDataImage##suffix::vistalDataImage##suffix(void) : medAbstractImageData(), d(new vistalDataImage##suffix##Private) \
	{ \
		d->image = 0; \
		d->range_min = 0; \
		d->range_max = 0; \
		d->defaultThumbnail = QImage(128, 128, QImage::Format_ARGB32); \
		d->defaultThumbnail.fill(0); \
	} \
	vistalDataImage##suffix::~vistalDataImage##suffix(void) \
	{ \
		if (d->image) \
			delete d->image; \
		delete d; \
		d = 0; \
	} \
	bool vistalDataImage##suffix::registered(void) \
	{ \
        return medAbstractDataFactory::instance()->registerDataType<vistalDataImage##suffix>(); \
	} \
	void * vistalDataImage##suffix::data() \
	{ \
		return d->image; \
	} \
	void * vistalDataImage##suffix::output() \
	{ \
		return d->image; \
	} \
	void vistalDataImage##suffix::setData(void* data) \
	{ \
		d->image = static_cast<vistal::Image3D< type > *> (data); \
	} \
	int vistalDataImage##suffix::xDimension(void) \
	{ \
		if (d->image != NULL) \
			return d->image->nbx; \
		else \
			return -1; \
	} \
	int vistalDataImage##suffix::yDimension(void) \
	{ \
		if (d->image != NULL) \
			return d->image->nby; \
		else \
			return -1; \
	} \
	int vistalDataImage##suffix::zDimension(void) \
	{ \
		if (d->image != NULL) \
			return d->image->nbz; \
		else \
			return -1; \
	} \
	int vistalDataImage##suffix::tDimension(void) \
	{ \
		if (d->image != NULL) \
			return d->image->nbt; \
		else \
			return -1; \
	} \
	int vistalDataImage##suffix::minRangeValue(void) \
	{ \
		if (d->range_min == 0) \
		{ \
			if (d->image != 0) \
				d->range_min = vistal::stats::GetMinPixelValue (*d->image); \
		} \
		return d->range_min; \
	} \
	int vistalDataImage##suffix::maxRangeValue(void) \
	{ \
		if (d->range_max == 0) \
		{ \
			if (d->image != 0) \
				d->range_max = vistal::stats::GetMaxPixelValue (*d->image); \
		} \
		return d->range_max; \
    }
#endif
