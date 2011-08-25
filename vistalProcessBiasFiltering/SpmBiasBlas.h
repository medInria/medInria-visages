#ifndef SPMBIAS_BLAS_H
#define SPMBIAS_BLAS_H

struct Basis
{
	
	
	
	enum BasisType { DiscretCosines , LegendrePolynomials, HermitePolynomials };
	
	Basis(Vect3Di _dimension, Vect3Di _order):
    dimension(_dimension), order(_order),
    B0(dimension.x(), order.x()),
    B1(dimension.y(), order.y()),
    B2(dimension.z(), order.z()),
    T(order.x(), order.y(), order.z(), 0)
	{
		// Build the Basis
		InitBasis(B0, dimension.x(), order.x());
		InitBasis(B1, dimension.y(), order.y());
		InitBasis(B2, dimension.z(), order.z());
		//   std::cout << B0 << std::endl;
	}
	
	Basis(Vect3Di _dimension, Vect3Di _order, enum BasisType type):
    dimension(_dimension), order(_order),
    B0(dimension.x(), order.x()),
    B1(dimension.y(), order.y()),
    B2(dimension.z(), order.z()),
    T(order.x(), order.y(), order.z(), 0)
	{
		// Build the Basis
		InitBasis(B0, dimension.x(), order.x(), type);
		InitBasis(B1, dimension.y(), order.y(), type);
		InitBasis(B2, dimension.z(), order.z(), type);
		//   std::cout << B0 << std::endl;
		
		switch (type)
		
		{
				
			case HermitePolynomials: std::cout << "Hermite Polynomials Basis" << std::endl; break;
			case LegendrePolynomials: std::cout << "Legendre Polynomials Basis" << std::endl; break;
			case DiscretCosines: std::cout << "Discret Cosines Basis" << std::endl; break;
				
				
		}		
		/*    std::ofstream fB1("/tmp/b0"); fB1 << B0;
		 std::ofstream fB2("/tmp/b1"); fB2 << B1;
		 std::ofstream fB3("/tmp/b2"); fB3 << B2;
		 */  
		
	}
	
	
	void InitBasis(ublas::matrix<MatrixDataType>& B, float N, int K, enum BasisType type = DiscretCosines)
	{
		
		switch (type)
		{
				
			case HermitePolynomials:
			{ // Consider the space between ]-1 and 1[
				//double sN = 1./ sqrt(N);
				double sN = 1.;// / (N);
				for (int i = 0; i < N; ++i)  B(i, 0) = sN;
				
				//	  sN = sqrt(2./N);
				for (int k = 1; k < K; ++k)
					for (int i = 0; i < N; ++i)
						B(i,k) = sN * HermiteTable[k](((i+1)-((N+1)/2))/(.5*N));
				break;
			}
				
			case LegendrePolynomials:
			{
				//float sN = 1./ sqrt(N);
				double sN = 1.;// / (N);
				for (int i = 0; i < N; ++i)  B(i, 1) = sN;
				
				//	  sN = sqrt(2./N);
				for (int k = 1; k < K; ++k)
					for (int i = 0; i < N; ++i)
						B(i,k) = sN * LegendreTable[k](((i+1)-((N+1)/2))/(.5*N));
				break;
			}
			default:
			case DiscretCosines:
			{
				
				// Change the basis shape here
				// DCT Basis
				double sN = 1./ sqrt(N);
				for (int i = 0; i < N; ++i)  B(i, 0) = sN;
				
				sN = sqrt(2./N);
				for (int k = 1; k < K; ++k)
					for (int i = 0; i < N; ++i)
						B(i,k) = sN * cos(M_PI*(2.*(i)+1)*(k)/(2.*N));
				break;
			}
		} 
		
		
	}
	
	
	vistal::Image3D<float> bias(vistal::Image3D<float>& ref)
	{
		vistal::Image3D<float> ima(ref, 0);
		
		int i0, i1, i2;
		int j0, j1, j2;
		float t2[MAXB*MAXB], t1[MAXB];
		
		int n0 = ima.nbx, n1 = ima.nby, n2 = ima.nbz;
		int m0 = order.x(), m1 = order.y(), m2 = order.z();
		
		//    std::fill(&data[0], &data[nh], 0);
		
		for(j2=0;j2<n2; j2++)
		{
			//	get_slice(vol,j2,dat);
			for(i0=0; i0<m0; i0++)
			{
				//	    t2[i0] = 0.0;
				for (i1 = 0; i1 < m1; ++i1)
				{
					t2[i0+i1*m0] = 0.0;
					for(i2=0;i2<m2; i2++)
						t2[i0+i1*m0] += B2(j2,i2)*T(i0,i1,i2);
				}
			}
			
			for(j1=0; j1<n1; j1++)
			{
				//  float *pdat = dat+j1*n0;
				for(i0=0; i0<m0; i0++)
				{
					t1[i0] = 0.0;
					for(i1=0;i1<m1; i1++)
						t1[i0] += B1(j1,i1)*t2[i0+m0*i1];
				}
				for(j0=0; j0<n0; j0++)
				{
					//		float y, y0 = ima(j0,j1,j2);//pdat[j0]*s;
					float sc = 0.0;
					for(i0=0;i0<m0; i0++)
						sc += B0(j0,i0)*t1[i0];
					float t = exp(sc);
					if (std::isfinite(t))
						ima(j0,j1,j2) = t;		
					else
						ima(j0,j1,j2) = 1;		
					// y is the bias corrected data
					
				}
			}
		}
		return ima;
	}
	
