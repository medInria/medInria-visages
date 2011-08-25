/*
** Legendre.hh
** Login : <nwiestda@pallium.irisa.fr>
** Started on  Thu Jun 18 11:37:32 2009 Nicolas Wiest-Daessle
** $Id$
** 
** Copyright (C) 2009 Nicolas Wiest-Daessle
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

#ifndef   	LEGENDRE_HH_
# define   	LEGENDRE_HH_

#include <boost/preprocessor/repetition/for.hpp>

// Recursive template for legendre polynomials

template <int order>
float PolynomeDeLegendre(float x)
{
  return 
    ((2.*order) * x * 
     PolynomeDeLegendre<order-1>(x)-((float)order-1.) * 
     PolynomeDeLegendre<order-2>(x))
    / (float)order;
}

template<>
float PolynomeDeLegendre<0>(float x)
{
  return 1;
}

template<>
float PolynomeDeLegendre<1>(float x)
{
  return x;
}

template<>
float PolynomeDeLegendre<2>(float x)
{
  return 0.5*(3*pow(x,2.f)-1);
}

template<>
float PolynomeDeLegendre<3>(float x)
{
  return 0.5*(5*pow(x,3.f)-3*x);
}

template<>
float PolynomeDeLegendre<4>(float x)
{
  return 1./8.*(35*pow(x,4.f)-30*pow(x,2.f)+3);
}

template<>
float PolynomeDeLegendre<5>(float x)
{
  return 1./8.*(63*pow(x,5.f)-70*pow(x,3.f)+15*x);
}


template<>
float PolynomeDeLegendre<6>(float x)
{
  return 1./16.*(231.*pow(x,6.f)-315.*pow(x,4.f)+105.*pow(x,2.f)-5.);
}


template<>
float PolynomeDeLegendre<7>(float x)
{
  return 1./16.*(429.*pow(x,7.f) - 693.*pow(x,5.f)+315.*pow(x,3.f)-35.*x);
}

template<>
float PolynomeDeLegendre<8>(float x)
{
  return 1./128.*(6435.*pow(x,8.f) - 12012.*pow(x,6.f)+ 6930.*pow(x,4.f)-1260.*pow(x,2.f)+35.);
}

template<>
float PolynomeDeLegendre<9>(float x)
{
  return 1./128.*(12155.*pow(x,9.f) - 25740.*pow(x,7.f)+ 18018.*pow(x,5.f)-4620*pow(x,3.f)+315.*x);
}

template<>
float PolynomeDeLegendre<10>(float x)
{
  return 1./256.*(46189.*pow(x,10.f) - 109395.*pow(x,8.f)+ 
		  90090.*pow(x,6.f) - 30030*pow(x,4.f)+ 3565*pow(x,2.f) - 63);
}







// Creates the table of legendre polynomials, to unroll the templates
// use this to get a specific order legendre polynomial
// LegendreTable[order](x)
// gives you the value of the lgendre polynom of order 'order' at x
#define LegendreCount 55
float (*LegendreTable[])(float x) =
{
#define GEN_Legendre_D(Count) PolynomeDeLegendre<Count>,
#define GEN_Legendre(r, state) GEN_Legendre_D(BOOST_PP_TUPLE_ELEM(2,0, state))

//  BOOST_PP_FOR((0, LegendreCount), PRED, OP, GEN_Legendre)
	PolynomeDeLegendre<0>,
	PolynomeDeLegendre<1>,
	PolynomeDeLegendre<2>,
	PolynomeDeLegendre<3>,
	PolynomeDeLegendre<4>,
	PolynomeDeLegendre<5>,
	PolynomeDeLegendre<6>,
	PolynomeDeLegendre<7>,
	PolynomeDeLegendre<8>,
	PolynomeDeLegendre<9>,
	PolynomeDeLegendre<10>,
	PolynomeDeLegendre<11>,
	PolynomeDeLegendre<12>,
	PolynomeDeLegendre<13>,
	PolynomeDeLegendre<14>,
	PolynomeDeLegendre<15>,
	PolynomeDeLegendre<16>,
	PolynomeDeLegendre<17>,
	PolynomeDeLegendre<18>,
	PolynomeDeLegendre<19>,
	PolynomeDeLegendre<20>,
	PolynomeDeLegendre<21>,
	PolynomeDeLegendre<22>,
	PolynomeDeLegendre<23>,
	PolynomeDeLegendre<24>,
	PolynomeDeLegendre<25>,
	PolynomeDeLegendre<26>,
	PolynomeDeLegendre<27>,
	PolynomeDeLegendre<28>,
	PolynomeDeLegendre<29>,
	PolynomeDeLegendre<30>,
	PolynomeDeLegendre<31>,
	PolynomeDeLegendre<32>,
	PolynomeDeLegendre<33>,
	PolynomeDeLegendre<34>,
	PolynomeDeLegendre<35>,
	PolynomeDeLegendre<36>,
	PolynomeDeLegendre<37>,
	PolynomeDeLegendre<38>,
	PolynomeDeLegendre<39>,
	PolynomeDeLegendre<40>,
	PolynomeDeLegendre<41>,
	PolynomeDeLegendre<42>,
	PolynomeDeLegendre<43>,
	PolynomeDeLegendre<44>,
	PolynomeDeLegendre<45>,
	PolynomeDeLegendre<46>,
	PolynomeDeLegendre<47>,
	PolynomeDeLegendre<48>,
	PolynomeDeLegendre<49>,
	PolynomeDeLegendre<50>,
	PolynomeDeLegendre<51>,
	PolynomeDeLegendre<52>,
	PolynomeDeLegendre<53>,
	PolynomeDeLegendre<54>,
	PolynomeDeLegendre<55>,
  0
};


#endif	    /* !LEGENDRE_HH_ */
