/*
 ** SPlineImage.hh
 ** Login : <nwiestda@pallium.irisa.fr>
 ** Started on  Tue Feb 26 16:13:58 2008 Nicolas Wiest-Daessle
 ** $Id$
 **
 ** Copyright (C) 2008 Nicolas Wiest-Daessle
 ** This program is free software; you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program; if not, write to the Free Software
 ** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef   	SPLINEIMAGE_HH_
# define   	SPLINEIMAGE_HH_

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include "Image3D.hh"


// Represents a 3D volume as a continous field using Spline
// interpolation, template parameter indicate the "degree" at wich the
// spline is to be represented
//
// Value are truncated between min and max of the input image
// Spline coefficients are represented as floating point values
// It does not sub-class image data types
// No iterators or image decoration is provided
// Image support size is non existing


enum ClampOption        { NoClamp, ClampMin, ClampMax, ClampBoth };
enum BoundaryCondition  { Zero, Mirror };

template <unsigned int SplineDegree = 3,
BoundaryCondition bound = Zero,
ClampOption clamp = NoClamp, bool ShiftedInterpolation = false>
class SPlineImage3D
{
        vistal::Image3D<float> coeffs;
        float VMin, VMax; // Min and Max values of input data

        static const double BasisShift = 0.2113248654051871177454256097490212721761991243649365619906988367580;//(.5-sqrt(1.0 / 12.0));

        template <class DataType>
        void GetX(vistal::Image3D<DataType>& ima, int i, int j, float* v)
        {
                for (int z = 0; z < ima.nbx; ++z)
                {
                        v[z] = ima(z, i, j);
                        if (v[z] < VMin) VMin = v[z];
                        else if (v[z] > VMax) VMax = v[z];
                }
        }
        template <class DataType>
        void SetX(vistal::Image3D<DataType>& ima, int i, int j, float* v)
        {
                for (int z = 0; z < ima.nbx; ++z)
                        ima(z, i, j) = v[z];
        }

        template <class DataType>
        void GetY(vistal::Image3D<DataType>& ima, int i, int j, float* v)
        {
                for (int z = 0; z < ima.nby; ++z)
                {
                        v[z] = ima(i, z, j);
                        if (v[z] < VMin) VMin = v[z];
                        else if (v[z] > VMax) VMax = v[z];
                }
        }


        template <class DataType>
        void SetY(vistal::Image3D<DataType>& ima, int i, int j, float* v)
        {
                for (int z = 0; z < ima.nby; ++z)
                        ima(i, z, j) = v[z];
        }

        template <class DataType>
        void GetZ(vistal::Image3D<DataType>& ima, int i, int j, float* v)
        {
                for (int z = 0; z < ima.nbz; ++z)
                {
                        v[z] = ima(i,j, z);
                        if (v[z] < VMin) VMin = v[z];
                        else if (v[z] > VMax) VMax = v[z];
                }
        }

        template <class DataType>
        void SetZ(vistal::Image3D<DataType>& ima, int i, int j, float* v)
        {
                for (int z = 0; z < ima.nbz; ++z)
                        ima(i, j, z) = v[z];

        }

public:
        // Constructor, just uses the input image as a coefficient
        // definition image
        template <class DataType>
        SPlineImage3D(vistal::Image3D<DataType>& ima): coeffs(ima, 0), VMin(std::numeric_limits<float>::max()), VMax(-VMin)
        {
                // Static Assert
                BOOST_STATIC_ASSERT(SplineDegree <= 9);
                BOOST_STATIC_ASSERT(SplineDegree > 0);

                // avoid ill posed cases
                assert(ima.nbx > 1);
                assert(ima.nby > 1);
                assert(ima.nbz > 1);


                // do the sample to coefficient thing
                float *Line;
                float Pole[4];
                int  NbPoles = 0;
                // Thanks to compiler optimisation non usefull data get removed
                switch (SplineDegree)
                {
                        case 2:
                                NbPoles = 1;
                                Pole[0] = sqrt(8.0) - 3.0;
                                break;
                        case 3:
                                NbPoles = 1;
                                Pole[0] = sqrt(3.0) - 2.0;
                                break;
                        case 4:
                                NbPoles = 2;
                                Pole[0] = sqrt(664.0 - sqrt(438976.0)) + sqrt(304.0) - 19.0;
                                Pole[1] = sqrt(664.0 + sqrt(438976.0)) - sqrt(304.0) - 19.0;
                                break;
                        case 5:
                                NbPoles = 2;
                                Pole[0] = sqrt(135.0 / 2.0 - sqrt(17745.0 / 4.0)) + sqrt(105.0 / 4.0)
                                - 13.0 / 2.0;
                                Pole[1] = sqrt(135.0 / 2.0 + sqrt(17745.0 / 4.0)) - sqrt(105.0 / 4.0)
                                - 13.0 / 2.0;
                                break;
                        case 6:
                                NbPoles = 3;
                                Pole[0] = -0.48829458930304475513011803888378906211227916123938;
                                Pole[1] = -0.081679271076237512597937765737059080653379610398148;
                                Pole[2] = -0.0014141518083258177510872439765585925278641690553467;
                                break;
                        case 7:
                                NbPoles = 3;
                                Pole[0] = -0.53528043079643816554240378168164607183392315234269;
                                Pole[1] = -0.12255461519232669051527226435935734360548654942730;
                                Pole[2] = -0.0091486948096082769285930216516478534156925639545994;
                                break;
                        case 8:
                                NbPoles = 4;
                                Pole[0] = -0.57468690924876543053013930412874542429066157804125;
                                Pole[1] = -0.16303526929728093524055189686073705223476814550830;
                                Pole[2] = -0.023632294694844850023403919296361320612665920854629;
                                Pole[3] = -0.00015382131064169091173935253018402160762964054070043;
                                break;
                        case 9:
                                NbPoles = 4;
                                Pole[0] = -0.60799738916862577900772082395428976943963471853991;
                                Pole[1] = -0.20175052019315323879606468505597043468089886575747;
                                Pole[2] = -0.043222608540481752133321142979429688265852380231497;
                                Pole[3] = -0.0021213069031808184203048965578486234220548560988624;
                                break;
                }

                Line = new float[std::max(ima.nbx, std::max(ima.nby, ima.nbz))];
                // First compute along X
                for (int i = 0; i < ima.nby; ++i)
                        for (int j = 0; j < ima.nbz; ++j)
                        {
                                GetX(ima, i, j, Line);
                                convertToInterpolationCoefficients(Line, ima.nbx, Pole, NbPoles, 10*std::numeric_limits<float>::min());
                                SetX(coeffs, i, j, Line);
                        }
                // then Y
                for (int i = 0; i < ima.nbx; ++i)
                        for (int j = 0; j < ima.nbz; ++j)
                        {
                                GetY(ima, i, j, Line);
                                convertToInterpolationCoefficients(Line, ima.nby, Pole, NbPoles, 10*std::numeric_limits<float>::min());
                                SetY(coeffs, i, j, Line);
                        }
                // then Z
                for (int i = 0; i < ima.nbx; ++i)
                        for (int j = 0; j < ima.nby; ++j)
                        {
                                GetZ(ima, i, j, Line);
                                convertToInterpolationCoefficients(Line, ima.nbz, Pole, NbPoles, 10*std::numeric_limits<float>::min());
                                SetZ(coeffs, i, j, Line);
                        }
                delete[] Line;
        }

        inline float mad(float x, float y, float z)
        {
                return x*y+z;
        }
        inline float lerp(const float a, const float b, const float t)
        {
                return mad(b-a, t, a);
        }

        float operator()(float x, float y, float z)
        {
                double xWeight[SplineDegree+1], yWeight[SplineDegree+1], zWeight[SplineDegree+1];
                float w, w2, w4, t, t0, t1;
                int xIndex[SplineDegree+1], yIndex[SplineDegree+1], zIndex[SplineDegree+1];
                int nbX2 = 2*coeffs.nbx-2, nbY2 = 2*coeffs.nby-2, nbZ2 = 2*coeffs.nbz-2;

                if (ShiftedInterpolation)
                {
                        x -= BasisShift;
                        y -= BasisShift;
                        z -= BasisShift;
                }


#if 1
                if (SplineDegree == 3)
                {

///			   typedef float v4sf __attribute__ ((vector_size(4)));
        //			const float arr[] = {x,y,z, 0};

                                const float indexX = floor(x);
                                const float indexY = floor(y);
                                const float indexZ = floor(z);

//			v4sf index =  __builtin_ia32_loadsss(arr);

                                const float fractionx = x - indexX;
                                const float fractiony = y - indexY;
                                const float fractionz = z - indexZ;

                                float w0x, w0y, w0z, w1x, w1y, w1z, w2x, w2y, w2z, w3x, w3y, w3z;

                                const float one_fracx = 1.0f - fractionx;
                                const float one_fracy = 1.0f - fractiony;
                                const float one_fracz = 1.0f - fractionz;

                                w0x = 1.0f/6.0f * one_fracx*one_fracx*one_fracx;
                                w0y = 1.0f/6.0f * one_fracy*one_fracy*one_fracy;
                                w0z = 1.0f/6.0f * one_fracz*one_fracz*one_fracz;

                                w1x = 2.0f/3.0f - 0.5f * fractionx*fractionx*(2.0f-fractionx);
                                w1y = 2.0f/3.0f - 0.5f * fractiony*fractiony*(2.0f-fractiony);
                                w1z = 2.0f/3.0f - 0.5f * fractionz*fractionz*(2.0f-fractionz);

                                w2x = 2.0f/3.0f - 0.5f * one_fracx*one_fracx*(2.0f-one_fracx);
                                w2y = 2.0f/3.0f - 0.5f * one_fracy*one_fracy*(2.0f-one_fracy);
                                w2z = 2.0f/3.0f - 0.5f * one_fracz*one_fracz*(2.0f-one_fracz);

                                w3x = 1.0f/6.0f * fractionx*fractionx*fractionx;
                                w3y = 1.0f/6.0f * fractiony*fractiony*fractiony;
                                w3z = 1.0f/6.0f * fractionz*fractionz*fractionz;


                                const float g0x = w0x + w1x;
                                const float g0y = w0y + w1y;
                                const float g0z = w0z + w1z;


                                const float g1x = w2x + w3x;
                                const float g1y = w2y + w3y;
                                const float g1z = w2z + w3z;

                                const float h0x = (w1x / g0x) - 0.f + indexX;
                                const float h0y = (w1y / g0y) - 0.f + indexY;
                                const float h0z = (w1z / g0z) - 0.f + indexZ;

                                const float h1x = (w3x / g1x) + 1.f + indexX;
                                const float h1y = (w3y / g1y) + 1.f + indexY;
                                const float h1z = (w3z / g1z) + 1.f + indexZ;
                                // fetch the eight linear interpolations
                                // weighting and fetching is interleaved for performance and stability reasons
                                float tex000 = coeffs.isInside(h0x, h0y, h0z) ? coeffs(h0x, h0y, h0z) : 0;
                                float tex100 = coeffs.isInside(h1x, h0y, h0z) ? coeffs(h1x, h0y, h0z) : 0;


                                tex000 = lerp(tex100, tex000, g0x);  //weigh along the x-direction
                                float tex010 = coeffs.isInside(h0x, h1y, h0z) ? coeffs(h0x, h1y, h0z) : 0;
                                float tex110 = coeffs.isInside(h1x, h1y, h0z) ? coeffs(h1x, h1y, h0z) : 0;
                                tex010 = lerp(tex110, tex010, g0x);  //weigh along the x-direction
                                tex000 = lerp(tex010, tex000, g0y);  //weigh along the y-direction
                                float tex001 = coeffs.isInside(h0x, h0y, h1z) ? coeffs(h0x, h0y, h1z) : 0;
                                float tex101 = coeffs.isInside(h1x, h0y, h1z) ? coeffs(h1x, h0y, h1z) : 0;
                                tex001 = lerp(tex101, tex001, g0x);  //weigh along the x-direction
                                float tex011 = coeffs.isInside(h0x, h1y, h1z) ? coeffs(h0x, h1y, h1z) : 0;
                                float tex111 = coeffs.isInside(h1x, h1y, h1z) ? coeffs(h1x, h1y, h1z) : 0;
                                tex011 = lerp(tex111, tex011, g0x);  //weigh along the x-direction
                                tex001 = lerp(tex011, tex001, g0y);  //weigh along the y-direction

                                float interpolated = lerp(tex001, tex000, g0z);  //weigh along the z-direction

                                if (clamp == ClampBoth)
                                        return (interpolated < VMin ? VMin : (interpolated > VMax ? VMax : interpolated));
                                else if (clamp == ClampMin)
                                        return (interpolated < VMin ? VMin : interpolated);
                                else if (clamp == ClampMax)
                                        return (interpolated > VMax ? VMax : interpolated);
                                else // NoClamp (default)
                                        return(interpolated);


                }
                else
#endif
                {


                        if (SplineDegree & 1) // Compiler should remove this test
                        {
                                int i = (int)(floor(x)- SplineDegree / 2);
                                int j = (int)(floor(y)- SplineDegree / 2);
                                int k = (int)(floor(z)- SplineDegree / 2);

                                for (unsigned int m = 0; m <= SplineDegree; ++m)
                                {
                                        xIndex[m] = i++;
                                        yIndex[m] = j++;
                                        zIndex[m] = k++;
                                }
                        }
                        else
                        {
                                int i =  (int)(floor(x+.5)- SplineDegree / 2);
                                int j =  (int)(floor(y+.5)- SplineDegree / 2);
                                int k =  (int)(floor(z+.5)- SplineDegree / 2);

                                for (unsigned int m = 0; m <= SplineDegree; ++m)
                                {
                                        xIndex[m] = i++;
                                        yIndex[m] = j++;
                                        zIndex[m] = k++;
                                }
                        }
                        // Compute Weights
                        switch (SplineDegree) {
                                case 2:
                                        /* x */
                                        w = x - (float)xIndex[1];
                                        xWeight[1] = 3.0 / 4.0 - w * w;
                                        xWeight[2] = (1.0 / 2.0) * (w - xWeight[1] + 1.0);
                                        xWeight[0] = 1.0 - xWeight[1] - xWeight[2];
                                        /* y */
                                        w = y - (float)yIndex[1];
                                        yWeight[1] = 3.0 / 4.0 - w * w;
                                        yWeight[2] = (1.0 / 2.0) * (w - yWeight[1] + 1.0);
                                        yWeight[0] = 1.0 - yWeight[1] - yWeight[2];
                                        /* z */
                                        w = z - (float)zIndex[1];
                                        zWeight[1] = 3.0 / 4.0 - w * w;
                                        zWeight[2] = (1.0 / 2.0) * (w - zWeight[1] + 1.0);
                                        zWeight[0] = 1.0 - zWeight[1] - zWeight[2];

                                        break;
                                case 3:
                                        /* x */
                                        w = x - (float)xIndex[1];
                                        xWeight[3] = (1.0 / 6.0) * w * w * w;
                                        xWeight[0] = (1.0 / 6.0) + (1.0 / 2.0) * w * (w - 1.0) - xWeight[3];
                                        xWeight[2] = w + xWeight[0] - 2.0 * xWeight[3];
                                        xWeight[1] = 1.0 - xWeight[0] - xWeight[2] - xWeight[3];
                                        /* y */
                                        w = y - (float)yIndex[1];
                                        yWeight[3] = (1.0 / 6.0) * w * w * w;
                                        yWeight[0] = (1.0 / 6.0) + (1.0 / 2.0) * w * (w - 1.0) - yWeight[3];
                                        yWeight[2] = w + yWeight[0] - 2.0 * yWeight[3];
                                        yWeight[1] = 1.0 - yWeight[0] - yWeight[2] - yWeight[3];
                                        /* z */
                                        w = z - (float)zIndex[1];
                                        zWeight[3] = (1.0 / 6.0) * w * w * w;
                                        zWeight[0] = (1.0 / 6.0) + (1.0 / 2.0) * w * (w - 1.0) - zWeight[3];
                                        zWeight[2] = w + zWeight[0] - 2.0 * zWeight[3];
                                        zWeight[1] = 1.0 - zWeight[0] - zWeight[2] - zWeight[3];
                                        break;
                                case 4:
                                        /* x */
                                        w = x - (float)xIndex[2];
                                        w2 = w * w;
                                        t = (1.0 / 6.0) * w2;
                                        xWeight[0] = 1.0 / 2.0 - w;
                                        xWeight[0] *= xWeight[0];
                                        xWeight[0] *= (1.0 / 24.0) * xWeight[0];
                                        t0 = w * (t - 11.0 / 24.0);
                                        t1 = 19.0 / 96.0 + w2 * (1.0 / 4.0 - t);
                                        xWeight[1] = t1 + t0;
                                        xWeight[3] = t1 - t0;
                                        xWeight[4] = xWeight[0] + t0 + (1.0 / 2.0) * w;
                                        xWeight[2] = 1.0 - xWeight[0] - xWeight[1] - xWeight[3] - xWeight[4];
                                        /* y */
                                        w = y - (float)yIndex[2];
                                        w2 = w * w;
                                        t = (1.0 / 6.0) * w2;
                                        yWeight[0] = 1.0 / 2.0 - w;
                                        yWeight[0] *= yWeight[0];
                                        yWeight[0] *= (1.0 / 24.0) * yWeight[0];
                                        t0 = w * (t - 11.0 / 24.0);
                                        t1 = 19.0 / 96.0 + w2 * (1.0 / 4.0 - t);
                                        yWeight[1] = t1 + t0;
                                        yWeight[3] = t1 - t0;
                                        yWeight[4] = yWeight[0] + t0 + (1.0 / 2.0) * w;
                                        yWeight[2] = 1.0 - yWeight[0] - yWeight[1] - yWeight[3] - yWeight[4];
                                        /* z */
                                        w = z - (float)zIndex[2];
                                        w2 = w * w;
                                        t = (1.0 / 6.0) * w2;
                                        zWeight[0] = 1.0 / 2.0 - w;
                                        zWeight[0] *= zWeight[0];
                                        zWeight[0] *= (1.0 / 24.0) * zWeight[0];
                                        t0 = w * (t - 11.0 / 24.0);
                                        t1 = 19.0 / 96.0 + w2 * (1.0 / 4.0 - t);
                                        zWeight[1] = t1 + t0;
                                        zWeight[3] = t1 - t0;
                                        zWeight[4] = zWeight[0] + t0 + (1.0 / 2.0) * w;
                                        zWeight[2] = 1.0 - zWeight[0] - zWeight[1] - zWeight[3] - zWeight[4];

                                        break;
                                case 5:
                                        /* x */
                                        w = x - (float)xIndex[2];
                                        w2 = w * w;
                                        xWeight[5] = (1.0 / 120.0) * w * w2 * w2;
                                        w2 -= w;
                                        w4 = w2 * w2;
                                        w -= 1.0 / 2.0;
                                        t = w2 * (w2 - 3.0);
                                        xWeight[0] = (1.0 / 24.0) * (1.0 / 5.0 + w2 + w4) - xWeight[5];
                                        t0 = (1.0 / 24.0) * (w2 * (w2 - 5.0) + 46.0 / 5.0);
                                        t1 = (-1.0 / 12.0) * w * (t + 4.0);
                                        xWeight[2] = t0 + t1;
                                        xWeight[3] = t0 - t1;
                                        t0 = (1.0 / 16.0) * (9.0 / 5.0 - t);
                                        t1 = (1.0 / 24.0) * w * (w4 - w2 - 5.0);
                                        xWeight[1] = t0 + t1;
                                        xWeight[4] = t0 - t1;
                                        /* y */
                                        w = y - (float)yIndex[2];
                                        w2 = w * w;
                                        yWeight[5] = (1.0 / 120.0) * w * w2 * w2;
                                        w2 -= w;
                                        w4 = w2 * w2;
                                        w -= 1.0 / 2.0;
                                        t = w2 * (w2 - 3.0);
                                        yWeight[0] = (1.0 / 24.0) * (1.0 / 5.0 + w2 + w4) - yWeight[5];
                                        t0 = (1.0 / 24.0) * (w2 * (w2 - 5.0) + 46.0 / 5.0);
                                        t1 = (-1.0 / 12.0) * w * (t + 4.0);
                                        yWeight[2] = t0 + t1;
                                        yWeight[3] = t0 - t1;
                                        t0 = (1.0 / 16.0) * (9.0 / 5.0 - t);
                                        t1 = (1.0 / 24.0) * w * (w4 - w2 - 5.0);
                                        yWeight[1] = t0 + t1;
                                        yWeight[4] = t0 - t1;
                                        /* z */
                                        w = z - (float)zIndex[2];
                                        w2 = w * w;
                                        zWeight[5] = (1.0 / 120.0) * w * w2 * w2;
                                        w2 -= w;
                                        w4 = w2 * w2;
                                        w -= 1.0 / 2.0;
                                        t = w2 * (w2 - 3.0);
                                        zWeight[0] = (1.0 / 24.0) * (1.0 / 5.0 + w2 + w4) - zWeight[5];
                                        t0 = (1.0 / 24.0) * (w2 * (w2 - 5.0) + 46.0 / 5.0);
                                        t1 = (-1.0 / 12.0) * w * (t + 4.0);
                                        zWeight[2] = t0 + t1;
                                        zWeight[3] = t0 - t1;
                                        t0 = (1.0 / 16.0) * (9.0 / 5.0 - t);
                                        t1 = (1.0 / 24.0) * w * (w4 - w2 - 5.0);
                                        zWeight[1] = t0 + t1;
                                        zWeight[4] = t0 - t1;


                                        break;
                                case 6:
                                        /* x */
                                        w = x - (float)xIndex[3];
                                        xWeight[0] = 1.0 / 2.0 - w;
                                        xWeight[0] *= xWeight[0] * xWeight[0];
                                        xWeight[0] *= xWeight[0] / 720.0;
                                        xWeight[1] = (361.0 / 192.0 - w * (59.0 / 8.0 + w
                                                                                                           * (-185.0 / 16.0 + w * (25.0 / 3.0 + w * (-5.0 / 2.0 + w)
                                                                                                                                                           * (1.0 / 2.0 + w))))) / 120.0;
                                        xWeight[2] = (10543.0 / 960.0 + w * (-289.0 / 16.0 + w
                                                                                                                 * (79.0 / 16.0 + w * (43.0 / 6.0 + w * (-17.0 / 4.0 + w
                                                                                                                                                                                                 * (-1.0 + w)))))) / 48.0;
                                        w2 = w * w;
                                        xWeight[3] = (5887.0 / 320.0 - w2 * (231.0 / 16.0 - w2
                                                                                                                 * (21.0 / 4.0 - w2))) / 36.0;
                                        xWeight[4] = (10543.0 / 960.0 + w * (289.0 / 16.0 + w
                                                                                                                 * (79.0 / 16.0 + w * (-43.0 / 6.0 + w * (-17.0 / 4.0 + w
                                                                                                                                                                                                  * (1.0 + w)))))) / 48.0;
                                        xWeight[6] = 1.0 / 2.0 + w;
                                        xWeight[6] *= xWeight[6] * xWeight[6];
                                        xWeight[6] *= xWeight[6] / 720.0;
                                        xWeight[5] = 1.0 - xWeight[0] - xWeight[1] - xWeight[2] - xWeight[3]
                                        - xWeight[4] - xWeight[6];
                                        /* y */
                                        w = y - (float)yIndex[3];
                                        yWeight[0] = 1.0 / 2.0 - w;
                                        yWeight[0] *= yWeight[0] * yWeight[0];
                                        yWeight[0] *= yWeight[0] / 720.0;
                                        yWeight[1] = (361.0 / 192.0 - w * (59.0 / 8.0 + w
                                                                                                           * (-185.0 / 16.0 + w * (25.0 / 3.0 + w * (-5.0 / 2.0 + w)
                                                                                                                                                           * (1.0 / 2.0 + w))))) / 120.0;
                                        yWeight[2] = (10543.0 / 960.0 + w * (-289.0 / 16.0 + w
                                                                                                                 * (79.0 / 16.0 + w * (43.0 / 6.0 + w * (-17.0 / 4.0 + w
                                                                                                                                                                                                 * (-1.0 + w)))))) / 48.0;
                                        w2 = w * w;
                                        yWeight[3] = (5887.0 / 320.0 - w2 * (231.0 / 16.0 - w2
                                                                                                                 * (21.0 / 4.0 - w2))) / 36.0;
                                        yWeight[4] = (10543.0 / 960.0 + w * (289.0 / 16.0 + w
                                                                                                                 * (79.0 / 16.0 + w * (-43.0 / 6.0 + w * (-17.0 / 4.0 + w
                                                                                                                                                                                                  * (1.0 + w)))))) / 48.0;
                                        yWeight[6] = 1.0 / 2.0 + w;
                                        yWeight[6] *= yWeight[6] * yWeight[6];
                                        yWeight[6] *= yWeight[6] / 720.0;
                                        yWeight[5] = 1.0 - yWeight[0] - yWeight[1] - yWeight[2] - yWeight[3]
                                        - yWeight[4] - yWeight[6];
                                        /* z */
                                        w = z - (float)zIndex[3];
                                        zWeight[0] = 1.0 / 2.0 - w;
                                        zWeight[0] *= zWeight[0] * zWeight[0];
                                        zWeight[0] *= zWeight[0] / 720.0;
                                        zWeight[1] = (361.0 / 192.0 - w * (59.0 / 8.0 + w
                                                                                                           * (-185.0 / 16.0 + w * (25.0 / 3.0 + w * (-5.0 / 2.0 + w)
                                                                                                                                                           * (1.0 / 2.0 + w))))) / 120.0;
                                        zWeight[2] = (10543.0 / 960.0 + w * (-289.0 / 16.0 + w
                                                                                                                 * (79.0 / 16.0 + w * (43.0 / 6.0 + w * (-17.0 / 4.0 + w
                                                                                                                                                                                                 * (-1.0 + w)))))) / 48.0;
                                        w2 = w * w;
                                        zWeight[3] = (5887.0 / 320.0 - w2 * (231.0 / 16.0 - w2
                                                                                                                 * (21.0 / 4.0 - w2))) / 36.0;
                                        zWeight[4] = (10543.0 / 960.0 + w * (289.0 / 16.0 + w
                                                                                                                 * (79.0 / 16.0 + w * (-43.0 / 6.0 + w * (-17.0 / 4.0 + w
                                                                                                                                                                                                  * (1.0 + w)))))) / 48.0;
                                        zWeight[6] = 1.0 / 2.0 + w;
                                        zWeight[6] *= zWeight[6] * zWeight[6];
                                        zWeight[6] *= zWeight[6] / 720.0;
                                        zWeight[5] = 1.0 - zWeight[0] - zWeight[1] - zWeight[2] - zWeight[3]
                                        - zWeight[4] - zWeight[6];

                                        break;
                                case 7:
                                        /* x */
                                        w = x - (float)xIndex[3];
                                        xWeight[0] = 1.0 - w;
                                        xWeight[0] *= xWeight[0];
                                        xWeight[0] *= xWeight[0] * xWeight[0];
                                        xWeight[0] *= (1.0 - w) / 5040.0;
                                        w2 = w * w;
                                        xWeight[1] = (120.0 / 7.0 + w * (-56.0 + w * (72.0 + w
                                                                                                                                  * (-40.0 + w2 * (12.0 + w * (-6.0 + w)))))) / 720.0;
                                        xWeight[2] = (397.0 / 7.0 - w * (245.0 / 3.0 + w * (-15.0 + w
                                                                                                                                                * (-95.0 / 3.0 + w * (15.0 + w * (5.0 + w
                                                                                                                                                                                                                  * (-5.0 + w))))))) / 240.0;
                                        xWeight[3] = (2416.0 / 35.0 + w2 * (-48.0 + w2 * (16.0 + w2
                                                                                                                                          * (-4.0 + w)))) / 144.0;
                                        xWeight[4] = (1191.0 / 35.0 - w * (-49.0 + w * (-9.0 + w
                                                                                                                                        * (19.0 + w * (-3.0 + w) * (-3.0 + w2))))) / 144.0;
                                        xWeight[5] = (40.0 / 7.0 + w * (56.0 / 3.0 + w * (24.0 + w
                                                                                                                                          * (40.0 / 3.0 + w2 * (-4.0 + w * (-2.0 + w)))))) / 240.0;
                                        xWeight[7] = w2;
                                        xWeight[7] *= xWeight[7] * xWeight[7];
                                        xWeight[7] *= w / 5040.0;
                                        xWeight[6] = 1.0 - xWeight[0] - xWeight[1] - xWeight[2] - xWeight[3]
                                        - xWeight[4] - xWeight[5] - xWeight[7];
                                        /* y */
                                        w = y - (float)yIndex[3];
                                        yWeight[0] = 1.0 - w;
                                        yWeight[0] *= yWeight[0];
                                        yWeight[0] *= yWeight[0] * yWeight[0];
                                        yWeight[0] *= (1.0 - w) / 5040.0;
                                        w2 = w * w;
                                        yWeight[1] = (120.0 / 7.0 + w * (-56.0 + w * (72.0 + w
                                                                                                                                  * (-40.0 + w2 * (12.0 + w * (-6.0 + w)))))) / 720.0;
                                        yWeight[2] = (397.0 / 7.0 - w * (245.0 / 3.0 + w * (-15.0 + w
                                                                                                                                                * (-95.0 / 3.0 + w * (15.0 + w * (5.0 + w
                                                                                                                                                                                                                  * (-5.0 + w))))))) / 240.0;
                                        yWeight[3] = (2416.0 / 35.0 + w2 * (-48.0 + w2 * (16.0 + w2
                                                                                                                                          * (-4.0 + w)))) / 144.0;
                                        yWeight[4] = (1191.0 / 35.0 - w * (-49.0 + w * (-9.0 + w
                                                                                                                                        * (19.0 + w * (-3.0 + w) * (-3.0 + w2))))) / 144.0;
                                        yWeight[5] = (40.0 / 7.0 + w * (56.0 / 3.0 + w * (24.0 + w
                                                                                                                                          * (40.0 / 3.0 + w2 * (-4.0 + w * (-2.0 + w)))))) / 240.0;
                                        yWeight[7] = w2;
                                        yWeight[7] *= yWeight[7] * yWeight[7];
                                        yWeight[7] *= w / 5040.0;
                                        yWeight[6] = 1.0 - yWeight[0] - yWeight[1] - yWeight[2] - yWeight[3]
                                        - yWeight[4] - yWeight[5] - yWeight[7];

                                        /* z */
                                        w = z - (float)zIndex[3];
                                        zWeight[0] = 1.0 - w;
                                        zWeight[0] *= zWeight[0];
                                        zWeight[0] *= zWeight[0] * zWeight[0];
                                        zWeight[0] *= (1.0 - w) / 5040.0;
                                        w2 = w * w;
                                        zWeight[1] = (120.0 / 7.0 + w * (-56.0 + w * (72.0 + w
                                                                                                                                  * (-40.0 + w2 * (12.0 + w * (-6.0 + w)))))) / 720.0;
                                        zWeight[2] = (397.0 / 7.0 - w * (245.0 / 3.0 + w * (-15.0 + w
                                                                                                                                                * (-95.0 / 3.0 + w * (15.0 + w * (5.0 + w
                                                                                                                                                                                                                  * (-5.0 + w))))))) / 240.0;
                                        zWeight[3] = (2416.0 / 35.0 + w2 * (-48.0 + w2 * (16.0 + w2
                                                                                                                                          * (-4.0 + w)))) / 144.0;
                                        zWeight[4] = (1191.0 / 35.0 - w * (-49.0 + w * (-9.0 + w
                                                                                                                                        * (19.0 + w * (-3.0 + w) * (-3.0 + w2))))) / 144.0;
                                        zWeight[5] = (40.0 / 7.0 + w * (56.0 / 3.0 + w * (24.0 + w
                                                                                                                                          * (40.0 / 3.0 + w2 * (-4.0 + w * (-2.0 + w)))))) / 240.0;
                                        zWeight[7] = w2;
                                        zWeight[7] *= zWeight[7] * zWeight[7];
                                        zWeight[7] *= w / 5040.0;
                                        zWeight[6] = 1.0 - zWeight[0] - zWeight[1] - zWeight[2] - zWeight[3]
                                        - zWeight[4] - zWeight[5] - zWeight[7];
                                        break;
                                case 8:
                                        /* x */
                                        w = x - (float)xIndex[4];
                                        xWeight[0] = 1.0 / 2.0 - w;
                                        xWeight[0] *= xWeight[0];
                                        xWeight[0] *= xWeight[0];
                                        xWeight[0] *= xWeight[0] / 40320.0;
                                        w2 = w * w;
                                        xWeight[1] = (39.0 / 16.0 - w * (6.0 + w * (-9.0 / 2.0 + w2)))
                                        * (21.0 / 16.0 + w * (-15.0 / 4.0 + w * (9.0 / 2.0 + w
                                                                                                                         * (-3.0 + w)))) / 5040.0;
                                        xWeight[2] = (82903.0 / 1792.0 + w * (-4177.0 / 32.0 + w
                                                                                                                  * (2275.0 / 16.0 + w * (-487.0 / 8.0 + w * (-85.0 / 8.0 + w
                                                                                                                                                                                                          * (41.0 / 2.0 + w * (-5.0 + w * (-2.0 + w)))))))) / 1440.0;
                                        xWeight[3] = (310661.0 / 1792.0 - w * (14219.0 / 64.0 + w
                                                                                                                   * (-199.0 / 8.0 + w * (-1327.0 / 16.0 + w * (245.0 / 8.0 + w
                                                                                                                                                                                                                * (53.0 / 4.0 + w * (-8.0 + w * (-1.0 + w)))))))) / 720.0;
                                        xWeight[4] = (2337507.0 / 8960.0 + w2 * (-2601.0 / 16.0 + w2
                                                                                                                         * (387.0 / 8.0 + w2 * (-9.0 + w2)))) / 576.0;
                                        xWeight[5] = (310661.0 / 1792.0 - w * (-14219.0 / 64.0 + w
                                                                                                                   * (-199.0 / 8.0 + w * (1327.0 / 16.0 + w * (245.0 / 8.0 + w
                                                                                                                                                                                                           * (-53.0 / 4.0 + w * (-8.0 + w * (1.0 + w)))))))) / 720.0;
                                        xWeight[7] = (39.0 / 16.0 - w * (-6.0 + w * (-9.0 / 2.0 + w2)))
                                        * (21.0 / 16.0 + w * (15.0 / 4.0 + w * (9.0 / 2.0 + w
                                                                                                                        * (3.0 + w)))) / 5040.0;
                                        xWeight[8] = 1.0 / 2.0 + w;
                                        xWeight[8] *= xWeight[8];
                                        xWeight[8] *= xWeight[8];
                                        xWeight[8] *= xWeight[8] / 40320.0;
                                        xWeight[6] = 1.0 - xWeight[0] - xWeight[1] - xWeight[2] - xWeight[3]
                                        - xWeight[4] - xWeight[5] - xWeight[7] - xWeight[8];

                                        /* y */
                                        w = y - (float)yIndex[4];
                                        yWeight[0] = 1.0 / 2.0 - w;
                                        yWeight[0] *= yWeight[0];
                                        yWeight[0] *= yWeight[0];
                                        yWeight[0] *= yWeight[0] / 40320.0;
                                        w2 = w * w;
                                        yWeight[1] = (39.0 / 16.0 - w * (6.0 + w * (-9.0 / 2.0 + w2)))
                                        * (21.0 / 16.0 + w * (-15.0 / 4.0 + w * (9.0 / 2.0 + w
                                                                                                                         * (-3.0 + w)))) / 5040.0;
                                        yWeight[2] = (82903.0 / 1792.0 + w * (-4177.0 / 32.0 + w
                                                                                                                  * (2275.0 / 16.0 + w * (-487.0 / 8.0 + w * (-85.0 / 8.0 + w
                                                                                                                                                                                                          * (41.0 / 2.0 + w * (-5.0 + w * (-2.0 + w)))))))) / 1440.0;
                                        yWeight[3] = (310661.0 / 1792.0 - w * (14219.0 / 64.0 + w
                                                                                                                   * (-199.0 / 8.0 + w * (-1327.0 / 16.0 + w * (245.0 / 8.0 + w
                                                                                                                                                                                                                * (53.0 / 4.0 + w * (-8.0 + w * (-1.0 + w)))))))) / 720.0;
                                        yWeight[4] = (2337507.0 / 8960.0 + w2 * (-2601.0 / 16.0 + w2
                                                                                                                         * (387.0 / 8.0 + w2 * (-9.0 + w2)))) / 576.0;
                                        yWeight[5] = (310661.0 / 1792.0 - w * (-14219.0 / 64.0 + w
                                                                                                                   * (-199.0 / 8.0 + w * (1327.0 / 16.0 + w * (245.0 / 8.0 + w
                                                                                                                                                                                                           * (-53.0 / 4.0 + w * (-8.0 + w * (1.0 + w)))))))) / 720.0;
                                        yWeight[7] = (39.0 / 16.0 - w * (-6.0 + w * (-9.0 / 2.0 + w2)))
                                        * (21.0 / 16.0 + w * (15.0 / 4.0 + w * (9.0 / 2.0 + w
                                                                                                                        * (3.0 + w)))) / 5040.0;
                                        yWeight[8] = 1.0 / 2.0 + w;
                                        yWeight[8] *= yWeight[8];
                                        yWeight[8] *= yWeight[8];
                                        yWeight[8] *= yWeight[8] / 40320.0;
                                        yWeight[6] = 1.0 - yWeight[0] - yWeight[1] - yWeight[2] - yWeight[3]
                                        - yWeight[4] - yWeight[5] - yWeight[7] - yWeight[8];

                                        /* z */
                                        w = z - (float)zIndex[4];
                                        zWeight[0] = 1.0 / 2.0 - w;
                                        zWeight[0] *= zWeight[0];
                                        zWeight[0] *= zWeight[0];
                                        zWeight[0] *= zWeight[0] / 40320.0;
                                        w2 = w * w;
                                        zWeight[1] = (39.0 / 16.0 - w * (6.0 + w * (-9.0 / 2.0 + w2)))
                                        * (21.0 / 16.0 + w * (-15.0 / 4.0 + w * (9.0 / 2.0 + w
                                                                                                                         * (-3.0 + w)))) / 5040.0;
                                        zWeight[2] = (82903.0 / 1792.0 + w * (-4177.0 / 32.0 + w
                                                                                                                  * (2275.0 / 16.0 + w * (-487.0 / 8.0 + w * (-85.0 / 8.0 + w
                                                                                                                                                                                                          * (41.0 / 2.0 + w * (-5.0 + w * (-2.0 + w)))))))) / 1440.0;
                                        zWeight[3] = (310661.0 / 1792.0 - w * (14219.0 / 64.0 + w
                                                                                                                   * (-199.0 / 8.0 + w * (-1327.0 / 16.0 + w * (245.0 / 8.0 + w
                                                                                                                                                                                                                * (53.0 / 4.0 + w * (-8.0 + w * (-1.0 + w)))))))) / 720.0;
                                        zWeight[4] = (2337507.0 / 8960.0 + w2 * (-2601.0 / 16.0 + w2
                                                                                                                         * (387.0 / 8.0 + w2 * (-9.0 + w2)))) / 576.0;
                                        zWeight[5] = (310661.0 / 1792.0 - w * (-14219.0 / 64.0 + w
                                                                                                                   * (-199.0 / 8.0 + w * (1327.0 / 16.0 + w * (245.0 / 8.0 + w
                                                                                                                                                                                                           * (-53.0 / 4.0 + w * (-8.0 + w * (1.0 + w)))))))) / 720.0;
                                        zWeight[7] = (39.0 / 16.0 - w * (-6.0 + w * (-9.0 / 2.0 + w2)))
                                        * (21.0 / 16.0 + w * (15.0 / 4.0 + w * (9.0 / 2.0 + w
                                                                                                                        * (3.0 + w)))) / 5040.0;
                                        zWeight[8] = 1.0 / 2.0 + w;
                                        zWeight[8] *= zWeight[8];
                                        zWeight[8] *= zWeight[8];
                                        zWeight[8] *= zWeight[8] / 40320.0;
                                        zWeight[6] = 1.0 - zWeight[0] - zWeight[1] - zWeight[2] - zWeight[3]
                                        - zWeight[4] - zWeight[5] - zWeight[7] - zWeight[8];
                                        break;
                                case 9:
                                        /* x */
                                        w = x - (float)xIndex[4];
                                        xWeight[0] = 1.0 - w;
                                        xWeight[0] *= xWeight[0];
                                        xWeight[0] *= xWeight[0];
                                        xWeight[0] *= xWeight[0] * (1.0 - w) / 362880.0;
                                        xWeight[1] = (502.0 / 9.0 + w * (-246.0 + w * (472.0 + w
                                                                                                                                   * (-504.0 + w * (308.0 + w * (-84.0 + w * (-56.0 / 3.0 + w
                                                                                                                                                                                                                          * (24.0 + w * (-8.0 + w))))))))) / 40320.0;
                                        xWeight[2] = (3652.0 / 9.0 - w * (2023.0 / 2.0 + w * (-952.0 + w
                                                                                                                                                  * (938.0 / 3.0 + w * (112.0 + w * (-119.0 + w * (56.0 / 3.0 + w
                                                                                                                                                                                                                                                   * (14.0 + w * (-7.0 + w))))))))) / 10080.0;
                                        xWeight[3] = (44117.0 / 42.0 + w * (-2427.0 / 2.0 + w * (66.0 + w
                                                                                                                                                         * (434.0 + w * (-129.0 + w * (-69.0 + w * (34.0 + w * (6.0 + w
                                                                                                                                                                                                                                                                        * (-6.0 + w))))))))) / 4320.0;
                                        w2 = w * w;
                                        xWeight[4] = (78095.0 / 63.0 - w2 * (700.0 + w2 * (-190.0 + w2
                                                                                                                                           * (100.0 / 3.0 + w2 * (-5.0 + w))))) / 2880.0;
                                        xWeight[5] = (44117.0 / 63.0 + w * (809.0 + w * (44.0 + w
                                                                                                                                         * (-868.0 / 3.0 + w * (-86.0 + w * (46.0 + w * (68.0 / 3.0 + w
                                                                                                                                                                                                                                         * (-4.0 + w * (-4.0 + w))))))))) / 2880.0;
                                        xWeight[6] = (3652.0 / 21.0 - w * (-867.0 / 2.0 + w * (-408.0 + w
                                                                                                                                                   * (-134.0 + w * (48.0 + w * (51.0 + w * (-4.0 + w) * (-1.0 + w)
                                                                                                                                                                                                                * (2.0 + w))))))) / 4320.0;
                                        xWeight[7] = (251.0 / 18.0 + w * (123.0 / 2.0 + w * (118.0 + w
                                                                                                                                                 * (126.0 + w * (77.0 + w * (21.0 + w * (-14.0 / 3.0 + w
                                                                                                                                                                                                                                 * (-6.0 + w * (-2.0 + w))))))))) / 10080.0;
                                        xWeight[9] = w2 * w2;
                                        xWeight[9] *= xWeight[9] * w / 362880.0;
                                        xWeight[8] = 1.0 - xWeight[0] - xWeight[1] - xWeight[2] - xWeight[3]
                                        - xWeight[4] - xWeight[5] - xWeight[6] - xWeight[7] - xWeight[9];

                                        /* y */
                                        w = y - (float)yIndex[4];
                                        yWeight[0] = 1.0 - w;
                                        yWeight[0] *= yWeight[0];
                                        yWeight[0] *= yWeight[0];
                                        yWeight[0] *= yWeight[0] * (1.0 - w) / 362880.0;
                                        yWeight[1] = (502.0 / 9.0 + w * (-246.0 + w * (472.0 + w
                                                                                                                                   * (-504.0 + w * (308.0 + w * (-84.0 + w * (-56.0 / 3.0 + w
                                                                                                                                                                                                                          * (24.0 + w * (-8.0 + w))))))))) / 40320.0;
                                        yWeight[2] = (3652.0 / 9.0 - w * (2023.0 / 2.0 + w * (-952.0 + w
                                                                                                                                                  * (938.0 / 3.0 + w * (112.0 + w * (-119.0 + w * (56.0 / 3.0 + w
                                                                                                                                                                                                                                                   * (14.0 + w * (-7.0 + w))))))))) / 10080.0;
                                        yWeight[3] = (44117.0 / 42.0 + w * (-2427.0 / 2.0 + w * (66.0 + w
                                                                                                                                                         * (434.0 + w * (-129.0 + w * (-69.0 + w * (34.0 + w * (6.0 + w
                                                                                                                                                                                                                                                                        * (-6.0 + w))))))))) / 4320.0;
                                        w2 = w * w;
                                        yWeight[4] = (78095.0 / 63.0 - w2 * (700.0 + w2 * (-190.0 + w2
                                                                                                                                           * (100.0 / 3.0 + w2 * (-5.0 + w))))) / 2880.0;
                                        yWeight[5] = (44117.0 / 63.0 + w * (809.0 + w * (44.0 + w
                                                                                                                                         * (-868.0 / 3.0 + w * (-86.0 + w * (46.0 + w * (68.0 / 3.0 + w
                                                                                                                                                                                                                                         * (-4.0 + w * (-4.0 + w))))))))) / 2880.0;
                                        yWeight[6] = (3652.0 / 21.0 - w * (-867.0 / 2.0 + w * (-408.0 + w
                                                                                                                                                   * (-134.0 + w * (48.0 + w * (51.0 + w * (-4.0 + w) * (-1.0 + w)
                                                                                                                                                                                                                * (2.0 + w))))))) / 4320.0;
                                        yWeight[7] = (251.0 / 18.0 + w * (123.0 / 2.0 + w * (118.0 + w
                                                                                                                                                 * (126.0 + w * (77.0 + w * (21.0 + w * (-14.0 / 3.0 + w
                                                                                                                                                                                                                                 * (-6.0 + w * (-2.0 + w))))))))) / 10080.0;
                                        yWeight[9] = w2 * w2;
                                        yWeight[9] *= yWeight[9] * w / 362880.0;
                                        yWeight[8] = 1.0 - yWeight[0] - yWeight[1] - yWeight[2] - yWeight[3]
                                        - yWeight[4] - yWeight[5] - yWeight[6] - yWeight[7] - yWeight[9];

                                        /* z */
                                        w = z - (float)zIndex[4];
                                        zWeight[0] = 1.0 - w;
                                        zWeight[0] *= zWeight[0];
                                        zWeight[0] *= zWeight[0];
                                        zWeight[0] *= zWeight[0] * (1.0 - w) / 362880.0;
                                        zWeight[1] = (502.0 / 9.0 + w * (-246.0 + w * (472.0 + w
                                                                                                                                   * (-504.0 + w * (308.0 + w * (-84.0 + w * (-56.0 / 3.0 + w
                                                                                                                                                                                                                          * (24.0 + w * (-8.0 + w))))))))) / 40320.0;
                                        zWeight[2] = (3652.0 / 9.0 - w * (2023.0 / 2.0 + w * (-952.0 + w
                                                                                                                                                  * (938.0 / 3.0 + w * (112.0 + w * (-119.0 + w * (56.0 / 3.0 + w
                                                                                                                                                                                                                                                   * (14.0 + w * (-7.0 + w))))))))) / 10080.0;
                                        zWeight[3] = (44117.0 / 42.0 + w * (-2427.0 / 2.0 + w * (66.0 + w
                                                                                                                                                         * (434.0 + w * (-129.0 + w * (-69.0 + w * (34.0 + w * (6.0 + w
                                                                                                                                                                                                                                                                        * (-6.0 + w))))))))) / 4320.0;
                                        w2 = w * w;
                                        zWeight[4] = (78095.0 / 63.0 - w2 * (700.0 + w2 * (-190.0 + w2
                                                                                                                                           * (100.0 / 3.0 + w2 * (-5.0 + w))))) / 2880.0;
                                        zWeight[5] = (44117.0 / 63.0 + w * (809.0 + w * (44.0 + w
                                                                                                                                         * (-868.0 / 3.0 + w * (-86.0 + w * (46.0 + w * (68.0 / 3.0 + w
                                                                                                                                                                                                                                         * (-4.0 + w * (-4.0 + w))))))))) / 2880.0;
                                        zWeight[6] = (3652.0 / 21.0 - w * (-867.0 / 2.0 + w * (-408.0 + w
                                                                                                                                                   * (-134.0 + w * (48.0 + w * (51.0 + w * (-4.0 + w) * (-1.0 + w)
                                                                                                                                                                                                                * (2.0 + w))))))) / 4320.0;
                                        zWeight[7] = (251.0 / 18.0 + w * (123.0 / 2.0 + w * (118.0 + w
                                                                                                                                                 * (126.0 + w * (77.0 + w * (21.0 + w * (-14.0 / 3.0 + w
                                                                                                                                                                                                                                 * (-6.0 + w * (-2.0 + w))))))))) / 10080.0;
                                        zWeight[9] = w2 * w2;
                                        zWeight[9] *= zWeight[9] * w / 362880.0;
                                        zWeight[8] = 1.0 - zWeight[0] - zWeight[1] - zWeight[2] - zWeight[3]
                                        - zWeight[4] - zWeight[5] - zWeight[6] - zWeight[7] - zWeight[9];
                                        break;
                        }

                        // Boundary condition (mirror)
                        if (bound == Mirror)
                                for (unsigned int k = 0; k <= SplineDegree; ++k)
                                {
                                        xIndex[k] = ((xIndex[k] < 0) ?
                                                                 (-xIndex[k] - nbX2 * ((-xIndex[k]) / nbX2))
                                                                 : (xIndex[k] - nbX2 * (xIndex[k] / nbX2)));
                                        if (coeffs.nbx <= xIndex[k]) {
                                                xIndex[k] = nbX2 - xIndex[k];
                                        }
                                        yIndex[k] = ((yIndex[k] < 0) ?
                                                                 (-yIndex[k] - nbY2 * ((-yIndex[k]) / nbY2))
                                                                 : (yIndex[k] - nbY2 * (yIndex[k] / nbY2)));
                                        if (coeffs.nby <= yIndex[k]) {
                                                yIndex[k] = nbY2 - yIndex[k];
                                        }

                                        zIndex[k] =  ((zIndex[k] < 0) ?
                                                                  (-zIndex[k] - nbZ2 * ((-zIndex[k]) / nbZ2))
                                                                  : (zIndex[k] - nbZ2 * (zIndex[k] / nbZ2)));
                                        if (coeffs.nbz <= zIndex[k]) {
                                                zIndex[k] = nbZ2 - zIndex[k];
                                        }

                                }

                        if (bound == Zero)
                                for (unsigned int k = 0; k <= SplineDegree; ++k)
                                {
                                        xIndex[k] =  ((xIndex[k] < 0) ?
                                                                  0
                                                                  : (xIndex[k] - nbX2 * (xIndex[k] / nbX2)));
                                        if (coeffs.nbx <= xIndex[k]) {
                                                xIndex[k] =0;
                                        }
                                        yIndex[k] =  ((yIndex[k] < 0) ?
                                                                  0
                                                                  : (yIndex[k] - nbY2 * (yIndex[k] / nbY2)));
                                        if (coeffs.nby <= yIndex[k]) {
                                                yIndex[k] = 0;
                                        }

                                        zIndex[k] = ((zIndex[k] < 0) ?
                                                                 0
                                                                 : (zIndex[k] - nbZ2 * (zIndex[k] / nbZ2)));
                                        if (coeffs.nbz <= zIndex[k]) {
                                                zIndex[k] = 0;
                                        }
                                }



                        float interpolated = 0.0;
                        for (unsigned int k = 0; k <= SplineDegree; k++)
                        {
                                float w2 = 0.0;
                                for (unsigned int j = 0; j <= SplineDegree; j++)
                                {
                                        float w = 0.0;
                                        for (unsigned int i = 0; i <= SplineDegree; i++)
                                                w += xWeight[i] * coeffs(xIndex[i], yIndex[j], zIndex[k]);
                                        w2 += yWeight[j] * w;
                                }
                                interpolated += zWeight[k] * w2;

                        }

                        // data clamp strategies
                        if (clamp == ClampBoth)
                                return (interpolated < VMin ? VMin : (interpolated > VMax ? VMax : interpolated));
                        else if (clamp == ClampMin)
                                return (interpolated < VMin ? VMin : interpolated);
                        else if (clamp == ClampMax)
                                return (interpolated > VMax ? VMax : interpolated);
                        else // NoClamp (default)
                                return(interpolated);
                }
        }



        float operator()(Vect3Df p)
        {
                return (*this)(p.x(),p.y(), p.z());
        }


        inline vistal::Image3D<float>& getCoefficients() { return coeffs; }

        inline float& coef(int x, int y, int z ) { return coeffs(x,y,z); }
        inline float& coef(Vect3Di p) { return coef(p.x(), p.y(), p.z()); }

