#ifndef _GAMMA_UNARY_HPP_INCLUDED_2I8HJFASKJLNHVJMNXVUHNZVSJHWOIUHAP9I3LKJSOIUJ3OIJSIA
#define _GAMMA_UNARY_HPP_INCLUDED_2I8HJFASKJLNHVJMNXVUHNZVSJHWOIUHAP9I3LKJSOIUJ3OIJSIA

#include <cmath>
#include <cstddef>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct gamma_unary
    {
            typedef Return_Type                         		return_type;
            typedef Engine                              		engine_type;
            typedef return_type                                 value_type;
            typedef typename engine_type::size_type          	size_type;
            typedef typename engine_type::final_type    	    final_type;
            typedef typename engine_type::seed_type     	    seed_type;

            value_type          a_;
            engine_type         e_;

            explicit gamma_unary(	const value_type a = value_type( 1 ),
                                    const seed_type sd = 0 )
                : a_( a ), e_( sd )
            {
                assert( a > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( a_ );
            }

        protected:
            return_type
            do_generation( const value_type A )
            {
                if ( A < 10 )
                    { return direct_impl( A ); }

                return rejection_method( A );
            }

        private:
            // from Knuth, vol 2, 2nd ed, p. 129.
            return_type
            direct_impl( const value_type A )
            {
                final_type ans = 0;
                const std::size_t N = static_cast<std::size_t>( A );

                for ( std::size_t i = 0; i < N; ++i )
                {
                    ans -= std::log( e_() );
                }

                if ( A-N != value_type(0) )
                {
                    const value_type diff = A - N;
                    ans += frac_method( diff );
                }

                return static_cast<return_type>( ans );
            }

            return_type
            rejection_method( const value_type A )
            {
                const final_type pi = 3.1415926535897932384626433L;
                const final_type sqr_AA1 = std::sqrt( A + A - 1 );

                for ( ;; )
                {
                    const final_type U = e_();
                    const final_type Y = std::tan( pi * U );
                    const final_type X = sqr_AA1 * Y + A - 1;

                    if ( X < 0 )
                        { continue; }

                    if ( e_() <= ( 1 + Y * Y )*std::exp(( A - 1 )*std::log( X / ( A - 1 ) ) ) - sqr_AA1 * Y )
                        { return static_cast<return_type>( X ); }
                }
            }

            return_type
            frac_method( const value_type A )
            {
                const final_type e = 2.7182818284590452353602875L;
                const final_type P = e / ( final_type( A ) + e );

                for ( ;; )
                {
                    final_type logv;
                    final_type Q;
                    final_type ans;

                    for ( ;; )
                    {
                        logv = e_();

                        if ( logv != final_type( 0 ) )
                        {
                            logv = std::log( logv );
                            break;
                        }
                    }

                    if ( e_() < P )
                    {
                        ans = std::exp( final_type( 1 ) / final_type( A ) ) * logv;
                        Q = std::exp( -ans );
                    }
                    else
                    {
                        ans = final_type( 1 ) - logv;
                        Q = std::exp( A * std::log( ans ) ) / ans;
                    }

                    if ( Q > e_() )
                        { return static_cast<return_type>( ans ); }
                }
            }

    };
}//vg

#endif//_GAMMA_UNARY_HPP_INCLUDED_2I8HJFASKJLNHVJMNXVUHNZVSJHWOIUHAP9I3LKJSOIUJ3OIJSIA




