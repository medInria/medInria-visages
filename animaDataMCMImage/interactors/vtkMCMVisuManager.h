#pragma once

#include <animaDataMCMImagePluginExport.h>
#include <animaMultiCompartmentModel.h>

#include <vtkMCMSource.h>

class vtkMCMSource;
class vtkMCMGlyph;
class vtkExtractVOI;
class vtkPolyDataMapper;
class vtkActor;
class vtkImageData;

class ANIMADATAMCMIMAGEPLUGIN_EXPORT vtkMCMVisuManager : public vtkObject
{
public:
    static vtkMCMVisuManager *New();
    vtkTypeMacro(vtkMCMVisuManager, vtkObject);

    void SetGlyphScale (const float& scale);

    /** Get the Polyhedron type to be tesselated */

    void SetTesselationType (const int& type);

    /** Set the Polyhedron type to be tesselated */

    int GetTesselationType() const
    { return this->MCMSource->GetTesselationType(); }

    void SetGlyphResolution (const int&);
    void SetSampleRate (const int&,const int&, const int&);

    void FlipX (const int&);
    void FlipY (const int&);
    void FlipZ (const int&);

    void SetNormalization (const int& a);

    /** Set the Volume Of Interest (VOI). Consists in
      * 6 integers: xmin, xmax, ymin, ymax, zmin, zmax.*/
    void SetVOI(const int&,const int&,const int&,const int&,const int&,const int&);

    void SetInput (vtkImageData*);

    typedef anima::MultiCompartmentModel MCModelType;
    typedef MCModelType::Pointer MCModelPointer;
    void SetReferenceMCM(MCModelPointer &model);

    /** Get the object that computes the MCM glyph*/
    vtkGetObjectMacro (MCMSource, vtkMCMSource);

    /** Get the object that controls the display the MCM glyph*/
    vtkGetObjectMacro (MCMGlyph, vtkMCMGlyph);

    /** Get the VOI to be displayed as MCM glyph*/
    vtkGetObjectMacro (VOI, vtkExtractVOI);

    /** Get the normals used to display the MCM glyph*/
    vtkGetObjectMacro (Mapper, vtkPolyDataMapper);

    vtkGetObjectMacro (Actor, vtkActor);

    /** Set into the slice VisuManager the transformation matrix that is used
      * to display the glyphs according to the image coordinate system*/
    vtkSetObjectMacro (MatrixT, vtkMatrix4x4);

    /** Get from the slice VisuManager the transformation matrix that is used
      * to display the glyphs according to the image coordinate system*/
    vtkGetObjectMacro (MatrixT, vtkMatrix4x4);

protected:
    vtkMCMVisuManager();
    ~vtkMCMVisuManager();

private:   
    vtkMCMSource* MCMSource;
    vtkMCMGlyph*  MCMGlyph;
    vtkExtractVOI* VOI;
    vtkPolyDataMapper* Mapper;
    vtkActor* Actor;

    vtkMatrix4x4* MatrixT;
};
