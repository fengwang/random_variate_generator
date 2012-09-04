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

#ifndef _ARCSINE_HPP_INCLUEDE_WHAOUT98U49387FSDIUJ4983UASDKLJHSJAFDHAJDFHKAJSDFHKASJDFHKJASDFHKASJFDHIU4YKJSDFHIUHFKJHSSU
#define _ARCSINE_HPP_INCLUEDE_WHAOUT98U49387FSDIUJ4983UASDKLJHSJAFDHAJDFHKAJSDFHKASJDFHKJASDFHKASJFDHIU4YKJSDFHIUHFKJHSSU

#include <vg/utility/singleton.hpp>

#include <cmath>

namespace vg
{

    template < typename Return_Type, typename Engine >
    struct arcsine
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef Engine                          engine_type;

            engine_type& e_;

            explicit arcsine( const seed_type sd = 0 ) : e_( singleton<engine_type>::instance() )
            {
                e_.reset_seed( sd );
            }

            return_type
            operator()()
            {
                return do_generation();
            }

        protected:
            return_type
            do_generation()
            {
                return direct_impl();
            }

        private:
            return_type
            direct_impl()
            {
                const final_type u = e_();
                const final_type pi = 3.1415926535897932384626433L;
                const final_type ans = std::sin( pi * u );
                return ans;
            }

    };

}//namespace vg

#endif//_ARCSINE_HPP_INCLUEDE_WHAOUT98U49387FSDIUJ4983UASDKLJHSJAFDHAJDFHKAJSDFHKASJDFHKJASDFHKASJFDHIU4YKJSDFHIUHFKJHSSU

