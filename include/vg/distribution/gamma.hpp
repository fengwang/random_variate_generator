#ifndef _GAMMA_HPP_INCLUDED_2I8HJFASKJLNHVJMNXVUHNZVSJHWOIUHAP9I3LKJSOIUJ3OIJSIA
#define _GAMMA_HPP_INCLUDED_2I8HJFASKJLNHVJMNXVUHNZVSJHWOIUHAP9I3LKJSOIUJ3OIJSIA

#include "normal.hpp"

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct gamma : private normal<Return_Type, Engine>
    {
            typedef Return_Type                         		return_type;
            typedef Engine                              		engine_type;
            typedef return_type                                 value_type;
            typedef typename engine_type::size_type          	size_type;
            typedef typename engine_type::final_type    	    final_type;
            typedef typename engine_type::seed_type     	    seed_type;

            value_type          a_;
            value_type          b_;
            engine_type         e_;

            explicit gamma(	const value_type a = value_type( 1 ),
                            const value_type b = value_type( 1 ),
                            const seed_type sd = 0 )
                : a_( a ), b_( b ), e_( sd )
            {
                assert( a > 0 );
            }

            return_type
            operator()()
            {
                return marsaglia_tsang_method( a_, b_ );
            }

        protected:
            //Marsaglia and Tsang, "A Simple Method for generating gamma variables",
            //ACM Transactions on Mathematical Software, Vol 26, No 3 (2000), p363-372.
            return_type
            marsaglia_tsang_method( const final_type A, const final_type B )
            {
                const final_type a = A < final_type( 1 ) ? A + final_type( 1 ) : A;
                const final_type b = B;
                const final_type d = a - final_type( 1 ) / final_type( 3 );
                const final_type c = final_type( 1 ) / final_type( 3 ) / std::sqrt( d );
                final_type u( 0 );
                final_type v( 0 );
                final_type x( 0 );

                for ( ;; )
                {
                    for ( ;; )
                    {
                        //x = kinderman_monahan_method(); //normal distribution
                        x = normal<Return_Type,Engine>::kinderman_monahan_method(); //normal distribution
                        v = final_type( 1 ) + c * x;

                        if ( v > 0 )
                            { break; }
                    }

                    const final_type xx = x * x;

                    v *= v * v;

                    u = e_();

                    if ( u < final_type( 1 ) - final_type( 0.0331 ) * xx * xx )
                        { break; }

                    if ( std::log( u ) < 0.5 * xx + d *( final_type( 1 ) - v + std::log( v ) ) )
                        { break; }
                }

                final_type ans = b * d * v;

                if ( A < 1 )
                    { ans *= std::pow( e_(), final_type( 1 ) / A ); }

                return static_cast<return_type>(ans);
            }
    };
}//vg

#endif//_GAMMA_HPP_INCLUDED_2I8HJFASKJLNHVJMNXVUHNZVSJHWOIUHAP9I3LKJSOIUJ3OIJSIA




