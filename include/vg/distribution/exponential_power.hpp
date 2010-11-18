#ifndef _EXPONENTIAL_POWER_HPP_INCLUDED_DSOIJ4OIUASDFLKJ4OIUSFDLKJ4OIJASFDLKJAFSDKLJXCV
#define _EXPONENTIAL_POWER_HPP_INCLUDED_DSOIJ4OIUASDFLKJ4OIUSFDLKJ4OIJASFDLKJAFSDKLJXCV

#include <vg/distribution/exponential_power.hpp>
#include <vg/distribution/laplace.hpp>
#include <vg/distribution/normal.hpp>
#include <vg/utility.hpp>

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct exponential_power : 
                                private gamma<Return_Type, Engine>,
                                private laplace<Return_Type, Engine>,
                                private proxy<normal<Return_Type, Engine> >

    {
            typedef gamma<Return_Type, Engine>                  gamm_type;
            typedef laplace<Return_Type, Engine>                laplace_type;
            typedef proxy<normal<Return_Type, Engine> >         normal_type;
            typedef Return_Type                         		return_type;
            typedef Engine                              		engine_type;
            typedef return_type                                 value_type;
            typedef typename engine_type::size_type          	size_type;
            typedef typename engine_type::final_type    	    final_type;
            typedef typename engine_type::seed_type     	    seed_type;

            value_type          a_;
            value_type          b_;
            engine_type         e_;

            explicit exponential_power(	const value_type a = value_type( 1 ),
                                        const value_type b = value_type( 1 ),
                                        const seed_type sd = 0 )
                : a_( a ), b_( b ), e_( sd ) {}

            return_type
            operator()()
            {
                return do_generation( a_, b_ );
            }

        protected:
            return_type
            do_generation( const final_type A, const final_type B )
            {
                if ( final_type(1) == B )
                    return laplace_impl( A );

                if ( B > final_type(1) && B < final_type( 2 ) )
                    return laplace_reject_impl( A, B );//

                if ( final_type(2) == B )
                    return gaussian_impl( A );

                if ( B > final_type(2) && B <= final_type( 4) )
                    return gaussian_reject_impl( A, B );

                return gamma_impl(A, B );

            }

        private:
            return_type 
            laplace_impl( const final_type A )
            {
                return laplace_type::do_generation( final_type(), A );                
            }

            return_type 
            gaussian_impl( const final_type A )
            {
                return A * normal_type::do_generation();                
            }

            return_type
            laplace_reject_impl( const final_type A, const final_type B )
            {
                const final_type b = std::pow( final_type(1)/B, final_type(1)/B);
                for (;;)
                {
                    const final_type x = laplace_type::do_generation( final_type(), b );
                    final_type y = e_();
                    while ( final_type(0) == y ) { y = e_(); }
                    const final_type z = std::fabs( x ) / b - final_type(1) +
                                         final_type(1) / B -
                                         std::pow( std::fabs(x), B ); 
                    if ( std::log(y) > z )
                        return A * x;
                }
            }

            return_type
            gaussian_reject_impl( const final_type A, const final_type B )
            {
                const final_type b = std::pow( final_type(1)/B, final_type(1)/B);
                for (;;)
                {
                    const final_type x = normal_type::do_generation() * b;
                    final_type y = e_();
                    while ( final_type(0) == y ) { y = e_(); }
                    const final_type z = x * x / ( final_type(2) * b * b ) +
                                         final_type(1) / B - final_type(0.5) - 
                                         std::pow( std::fabs(x), B );
                    if ( std::log(y) > z )
                        return A * x;
                }
            }

            return_type
            gamma_impl( const final_type A, const final_type B )
            {
                const final_type x = e_();
                const final_type y = gamm_type::do_generation( final_type(1)/B, final_type(1) );
                const final_type z = A * std::pow( y, final_type(1)/B );

                return x > final_type(0.5) ? z : -z;
            }

    };
}//vg



#endif//_EXPONENTIAL_POWER_HPP_INCLUDED_DSOIJ4OIUASDFLKJ4OIUSFDLKJ4OIJASFDLKJAFSDKLJXCV





















