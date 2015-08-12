#pragma once
#include <animaDataMCMImagePluginExport.h>

#include <vtkPolyDataAlgorithm.h>
#include <vtkMatrix4x4.h>

#include <itkVariableSizeMatrix.h>
#include <itkVector.h>
#include <vtkTessellatedSphereSource.h>

#include <animaMultiCompartmentModel.h>

class vtkMatrix4x4;

class ANIMADATAMCMIMAGEPLUGIN_EXPORT vtkMCMSource: public vtkPolyDataAlgorithm
{
public:
    vtkTypeRevisionMacro(vtkMCMSource,vtkPolyDataAlgorithm);
    void PrintSelf(ostream& os,vtkIndent indent);

    static vtkMCMSource* New();

    vtkSetMacro(Tesselation,int);
    vtkGetMacro(Tesselation,int);
    
    int *GetTesselationRange();
    void GetTesselationRange(int *);
    
    /** Set Type of tesselation : cube, dodecahedron, icosahedron, octahedron, tetrahedron
      * determines the angular sampling scheme*/
    vtkSetMacro(TesselationType,int);

    /** Get Type of tesselation : cube, dodecahedron, icosahedron, octahedron, tetrahedron
      * determines the angular sampling scheme*/
    vtkGetMacro(TesselationType,int);

    enum
    {
        Icosahedron=0,
        Dodecahedron,
        Octahedron ,
        Cube,
        Tetrahedron
    } TesselationMode;

    typedef anima::MultiCompartmentModel MCModelType;
    typedef MCModelType::ModelOutputVectorType MCModelVectorType;
    typedef MCModelType::Pointer MCModelPointer;

    void SetReferenceMCM(MCModelPointer &model) {referenceMCM = model;}
    void SetMCMData(MCModelVectorType &coeff);
    
    vtkSetClampMacro(Radius,double,0.0,VTK_DOUBLE_MAX);
    vtkGetMacro(Radius,double);

    vtkSetVector3Macro(Center,double);
    vtkGetVectorMacro(Center,double,3);
    
    /** Set Normalization On/Off
      *  If On, spherical values are (0,1) Normalized*/

    vtkSetMacro(Normalization,bool);

    /** Set Normalization On/Off
      *  If On, spherical values are (0,1) Normalized*/

    vtkBooleanMacro(Normalization,bool);

    /** Get Normalization On/Off
      *  If On, spherical values are (0,1) Normalized*/

    vtkGetMacro(Normalization,bool);

    /** Set FlipVector On/Off If On, x direction is flipped in the
      * reconstruction directions defining the basis function*/
    vtkSetVector3Macro(FlipVector,const bool);

    /** Get FlipVector On/Off If On, x direction is flipped in the reconstruction
      * directions defining the basis function*/
    vtkGetVector3Macro(FlipVector,bool);

    /** Set the rotation matrix that defines the individual tesselated deformed
      *  sphere pose. virtual*/
    void SetRotationMatrix (vtkMatrix4x4 *mat);

    /** Get the rotation matrix that defines the individual tesselated deformed
      *  sphere pose. virtual*/
    vtkGetObjectMacro(RotationMatrix,vtkMatrix4x4);

    void UpdateMCMSource();

    static void TranslateAndDeformShell(vtkPolyData* shell,vtkPoints* outPts,double center[3],
                                        vtkMatrix4x4* transform=0);
    
protected:
     vtkMCMSource(const int tess=2);
    ~vtkMCMSource();
    
    int RequestData(vtkInformation*,vtkInformationVector**,vtkInformationVector*);
    int RequestInformation(vtkInformation*,vtkInformationVector**,vtkInformationVector*);

    double Radius;
    double Center[3];
    
    vtkTessellatedSphereSource *sphereT;

    /** MCM representation */

    MCModelVectorType MCMData;
    MCModelPointer referenceMCM;

    /** Type of tesselation : cube, dodecahedron, icosahedron, octahedron, tetrahedron
      * determines the angular sampling scheme*/
    int TesselationType;

    /** Tesselation order, determines the angular sampling*/
    int Tesselation;
    
    /** FlipVector {X,Y,Z} On/Off
      * If On, the correponding direction is flipped in the reconstruction directions defining
      * the basis function By default we need to flip Z to have glyphs correctly aligned.      */
    bool FlipVector[3];

    bool Normalization;

    vtkMatrix4x4 *RotationMatrix;
    vtkMatrix4x4 *InverseRotationMatrix;

private:
    vtkMCMSource(const vtkMCMSource&);  // Not implemented.
    void operator=(const vtkMCMSource&);  // Not implemented.
};


