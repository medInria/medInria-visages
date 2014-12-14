#include <vtkMCMManager.h>
#include <vtkObjectFactory.h>

vtkCxxRevisionMacro(vtkMCMManager, "$Revision: 477 $");
vtkStandardNewMacro(vtkMCMManager);

vtkMCMManager::vtkMCMManager()
{
    RenderWindowInteractor = 0;

    Input = 0;
    MatrixT = 0;
    Renderer = 0;

    MCMVisuManagerAxial = vtkMCMVisuManager::New();
    MCMVisuManagerSagittal = vtkMCMVisuManager::New();
    MCMVisuManagerCoronal = vtkMCMVisuManager::New();

    for(int i=0;i<3;++i)
        CurrentPosition[i] = 0;
}

vtkMCMManager::~vtkMCMManager()
{
    this->Initialize();

    if (RenderWindowInteractor)
        RenderWindowInteractor->Delete();

    if (Input)
        Input->Delete();

    if (MatrixT)
        MatrixT->Delete();

    if (MCMVisuManagerAxial)
        MCMVisuManagerAxial->Delete();

    if (MCMVisuManagerSagittal)
        MCMVisuManagerSagittal->Delete();

    if (MCMVisuManagerCoronal)
        MCMVisuManagerCoronal->Delete();
}

void vtkMCMManager::SetRenderWindowInteractor(vtkRenderWindowInteractor* rwin,vtkRenderer* ren)
{
    if (rwin!=RenderWindowInteractor)
    {
        if (RenderWindowInteractor!=NULL)
        {
            Initialize();
            RenderWindowInteractor->UnRegister(this);
        }

        RenderWindowInteractor = rwin;
        if (RenderWindowInteractor)
            RenderWindowInteractor->Register(this);
    }

    if (ren)
    {
        Renderer = ren;
        return;
    }

    if (RenderWindowInteractor)
    {
        RenderWindowInteractor->GetRenderWindow()->GetRenderers()->InitTraversal();
        vtkRenderer* first_renderer = RenderWindowInteractor->GetRenderWindow()->GetRenderers()->GetNextItem();

        int numLayers = RenderWindowInteractor->GetRenderWindow()->GetNumberOfLayers();
        RenderWindowInteractor->GetRenderWindow()->SetNumberOfLayers(numLayers + 1);

        Renderer = vtkRenderer::New();
        Renderer->SetLayer(numLayers);
        if (first_renderer)
            Renderer->SetActiveCamera(first_renderer->GetActiveCamera());

        RenderWindowInteractor->GetRenderWindow()->AddRenderer(Renderer);

        Renderer->Delete();
    }
}

void vtkMCMManager::Initialize()
{
    if (Renderer && RenderWindowInteractor)
    {
        Renderer->RemoveActor(MCMVisuManagerAxial->GetActor());
        Renderer->RemoveActor(MCMVisuManagerSagittal->GetActor());
        Renderer->RemoveActor(MCMVisuManagerCoronal->GetActor());
    }
}

void vtkMCMManager::Update()
{
    if (!Input || !RenderWindowInteractor)
        return;

    Initialize();
    int* dims = Input->GetDimensions();

    const int X = clamp(CurrentPosition[0],dims[0]);
    const int Y = clamp(CurrentPosition[1],dims[1]);
    const int Z = clamp(CurrentPosition[2],dims[2]);

    MCMVisuManagerAxial->SetMatrixT(MatrixT);
    MCMVisuManagerSagittal->SetMatrixT(MatrixT);
    MCMVisuManagerCoronal->SetMatrixT(MatrixT);

    // synchronize with VOI
    MCMVisuManagerSagittal->SetVOI(X, X, 0, dims[1]-1, 0, dims[2]-1);
    MCMVisuManagerCoronal->SetVOI(0, dims[0]-1, Y, Y, 0, dims[2]-1);
    MCMVisuManagerAxial->SetVOI(0, dims[0]-1, 0, dims[1]-1, Z, Z);

    // finally set the data
    MCMVisuManagerAxial->SetInput(Input);
    MCMVisuManagerSagittal->SetInput(Input);
    MCMVisuManagerCoronal->SetInput(Input);

    if (Renderer)
    {
        Renderer->AddActor(MCMVisuManagerAxial->GetActor());
        Renderer->AddActor(MCMVisuManagerSagittal->GetActor());
        Renderer->AddActor(MCMVisuManagerCoronal->GetActor());
    }
}

void vtkMCMManager::SetCurrentPosition(const int& X, const int& Y, const int& Z)
{
    if (!Input)
        return;

    int* dims = Input->GetDimensions();

    // clamping

    const int XX = clamp(X,dims[0]);
    const int YY = clamp(Y,dims[1]);
    const int ZZ = clamp(Z,dims[2]);

    // synchronize with VOI
    MCMVisuManagerSagittal->SetVOI(XX, XX, 0, dims[1]-1, 0, dims[2]-1);
    MCMVisuManagerCoronal->SetVOI(0, dims[0]-1, YY, YY, 0, dims[2]-1);
    MCMVisuManagerAxial->SetVOI(0, dims[0]-1, 0, dims[1]-1, ZZ, ZZ);

    CurrentPosition[0] = X;
    CurrentPosition[1] = Y;
    CurrentPosition[2] = Z;
}

void vtkMCMManager::SetCurrentPosition(const int pos[3])
{
    SetCurrentPosition(pos[0], pos[1], pos[2]);
}

void vtkMCMManager::ResetPosition()
{
    if (!Input)
        return;

    int* dims = Input->GetDimensions();

    const int X = dims[0]/2;
    const int Y = dims[1]/2;
    const int Z = dims[2]/2;

    SetCurrentPosition(X,Y,Z);
}

void vtkMCMManager::SetSampleRate(const int& n1,const int& n2, const int& n3)
{
    MCMVisuManagerAxial->SetSampleRate(n1, n2, n3);
    MCMVisuManagerSagittal->SetSampleRate(n1, n2, n3);
    MCMVisuManagerCoronal->SetSampleRate(n1, n2, n3);
}

void vtkMCMManager::SetGlyphResolution(const int res)
{
    MCMVisuManagerAxial->SetGlyphResolution(res);
    MCMVisuManagerSagittal->SetGlyphResolution(res);
    MCMVisuManagerCoronal->SetGlyphResolution(res);
}

void vtkMCMManager::SetTesselationType(const int& type)
{
    MCMVisuManagerAxial->SetTesselationType(type);
    MCMVisuManagerSagittal->SetTesselationType(type);
    MCMVisuManagerCoronal->SetTesselationType(type);
}

void vtkMCMManager::FlipX(const bool a)
{
    MCMVisuManagerAxial->FlipX(a);
    MCMVisuManagerSagittal->FlipX(a);
    MCMVisuManagerCoronal->FlipX(a);
}

void vtkMCMManager::FlipY(const bool a)
{
    MCMVisuManagerAxial->FlipY(a);
    MCMVisuManagerSagittal->FlipY(a);
    MCMVisuManagerCoronal->FlipY(a);
}

void vtkMCMManager::FlipZ(const bool a)
{
    MCMVisuManagerAxial->FlipZ(a);
    MCMVisuManagerSagittal->FlipZ(a);
    MCMVisuManagerCoronal->FlipZ(a);
}

void vtkMCMManager::SetNormalization(const bool a)
{
    MCMVisuManagerAxial->SetNormalization(a);
    MCMVisuManagerSagittal->SetNormalization(a);
    MCMVisuManagerCoronal->SetNormalization(a);
}

void vtkMCMManager::GetMCMDimensions(int * dims)
{
    if (Input!=0)
        Input->GetDimensions(dims);
}

void vtkMCMManager::SetAxialSliceVisibility(const int i)
{
    MCMVisuManagerAxial->GetActor()->SetVisibility(i);
}

void vtkMCMManager::SetSagittalSliceVisibility(const int i)
{
    MCMVisuManagerSagittal->GetActor()->SetVisibility(i);
}

void vtkMCMManager::SetCoronalSliceVisibility(const int i)
{
    MCMVisuManagerCoronal->GetActor()->SetVisibility(i);
}

void vtkMCMManager::SetGlyphScale(const float& scale)
{
    MCMVisuManagerAxial->SetGlyphScale(scale);
    MCMVisuManagerSagittal->SetGlyphScale(scale);
    MCMVisuManagerCoronal->SetGlyphScale(scale);
}