protected:


        float InitialAntiCausalCoefficient(float c[], unsigned int DataLength, float z)
        {
                return((z / (z * z - 1.0)) * (z * c[DataLength - 2] + c[DataLength - 1]));
        }

        double	InitialCausalCoefficient(float	c[], long DataLength,
                                                                         float	z, float Tolerance)

        {
                float	Sum, zn, z2n, iz;
                long	n, Horizon;

                Horizon = DataLength;
                if (Tolerance > 0.0) {
                        Horizon = (long)ceil(log(Tolerance) / log(fabs(z)));
                }
                if (Horizon < DataLength) {
                        zn = z;
                        Sum = c[0];
                        for (n = 1L; n < Horizon; n++) {
                                Sum += zn * c[n];
                                zn *= z;
                        }
                        return(Sum);
                }
                else {
                        zn = z;
                        iz = 1.0 / z;
                        z2n = pow(z, (float)(DataLength - 1));
                        Sum = c[0] + z2n * c[DataLength - 1];
                        z2n *= z2n * iz;
                        for (n = 1L; n <= DataLength - 2L; n++) {
                                Sum += (zn + z2n) * c[n];
                                zn *= z;
                                z2n *= iz;
                        }
                        return(Sum / (1.0 - zn * zn));
                }
        }


        void convertToInterpolationCoefficients(float c[], long DataLength,
                                                                                        float z[], long NbPoles,
                                                                                        float Tolerance)

        {
                double	Lambda = 1.0;
                long	n, k;

                if (DataLength == 1) {
                        return;
                }
                for (k = 0L; k < NbPoles; k++) {
                        Lambda = Lambda * (1.0 - z[k]) * (1.0 - 1.0 / z[k]);
                }
                for (n = 0L; n < DataLength; n++) {
                        c[n] *= Lambda;
                }
                for (k = 0L; k < NbPoles; k++) {
                        c[0] = InitialCausalCoefficient(c, DataLength, z[k], Tolerance);
                        for (n = 1; n < DataLength; n++) {
                                c[n] += z[k] * c[n - 1];
                        }
                        c[DataLength - 1] = InitialAntiCausalCoefficient(c, DataLength, z[k]);
                        for (n = DataLength - 2; 0 <= n; n--) {
                                c[n] = z[k] * (c[n + 1] - c[n]);
                        }
                }
        }

};


// Classical Spline definition

typedef  SPlineImage3D<2> LinearSplineImage;
typedef  SPlineImage3D<3> CubicSplineImage;
typedef  SPlineImage3D<4> QuadraticSplineImage;




#endif	    /* !SPLINEIMAGE_HH_ */
