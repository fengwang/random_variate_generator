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

#ifndef _SINGH_MADDALA_HPP_INCLUDED_SOFIJ348UAS9F834298SFDOIU4OEIUWREOIUQW98RUY3428OUWE98UY498SFDJKHCKJHSKFJHSUH4387YSJKW
#define _SINGH_MADDALA_HPP_INCLUDED_SOFIJ348UAS9F834298SFDOIU4OEIUWREOIUQW98RUY3428OUWE98UY498SFDJKHCKJHSKFJHSUH4387YSJKW

#include <vg/distribution/burr.hpp>
#include <vg/utility/singleton.hpp>

/*
#include <functional>
#include <cmath>
#include <cassert>
*/

namespace vg
{

    template < typename Return_Type, typename Engine >
    struct singh_maddala : private burr<Return_Type, Engine>
    {
            typedef burr<Return_Type, Engine>                   burr_type;
            typedef Return_Type                         		return_type;
            typedef Engine                              		engine_type;
            typedef return_type                                 value_type;
            typedef typename engine_type::size_type          	size_type;
            typedef typename engine_type::final_type    	    final_type;
            typedef typename engine_type::seed_type     	    seed_type;

            final_type          c_;
            final_type          k_;
            final_type          r_;
            engine_type&        e_;

            explicit singh_maddala(  const final_type c = final_type(1), const final_type k = final_type(1), const final_type r = final_type(1), const seed_type sd = 0 )
                : c_( c ), k_( k ), r_( r ), e_( singleton<engine_type>::instance() )
            {
                assert( c > 0 );
                assert( k > 0 );
                e_.reset_seed( sd );
            }

            return_type
            operator()() const
            {
                return do_generation( c_, k_, r_ );
            }

        protected:
            final_type
            do_generation( const final_type C, const final_type K, const final_type R ) const
            {
                return direct_impl( C, K, R );
            }

        private:
            final_type
            direct_impl( const size_type N, const final_type C, const final_type K, const final_type R ) const
            {
                return burr_type::do_generation( 12, C, K, R );
            }
    };

}//vg

#endif//_SINGH_MADDALA_HPP_INCLUDED_SOFIJ348UAS9F834298SFDOIU4OEIUWREOIUQW98RUY3428OUWE98UY498SFDJKHCKJHSKFJHSUH4387YSJKW

