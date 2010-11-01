#ifndef _POISSON_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK
#define _POISSON_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK

#include "normal.hpp"

#include <cmath>
#include <cstddef>
#include <limits>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct poisson : private normal<Return_Type, Engine>
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef Engine                          engine_type;

            final_type  lambda_;
            engine_type e_;

            explicit poisson( const final_type lambda = 1, const seed_type sd = 0 )
                : lambda_( lambda ), e_( sd ) {}

            return_type
            operator()()
            {
                return do_generation( lambda_ );
            }

        protected:
            return_type
            do_generation( const final_type lambda )
            {
                //if (lambda < final_type(10) )
                    return exponential_inter_arrival_times_method( lambda );
                return rejection_method(lambda);
            }

        private:

            return_type
            exponential_inter_arrival_times_method( const final_type lambda )
            {
                return_type ans = 0;
                const final_type exp_lambda = std::exp( -lambda );
                final_type prod = e_();

                while ( prod > exp_lambda )
                {
                    prod *= e_();
                    ++ans;
                }

                return ans;
            }

            return_type
            rejection_method( const final_type lambda )
            {
                const final_type mu = std::floor( lambda );
                const final_type delta = std::round( mu / final_type( 2 ) + final_type( 3 ) );
                const final_type mu_mu_delta = mu + mu + delta;
                const final_type pi = 3.1415926535897932384626433L;
                const final_type c_1 = std::sqrt( pi * mu / final_type( 2 ) );
                const final_type c_2 = c_1 + std::sqrt( pi * mu_mu_delta / final_type( 4 ) ) * std::exp( final_type(1) / ( mu_mu_delta ) );
                const final_type c_3 = c_2 + final_type( 1 );
                const final_type c_4 = c_3 + std::exp( final_type( 1 ) / final_type( 78 ) );
                const final_type c = c_4 + ( mu_mu_delta + mu_mu_delta ) / delta * std::exp( - delta * ( final_type( 2 ) + delta ) / ( mu_mu_delta + mu_mu_delta ) );
                final_type W;
                final_type X;

                for ( ;; )
                {
                    final_type U = c * e_();
                    final_type E = -std::log( e_() );

                    if ( U <= c_1 )
                    {
                        const final_type N = normal<return_type, engine_type>::do_generation();
                        const final_type Y = - std::fabs( N ) * std::sqrt( mu );
                        X = std::floor( Y );
                        W = - N * N / final_type( 2 ) - E - X * std::log( lambda / mu );

                        if ( X >= -mu )
                            { W = std::numeric_limits<final_type>::max(); }
                    }
                    else
                        if ( U <= c_2 )
                        {
                            const final_type N = normal<return_type, engine_type>::do_generation();
                            const final_type Y = final_type( 1 ) + std::fabs( N ) * std::sqrt( mu_mu_delta / final_type( 2 ) );
                            X = std::ceil( Y );
                            W = Y * ( final_type( 2 ) - Y ) / mu_mu_delta - E - X * log( lambda / mu );

                            if ( X <= delta )
                                { W = std::numeric_limits<final_type>::max(); }
                        }
                        else
                            if ( U <= c_3 )
                            {
                                X = final_type( 0 );
                                W = - E;
                            }
                            else
                                if ( U <= c_4 )
                                {
                                    X = final_type( 1 );
                                    W = - E - std::log( lambda / mu );
                                }
                                else
                                {
                                    const final_type V = -std::log( e_() );
                                    const final_type Y = delta + ( V + V ) * mu_mu_delta / delta;
                                    X = std::ceil( Y );
                                    W = delta * ( final_type( 2 ) + Y ) / ( mu_mu_delta + mu_mu_delta ) - E - X * std::log( lambda / mu );
                                }

                    if ( W > X * std::log( lambda ) + std::lgamma( mu ) - std::lgamma( mu + X ) )
                        { break; }
                }

                return static_cast<return_type>( X + mu );
            }




    };




}//namespace vg




#endif//_POISSON_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK


