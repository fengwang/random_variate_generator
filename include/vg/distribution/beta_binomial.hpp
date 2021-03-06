/*
vg -- random variate generator library 
Copyright (C) 2010-2012  Feng Wang (feng.wang@uni-ulm.de) 

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by 
the Free Software Foundation, either version 3 of the License, or 
(at your option) any later version. 

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU General Public License for more details. 

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _BETA_BINOMIAL_HPP_INCLUDED_SDFOIUJ4O8UIASFL89UY32SSSSSSSSSSSSSFFFFFFFSFODIJ4ELKJASFDOPIUJE9R8
#define _BETA_BINOMIAL_HPP_INCLUDED_SDFOIUJ4O8UIASFL89UY32SSSSSSSSSSSSSFFFFFFFSFODIJ4ELKJASFDOPIUJE9R8 

#include <vg/distribution/beta.hpp>
#include <vg/distribution/binomial.hpp>
#include <vg/utility.hpp>

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct beta_binomial: private proxy<beta<typename Engine::final_type, Engine> >,
                          private proxy<binomial<Return_Type, Engine> >  
    {
            typedef proxy<beta<typename Engine::final_type, Engine> >   beta_type;
            typedef proxy<binomial<Return_Type, Engine> >               binomial_type;
            typedef Return_Type                         		return_type;
            typedef Engine                              		engine_type;
            typedef return_type                                 value_type;
            typedef typename engine_type::size_type          	size_type;
            typedef typename engine_type::final_type    	    final_type;
            typedef typename engine_type::seed_type     	    seed_type;

            value_type          n_;
            final_type          a_;
            final_type          b_;
            engine_type&        e_;

            explicit beta_binomial(	const value_type n = value_type( 10 ),
                                    const final_type a = final_type(1),
                                    const final_type b = final_type(1),
                                    const seed_type sd = 0 ) noexcept
                : n_(n), a_( a ), b_( b ), e_( singleton<engine_type>::instance() )
            {
                assert( n > 0 );
                assert( a > 0 );
                assert( b > 0 );
                 e_.reset_seed( sd );
            }

            /*
                Testing [beta_binomial with n = 100, alpha = 0.1, beta = 0.2] distribution with N = 10000000
                |        |              Theory          |               Pseudo          |
                |  Mean  |      33.3333333333333        |       33.3264832000000        |
                |Variance|      1714.52991452991        |       1714.49191808349        |
                |Skewness|      12.8188529096048        |       0.701374380851282       |  
            */
            return_type
            operator()() const noexcept
            {
                return do_generation( n_, a_, b_ );
            }

        protected:
            return_type
            do_generation( const value_type N, const final_type A, const final_type B ) const noexcept
            {
                return direct_beta_binomial_impl( N, A, B );
            }

        private:
            return_type
            direct_beta_binomial_impl( const value_type N, const final_type A, const final_type B ) const noexcept
            {
                const final_type p = static_cast<final_type>(beta_type::do_generation( A, B ));
                const final_type ans = static_cast<final_type>(binomial_type::do_generation( static_cast<size_type>(N), p ));
                return static_cast<return_type>(ans);
            }
    };

}//vg

#endif//_BETA_BINOMIAL_HPP_INCLUDED_SDFOIUJ4O8UIASFL89UY32SSSSSSSSSSSSSFFFFFFFSFODIJ4ELKJASFDOPIUJE9R8 

