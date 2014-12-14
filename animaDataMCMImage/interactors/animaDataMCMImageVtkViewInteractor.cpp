#include <animaDataMCMImageVtkViewInteractor.h>

#include <vtkMCMManager.h>
#include <vtkStructuredPoints.h>

#include <vtkImageActor.h>
#include <vtkImageView2D.h>
#include <vtkImageView3D.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>

#include <medAbstractData.h>
#include <medAbstractParameter.h>
#include <medStringListParameter.h>
#include <medIntParameter.h>
#include <medBoolParameter.h>
#include <medDoubleParameter.h>
#include <medAbstractImageView.h>
#include <medViewFactory.h>
#include <medVtkViewBackend.h>

#include <animaMCMITKToVTKFilter.h>

#include <itkImage.h>
#include <itkVectorImage.h>

class animaDataMCMImageVtkViewInteractorPrivate
{
public:

    medAbstractData* data;
    medAbstractImageView *view;
    vtkImageView2D *view2d;
    vtkImageView3D *view3d;
    vtkRenderWindow *render;

    QList <medAbstractParameter*> parameters;
    vtkMCMManager *manager;
    double imageBounds[6];

    int minorScaling;
    int majorScalingExponent;

    medIntParameter *slicingParameter;

    typedef vtkSmartPointer <vtkProperty>  PropertySmartPointer;
    PropertySmartPointer actorProperty;

    //  The filters will convert from itk MCM image format to vtkStructuredPoint (format handled by the MCM manager)

    animaMCMITKToVTKFilter<itk::VectorImage<float,3> >::Pointer  filterFloat;
    animaMCMITKToVTKFilter<itk::VectorImage<double,3> >::Pointer filterDouble;

    template <typename MCM_IMAGE>
    void setVTKFilter(medAbstractData* d,typename animaMCMITKToVTKFilter<MCM_IMAGE>::Pointer& filter)
    {
        MCM_IMAGE* dataset = static_cast<MCM_IMAGE*>(d->data());

        if (filter)
            filter->Delete();

        filter = animaMCMITKToVTKFilter<MCM_IMAGE>::New();
        filter->SetInput(dataset);
        filter->Update();

        manager->SetInput(filter->GetVTKMCMData());
        manager->SetMatrixT(filter->GetDirectionMatrix());

        manager->ResetPosition();

        manager->Update();
        data = d;
    }
};

animaDataMCMImageVtkViewInteractor::animaDataMCMImageVtkViewInteractor(medAbstractView *parent)
    : medAbstractImageViewInteractor(parent), d(new animaDataMCMImageVtkViewInteractorPrivate)
{
    d->data = 0;

    d->view = dynamic_cast<medAbstractImageView*>(parent);
    connect(d->view,SIGNAL(orientationChanged()),this,SLOT(changeOrientationVisibility()), Qt::UniqueConnection);

    medVtkViewBackend* backend = static_cast<medVtkViewBackend*>(parent->backend());
    d->view2d = backend->view2D;
    d->view3d = backend->view3D;
    d->render = backend->renWin;

    d->manager = vtkMCMManager::New();

    d->filterFloat = 0;
    d->filterDouble = 0;

    d->minorScaling = 1;
    d->majorScalingExponent = 0;

    //  Set default properties
    d->manager->SetTesselationType(0);
    d->manager->SetNormalization(false);

    for (int i=0; i<6; i++)
        d->imageBounds[i] = 0;

    d->manager->SetRenderWindowInteractor(d->render->GetInteractor(), d->view3d->GetRenderer());

    connect(d->view->positionBeingViewedParameter(), SIGNAL(valueChanged(QVector3D)),
            this, SLOT(setPosition(QVector3D)));

    d->slicingParameter = new medIntParameter("Slicing", this);
}

animaDataMCMImageVtkViewInteractor::~animaDataMCMImageVtkViewInteractor()
{
    delete d;
    d = 0;
}

QString animaDataMCMImageVtkViewInteractor::description() const
{
    return tr("Interactor displaying multi-compartment models");
}

QString animaDataMCMImageVtkViewInteractor::identifier() const
{
    return "animaDataMCMImageVtkViewInteractor";
}

QStringList animaDataMCMImageVtkViewInteractor::handled() const
{
    return animaDataMCMImageVtkViewInteractor::dataHandled();
}

QStringList animaDataMCMImageVtkViewInteractor::dataHandled()
{
    QStringList datahandled = QStringList() << "animaDataMCMImageDouble3" << "animaDataMCMImageFloat3";
    return  datahandled;
}

