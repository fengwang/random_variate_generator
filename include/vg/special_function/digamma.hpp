#ifndef _DIGAMMA_HPP_INCLUDED_SLKJSDLKJSDFKLJCM3USDKJH498YSDKJHSIUHEKJHSIUHSAKFJHASKJH4IUHSFKDJH4EIUHSKJHSKJHASKJHLASDFKJHFDSDF
#define _DIGAMMA_HPP_INCLUDED_SLKJSDLKJSDFKLJCM3USDKJH498YSDKJHSIUHEKJHSIUHSAKFJHASKJH4IUHSFKDJH4EIUHSKJHSKJHASKJHLASDFKJHFDSDF 

#include <cmath>

namespace vg
{

    namespace special_function
    {
        struct digamma
        {

            long double operator()( long double x ) const
            {
                const long double S = 1.0e-10L;
                const long double C = 255.0L;

                if ( x <= 0.0L ) return 0.0L;
                if ( x <= S ) return less_than_s( x );
                if ( x >= C ) return greater_than_c( x );
                return between_s_and_c( x );
            }

            // \psi(x) = - \gamma - \frac{1}{x} + O{x} \ldots x -> 0
            // x -- [0, S]
            long double less_than_s( const long double x ) const 
            {
                const long double euler_constant = 0.57721566490153286060651209008240243104215933593992;
                return euler_constant - 1.0L / x;
            }

            // \psi(x+1) = \psi(x) + \frac{1}{x}
            // x -- ( S, C )
            long double between_s_and_c( const long double x ) const 
            {
                return 1.0L / x + digamma()( x - 1.0L );
            }

            // \psi(x) = ln(x) - \frac{1}{2x} - \frac{1}{12x^2} + \frac{1}{120x^4} - \frac{1}{252x^6} + O\(\frac{1}{x^8}\) \ldots x -> \infinit
            // x -- ( [ C, +infinit)
            long double greater_than_c( const long double x ) const 
            {
                const long double a1 = 0.5L;
                const long double a2 = 1.0L / 12.0L;
                const long double a4 = 1.0L / 120.0L;
                const long double a6 = 1.0L / 252.0L;
                long double r = 1.0L / x;
                long double ans = std::log( x ) - r * a1;
                r *= r;
                ans -= r * ( a2 - r * ( a4 - r * a6 ) );

                return ans;
            }

        };// digamma

    }// namespace special_function 

}// namespace vg

#endif//_DIGAMMA_HPP_INCLUDED_SLKJSDLKJSDFKLJCM3USDKJH498YSDKJHSIUHEKJHSIUHSAKFJHASKJH4IUHSFKDJH4EIUHSKJHSKJHASKJHLASDFKJHFDSDF 

