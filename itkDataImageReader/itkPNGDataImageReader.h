#ifndef ITKPNGDATAIMAGEREADER_H
#define ITKPNGDATAIMAGEREADER_H

#include "itkDataImageReaderBase.h"

#include "itkDataImageReaderPluginExport.h"

class ITKDATAIMAGEREADERPLUGIN_EXPORT itkPNGDataImageReader : public itkDataImageReaderBase
{
    Q_OBJECT
	
public:
    itkPNGDataImageReader(void);
    virtual ~itkPNGDataImageReader(void);
	
    virtual QString description(void) const;
	
    static bool registered(void);	
};

dtkAbstractDataReader *createItkPNGDataImageReader(void);

#endif