	vistal::Image3D<float> correct(vistal::Image3D<float>& ima, float scale = 1)
	{
		vistal::Image3D<float> im(ima, 0);
		
		int i0, i1, i2;
		int j0, j1, j2;
		float t2[MAXB*MAXB], t1[MAXB];
		
		int n0 = ima.nbx, n1 = ima.nby, n2 = ima.nbz;
		int m0 = order.x(), m1 = order.y(), m2 = order.z();
		
		//    std::fill(&data[0], &data[nh], 0);
		
		for(j2=0;j2<n2; j2++)
		{
			//	get_slice(vol,j2,dat);
			for(i0=0; i0<m0; i0++)
			{
				//	    t2[i0] = 0.0;
				for (i1 = 0; i1 < m1; ++i1)
				{
					t2[i0+i1*m0] = 0.0;
					for(i2=0;i2<m2; i2++)
						t2[i0+i1*m0] += B2(j2,i2)*T(i0,i1,i2);
				}
			}
			
			for(j1=0; j1<n1; j1++)
			{
				//  float *pdat = dat+j1*n0;
				for(i0=0; i0<m0; i0++)
				{
					t1[i0] = 0.0;
					for(i1=0;i1<m1; i1++)
						t1[i0] += B1(j1,i1)*t2[i0+m0*i1];
				}
				for(j0=0; j0<n0; j0++)
				{
					float y0 = ima(j0,j1,j2)*scale;//pdat[j0]*s;
					float sc = 0.0;
					
					for(i0=0;i0<m0; i0++)
						sc += B0(j0,i0)*t1[i0];
					
					float r = y0*exp(sc);
					
					if (std::isfinite(r))
						im(j0,j1,j2) = r;
				}
			}
		}
		return im;
	}
	
	
	Vect3Di dimension; // Size of each basis
	Vect3Di order;
	
	ublas::matrix<MatrixDataType> B0,B1,B2;
	
	
	
	//  Matrix B0, B1, B2; //  basis function
	vistal::Image3D<float> T;  //  basis weighting
};


ublas::vector<MatrixDataType> pow(ublas::vector<MatrixDataType>& v, int p)
{
	ublas::vector<MatrixDataType> r(v.size());
	for (unsigned i = 1; i < v.size(); ++i)
		r(i) = pow(v(i), p);
	
	return r;
}
// to compute the regularization parameter
ColumnVector pow(ColumnVector& v, int p)
{
	ColumnVector r(v.nrows());
	for (int i = 1; i < v.nrows(); ++i)
		r(i) = pow(v(i), p);	
	return r;
}

namespace spm
{
	
	class Histo
	{
		int _psh;
		int nh;
		
		float *data;
		float s;
		
		static const float EPS = 2.2204460492503130808e-16;
		
	public:
		
		Histo(int nbins, float mx): nh(nbins), s((nh-1.0)/mx)
		{
			data = new float[nbins];
		}
		
		~Histo() 
		{ 
			delete[] data;
		}
		
		int bins()
		{
			return nh;
		}
		int psh()
		{
			return _psh;
		}
		
		float scale()
		{
			return s;
		}
		
