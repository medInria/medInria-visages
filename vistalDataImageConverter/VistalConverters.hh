
/*
 ** VistalConverters.hh
 ** Login : <nwiestda@pallium.irisa.fr>
 ** Started on  Thu Feb 23 16:13:27 2006 Nicolas Wiest-Daessle
 
 */

#ifndef   	VistalConverters_hh
# define   	VistalConverters_hh


#include "Histogram.hh"


namespace vistal
{
	
	namespace converters
	{
		
		struct Parameters// Used to specify the conversion parameters
		{
			Parameters(): lquantile(0), rquantile(0), complement(false), copy(false), clamp(false)
			{}
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

				inline void ConvertImages(Image3D<DataType1>& im, Image3D<DataType2>& res, const Parameters& p)
			{				
				if (res.nbx != im.nbx || res.nby != im.nby || res.nbz != im.nbz)
					res = Image3D<DataType2> (im, 0);
					
				//vistal::copie_param_volume(res, im);
				
				
				if (p.complement)
					complement(im);
				
				if (!p.copy && !p.clamp)
				{
					FloatHistogram<DataType1> h(im, 512);
					
					
					double min = h.min();
					double max = h.max();
					
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
					
					typename Image3D<DataType1>::iterator it1 = im.begin();
					typename Image3D<DataType1>::iterator iend = im.end();
					typename Image3D<DataType2>::iterator it2 = res.begin();
					while (it1 != iend)
					{
						*it2 = (DataType2)(std::numeric_limits<DataType2>::max() * 
										   ((std::min(max, std::max((double)*it1,min)) - min)/(max-min)));
						++it1; ++it2;
					}
				}
				else
				{
					//qDebug() << "Copy or Clamp mode";
					typename Image3D<DataType1>::iterator it1 = im.begin();
					typename Image3D<DataType1>::iterator iend = im.end();
					typename Image3D<DataType2>::iterator it2 = res.begin();
					
					double DT2max = std::numeric_limits<DataType2>::max(),
					DT2min = std::numeric_limits<DataType2>::is_integer ? std::numeric_limits<DataType2>::min() : -std::numeric_limits<DataType2>::max();
					
					while (it1 != iend)
					{
						if (p.copy )
							*it2 = (DataType2)*it1;
						else
							*it2 = (DataType2)std::min(DT2max, std::max(DT2min, (double)*it1));
						
						++it1; ++it2;
					}
				}
			}

		
	}
	
		namespace medinria	
		{
			// Function to convert a dtkAbstractData pointer containing a vistal image of type typeIn to a dtkAbstractData itk image of type typeOut
			void convertToItk(QString typeIn, QString typeOut, dtkAbstractData* imageIn, dtkAbstractData*& imageOut);
			
			// Function to convert a dtkAbstractData pointer containing a itk image of type typeIn to a dtkAbstractData vistal image of type typeOut
			void convertFromItk(QString typeIn, QString typeOut, dtkAbstractData* imageIn, dtkAbstractData*& imageOut);
			
			// Function to convert a vistal image of type typeIn to a vistal image of type typeOut stored in a dtkAbstractData
			void convert(QString typeIn, QString typeOut, dtkAbstractData* imageIn, dtkAbstractData*& imageOut);
		}	
}

#endif