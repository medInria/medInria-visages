#pragma once

#include <medAbstractImageViewInteractor.h>
#include <animaDataMCMImagePluginExport.h>

class animaDataMCMImageVtkViewInteractorPrivate;

class medAbstractData;
class dtkAbstractView;

/**
 * @class animaDataMCMImageVtkViewInteractor
 * @brief Extents a view by providing Spherical harmonics viewing/managing capabilities.
 *
 * An interactor is an extension to a view (medVtkView in this case)
 * that provides additional functionality. This class extents the view by
 * adding MCM handling capabilities like visualization and MCM-specific
 * properties.
 */
class ANIMADATAMCMIMAGEPLUGIN_EXPORT animaDataMCMImageVtkViewInteractor: public medAbstractImageViewInteractor
{
    Q_OBJECT

public:
    animaDataMCMImageVtkViewInteractor(medAbstractView* parent);
    virtual ~animaDataMCMImageVtkViewInteractor();

public:

    enum TesselationType
    {
        Icosahedron = 0,
        Dodecahedron,
        Octahedron,
        Hexahedron,
        Tetrahedron
    };

    virtual QString description() const;
    virtual QString identifier() const;
    virtual QStringList handled() const;

    static bool registered();

    virtual void setInputData(medAbstractData *data);

    virtual QWidget* buildLayerWidget();
    virtual QWidget* buildToolBoxWidget();
    virtual QWidget* buildToolBarWidget();
    virtual QList<medAbstractParameter*> linkableParameters();
    virtual QList<medBoolParameter*> mouseInteractionParameters();

    void removeData();

    /** get the image size it is used to set med gui slider appropiate size*/
    virtual void imageSize(int* range);

public slots:

    /** Change glyph shape */
    void setTesselationType (QString tesselationType);

    /** Modify sample rate */
    void setSampleRate (int sampleRate);

    /** Flip MCMs along the X axis */
    void setFlipX (const bool flipX);

    /** Flip MCMs along the Y axis */
    void setFlipY (const bool flipY);

    /** Flip MCMs along the Z axis */
    void setFlipZ (const bool flipZ);

    void setNormalization(const bool Norma);

    /** Glyph resolution changed */
    void setGlyphResolution (int glyphResolution);

    /** Scaling changed */
    void setScale (double scale);

    /** Change the position of the slices */
    void setPosition(const QVector3D& position);

    void setMajorScaling(int majorScalingExponent);
    void setMinorScaling(int minorScaling);
    void setScale(int minorScale, int majorScaleExponent);

    void setOpacity(double opacity);
    void setVisibility(bool visibility);
    void setWindowLevel(QHash<QString, QVariant>);

    virtual void setUpViewForThumbnail();

    virtual void updateWidgets();

    virtual void moveToSlice (int slice);

    virtual void changeOrientationVisibility();

protected:
    void setupParameters();

private:
    static QStringList dataHandled();
    void update();

private slots:
    void updateSlicingParam();

private:
    animaDataMCMImageVtkViewInteractorPrivate* d;
};
