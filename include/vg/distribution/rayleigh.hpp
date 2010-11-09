#ifndef _RAYLEIGH_HPP_INLCUDED_DSOIJ34O8UASFD98UY498UAFSDOIU3498UFLKJA0LDKLJASMA
#define _RAYLEIGH_HPP_INLCUDED_DSOIJ34O8UASFD98UY498UAFSDOIU3498UFLKJA0LDKLJASMA

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct rayleigh
    {
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;

            typedef typename engine_type::final_type    final_type;
            typedef typename engine_type::seed_type     seed_type;

            return_type delta_;
            engine_type e_;

            explicit rayleigh(	const return_type delta = 1,
                                const seed_type sd = 0 )
                : delta_( delta ), e_( sd )
            {
                assert( delta_ > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( delta_ );
            }

        protected:
            return_type
            do_generation( const return_type delta )
            {
                return direct_impl( delta );
            }

        private:
            return_type
            direct_impl( const return_type delta )
            {
                const final_type u = e_();
                const final_type tmp1 = - std::log( u );
                const final_type tmp2 = std::sqrt( tmp1 );
                const final_type ans = delta * tmp2;
                return static_cast<return_type>( ans );
            }
    };

}//vg

#endif//_RAYLEIGH_HPP_INLCUDED_DSOIJ34O8UASFD98UY498UAFSDOIU3498UFLKJA0LDKLJASMA


