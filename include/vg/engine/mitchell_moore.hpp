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
            mitchell_moore( const seed_type s = 0 ) noexcept : next_( 0 ), next_p_( 31 )
            {
                std::lock_guard<std::mutex> l( mtx );

                std::fill( a_, a_+56, value_type(0) ); //just to kill valgrind uninitialization error report
                initial( s );
            }

            void reset_seed( const seed_type s = 0 ) noexcept
            {
                if ( 0 == s ) return;

                std::lock_guard<std::mutex> l( mtx );
                initial( s );
            }

            final_type operator()() noexcept
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
            void initial( const seed_type s ) noexcept
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