bool animaDataMCMImageVtkViewInteractor::registered()
{
    medViewFactory *factory = medViewFactory::instance();
    factory->registerInteractor<animaDataMCMImageVtkViewInteractor>("animaDataMCMImageVtkViewInteractor",
                                                                    QStringList () << "medVtkView" <<
                                                                    animaDataMCMImageVtkViewInteractor::dataHandled());
    return true;
}

void animaDataMCMImageVtkViewInteractor::setInputData(medAbstractData *data)
{
    medAbstractInteractor::setInputData(data);

    if (!data || !data->data())
        return;

    //  Two MCM image formats are supported
    //  we need to convert them to vtkStructuredPoints so it's understood by the MCM manager

    const QString& identifier = data->identifier();
    if (identifier=="animaDataMCMImageFloat3")
        d->setVTKFilter<itk::VectorImage<float,3> >(data,d->filterFloat);
    else if (identifier=="animaDataMCMImageDouble3")
        d->setVTKFilter<itk::VectorImage<double,3> >(data,d->filterDouble);
    else
    {
        qDebug() << "Unrecognized MCM data type: " << identifier;
        return;
    }

    int dim[3];
    d->manager->GetMCMDimensions(dim);
    d->view2d->SetInput(d->manager->GetMCMVisuManagerAxial()->GetActor(), d->view->layer(d->data), dim);
    d->view2d->SetInput(d->manager->GetMCMVisuManagerSagittal()->GetActor(), d->view->layer(d->data), dim);
    d->view2d->SetInput(d->manager->GetMCMVisuManagerCoronal()->GetActor(), d->view->layer(d->data), dim);

    d->actorProperty = animaDataMCMImageVtkViewInteractorPrivate::PropertySmartPointer::New();
    d->manager->GetMCMVisuManagerAxial()->GetActor()->SetProperty( d->actorProperty );
    d->manager->GetMCMVisuManagerSagittal()->GetActor()->SetProperty( d->actorProperty );
    d->manager->GetMCMVisuManagerCoronal()->GetActor()->SetProperty( d->actorProperty );

    setupParameters();
}

void animaDataMCMImageVtkViewInteractor::removeData()
{
    d->view2d->RemoveLayer(d->view->layer(this->inputData()));
    d->manager->Delete();
}

void animaDataMCMImageVtkViewInteractor::setupParameters()
{
    QStringList tesselationTypeList;
    tesselationTypeList << "Icosahedron" << "Octahedron" << "Tetrahedron";
    medStringListParameter *tesselationTypeParam = new medStringListParameter("Tesselation Type", this);
    tesselationTypeParam->addItems(tesselationTypeList);

    //  Control sample rate
    medIntParameter *sampleRateParam = new medIntParameter("Sample Rate", this);
    sampleRateParam->setRange(1,10);
    sampleRateParam->setValue(1);

    //  flipX, flipY, flipZ and Enhance checkboxes
    medBoolParameter *flipXParam = new medBoolParameter("FlipX", this);
    medBoolParameter *flipYParam = new medBoolParameter("FlipY", this);
    medBoolParameter *flipZParam = new medBoolParameter("FlipZ", this);

    // Normalize parameter
    medBoolParameter *enhanceParam = new medBoolParameter("Enhance", this);

    //  Control glyph resolution
    medIntParameter *glyphResolutionParam = new medIntParameter("Resolution", this);
    glyphResolutionParam->setRange(0,10);
    glyphResolutionParam->setValue(2);

    //  Minor scaling
    medIntParameter *minorScalingParam = new medIntParameter("Scale", this);
    minorScalingParam->setRange(1,10);
    minorScalingParam->setValue(1);

    //  Major scaling
    medIntParameter *majorScalingParam = new medIntParameter("x10^", this);
    majorScalingParam->setRange(-10,10);
    majorScalingParam->setValue(0);

    d->parameters.append(tesselationTypeParam);
    d->parameters.append(sampleRateParam);
    d->parameters.append(flipXParam);
    d->parameters.append(flipYParam);
    d->parameters.append(flipZParam);
    d->parameters.append(enhanceParam);
    d->parameters.append(glyphResolutionParam);
    d->parameters.append(minorScalingParam);
    d->parameters.append(majorScalingParam);

    connect(tesselationTypeParam, SIGNAL(valueChanged(QString)), this, SLOT(setTesselationType(QString)));
    connect(sampleRateParam, SIGNAL(valueChanged(int)), this, SLOT(setSampleRate(int)));
    connect(flipXParam, SIGNAL(valueChanged(bool)), this, SLOT(setFlipX(bool)));
    connect(flipYParam, SIGNAL(valueChanged(bool)), this, SLOT(setFlipY(bool)));
    connect(flipZParam, SIGNAL(valueChanged(bool)), this, SLOT(setFlipZ(bool)));
    connect(enhanceParam, SIGNAL(valueChanged(bool)), this, SLOT(setNormalization(bool)));
    connect(glyphResolutionParam, SIGNAL(valueChanged(int)), this, SLOT(setGlyphResolution(int)));
    connect(minorScalingParam, SIGNAL(valueChanged(int)), this, SLOT(setMinorScaling(int)));
    connect(majorScalingParam, SIGNAL(valueChanged(int)), this, SLOT(setMajorScaling(int)));

    if(d->view->layer(d->data) == 0)
    {
        switch(d->view2d->GetViewOrientation())
        {
            case vtkImageView2D::VIEW_ORIENTATION_AXIAL:
                d->view->setOrientation(medImageView::VIEW_ORIENTATION_AXIAL);
                break;
            case vtkImageView2D::VIEW_ORIENTATION_SAGITTAL:
                d->view->setOrientation(medImageView::VIEW_ORIENTATION_SAGITTAL);
                break;
            case vtkImageView2D::VIEW_ORIENTATION_CORONAL:
                d->view->setOrientation(medImageView::VIEW_ORIENTATION_CORONAL);
                break;
        }
    }

    connect(d->slicingParameter, SIGNAL(valueChanged(int)), this, SLOT(moveToSlice(int)));
    connect(d->view->positionBeingViewedParameter(), SIGNAL(valueChanged(QVector3D)), this, SLOT(updateSlicingParam()));
    this->updateWidgets();
}

