// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALDATAIMAGEREADER_H
#define VISTALDATAIMAGEREADER_H

#include <dtkCore/dtkAbstractData.h>

#include "vistalDataImageReaderPluginExport.h"

#include "dtkCore/dtkAbstractDataReader.h"

class vistalDataImageReaderPrivate;

class VISTALDATAIMAGEREADERPLUGIN_EXPORT vistalDataImageReader : public dtkAbstractDataReader
{
    Q_OBJECT

public:
             vistalDataImageReader(void);
    virtual ~vistalDataImageReader(void);

    virtual QString description(void) const;

    static bool registered(void);

    virtual QStringList handled(void) const;


public slots:
    virtual bool canRead (QString path);
    virtual bool canRead (QStringList paths);
    
    virtual void readInformation (QString path);
    virtual void readInformation (QStringList paths);
    
    virtual bool read (QString path);
    virtual bool read (QStringList paths);

    virtual void setProgress (int value);


private:
    vistalDataImageReaderPrivate *d;
};

dtkAbstractDataReader *createVistalDataImageReader(void);

#endif
