#ifndef VISTALDATAIMAGEWRITER_H
#define VISTALDATAIMAGEWRITER_H

#include <dtkCore/dtkAbstractDataWriter.h>

#include "vistalDataImageWriterPluginExport.h"

class vistalDataImageWriterPrivate;

class VISTALDATAIMAGEWRITERPLUGIN_EXPORT vistalDataImageWriter : public dtkAbstractDataWriter
{
    Q_OBJECT

    public:
        vistalDataImageWriter(void);
        virtual
        ~vistalDataImageWriter(void);

        virtual QString
        description(void) const;

        static bool
        registered(void);

        virtual QStringList
        handled(void) const;

    public slots:
        bool
        write(QString path);
        bool
        canWrite(QString path);

    private:
        vistalDataImageWriterPrivate *d;
};

dtkAbstractDataWriter *
createVistalDataImageWriter(void);

#endif
