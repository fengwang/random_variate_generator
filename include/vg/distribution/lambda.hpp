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

#ifndef _LAMBDA_HPP_INCLUDED_SOFI348OUSFLDKJ43OUISAFDKLJH45U8SDFKLJ4OUIFFFFFFFFFFFFFFFFFFFFFFFFFSUFHDIEUHSAKFDJH4UHMVBSJK
#define _LAMBDA_HPP_INCLUDED_SOFI348OUSFLDKJ43OUISAFDKLJH45U8SDFKLJ4OUIFFFFFFFFFFFFFFFFFFFFFFFFFSUFHDIEUHSAKFDJH4UHMVBSJK

#include <vg/utility/singleton.hpp>

#include <cmath>

namespace vg
{

    template < typename Return_Type, typename Engine >
    struct lambda 
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef Engine                          engine_type;

            final_type      lambda1_;
            final_type      lambda2_;
            final_type      lambda3_;
            final_type      lambda4_;
            engine_type&    e_;

            explicit lambda( const return_type lambda1 = 1, const return_type lambda2 = 1, const return_type lambda3 = 1, const return_type lambda4 = 1, const seed_type sd = 0 )
                : lambda1_(lambda1), lambda2_(lambda2), lambda3_(lambda3), lambda4_(lambda4), e_(singleton<engine_type>::instance()) 
            {
                e_.reset_seed( sd );
            } 

            return_type
            operator()() const
            {
                return do_generation( lambda1_, lambda2_, lambda3_, lambda4_ );
            }

        protected:
            return_type
            do_generation( const final_type lambda1, const final_type lambda2, const final_type lambda3, const final_type lambda4 ) const
            {
                return direct_impl( lambda1, lambda2, lambda3, lambda4 );
            }

        private:
            return_type
            direct_impl(   const final_type lambda1, const final_type lambda2, const final_type lambda3, const final_type lambda4 ) const
            {
                const final_type U1 = e_();
                const final_type U2 = e_();
                const final_type ans = lambda1 +  ( std::pow(U1, lambda3) - std::pow(U2, lambda4) ) / lambda2;
                return ans;
            }

    };

}//namespace vg

#endif//_LAMBDA_HPP_INCLUDED_SOFI348OUSFLDKJ43OUISAFDKLJH45U8SDFKLJ4OUIFFFFFFFFFFFFFFFFFFFFFFFFFSUFHDIEUHSAKFDJH4UHMVBSJK