void animaDataMCMImageVtkViewInteractor::setWindowLevel(QHash<QString,QVariant>)
{
    //TODO
}

void animaDataMCMImageVtkViewInteractor::setOpacity(double opacity)
{
    d->actorProperty->SetOpacity(opacity);

    d->view->render();
}

void animaDataMCMImageVtkViewInteractor::setVisibility(bool visibility)
{
    int v = (visibility) ? 1 : 0;

    d->manager->GetMCMVisuManagerAxial()->GetActor()->SetVisibility(v);
    d->manager->GetMCMVisuManagerSagittal()->GetActor()->SetVisibility(v);
    d->manager->GetMCMVisuManagerCoronal()->GetActor()->SetVisibility(v);

    this->update();
}

void animaDataMCMImageVtkViewInteractor::changeOrientationVisibility()
{
    d->manager->GetMCMVisuManagerAxial()->GetActor()->SetVisibility(0);
    d->manager->GetMCMVisuManagerSagittal()->GetActor()->SetVisibility(0);
    d->manager->GetMCMVisuManagerCoronal()->GetActor()->SetVisibility(0);

    switch(d->view->orientation())
    {
        case medImageView::VIEW_ORIENTATION_AXIAL:
            d->manager->GetMCMVisuManagerAxial()->GetActor()->SetVisibility(1);
            break;
        case medImageView::VIEW_ORIENTATION_SAGITTAL:
            d->manager->GetMCMVisuManagerSagittal()->GetActor()->SetVisibility(1);
            break;
        case medImageView::VIEW_ORIENTATION_CORONAL:
            d->manager->GetMCMVisuManagerCoronal()->GetActor()->SetVisibility(1);
            break;
        case medImageView::VIEW_ORIENTATION_3D:
        default:
            d->manager->GetMCMVisuManagerAxial()->GetActor()->SetVisibility(1);
            d->manager->GetMCMVisuManagerSagittal()->GetActor()->SetVisibility(1);
            d->manager->GetMCMVisuManagerCoronal()->GetActor()->SetVisibility(1);
            break;
    }

    this->update();
}

void animaDataMCMImageVtkViewInteractor::imageSize(int* imSize)
{
    d->manager->GetMCMDimensions(imSize);
}

void animaDataMCMImageVtkViewInteractor::setTesselationType(QString tesselationType)
{
    if(tesselationType == "Icosahedron")
        d->manager->SetTesselationType(Icosahedron);
    else if(tesselationType == "Octahedron")
        d->manager->SetTesselationType(Octahedron);
    if(tesselationType == "Tetrahedron")
        d->manager->SetTesselationType(Tetrahedron);
    update();
}

void animaDataMCMImageVtkViewInteractor::setSampleRate(int sampleRate)
{
    d->manager->SetSampleRate(sampleRate,sampleRate,sampleRate);
    update();
}

