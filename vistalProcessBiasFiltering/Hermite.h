/*
** Hermite.hh
** Login : <nwiestda@pr167140>
** Started on  Fri Nov  6 15:13:54 2009 Nicolas Wiest-Daessle
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

#ifndef   	HERMITE_HH_
# define   	HERMITE_HH_


#include <boost/preprocessor/repetition/for.hpp>

// Recursive template for legendre polynomials

template <int order>
float PolynomeDeHermite(float x)
{
  return  2 * x * PolynomeDeHermite<order-1>(x)
    - 2*((float)order-1.) * 
    PolynomeDeHermite<order-2>(x);
}

template<>
float PolynomeDeHermite<0>(float x)
{
  return 1;
}

template<>
float PolynomeDeHermite<1>(float x)
{
  return 2*x;
}

template<>
float PolynomeDeHermite<2>(float x)
{
  return 4*pow(x,2.f) - 2;
}

template<>
float PolynomeDeHermite<3>(float x)
{
  return 8*pow(x,3.f)-12*x;
}

template<>
float PolynomeDeHermite<4>(float x)
{
  return 16*pow(x,4.f)-48*pow(x,2)+12;
}



// Creates the table of legendre polynomials, to unroll the templates
// use this to get a specific order legendre polynomial
// HermiteTable[order](x)
// gives you the value of the lgendre polynom of order 'order' at x
#define HermiteCount 55
float (*HermiteTable[])(float x) =
{
#define GEN_Hermite_D(Count) PolynomeDeHermite<Count>,
#define GEN_Hermite(r, state) GEN_Hermite_D(BOOST_PP_TUPLE_ELEM(2,0, state))

//  BOOST_PP_FOR((0, HermiteCount), PRED, OP, GEN_Hermite)
	
	PolynomeDeHermite<0>,
	PolynomeDeHermite<1>,
	PolynomeDeHermite<2>,
	PolynomeDeHermite<3>,
	PolynomeDeHermite<4>,
	PolynomeDeHermite<5>,
	PolynomeDeHermite<6>,
	PolynomeDeHermite<7>,
	PolynomeDeHermite<8>,
	PolynomeDeHermite<9>,
	PolynomeDeHermite<10>,
	PolynomeDeHermite<11>,
	PolynomeDeHermite<12>,
	PolynomeDeHermite<13>,
	PolynomeDeHermite<14>,
	PolynomeDeHermite<15>,
	PolynomeDeHermite<16>,
	PolynomeDeHermite<17>,
	PolynomeDeHermite<18>,
	PolynomeDeHermite<19>,
	PolynomeDeHermite<20>,
	PolynomeDeHermite<21>,
	PolynomeDeHermite<22>,
	PolynomeDeHermite<23>,
	PolynomeDeHermite<24>,
	PolynomeDeHermite<25>,
	PolynomeDeHermite<26>,
	PolynomeDeHermite<27>,
	PolynomeDeHermite<28>,
	PolynomeDeHermite<29>,
	PolynomeDeHermite<30>,
	PolynomeDeHermite<31>,
	PolynomeDeHermite<32>,
	PolynomeDeHermite<33>,
	PolynomeDeHermite<34>,
	PolynomeDeHermite<35>,
	PolynomeDeHermite<36>,
	PolynomeDeHermite<37>,
	PolynomeDeHermite<38>,
	PolynomeDeHermite<39>,
	PolynomeDeHermite<40>,
	PolynomeDeHermite<41>,
	PolynomeDeHermite<42>,
	PolynomeDeHermite<43>,
	PolynomeDeHermite<44>,
	PolynomeDeHermite<45>,
	PolynomeDeHermite<46>,
	PolynomeDeHermite<47>,
	PolynomeDeHermite<48>,
	PolynomeDeHermite<49>,
	PolynomeDeHermite<50>,
	PolynomeDeHermite<51>,
	PolynomeDeHermite<52>,
	PolynomeDeHermite<53>,
	PolynomeDeHermite<54>,
	PolynomeDeHermite<55>,
	
	
  0
};



#endif	    /* !HERMITE_HH_ */
