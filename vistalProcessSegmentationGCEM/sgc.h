#ifndef SGC_H
#define SGC_H

#include <cmath>
#include "graph.h"


typedef Graph<double, double, double> GraphType;
using namespace std;


template <class T1,class T2>
double dist( T1 x1, T2 x2, T1 y1, T2 y2, T1 z1, T2 z2 )
{
  return sqrt(pow( ( double ) ( ( double )x1 -(double)x2 ), 2.0 )
      + pow( ( double ) ( ( double )y1 - (double)y2 ), 2.0 )
      + pow( ( double ) ( ( double )z1 - (double)z2 ), 2.0 )
         );
}

double n_link( vistal::Image3D<float> &e, vistal::Image3D<float> &e_l, vistal::Image3D<float> &e_l_l,
               int z1, int y1, int x1, int z2, int y2, int x2)
{
  float g = ( e_l.ptr[ z1 ][ y1 ][ x1 ] / e.ptr[ z1 ][ y1 ][ x1 ] ) - ( e_l.ptr[ z2 ][ y2 ][ x2 ] / e.ptr[ z2 ][ y2 ][ x2 ] );
  float w = ( ( e.ptr[ z1 ][ y1 ][ x1 ] * e_l_l.ptr[ z1 ][ y1 ][ x1 ] - e_l.ptr[ z1 ][ y1 ][ x1 ] * e_l.ptr[ z1 ][ y1 ][ x1 ] )  / ( e.ptr[ z1 ][ y1 ][ x1 ] * e.ptr[ z1 ][ y1 ][ x1 ] ) ) - ( ( e.ptr[ z2 ][ y2 ][ x2 ] * e_l_l.ptr[ z2 ][ y2 ][ x2 ] - e_l.ptr[ z2 ][ y2 ][ x2 ] * e_l.ptr[ z2 ][ y2 ][ x2 ] ) / ( e.ptr[ z2 ][ y2 ][ x2 ] * e.ptr[ z2 ][ y2 ][ x2 ] ) );
  return ( double )( exp( -( g * g + w * w ) / ( 2 * 0.6 * 0.6 ) ) );
  //return (double) (exp(-(g*g+w*w)/(2*0.6*0.6)));
}

template <class T>
int somme( vistal::Image3D<T> &img )
{
  int a = 0;
  for ( int k = 0; k < img.nbz; k++ )
    for ( int j = 0; j < img.nby; j++ )
      for ( int i = 0; i < img.nbx; i++ )
        if ( img.ptr[ k ][ j ][ i ] != 0 )
          a += 1;
  return a;
}

template <class T,class T2>
void uncoarsening( vistal::Image3D<T> &input, vistal::Image3D<T> &output, vistal::Image3D<T2> &ref )
{
  output.redimensionne( ref.nbx, ref.nby, ref.nbz );
  output.dx = ref.dx;
  output.dy = ref.dy;
  output.dz = ref.dz;
  output.orientation = ref.orientation;
  output.init( 0 );
  for ( int k = 0; k < input.nbz; k++ )
    for ( int j = 0; j < input.nby; j++ )
      for ( int i = 0; i < input.nbx; i++ )
        if ( input.ptr[ k ][ j ][ i ] != 0 )
        {
          for ( int z = ( 2 * k ) - 1; z < ( 2 * k ) + 1; z++ )
            for ( int y = ( 2 * j ) - 1; y < ( 2 * j ) + 1; y++ )
              for ( int x = ( 2 * i ) - 1; x < ( 2 * i ) + 1; x++ )
                if ( output.isInside( x, y , z ) )
                  output.ptr[ z ][ y ][ x ] = 1;
        }

}

template <class T>
void ecrit_image ( GraphType *g, vistal::Image3D<T> &img, vistal::Image3D<unsigned char> &out, vistal::Image3D<unsigned char> &mask )
{
  out.redimensionne( mask );
  copie_param_volume(out,mask);

  if ( somme( mask ) != mask.size )
  {
    int cpt = 0;
    for ( int k = 0; k < out.nbz;k++ )
      for ( int j = 0; j < out.nby;j++ )
        for ( int i = 0; i < out.nbx;i++ )
          if ( mask.ptr[ k ][ j ][ i ] != 0 )
          {
//             ( g->what_segment( cpt ) == GraphType::SOURCE ) ? out.ptr[ k ][ j ][ i ] = 1 : out.ptr[ k ][ j ][ i ] = 0;
            (g->what_segment(cpt) == GraphType::SOURCE)? out.ptr[k][j][i]=1 : out.ptr[k][j][i]=3;
            if (g->what_segment(cpt) == GraphType::SINK)
              out.ptr[k][j][i]=0;
            cpt++;
          }
  }
  else
  {

    for ( int i = 0; i < img.size ; i++ )
    {
      int z = i / ( img.nbx * img.nby );
      int y = ( i % ( img.nbx * img.nby ) ) / img.nbx;
      int x = ( i % ( img.nbx * img.nby ) ) % img.nbx;
//       ( g->what_segment( i ) == GraphType::SOURCE ) ? out.ptr[ z ][ y ][ x ] = 1 : out.ptr[ z ][ y ][ x ] = 0;
      (g->what_segment(i) == GraphType::SOURCE)? out.ptr[z][y][x]=1 : out.ptr[z][y][x]=3;
      if (g->what_segment(i) == GraphType::SINK)
        out.ptr[z][y][x]=0;

    }
  }
}

