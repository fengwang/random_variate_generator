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
#ifndef _GUMBEL_1_HPP_INCLUDED_SODIJ4890USFLIUJ43908UASFLIU498UYAFSDKLJH34OIUAFF
#define _GUMBEL_1_HPP_INCLUDED_SODIJ4890USFLIUJ43908UASFLIU498UYAFSDKLJH34OIUAFF

#include <vg/utility/singleton.hpp>

#include <cmath>
#include <cstddef>
#include <limits>
#include <cassert>

namespace vg
{

#if 0
    f( x | a, b ) = a b e ^ { -( b e ^ { -ax} + ax )}\,

    for  - \infty < x < \infty.
#endif

template < typename Return_Type, typename Engine >
struct gumbel_1
{
        typedef typename Engine::final_type     final_type;
        typedef Return_Type                     return_type;
        typedef typename Engine::seed_type      seed_type;
        typedef typename Engine::size_type      size_type;
        typedef Engine                          engine_type;

        final_type      a_;
        final_type      b_;
        engine_type&    e_;

        explicit 
        gumbel_1( const return_type a = 1, const return_type b = 1, const seed_type sd = 0 )
            : a_( a ), b_( b ), e_( singleton<engine_type>::instance() )
        {
            assert( b > 0 );
            e_.reset_seed( sd );
        }

        return_type
        operator()() const
        {
            return do_generation( a_, b_ );
        }

    protected:
        return_type
        do_generation( const return_type a, const return_type b ) const 
        {
            return direct_impl( a, b );
        }

    private:
        return_type
        direct_impl( const return_type a, const return_type b ) const 
        {
            final_type x = e_();

            while ( final_type( 0 ) == x )
            {
                x = e_();
            }

            const final_type ans = ( std::log( b ) - std::log( -std::log( x ) ) ) / a;

            return ans;
        }

};

}//namespace vg

#endif//_GUMBEL_1_HPP_INCLUDED_SODIJ4890USFLIUJ43908UASFLIU498UYAFSDKLJH34OIUAFF

