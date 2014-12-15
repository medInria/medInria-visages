#pragma once

#include <animaDataMCMImagePluginExport.h>

#include <vtkObject.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkImageData.h>
#include <vtkLookupTable.h>

#include <vtkMCMVisuManager.h>

class ANIMADATAMCMIMAGEPLUGIN_EXPORT vtkMCMManager: public vtkObject
{
public:
    static vtkMCMManager *New();
    vtkTypeRevisionMacro(vtkMCMManager, vtkObject);

    void SetRenderWindowInteractor(vtkRenderWindowInteractor*, vtkRenderer* ren=0);
    vtkGetObjectMacro(RenderWindowInteractor, vtkRenderWindowInteractor);

    vtkSetObjectMacro(Input, vtkImageData);
    vtkGetObjectMacro(Input, vtkImageData);

    void SetDirectionMatrix(vtkMatrix4x4 *mat);
    vtkGetObjectMacro (DirectionMatrix, vtkMatrix4x4);

    vtkGetObjectMacro(MCMVisuManagerAxial, vtkMCMVisuManager);
    vtkGetObjectMacro(MCMVisuManagerSagittal, vtkMCMVisuManager);
    vtkGetObjectMacro(MCMVisuManagerCoronal, vtkMCMVisuManager);

    /** Set a scaling factor for the glyphs. */
    void SetGlyphScale(const float& f);

    /** Set the sample rate 1 over n MCM will be
     *  displayed.*/
    void SetSampleRate(const int&,const int&,const int&);

    /** Set the glyph resolution */
    void SetGlyphResolution(const int res);

    /** Set the Polyhedron type to be tesselated */
    void SetTesselationType(const int& type);

    /** Flip Spherical Harmonic's along the X axis */
    void FlipX(const bool a);

    /** Flip Spherical Harmonic's along the Y axis */
    void FlipY(const bool a);

    /** Flip Spherical Harmonic's along the Z axis */
    void FlipZ(const bool a);

    void SetNormalization(const bool a);

    /** get the image size it is used to set med gui slider appropiate size*/
    void GetMCMDimensions(int * dims);

    /** Generate the glyph and add them to the RenderWindowInteractor */
    void Update();

    /** Remove the actors from the renderer. */
    void Initialize();

    /** Set the current position in voxel coordinates. */
    void SetCurrentPosition(const int&, const int&, const int&);

    /** Set the current position in voxel coordinates. */
    void SetCurrentPosition(const int pos[3]);

    /** Set the current position in physical coordinates. */
    void SetCurrentPosition(const double& X, const double& Y, const double& Z);

    /** Set the current position in physical coordinates. */
    void SetCurrentPosition(double pos[3]);

    /** Get the current position. */
    const int* GetCurrentPosition() const { return this->CurrentPosition; }

    /** Get the current position. */
    void GetCurrentPosition(int pos[3]) const {
        for(int i=0;i<3;++i)
            pos[i] = this->CurrentPosition[i];
    }

    /** Reset the position to the center of the dataset. */
    void ResetPosition();

    /** Set the Axial/Coronal/Sagittal slice visibility on or off. */
    void SetAxialSliceVisibility(const int);

    /** Set the Axial/Coronal/Sagittal slice visibility on or off. */
    void SetSagittalSliceVisibility(const int);

    /** Set the Axial/Coronal/Sagittal slice visibility on or off. */
    void SetCoronalSliceVisibility(const int);

protected:
    vtkMCMManager();
    ~vtkMCMManager();

private:
    static int clamp(const int value,const int bound) {
        return (value>bound-1) ? (bound-1) : value;
    }

    vtkRenderWindowInteractor* RenderWindowInteractor;

    vtkImageData* Input;
    vtkMatrix4x4 *DirectionMatrix;
    vtkMatrix4x4 *PhysicalToVoxelCoordinatesTransformMatrix;

    vtkRenderer* Renderer;

    vtkMCMVisuManager* MCMVisuManagerAxial;
    vtkMCMVisuManager* MCMVisuManagerSagittal;
    vtkMCMVisuManager* MCMVisuManagerCoronal;

    int CurrentPosition[3];
};
