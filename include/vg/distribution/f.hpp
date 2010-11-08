#ifndef _F_HPP_INCLUDED_SOIFJ34LIJAFSPOIJ4398AFSOHSOIJ4LKJASFLKJ3LKJASFDLKJ3IFAK
#define _F_HPP_INCLUDED_SOIFJ34LIJAFSPOIJ4398AFSOHSOIJ4LKJASFLKJ3LKJASFDLKJ3IFAK

#include "gamma.hpp"
#include "chi_square.hpp"
#include "exponential.hpp"

#include <cmath>
#include <cstddef>
#include <limits>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct f :  private gamma<Return_Type, Engine>
    {
            typedef gamma<Return_Type, Engine>      gamma_type;

            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef typename Engine::size_type      size_type;
            typedef Engine                          engine_type;

            final_type  mu1_;
            final_type  mu2_;
            engine_type e_;

            explicit f( const return_type mu1 = 2, const return_type mu2 = 2, const seed_type sd = 0 )
                : mu1_( mu1 ), mu2_(mu2), e_( sd )
            {
                assert( mu1 > 0 );
                assert( mu2 > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( mu1_, mu2_ );
            }

        protected:
            return_type
            do_generation( const return_type mu1, const return_type mu2 )
            {
                return direct_impl( mu1, mu2 );
            }

        private:
            return_type
            direct_impl( const return_type mu1, const return_type mu2 )
            {
                const final_type y1 = gamma_type::do_generation( mu1/final_type(2), final_type(2) );
                const final_type y2 = gamma_type::do_generation( mu2/final_type(2), final_type(2) );
                const final_type ans = y1 * mu2 / (y2 * mu1);
                return ans;
            }

    };

}//namespace vg

#endif//_F_HPP_INCLUDED_SOIFJ34LIJAFSPOIJ4398AFSOHSOIJ4LKJASFLKJ3LKJASFDLKJ3IFAK