void print_error(char * ch)
{
  std::cout<<" ** ERROR in Graph: "<<ch<<std::endl;
}

template <class T>
void GC ( vistal::Image3D<T> &im1, vistal::Image3D<T> &im2, vistal::Image3D<T> &im3, vistal::Image3D<unsigned char> &out, vistal::Image3D<float> &p_source, vistal::Image3D<float> &p_puits, vistal::Image3D<unsigned char> mask, double alpha )
{

  double min_p_s = 1.0, min_p_p = 1.0, max_p_s = 0.0, max_p_p = 0.0, min_n_l = 1.0, max_n_l = 0.0;
  int nb_edges;
  bool mem = true;
  // double sig=120.0;
  GraphType *g;
  int nbpix = somme( mask );
  nb_edges = 7 * nbpix;
  try
  {
    g = new GraphType( nbpix, nb_edges, &print_error );
  }
  catch ( bad_alloc& )
  {
    //std::cout << "MÈmoire insuffisante - dÈcimation d'ordre 2" << std::endl;
    cout<<" ** Not enough memory : order 2 decimation"<<std::endl;
    mem = false;
  }

  if ( mem )
  {
    //    calcul de e et de ses dÈrivÈes spectrales
    vistal::Image3D<float> e, e_l, e_l_l;
    vistal::Image3D<float> proba_puits, proba_source;

    e.redimensionne( im1.nbx, im1.nby, im1.nbz );
    copie_param_volume(e,im1);

    e_l.redimensionne( im1.nbx, im1.nby, im1.nbz );
    copie_param_volume(e_l,im1);

    e_l_l.redimensionne( im1.nbx, im1.nby, im1.nbz );
    copie_param_volume(e_l_l,im1);

    cout<<" -- Computing spectral gradient"<<std::endl;
    for ( int k = 0; k < im1.nbz; k++ )
      for ( int j = 0; j < im1.nby; j++ )
        for ( int i = 0; i < im1.nbx; i++ )
        {
          e.ptr[ k ][ j ][ i ] =
              0.002358 * ( float ) im1.ptr[ k ][ j ][ i ]
              + 0.025174 * ( float ) im2.ptr[ k ][ j ][ i ]
              + 0.010821 * ( float ) im3.ptr[ k ][ j ][ i ];
          e_l.ptr[ k ][ j ][ i ] =
              0.011943 * ( float ) im1.ptr[ k ][ j ][ i ]
              + 0.001715 * ( float ) im2.ptr[ k ][ j ][ i ]
              - 0.013994 * ( float ) im3.ptr[ k ][ j ][ i ];
          e_l_l.ptr[ k ][ j ][ i ] =
              0.013743 * ( float ) im1.ptr[ k ][ j ][ i ]
              - 0.023965 * ( float ) im2.ptr[ k ][ j ][ i ]
              + 0.00657 * ( float ) im3.ptr[ k ][ j ][ i ];
        }




    cout << " -- Graph creation" << endl;
    for ( int k = 0; k < im1.nbz; k++ )
      for ( int j = 0; j < im1.nby; j++ )
        for ( int i = 0; i < im1.nbx; i++ )
        {
          if ( mask.ptr[ k ][ j ][ i ] > 0. )
            g -> add_node();
        }


    if ( nbpix != im1.size )
    {

      //version masquÈe
      cout<<" -- Masked version"<<std::endl;
      int compt = 0;
      int* num_pixel = new int[ im1.size ];
      //initialisation du tableau de correspondance

      for ( int k = 0; k < im1.nbz; k++ )
        for ( int j = 0; j < im1.nby; j++ )
          for ( int i = 0; i < im1.nbx; i++ )
      {
            if ( mask.ptr[ k ][ j ][ i ] > 0. )
            {
              //cela correspond donc au n∞ du node;
              num_pixel[ ( k ) * im1.nbx * im1.nby + ( j ) * im1.nbx + ( i ) ] = compt++;
            }
            else
            {
              num_pixel[ ( k ) * im1.nbx * im1.nby + ( j ) * im1.nbx + ( i ) ] = -1;
            }
      }

      //triple boucle de parcours
      std::cout<<" -- Adding weigths to the graph"<<std::endl;
      for ( int k = 0; k < im1.nbz; k++ )
        for ( int j = 0; j < im1.nby; j++ )
          for ( int i = 0; i < im1.nbx; i++ )
          {
            if ( mask.ptr[ k ][ j ][ i ] > 0. )
            {

              int pix_ref, pix_courant;
              pix_ref = num_pixel[ ( k ) * im1.nbx * im1.nby + ( j ) * im1.nbx + ( i ) ]; //le pixel de rÈfÈrence
              //T-liens
              double poids_source, poids_puits;

              poids_source = alpha * p_source.ptr[ k ][ j ][ i ];
              poids_puits = alpha * p_puits.ptr[ k ][ j ][ i ];

              if ( poids_source > max_p_s )
                max_p_s = poids_source;
              if ( poids_source < min_p_s )
                min_p_s = poids_source;
              if ( poids_puits > max_p_p )
                max_p_p = poids_puits;
              if ( poids_puits < min_p_p )
                min_p_p = poids_puits;

              g->add_tweights( pix_ref, poids_source, poids_puits );

              //N-liens
              //pour chacun des voisins (on considËre ici une 6-connexitÈ), on crÈe une arÍte sortante et une arÍte entrante.
              //On ne prends ici que la moitiÈ des voisins - soit 3 - afin de ne pas crÈer les arÍtes deux fois.

              double cap = 0, rcap = 0;
              if ( ( im1.isInside( i, j + 1 , k ) ) && ( mask.ptr[ k ][ j + 1 ][ i ] > 0. ) )
              {
                pix_courant = num_pixel[ ( k ) * im1.nbx * im1.nby + ( j + 1 ) * im1.nbx + ( i ) ]; //on calcule la position du noeud dans g
                cap =n_link( e, e_l, e_l_l, k, j + 1, i, k, j, i); //calcul de la capacitÈ de l'arÍte
                rcap = n_link( e, e_l, e_l_l, k, j, i, k, j + 1, i); //calcul de la capacitÈ de la reverse arÍte
                if ( !( cap >= 0 ) )
                {
                  cap = rcap = 0;
                }
                g-> add_edge( pix_ref, pix_courant, cap, rcap );
                if ( cap > max_n_l )
                  max_n_l = cap;
                if ( cap < min_n_l )
                  min_n_l = cap;
              }
              if ( ( im1.isInside( i + 1, j , k ) ) && ( mask.ptr[ k ][ j ][ i + 1 ] > 0. ) )
              {
                pix_courant = num_pixel[ ( k ) * im1.nbx * im1.nby + ( j ) * im1.nbx + ( i + 1 ) ]; //on calcule la position du noeud dans g
                cap = n_link( e, e_l, e_l_l, k, j, i, k, j, i + 1); //calcul de la capacitÈ de l'arÍte
                rcap =n_link( e, e_l, e_l_l, k, j, i + 1, k, j, i); //calcul de la capacitÈ de la reverse arÍte
                if ( !( cap >= 0 ) )
                {
                  cap = rcap = 0;
                }
                g-> add_edge( pix_ref, pix_courant, cap, rcap );
                if ( cap > max_n_l )
                  max_n_l = cap;
                if ( cap < min_n_l )
                  min_n_l = cap;
              }
              if ( ( im1.isInside( i, j , k + 1 ) ) && ( mask.ptr[ k + 1 ][ j ][ i ] > 0. ) )
              {
                pix_courant = num_pixel[ ( k + 1 ) * im1.nbx * im1.nby + ( j ) * im1.nbx + ( i ) ]; //on calcule la position du noeud dans g
                cap = n_link( e, e_l, e_l_l, k + 1, j, i, k, j, i ); //calcul de la capacitÈ de l'arÍte
                rcap =  n_link( e, e_l, e_l_l, k, j, i, k + 1, j, i ); //calcul de la capacitÈ de la reverse arÍte
                if ( !( cap >= 0 ) )
                {
                  cap = rcap = 0;
                }
                g-> add_edge( pix_ref, pix_courant, cap, rcap );
                if ( cap > max_n_l )
                  max_n_l = cap;
                if ( cap < min_n_l )
                  min_n_l = cap;
              }
            }
          }
    }
    else
    { //version sans masque

      cout<<" -- Non Masked version"<<std::endl;
      for ( int k = 0; k < im1.nbz; k++ )
        for ( int j = 0; j < im1.nby; j++ )
          for ( int i = 0; i < im1.nbx; i++ )
          {
            int pix_ref, pix_courant;
            pix_ref = ( k ) * im1.nbx * im1.nby + ( j ) * im1.nbx + ( i ); //le pixel de rÈfÈrence

            //T-liens
            double poids_source, poids_puits;

            poids_source = alpha * p_source.ptr[ k ][ j ][ i ];
            poids_puits = alpha * p_puits.ptr[ k ][ j ][ i ];

            if ( poids_source > max_p_s )
              max_p_s = poids_source;
            if ( poids_source < min_p_s )
              min_p_s = poids_source;
            if ( poids_puits > max_p_p )
              max_p_p = poids_puits;
            if ( poids_puits < min_p_p )
              min_p_p = poids_puits;


            g->add_tweights( pix_ref, poids_source, poids_puits );

            //N-liens
            //pour chacun des voisins (on considËre ici une 6-connexitÈ), on crÈe une arÍte sortante et une arÍte entrante.
            //On ne prends ici que la moitiÈ des voisins - soit 3 - afin de ne pas crÈer les arÍtes deux fois.

            double cap = 0, rcap = 0;

            if ( im1.isInside( i, j + 1 , k ) )
            {
              pix_courant = ( k ) * im1.nbx * im1.nby + ( j + 1 ) * im1.nbx + ( i ); //on calcule la position du noeud dans g
              cap = n_link( e, e_l, e_l_l, k, j + 1, i, k, j, i ); //calcul de la capacitÈ de l'arÍte
              rcap =n_link( e, e_l, e_l_l, k, j, i, k, j + 1, i ); //calcul de la capacitÈ de la reverse arÍte
              if ( !( cap >= 0 ) )
              {
                cap = rcap = 0;
              }
              g-> add_edge( pix_ref, pix_courant, cap, rcap );
              if ( cap > max_n_l )
                max_n_l = cap;
              if ( cap < min_n_l )
                min_n_l = cap;
            }
            if ( im1.isInside( i + 1, j , k ) )
            {
              pix_courant = ( k ) * im1.nbx * im1.nby + ( j ) * im1.nbx + ( i + 1 ); //on calcule la position du noeud dans g
              cap =n_link( e, e_l, e_l_l, k, j, i, k, j, i + 1 ); //calcul de la capacitÈ de l'arÍte
              rcap = n_link( e, e_l, e_l_l, k, j, i + 1, k, j, i ); //calcul de la capacitÈ de la reverse arÍte
              if ( !( cap >= 0 ) )
              {
                cap = rcap = 0;
              }
              g-> add_edge( pix_ref, pix_courant, cap, rcap );
              if ( cap > max_n_l )
                max_n_l = cap;
              if ( cap < min_n_l )
                min_n_l = cap;
            }
            if ( im1.isInside( i, j , k + 1 ) )
            {
              pix_courant = ( k + 1 ) * im1.nbx * im1.nby + ( j ) * im1.nbx + ( i ); //on calcule la position du noeud dans g
              cap = n_link( e, e_l, e_l_l, k + 1, j, i, k, j, i ); //calcul de la capacitÈ de l'arÍte
              rcap = n_link( e, e_l, e_l_l, k, j, i, k + 1, j, i); //calcul de la capacitÈ de la reverse arÍte
              if ( !( cap >= 0 ) )
              {
                cap = rcap = 0;
              }
              g-> add_edge( pix_ref, pix_courant, cap, rcap );
              if ( cap > max_n_l )
                max_n_l = cap;
              if ( cap < min_n_l )
                min_n_l = cap;
            }
          }
    }

    std::cout<<" -- Compute maxflow"<<std::endl;
    g -> maxflow();

    cout<<"    -- t-link sink   : max "<<max_p_p<<"\tmin : "<<min_p_p<<endl;
    cout<<"       t-link source : max "<<max_p_s<<"\tmin : "<<min_p_s<<endl;
    cout<<"       n-link        : max "<<max_n_l<<"\tmin : "<<min_n_l<<endl;

    std::cout<<" -- Save graph into the image"<<std::endl;
    ecrit_image ( g, im1, out, mask );
    delete g;
  }
  else
  {
    std::cout<<" -- Decimation the image!"<<std::endl;
    vistal::Image3D<T> im1_dec, im2_dec, im3_dec;
    vistal::Image3D<unsigned char> mask_dec;
    vistal::Image3D<float> puits_dec, source_dec;
    vistal::decimation( im1_dec, im1, 2 );
    vistal::decimation( im2_dec, im2, 2 );
    vistal::decimation( im3_dec, im3, 2 );
    vistal::decimation( mask_dec, mask, 2 );
    vistal::decimation( puits_dec, p_puits, 2 );
    vistal::decimation( source_dec, p_source, 2 );
    GC( im1_dec, im2_dec, im3_dec, out, source_dec, puits_dec, mask_dec,alpha );
    uncoarsening( out, mask, im1 );
    Dilate( mask, mask, 4 );
    cout << " -- Computing GraphCut in the real image" << endl;
    GC( im1, im2, im3, out, p_source, p_puits, mask,alpha );
  }
}



#endif // SGC_H
