#ifndef _T_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDKDSIJF
#define _T_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDKDSIJF

#include "normal.hpp"
#include "chi_square.hpp"
#include "exponential.hpp"
#include "../utility.hpp"

#include <cmath>
#include <cstddef>
#include <limits>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct t :  private proxy<normal<Return_Type, Engine> >,
                private chi_square<Return_Type, Engine>,
                private exponential<Return_Type, Engine>
    {
            typedef normal<Return_Type, Engine>         normal_type;
            typedef proxy<normal_type>                  proxy_normal_type;
            typedef chi_square<Return_Type, Engine>     chi_square_type;
            typedef exponential<Return_Type, Engine>    exponential_type;

            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef typename Engine::size_type      size_type;
            typedef Engine                          engine_type;

            final_type  mu_;
            engine_type e_;

            explicit t( const return_type mu = 1, const seed_type sd = 0 )
                : mu_( mu ), e_( sd )
            {
                assert( mu > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( mu_ );
            }

        protected:
            return_type
            do_generation( const return_type mu )
            {
                if ( mu <= final_type( 2 ) )
                    { return direct_impl( mu ); }

                return rejection_method( mu );
            }

        private:
            return_type
            direct_impl( const return_type mu )
            {
                const final_type y1 = proxy_normal_type::do_generation();
                const final_type y2 = chi_square_type::do_generation( mu );
                const final_type ans = y1 / std::sqrt( y2 / mu );
                return ans;
            }

            return_type
            rejection_method( const return_type mu )
            {
                for ( ;; )
                    {
                        const final_type y1 = proxy_normal_type::do_generation();
                        const final_type y2 = exponential_type::do_generation( final_type(mu-2)/final_type(2) );
                        const final_type y3 = y1 * y1 / final_type( mu - 2 );

                        if ( ( y3 < 1 ) && (  - std::log( final_type( 1 ) - y3 ) < ( y2 + y3 ) ) )
                            {
                                const final_type fac1 = final_type(mu-2) / final_type(mu);
                                const final_type fac2 = fac1 - fac1 * y3;
                                const final_type ans = y1 / std::sqrt( fac2 );

                                return ans;
                            }
                    }
            }
    };

}//namespace vg

#endif//_T_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDKDSIJF

