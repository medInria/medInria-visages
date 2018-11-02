#include <vtkMCMVisuManager.h>

#include <vtkMCMGlyph.h>
#include <vtkExtractVOI.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

#include <vtkImageData.h>
#include <vtkLookupTable.h>
#include <vtkProperty.h>

vtkStandardNewMacro(vtkMCMVisuManager);

vtkMCMVisuManager::vtkMCMVisuManager()
{
    MCMSource = vtkMCMSource::New();
    MCMGlyph  = vtkMCMGlyph::New();
    VOI    = vtkExtractVOI::New();
    Mapper = vtkPolyDataMapper::New();
    Actor  = vtkActor::New();

    MCMSource->SetTesselationType(vtkMCMSource::Icosahedron);
    MCMSource->SetTesselation(2);
    MCMSource->SetRadius(0.05);
    MCMSource->SetNormalization(false);
    MCMSource->UpdateMCMSource();

    MCMGlyph->SetSourceConnection(MCMSource->GetOutputPort());
    MCMGlyph->SetScaleFactor(1.0);
    MCMGlyph->SetMCMSource(MCMSource);
    MCMGlyph->GetOutput()->GetPointData()->SetActiveScalars(vtkMCMGlyph::GetRGBArrayName());

    VOI->ReleaseDataFlagOn();

    MCMGlyph->SetInputConnection(VOI->GetOutputPort());

    vtkLookupTable *lut = vtkLookupTable::New();
    //lut->SetHueRange(0.667, 0.0);
    lut->SetHueRange(0.0, 1.0);
    lut->SetRange(0.0, 1.0);
    lut->Build();

    Mapper->SetInputConnection(MCMGlyph->GetOutputPort());
    Mapper->ScalarVisibilityOn();
    Mapper->SetColorModeToMapScalars();
    Mapper->SetScalarModeToUsePointData();
    Mapper->SetLookupTable(lut);

    Mapper->SetScalarRange (0.0, 256);

    lut->Delete();

    MatrixT=0;

    Actor->SetMapper(Mapper);
    Actor->GetProperty()->SetSpecular(0.7);
    Actor->GetProperty()->SetSpecularPower(10.0);
    Actor->GetProperty()->SetInterpolationToGouraud();
    Actor->GetProperty()->SetOpacity(1);
}

vtkMCMVisuManager::~vtkMCMVisuManager()
{
    if (MCMGlyph)
        MCMGlyph->Delete();
    if (MCMSource)
        MCMSource->Delete();
    if (VOI)
        VOI->Delete();
    if (Mapper)
        Mapper->Delete();
    if (Actor)
        Actor->Delete();
    if (MatrixT)
        MatrixT->Delete();
}

void vtkMCMVisuManager::SetInput (vtkImageData* vtkMCM)
{
    MCMGlyph->SetTMatrix(MatrixT);

    if (!vtkMCM)
        return;

    VOI->SetInputData (vtkMCM);
    VOI->Update();
}

void vtkMCMVisuManager::SetVOI(const int& imin, const int& imax,
                               const int& jmin, const int& jmax,
                               const int& kmin, const int& kmax)
{
    VOI->SetVOI(imin,imax,jmin,jmax,kmin,kmax);
}

void vtkMCMVisuManager::SetGlyphScale (const float& scale)
{
    MCMGlyph->SetScaleFactor(scale);
}

void vtkMCMVisuManager::SetRadius(const double& value)
{
    MCMSource->SetRadius(value);
    MCMSource->UpdateMCMSource();
}

void vtkMCMVisuManager::SetTesselationType (const int& type)
{
    MCMSource->SetTesselationType (type);
    MCMSource->UpdateMCMSource();
}

void vtkMCMVisuManager::SetGlyphResolution (const int& res)
{
    MCMSource->SetTesselation(res);
    MCMSource->UpdateMCMSource();
}

void vtkMCMVisuManager::SetSampleRate (const int& n1,const int& n2,const int& n3)
{
    VOI->SetSampleRate(n1,n2,n3);
}

void vtkMCMVisuManager::FlipX (const int& a)
{
    bool* flip = MCMSource->GetFlipVector();
    flip[0] = a;
    MCMSource->SetFlipVector(flip);
    MCMSource->UpdateMCMSource();
}

void vtkMCMVisuManager::FlipY (const int& a)
{
    bool* flip = MCMSource->GetFlipVector();
    flip[1] = a;
    MCMSource->SetFlipVector(flip);
    MCMSource->UpdateMCMSource();
}

void vtkMCMVisuManager::FlipZ (const int& a)
{
    bool* flip = MCMSource->GetFlipVector();
    flip[2] = a;
    MCMSource->SetFlipVector(flip);
    MCMSource->UpdateMCMSource();
}

void vtkMCMVisuManager::SetNormalization (const int& a)
{
    MCMSource->SetNormalization(a);
}

void vtkMCMVisuManager::SetReferenceMCM(MCModelPointer &model)
{
    MCMSource->SetReferenceMCM(model);
}
