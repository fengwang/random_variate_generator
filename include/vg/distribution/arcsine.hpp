#ifndef _ARCSINE_HPP_INCLUEDE_WHAOUT98U49387FSDIUJ4983UASDKLJHSJAFDHAJDFHKAJSDFHKASJDFHKJASDFHKASJFDHIU4YKJSDFHIUHFKJHSSU
#define _ARCSINE_HPP_INCLUEDE_WHAOUT98U49387FSDIUJ4983UASDKLJHSJAFDHAJDFHKAJSDFHKASJDFHKJASDFHKASJFDHIU4YKJSDFHIUHFKJHSSU

#include "../utility/singleton.hpp"
#include "./beta.hpp"

//#include <cmath>

namespace vg
{

    template < typename Return_Type, typename Engine >
    struct arcsine : private beta<Return_Type, Engine>
    {
            typedef beta<Return_Type, Engine>       beta_type;
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef Engine                          engine_type;

            engine_type& e_;

            explicit arcsine( const seed_type sd = 0 ) noexcept : e_( singleton<engine_type>::instance() )
            {
                e_.reset_seed( sd );
            }

            return_type operator()() const noexcept
            {
                return do_generation();
            }

        protected:
            /*
            Numerical Test
            (1) using direct impl method :
                    Testing arcsine engine with n = 10000000
                    |        | Theoretical Value |  Generated value |
                   *|  Mean  |      0.5          |  0.636579    |
                   *|Variance|     0.125         |  0.0947444   |
                   *|Skewness|       0           |  -0.496869   |
            (2) using beta method:
                    Testing arcsine engine with n = 10000000
                    |        | Theoretical Value |  Generated value |
                    |  Mean  |      0.5          |  0.50005     |
                    |Variance|     0.125         |  0.127052    |
                    |Skewness|       0           |  0.000107981 |
            */
            return_type do_generation() const noexcept
            {
                return beta_impl();
            }

        private:
            return_type beta_impl() const noexcept
            {
                return beta_type::do_generation( final_type(0.5), final_type(0.5) );
            }

        private:
            return_type direct_impl() const noexcept
            {
                const final_type u = e_();
                const final_type pi = 3.1415926535897932384626433L;
                const final_type ans = std::sin( pi * u );
                return ans;
            }

    };

}//namespace vg

#endif//_ARCSINE_HPP_INCLUEDE_WHAOUT98U49387FSDIUJ4983UASDKLJHSJAFDHAJDFHKAJSDFHKASJDFHKJASDFHKASJFDHIU4YKJSDFHIUHFKJHSSU

