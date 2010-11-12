#ifndef _med_VistalDataImageMacros_h_
#define _med_VistalDataImageMacros_h_

#define medImplementVistalDataImage(type, suffix)		\
	class vistalDataImage##suffix##Private \
	{ \
	public: \
		vistal::Image3D< type > * image; \
		QList<QImage> thumbnails;	\
		QImage defaultThumbnail; \
		type range_min, range_max; \
	}; \
	vistalDataImage##suffix::vistalDataImage##suffix(void) : dtkAbstractDataImage(), d(new vistalDataImage##suffix##Private) \
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
		return dtkAbstractDataFactory::instance()->registerDataType("vistalDataImage"#suffix, createVistalDataImage##suffix); \
	} \
	QString vistalDataImage##suffix::description(void) const \
	{ \
		return "vistalDataImage"#suffix; \
	} \
	QImage & vistalDataImage##suffix::thumbnail(void) const \
	{ \
		return d->defaultThumbnail; \
	} \
	QList<QImage> & vistalDataImage##suffix::thumbnails(void) const \
	{ \
		if (d->thumbnails.isEmpty()) \
		{ \
			for (int i = 0;i < d->image->nbz;++i) \
				d->thumbnails.push_back(d->defaultThumbnail); \
		} \
		return d->thumbnails; \
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
	} \
	dtkAbstractData *createVistalDataImage##suffix(void) \
	{ \
		return new vistalDataImage##suffix; \
	}

#endif