#pragma once

#include <dtkCore/dtkAbstractDataReader.h>
#include <animaDataMCMImagePluginExport.h>

class ANIMADATAMCMIMAGEPLUGIN_EXPORT animaDataMCMImageReader : public dtkAbstractDataReader
{
    Q_OBJECT

public:
             animaDataMCMImageReader();
    virtual ~animaDataMCMImageReader();

    virtual QStringList handled() const;

    static QStringList s_handled();

    virtual QString identifier()  const;
    virtual QString description() const;

    static bool registered();

public slots:
    virtual bool canRead (const QString &path);
    virtual bool canRead (const QStringList &paths);

    /** it reads the information of vector animaDataMCMImageFloat3 or animaDataMCMImageDouble3 */
    virtual bool readInformation (const QString &path);
    virtual bool readInformation (const QStringList &paths);

    /** where the itk::VectorImage<double/float, 3> is read*/
    virtual bool read (const QString &path);
    virtual bool read (const QStringList &paths);

private:
};

dtkAbstractDataReader *createAnimaDataMCMImageReader();
