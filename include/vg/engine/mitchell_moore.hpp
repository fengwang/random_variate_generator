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
#ifndef _MITCHELL_MOORE_HPP_INCLUDED_3UHSFKJHNSAIFUNVCJMNZKJHDEIUHE3IUHSIKUJHEE8
#define _MITCHELL_MOORE_HPP_INCLUDED_3UHSFKJHNSAIFUNVCJMNZKJHDEIUHE3IUHSIKUJHEE8

#include <vg/engine/default_seed.hpp>

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <mutex>
#include <limits>

namespace vg
{

    struct mitchell_moore
    {
            typedef mitchell_moore          self_type;
            typedef long double             final_type;
            typedef std::uint_fast64_t      value_type;
            typedef value_type              seed_type;
            typedef std::size_t             size_type;

        private:
            static const value_type         ini_seed_ = 161803398;
            value_type                      a_[56];
            size_type                       next_;
            size_type                       next_p_;
            mutable std::mutex              mtx;

        public:
            mitchell_moore( const seed_type s = 0 )
                : next_( 0 ), next_p_( 31 )
            {
                std::lock_guard<std::mutex> l( mtx );

                std::fill( a_, a_+56, value_type(0) ); //just to kill valgrind uninitialization error report
                initial( s );
            }

            void reset_seed( const seed_type s = 0 )
            {
                if ( 0 == s ) return;

                std::lock_guard<std::mutex> l( mtx );
                initial( s );
            }

            final_type operator()()
            {
                std::lock_guard<std::mutex> l( mtx );

                if ( ++next_ == 56 )
                    { next_ = 1; }

                if ( ++next_p_ == 56 )
                    { next_p_ = 1; }

                value_type tmp = a_[next_] - a_[next_p_];

                a_[next_] = tmp;
                const final_type ans = static_cast<final_type>( tmp ) / static_cast<final_type>( std::numeric_limits<value_type>::max() );
                return ans;
            } // end of operator()

        private:
            void initial( const seed_type s )
            {
                const seed_type seed = s ? s : default_seed()();
                value_type mj = ini_seed_ - seed;
                value_type mk = 1;
                a_[55] = mj;

                for ( size_type i = 1; i < 55; i++ )
                {
                    const size_type ii = ( 21 * i ) % 55;
                    a_[ii] = mk;
                    mk = mj - mk;
                    mj = a_[ii];
                }

                for ( size_type k = 1; k < 5; k++ )
                    for ( size_type i = 1; i < 56; i++ )
                        { a_[i] -= a_[1 + ( i + 30 ) % 55]; }
            }// end of void initial( const seed_type)

        private://not to be implemented
            mitchell_moore( const self_type& );
            mitchell_moore& operator = ( const self_type& );
    };// end of struct mitchell_moore

}//namespace vg

#endif//_MITCHELL_MOORE_HPP_INCLUDED_3UHSFKJHNSAIFUNVCJMNZKJHDEIUHE3IUHSIKUJHEE8