		void update(Basis& b, vistal::Image3D<float>& ima)
		{
			int i0, i1, i2;
			int j0, j1, j2;
			float t2[MAXB*MAXB], t1[MAXB];
			
			int n0 = ima.nbx, n1 = ima.nby, n2 = ima.nbz;
			int m0 = b.order.x(), m1 = b.order.y(), m2 = b.order.z();
			
			std::fill(&data[0], &data[nh], 0);
			
			for(j2=0;j2<n2; j2++)
			{
				for(i0=0; i0<m0; i0++)
				{
					for (i1 = 0; i1 < m1; ++i1)
					{
						t2[i0+i1*m0] = 0.0;
						
						for(i2=0;i2<m2; i2++)
							t2[i0+i1*m0] += b.B2(j2,i2)*b.T(i0,i1,i2);
					}
				}
				
				for(j1=0; j1<n1; j1++)
				{
					//  float *pdat = dat+j1*n0;
					for(i0=0; i0<m0; i0++)
					{
						t1[i0] = 0.0;
						for(i1=0;i1<m1; i1++)
							t1[i0] += b.B1(j1,i1)*t2[i0+m0*i1];
					}
					for(j0=0; j0<n0; j0++)
					{
						float y, y0 = ima(j0,j1,j2) * s;//pdat[j0]*s;
						
						if ((skip0 && y0>0.0) || (!skip0 && y0>=0))
						{
							int iy;
							float dy, sc = 0.0;
							for(i0=0;i0<m0; i0++)
								sc += b.B0(j0,i0)*t1[i0];
							y = y0*exp(sc);
							
							if (y>=0 && y<(nh-1))
								
								
							{
								iy = (int)floor(y);
								dy = y-iy;
								data[iy] += 1-dy;
								data[iy+1] += dy;
							}
						}
					}
				}
			}
			normhist(nh,data,1/s);
		}
		
		
		void updateWNoise(Basis& b, vistal::Image3D<float>& ima)
		{
			// Random value for the insertion of noise
			static float ran[] = {
				0.141571,-0.193651,0.160932,-0.141983,0.438199,-0.012333,-0.40901,0.173834,
				0.0148803,-0.278421,0.225009,-0.431753,0.464124,-0.292343,-0.338882,0.138221,
				-0.499772,-0.164367,-0.2249,-0.455472,-0.406104,-0.0900026,0.316892,0.370517,
				-0.477445,0.227177,0.348009,0.2286,0.455099,0.156351,0.242305,-0.155034,
				0.384022,-0.152756,-0.440523,0.218415,0.458214,-0.343165,-0.0836469,-0.405965,
				-0.0500535,0.369152,-0.108383,-0.247216,-0.145618,0.242978,0.150832,0.439793,
				0.332799,-0.0300221,0.129866,-0.441812,0.0421874,-0.044274,0.363087,0.355197,
				-0.0277443,0.286924,0.155982,-0.49996,-0.368763,-0.00512524,-0.461667,-0.272564,
				-0.172117,0.399469,-0.18627,-0.248324,-0.0670109,0.342382,-0.315511,0.00817921,
				-0.0477603,-0.174416,-0.119924,0.38648,0.261261,0.383766,-0.0425937,0.299202,
				-0.365923,-0.434686,-0.124855,-0.126477,-0.0159776,0.469459,-0.157939,-0.247311,
				0.0848869,0.0237036,-0.336581,-0.0136019,-0.00393925,0.343194,0.306198,0.357786,
				0.109754,0.0657304,0.111899,-0.397023,-0.341684,-0.0863501,0.0604104,-0.231323,
				0.284254,-0.112129,-0.469016,0.0855018,0.0585585,-0.299304,-0.412578,0.43323,
				-0.24062,-0.295829,-0.450792,0.106161,0.0463487,-0.404163,0.136996,-0.0570517,
				-0.433618,-0.125707,-0.250897,0.424875,0.129499,0.378309,0.141674,0.298391,
				-0.064974,0.48114,-0.404042,0.0274824,0.0456458,-0.215657,-0.129197,-0.435307,
				0.0448091,0.336376,-0.354678,-0.32848,-0.431953,0.324012,-0.366029,0.384786,
				0.0147374,0.463636,-0.379505,-0.45171,-0.119848,-0.0872088,-0.0986087,-0.0790029,
				-0.123046,0.407337,0.170162,0.461839,-0.337021,0.248649,-0.125934,-0.0457635,
				-0.461439,0.062432,-0.127688,0.292784,0.295231,-0.117086,-0.24721,-0.157072,
				0.467804,-0.0201916,-0.131672,0.264567,-0.122851,0.400306,-0.316568,-0.131683,
				0.417457,0.0159161,-0.409693,0.235311,-0.495288,0.103123,0.456867,-0.102568,
				0.231551,0.184639,0.478503,-0.296215,0.0933028,0.451563,-0.239728,0.0146776,
				0.136332,-0.0990409,-0.0133887,0.250458,-0.373803,-0.456938,-0.129061,0.193302,
				0.435825,-0.0224244,-0.3709,-0.0161688,0.445597,-0.132256,-0.171514,0.272875,
				-0.202726,-0.322146,0.190799,-0.236055,-0.0422609,0.343692,0.381499,0.20002,
				0.255691,0.474515,-0.0978473,-0.368721,0.224734,0.399518,-0.329299,-0.456971,
				-0.0208408,-0.406064,0.15005,0.452278,-0.0422873,0.0368806,-0.433513,-0.00612992,
				-0.082459,-0.207743,-0.210336,0.253846,-0.403204,-0.423083,0.220915,0.264912,
				0.157945,0.310409,-0.125757,-0.193769,-0.1293,0.206747,-0.331634,0.313721,
				-0.0337717,0.222286,0.494869,-0.137497,0.230828,0.149667,0.181339,-0.492388,
				0.154149,0.445235,0.113271,0.282928,-0.496847,0.296958,0.141817,-0.321521,
				0.0294007,-0.281256,0.0480524,-0.441763,0.0875871,-0.0838964,-0.313555,-0.436089,
				-0.425217,-0.189963,0.444085,0.480727,0.0551155,0.488526,0.19156,-0.258339,
				0.309814,0.434512,-0.371197,0.186827,-0.202755,0.147221,-0.0362412,0.42279,
				-0.258278,0.160157,-0.167713,-0.023247,-0.0312267,0.205929,-0.260051,0.217203,
				0.365197,-0.0890103,-0.0752128,0.454286,0.381419,0.198588,-0.194599,0.329326,
				0.470605,-0.199897,0.498062,-0.0592516,-0.493773,-0.208099,0.191878,-0.00715073,
				-0.416522,-0.304213,0.477595,-0.133801,-0.360568,-0.485244,0.140641,0.237722,
				-0.473243,-0.397847,0.39333,0.263876,0.0826645,0.18543,0.467134,0.0503444,
				0.277197,0.11035,0.488593,-0.451738,0.485389,-0.295264,0.412477,0.165546,
				-0.0376786,-0.451667,-0.0395608,0.299951,-0.210567,0.195102,-0.240721,0.21323,
				0.22037,0.233277,0.122331,0.489779,-0.347622,-0.296677,0.319317,-0.441565,
				0.0385068,-0.309847,0.0994808,-0.207742,-0.408712,0.00676728,0.384132,0.115568,
				-0.453608,0.451924,-0.33097,0.326671,0.111377,0.347299,-0.385877,0.14922,
				-0.385185,-0.0265878,0.183181,-0.366701,-0.0359218,-0.42875,0.0812184,0.0659789,
				-0.244738,-0.261506,-0.484046,-0.115255,0.2573,0.07516,-0.0919145,-0.304292,
				0.0121743,0.213346,0.367386,0.241805,0.494833,0.366748,-0.0141872,0.403305,
				-0.479686,0.136787,0.444056,-0.45922,-0.214328,0.177254,0.0861783,-0.43503};
			
			int i0, i1, i2;
			int j0, j1, j2;
			float t2[MAXB*MAXB], t1[MAXB];
			
			int n0 = ima.nbx, n1 = ima.nby, n2 = ima.nbz;
			int m0 = b.order.x(), m1 = b.order.y(), m2 = b.order.z();
			
			std::fill(&data[0], &data[nh], 0);
			
			for(j2=0;j2<n2; j2++)
			{
				for(i0=0; i0<m0; i0++)
				{
					for (i1 = 0; i1 < m1; ++i1)
					{
						t2[i0+i1*m0] = 0.0;
						
						for(i2=0;i2<m2; i2++)
							t2[i0+i1*m0] += b.B2(j2,i2) * b.T(i0,i1,i2);
					}
				}
				int iran = j2*10;
				//	      iran = j2*10;
				
				for(j1=0; j1<n1; j1++)
				{												
					//  float *pdat = dat+j1*n0;
					for(i0=0; i0<m0; i0++)
					{
						t1[i0] = 0.0;
						for(i1=0;i1<m1; i1++)
							t1[i0] += b.B1(j1,i1)*t2[i0+m0*i1];
					}
					
					for(j0=0; j0<n0; j0++)
					{
						
						iran = (iran+1)%397;
						float y, y0 = ima(j0,j1,j2) * s + ran[iran];//pdat[j0]*s;
						if ((skip0 && y0>0.0) || (!skip0 && y0>=0))
						{
							int iy;
							float dy, sc = 0.0;
							for(i0=0;i0<m0; i0++)
								sc += b.B0(j0,i0)*t1[i0];
							y = y0*exp(sc);
							if (y>=0 && y<(nh-1))
							{
								iy = (int)floor(y);
								dy = y-iy;
								data[iy] += 1-dy;
								data[iy+1] += dy;
							}
						}
					}
				}
			}
			normhist(nh,data,1/s);
		}
		
