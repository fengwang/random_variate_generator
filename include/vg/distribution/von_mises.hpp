#ifndef _VON_MISES_HPP_INCLUDED_SOIJ4OIUFSDLKJ4OIUKLJGDKLJROIUDGLKJFLKJDOIU5LKJDGOIUOIUDGLKJDLKJDLKJGOIJDOIJDLKJGOIJFLKJG
#define _VON_MISES_HPP_INCLUDED_SOIJ4OIUFSDLKJ4OIUKLJGDKLJROIUDGLKJFLKJDOIU5LKJDGOIUOIUDGLKJDLKJDLKJGOIJDOIJDLKJGOIJFLKJG

#include <cassert>
#include <cmath>

namespace vg
{

    template <
                typename Return_Type,
                typename Engine
             >
    struct von_mises
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef Return_Type                     value_type;
            typedef typename Engine::seed_type      seed_type;

            value_type      a_;
            value_type      k_;
            Engine          e_;

            explicit von_mises( const value_type a = value_type( 0 ),
                              const value_type k = value_type( 1 ),
                              const seed_type s = seed_type( 0 ) )
                : a_( a ), k_( k ), e_( s )
            {
                asset( k > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( a_, k_ );
            }

        protected:
            return_type
            do_generation( const value_type a, const value_type k )
            {
                return direct_impl( a, k );
            }

        private:
            return_type
            direct_impl( const value_type a, const value_type k )
            {
                const final_type r = final_type(1) + std::sqrt( final_type(1) + k * k * final_type(4) );
                const final_type rho = ( r - std::sqrt( r + r ) ) / ( k + k );
                const final_type s = ( final_type(1) + rho * rho ) / ( rho + rho );

                for ( ; ; )
                {
                    const final_type u = e_();
                    const final_type v = e_();
                    const final_type pi = 3.1415926535897932384626433L;
                    const final_type z = std::cos( pi * u );
                    const final_type w = ( final_type(1) + s * z ) / ( s + z );
                    const final_type y = k * ( s - w );
                    const bool accept =  ( y + y >= y * y + v ) ? true : ( std::log( y / v ) + final_type(1) >= y );
                    if ( accept ) 
                        return a + ( u  > final_type(0.5L) ? final_type(1.0L) : final_type(-1.0L) ) / std::cos(w);
                }

            }
    };

}//namespace vg


#endif//_VON_MISES_HPP_INCLUDED_SOIJ4OIUFSDLKJ4OIUKLJGDKLJROIUDGLKJFLKJDOIU5LKJDGOIUOIUDGLKJDLKJDLKJGOIJDOIJDLKJGOIJFLKJG

