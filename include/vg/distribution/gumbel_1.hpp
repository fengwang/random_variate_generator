#ifndef _GUMBEL_1_HPP_INCLUDED_SODIJ4890USFLIUJ43908UASFLIU498UYAFSDKLJH34OIUAFF
#define _GUMBEL_1_HPP_INCLUDED_SODIJ4890USFLIUJ43908UASFLIU498UYAFSDKLJH34OIUAFF

#include <cmath>
#include <cstddef>
#include <limits>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct gumbel_1
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef typename Engine::size_type      size_type;
            typedef Engine                          engine_type;

            final_type  a_;
            final_type  b_;
            engine_type e_;

            explicit gumbel_1( const return_type a = 1, const return_type b = 1, const seed_type sd = 0 )
                : a_( a ), b_(b), e_( sd )
            {
                assert( a > 0 );
                assert( b > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( a_, b_ );
            }

        protected:
            return_type
            do_generation( const return_type a, const return_type b )
            {
                return direct_impl( a, b );
            }

        private:
            return_type
            direct_impl( const return_type a, const return_type b )
            {
                final_type x = e_();
                while ( final_type(0) == x )
                {
                    x = e_();
                }

                const final_type ans = ( std::log(b) - log( -log(x) ) ) / a;

                return ans;
            }

    };

}//namespace vg

#endif//_GUMBEL_1_HPP_INCLUDED_SODIJ4890USFLIUJ43908UASFLIU498UYAFSDKLJH34OIUAFF