		void weights(float dat, double sc,
					 MatrixDataType &wt0, MatrixDataType &wt1, double &ll)
		{
			float y, dy, f, df, t;
			int iy;
			
			y = dat*sc*s;
			if ( ((skip0 && y > 0.0) || (!skip0 && y>=0)) && y < nh-1.0 )
			{
				iy   = (int)floor(y);
				dy   = y-iy;
				f    = ((1.0-dy)*data[iy] + dy*data[iy+1])+EPS;
				df   = (data[iy+1]-data[iy])*s;
				t    = dat*sc*df/f;
				wt0 = -1.0 - t;
				wt1 =  t*t - t;
				ll -=  log(f*sc);
			}
			else
			{
				wt0 = 0.0;
				wt1 = 0.0;
			}
		}
		
		
	protected:
		void normhist(int nh, float h[], float binwidth)
		{
			float sh = 0.0;
			int i;
			for(i=0; i<nh; i++)
				sh += h[i];
			for(i=0; i<nh; i++)
				h[i]/= binwidth*sh;
			
			_psh = (int)rint(sh);
		}
		
		
	};
	
}



/********************************************************************************/
/* Beta = kron(B1,B0)'*img(:)
 * m0  - rows in B0
 * m1  - rows in B1
 * n0  - columns in B0
 * n1  - columns in B1
 * img - m0*m1 vector
 * B0  - basis functions - x
 * B1  - basis functions - y
 * Beta - resulting vector
 *
 * required: n0, n1, m0, m1, img, B0, B1
 * modified: Beta
 */
