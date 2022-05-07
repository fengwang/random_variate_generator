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
#ifndef _BALDING_NICHOLS_HPP_INCLUDED_SDFPONA34P98ASLFKDJH43U89HASDFKMNBSFDALKHF 
#define _BALDING_NICHOLS_HPP_INCLUDED_SDFPONA34P98ASLFKDJH43U89HASDFKMNBSFDALKHF 

#include "./beta.hpp"

//#include <cassert>

namespace vg
{

    template < typename Return_Type, typename Engine >
    struct balding_nichols: private beta<typename Engine::final_type, Engine>
    {
            typedef beta<typename Engine::final_type, Engine>           beta_type;
            typedef Return_Type                                         return_type;
            typedef Engine                                              engine_type;
            typedef typename engine_type::final_type                    final_type;
            typedef typename engine_type::seed_type                     seed_type;

            final_type          f_;
            final_type          p_;
            engine_type&        e_;

            explicit balding_nichols( const final_type f = final_type(0.5), const final_type p = final_type(0.5), const seed_type sd = 0 ) noexcept : f_( f ), p_( p ), e_( singleton<engine_type>::instance() )
            {
                assert( f > final_type{0} );
                assert( f < final_type{1} );
                assert( p > final_type{0} );
                assert( p < final_type{1} );
                e_.reset_seed( sd );
            }

            /*
            Testing [balding_nichols] distribution with n = 10000000, parameter(0.5,0.5)
            |        |      Theory          |       Pseudo              |
            |  Mean  |  0.500000000000000   |   0.500126787066542       |
            |Variance|  0.125000000000000   |   0.124951107077455       |
            |Skewness|  0.00000000000000    |   -0.000512026835995461   |
            */
            return_type operator()() const noexcept
            {
                return do_generation( f_, p_ );
            }

        protected:
            return_type do_generation( const final_type F, const final_type P ) const noexcept
            {
                return direct_balding_nichols_impl( F, P );
            }

        private:
            return_type direct_balding_nichols_impl( const final_type F, const final_type P ) const noexcept
            {
                const final_type l = final_type{1};
                const final_type ans = beta_type::do_generation( P*(l-F)/F, (l-P)*(l-F)/F );
                return static_cast<return_type>(ans);
            }
    };

}//vg

#endif//_BALDING_NICHOLS_HPP_INCLUDED_SDFPONA34P98ASLFKDJH43U89HASDFKMNBSFDALKHF 

