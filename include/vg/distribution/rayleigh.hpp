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
#ifndef _RAYLEIGH_HPP_INLCUDED_DSOIJ34O8UASFD98UY498UAFSDOIU3498UFLKJA0LDKLJASMA
#define _RAYLEIGH_HPP_INLCUDED_DSOIJ34O8UASFD98UY498UAFSDOIU3498UFLKJA0LDKLJASMA

#include <vg/utility/singleton.hpp>

#include <cmath>
#include <cassert>

namespace vg
{

    template < typename Return_Type, typename Engine >
    struct rayleigh
    {
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;

            typedef typename engine_type::final_type    final_type;
            typedef typename engine_type::seed_type     seed_type;

            return_type     delta_;
            engine_type&    e_;

            explicit rayleigh(	const return_type delta = 1, const seed_type sd = 0 )
                : delta_( delta ), e_( singleton<engine_type>::instance() )
            {
                assert( delta_ > 0 );
                e_.reset_seed( sd );
            }

            return_type
            operator()() const
            {
                return do_generation( delta_ );
            }

        protected:
            return_type
            do_generation( const return_type delta ) const
            {
                return direct_impl( delta );
            }

        private:
            return_type
            direct_impl( const return_type delta ) const
            {
                const final_type u = e_();
                const final_type tmp1 = - std::log( u );
                const final_type tmp2 = std::sqrt( tmp1 );
                const final_type ans = delta * tmp2;
                return ans;
            }
    };

}//vg

#endif//_RAYLEIGH_HPP_INLCUDED_DSOIJ34O8UASFD98UY498UAFSDOIU3498UFLKJA0LDKLJASMA