static void kronutil1(Basis& basis, ublas::matrix<MatrixDataType>&  img, double Beta[])
{
	double Beta1[basis.order.x()];
	
	const int n0 = basis.order.x();
	const int n1 = basis.order.y();
	
	const int m0 = basis.dimension.x();
	const int m1 = basis.dimension.y();
	
	/* Zero Beta */
	for(int j1 = 0; j1 < n0 * n1; j1++) Beta[j1]=0.0;
	
	for(int i2 = 0; i2 < m1; i2++)
    {
		/* generate small Beta */
		for(int j1 = 0; j1 < n0; j1++) Beta1[j1]=0.0;
		for(int i1 = 0; i1 < m0; i1++)
		{
			double wt = img(i1,i2);
			for(int j1 = 0; j1 < n0; j1++)
				Beta1[j1] += basis.B0(i1, j1)*wt;
		}
		
		/* kronecker tensor product to increment Beta */
		for(int j2 = 0; j2 < n1; j2++)
		{
			double wt = basis.B1(i2, j2);
			double *ptrb = Beta+(n0*j2);
			for(int j1 = 0; j1 < n0; j1++)
				ptrb[j1] += wt*Beta1[j1];
		}
    }  
	/*
	 std::ofstream f("betaBlas");
	 for (int i = 0; i < n0*n1; ++i)
	 f << Beta[i] << std::endl;
	 exit(0);
	 */
}
/********************************************************************************/

/********************************************************************************/
/* Alpha = kron(B1,B0)'*diag(img(:))*kron(B1,B0)
 * m0  - rows in B0
 * m1  - rows in B1
 * n0  - columns in B0
 * n1  - columns in B1
 * img - m0*m1 vector
 * B0  - basis functions - x
 * B1  - basis functions - y
 * Alpha - resulting matrix
 *
 * required: n0, n1, m0, m1, img, B0, B1
 * modified: Alpha
 */
