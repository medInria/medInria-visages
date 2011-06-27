
/*
 ** VistalConverters.hh
 ** Login : <nwiestda@pallium.irisa.fr>
 ** Started on  Thu Feb 23 16:13:27 2006 Nicolas Wiest-Daessle
 ** $Id$
 **
 ** Copyright (C) 2006 Nicolas Wiest-Daessle
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

#ifndef   	VistalConverters_hh
# define   	VistalConverters_hh


namespace vistal
{
	
	namespace converters
	{
		
		struct Parameters// Used to specify the conversion parameters
		{
			float lquantile;  // Large size Type to Lower sized type quantile
			float rquantile;  // Large size Type to Lower sized type quantile
			bool complement;
			bool copy;
			bool clamp;
		};
		
		
		template <class DataType>
		static inline void complement(Image3D<DataType>& img)
		{
			for (typename Image3D<DataType>::iterator it = img.begin(); it != img.end(); ++it)
				*it = (- *it) + 1;
		}
		
		template <class DataType, class DataType2>
		DataType2 trunc(DataType v)
		{
			
			return (DataType2)std::max(std::min((float)std::numeric_limits<DataType2>::max(),
												(float)std::numeric_limits<DataType2>::max() * v),	   
									   (float)(std::numeric_limits<DataType2>::is_integer ? 
											   std::numeric_limits<DataType2>::min() : 
											   -std::numeric_limits<DataType2>::max()));
		}
		
		
		
		// Default data type conversion
		template <class DataType1, class DataType2>
		struct ConvertImages
		{
			static void Work(const Image3D<DataType1>& im, Image3D<DataType2>& res, const Parameters& p)
			{
				res = Image3D<DataType2> (im, 0);
				
				copie_param_volume(res, im);

				
				if (p.complement)
					complement(im);
				
				if (!p.copy && !p.clamp)
				{
					FloatHistogram<DataType1> h(im, 512);
					
					
					float min = h.min();
					float max = h.max();
					
					if (p.lquantile != 0)
					{ // Search the min and max inside the quantile
						float cumul = 0;
						for (int i = 0; i < h.Bins(); ++i)
						{
							cumul += h.proba(i);
							if (cumul > p.lquantile) { cumul = i-1; break; }
						}
						min = h.value((int)cumul);
					}
					if (p.rquantile != 0)
					{
						float cumul = 0;
						for (int i = h.Bins(); i >= 0 ; --i)
						{
							cumul += h.proba(i);
							if (cumul > p.rquantile) { cumul = i+1; break; }
						}
						max = h.value((int)cumul);	
					}
					
					Image3D<DataType1>::iterator it1 = im.begin();
					typename Image3D<DataType2>::iterator it2 = res.begin();
					while (it1 != im.end())
					{
						*it2 = (DataType2)(std::numeric_limits<DataType2>::max() * 
										   ((std::min(max, std::max(*it1,min)) - min)/(max-min)));
						++it1; ++it2;
					}
				}
				else
				{
				
					typename Image3D<DataType1>::iterator it1 = im.begin(), iend = im.end();
				typename Image3D<DataType2>::iterator it2 = res.begin();
					
					double DT2max = std::numeric_limits<DataType2>::max(),
					DT2min = std::numeric_limits<DataType2>::is_integer ? std::numeric_limits<DataType2>::min() : -std::numeric_limits<DataType2>::max();
					
					while (it1 != iend)
				{
					if (p.copy && !p.clamp)
						*it2 = (DataType2)*it1;
					else
						*it2 = (DataType2)std::min(DT2max, std::max(DT2min, (double)*it1))
					
					++it1; ++it2;
				}
			}
			}
			
		}
		
				
		
		
		
	}
}

#endif