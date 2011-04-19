/*
vg -- random variate generator library 
Copyright (C) 2010-2011  Feng Wang (wanng.fenng@gmail.com) 

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

#ifndef _EXTREME_VALUE_HPP_INCLUDED_SDFOIU4897USFD98743KLJSFDKLJSFDOIU498YSFIU45O8IUFSOIU498UFSDIUROUIOIEULDGKJDGOIU45OIU
#define _EXTREME_VALUE_HPP_INCLUDED_SDFOIU4897USFD98743KLJSFDKLJSFDOIU498YSFIU45O8IUFSOIU498UFSDIUROUIOIEULDGKJDGOIU45OIU

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct extreme_value
    {
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;

            typedef typename engine_type::final_type    final_type;
            typedef typename engine_type::seed_type     seed_type;

            return_type         mu_;        //location
            return_type         sigma_;     //scale
            return_type         xi_;        //sharp
            engine_type         e_;

            explicit extreme_value(	const return_type mu = 0,
                                    const return_type sigma = 1,
                                    const return_type xi = 0,
                                    const seed_type sd = 0 )
                : mu_(mu), sigma_(sigma), xi_(xi), e_( sd )
            {
                assert( sigma_ > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( mu_, sigma_, xi_ );
            }

        protected:
            return_type
            do_generation( const final_type Mu, const final_type Sigma, const final_type Xi )
            {
                return direct_reverse_impl( Mu, Sigma, Xi );
            }

        private:
            //the distribution function is
            //F(x;\mu,\sigma,\xi) = \exp\left\{-\left[1+\xi\left(\frac{x-\mu}{\sigma}\right)\right]^{-1/\xi}\right\}
            return_type
            direct_reverse_impl( const final_type Mu, const final_type Sigma, const final_type Xi )
            {
                const final_type u = e_();
                const final_type ans = Mu + ( std::exp(-Xi * std::log( -std::log(u) ) ) - final_type(1) ) * Sigma / Xi;
                return ans;
            }

    };

}//vg


#endif//_EXTREME_VALUE_HPP_INCLUDED_SDFOIU4897USFD98743KLJSFDKLJSFDOIU498YSFIU45O8IUFSOIU498UFSDIUROUIOIEULDGKJDGOIU45OIU