void animaDataMCMImageVtkViewInteractor::setGlyphResolution(int glyphResolution)
{
    d->manager->SetGlyphResolution(glyphResolution);
    update();
}

void animaDataMCMImageVtkViewInteractor::setScale(double scale)
{
    d->manager->SetGlyphScale((float)scale);
    update();
}

void animaDataMCMImageVtkViewInteractor::setMajorScaling(int majorScalingExponent)
{
    d->majorScalingExponent = majorScalingExponent;
    setScale(d->minorScaling, d->majorScalingExponent);
}

void animaDataMCMImageVtkViewInteractor::setMinorScaling(int minorScaling)
{
    d->minorScaling = minorScaling;
    setScale(d->minorScaling, d->majorScalingExponent);
}

void animaDataMCMImageVtkViewInteractor::setScale(int minorScale, int majorScaleExponent)
{
    double majorScale = pow(10.0, majorScaleExponent);
    double scale = majorScale * minorScale;
    setScale(scale);
}

void animaDataMCMImageVtkViewInteractor::setFlipX(const bool flipX)
{
    d->manager->FlipX(flipX);
    update();
}

void animaDataMCMImageVtkViewInteractor::setFlipY(const bool flipY)
{
    d->manager->FlipY(flipY);
    update();
}

void animaDataMCMImageVtkViewInteractor::setFlipZ(const bool flipZ)
{
    d->manager->FlipZ(flipZ);
    update();
}

void animaDataMCMImageVtkViewInteractor::setNormalization(const bool Norma)
{
    d->manager->SetNormalization(Norma);
    update();
}

void animaDataMCMImageVtkViewInteractor::setPosition(const QVector3D& position)
{
    d->manager->SetCurrentPosition(position.x(),position.y(),position.z());
    update();
}

void animaDataMCMImageVtkViewInteractor::setUpViewForThumbnail()
{
    d->view2d->Reset();
    d->view2d->SetBackground(0.0, 0.0, 0.0);
    d->view2d->CursorFollowMouseOff();
    d->view2d->ShowImageAxisOff();
    d->view2d->ShowScalarBarOff();
    d->view2d->ShowAnnotationsOff();
    d->view2d->ShowRulerWidgetOff();
}

void animaDataMCMImageVtkViewInteractor::moveToSlice(int slice)
{
    if(d->view->is2D() && slice != d->view2d->GetSlice())
    {
        d->view2d->SetSlice(slice);
        d->view2d->Render();
    }
}

QWidget* animaDataMCMImageVtkViewInteractor::buildLayerWidget()
{
    this->opacityParameter()->getSlider()->setOrientation(Qt::Horizontal);
    return this->opacityParameter()->getSlider();
}

QWidget* animaDataMCMImageVtkViewInteractor::buildToolBoxWidget()
{
    QWidget *toolbox = new QWidget;
    QFormLayout *layout = new QFormLayout(toolbox);
    foreach(medAbstractParameter *parameter, d->parameters)
        layout->addRow(parameter->getLabel(), parameter->getWidget());

    return toolbox;
}

QWidget* animaDataMCMImageVtkViewInteractor::buildToolBarWidget()
{
    d->slicingParameter->getSlider()->setOrientation(Qt::Horizontal);
    return d->slicingParameter->getSlider();
}

QList<medAbstractParameter*> animaDataMCMImageVtkViewInteractor::linkableParameters()
{
    QList <medAbstractParameter*> linkableParams = d->parameters;
    linkableParams << this->visibilityParameter() << this->opacityParameter();
    return linkableParams;
}

QList<medBoolParameter*> animaDataMCMImageVtkViewInteractor::mouseInteractionParameters()
{
    // no parameters related to mouse interactions
    return QList<medBoolParameter*>();
}

void animaDataMCMImageVtkViewInteractor::update()
{
    d->view->render();
}

void animaDataMCMImageVtkViewInteractor::updateWidgets()
{
    if(!d->view->is2D())
        d->slicingParameter->getSlider()->setEnabled(false);
    else
    {
        d->slicingParameter->getSlider()->setEnabled(true);
        this->updateSlicingParam();
    }
}

void animaDataMCMImageVtkViewInteractor::updateSlicingParam()
{
    if(!d->view->is2D())
        return;

    d->slicingParameter->blockSignals(true);
    d->slicingParameter->setRange(d->view2d->GetSliceMin(), d->view2d->GetSliceMax());
    d->slicingParameter->blockSignals(false);

    d->slicingParameter->setValue(d->view2d->GetSlice());
}