static void kronutil2(Basis& basis, ublas::matrix<MatrixDataType>& img, double Alpha[])
{
	double Alpha1[basis.order.x()*basis.order.y()];
	
	const int n0 = basis.order.x();
	const int n1 = basis.order.y();
	
	const int m0 = basis.dimension.x();
	const int m1 = basis.dimension.y();
	
	const int n01 = n0 * n1;
	/* Zero Alpha */
	for(int j21 = 0; j21 < n01; j21++)
		for(int j11 = 0; j11 <= j21; j11++)
			Alpha[j11+j21*n01] = 0.0;
	
	for(int i2 = 0; i2 < m1; i2++)
    {
		/* zero small Alpha */
		for(int j21 = 0; j21 < n0; j21++)
			for(int j11 = 0; j11 <= j21; j11++)
				Alpha1[j11+j21*n0]=0.0;
		
		/* generate upper half of small Alpha */
		for(int i1 = 0; i1 < m0; i1++)
		{
			double wt = img(i1, i2);
			for(int j21 = 0; j21 < n0; j21++)
			{
				double wt2 = wt*basis.B0(i1,j21);
				for(int j11=0; j11 <= j21; j11++)
					Alpha1[j11+j21*n0] += wt2*basis.B0(i1, j11);
			}
		}
		
		/* kronecker tensor product to increment upper half of large Alpha */
		for(int j22 = 0; j22 < n1; j22++)
		{
			double wt = basis.B1(i2, j22);
			for(int j12 = 0; j12 <= j22; j12++)
			{
				double *ptra = Alpha+(n0*j12+n0*n01*j22);
				float wt2 = wt*basis.B1(i2,j12);
				
				for(int j21=0; j21<n0; j21++)
					for(int j11=0; j11<=j21; j11++)
						ptra[j11+j21*n01] += wt2*Alpha1[j11+j21*n0];
			}
		}
    }
	/* fill in lower triangle of symmetric submatrices of Alpha */
	for(int j22=0; j22<n1; j22++)
		for(int j12=0; j12<j22; j12++)
		{
			double *ptra = Alpha+(n0*j12+n0*n01*j22);
			for(int j21=0; j21<n0; j21++)
				for(int j11=0; j11<j21; j11++)
					ptra[j21+j11*n01] = ptra[j11+j21*n01];
		}
	
	/* fill in lower triangle of Alpha */
	for(int j22=0; j22<n1*n0; j22++)
		for(int j12=0; j12<j22; j12++)
			Alpha[j22+j12*n01]=Alpha[j12+j22*n01];
	
}
/********************************************************************************/

void kronutil(Basis& basis, int slice,
			  ublas::matrix<MatrixDataType>& wt0, ublas::matrix<MatrixDataType>& wt1,
			  ublas::matrix<MatrixDataType>& Alpha, ublas::vector<MatrixDataType>& Beta)
{
	// Buffer
	double Alpha1[basis.order.x()*basis.order.y()*basis.order.x()*basis.order.y()];
	double Beta1[basis.order.x()*basis.order.y()];
	
	// Need kronutil1 and kronutil2
	kronutil1(basis, wt0, Beta1);
	kronutil2(basis, wt1, Alpha1);
	
	int n01 = basis.order.x()*basis.order.y();
	int n2 = basis.order.z();
	
	// parallelize on z
	for (int j2 = 0; j2 < basis.order.z(); ++j2)
    {
		//int k01,k2;
		
		for (int j01 = 0; j01 < basis.order.x()*basis.order.y(); ++j01)
			Beta(j01 + j2*n01)  += Beta1[j01]*basis.B2(slice, j2);
		for(int k2 = 0; k2 < basis.order.z(); ++k2)
		{
			double tmp = basis.B2(slice, j2)*basis.B2(slice, k2);
			for(int j01=0; j01 < n01; j01++)
				for(int k01=0; k01 < n01; k01++)
					Alpha.data()[k01 + k2*n01 + (j01 + j2*n01)*(n01*n2)] += Alpha1[k01 + j01*n01]*tmp;
		}
    }
	
}





#endif /* #ifndef SPMBIAS_BLAS_H */