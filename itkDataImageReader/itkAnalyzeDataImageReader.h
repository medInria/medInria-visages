#ifndef ITKANALYZEDATAIMAGEREADER_H
#define ITKANALYZEDATAIMAGEREADER_H

#include "itkDataImageReaderBase.h"

#include "itkDataImageReaderPluginExport.h"

class ITKDATAIMAGEREADERPLUGIN_EXPORT itkAnalyzeDataImageReader : public itkDataImageReaderBase
{
    Q_OBJECT
	
public:
    itkAnalyzeDataImageReader(void);
    virtual ~itkAnalyzeDataImageReader(void);
	
    virtual QString description(void) const;
	
    static bool registered(void);	
};

dtkAbstractDataReader *createItkAnalyzeDataImageReader(void);

#endif