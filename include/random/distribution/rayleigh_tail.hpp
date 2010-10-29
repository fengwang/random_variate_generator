#ifndef _RAYLEIGH_TAIL_HPP_INCLUDED_SLDKJ34OIUSAFO87U3LKJASFO9834IKASFDLIJHSFDLK
#define _RAYLEIGH_TAIL_HPP_INCLUDED_SLDKJ34OIUSAFO87U3LKJASFO9834IKASFDLIJHSFDLK

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
				 typename Engine
             >
    struct rayleigh_tail
    {
        typedef Return_Type                         return_type;
        typedef Engine                              engine_type;

        typedef typename engine_type::final_type    final_type;
        typedef typename engine_type::seed_type     seed_type;

        return_type delta_;
        engine_type e_;

        explicit rayleigh_tail(  	const return_type delta = 1,
									const seed_type sd = 0)
            : delta_( delta ), e_( sd )
        {
			assert( delta_ > 0 );
        }

        return_type
        operator ()()
        {
            const final_type u      =   e_();
			const final_type tmp1   =   std::log( u );
			const final_type tmp2   =   delta_ * delta_ - tmp1 - tmp1;
			const final_type ans    =   std::sqrt( tmp2 );

			return static_cast<return_type>( ans );
        }
    };

}//vg

#endif//_RAYLEIGH_TAIL_HPP_INCLUDED_SLDKJ34OIUSAFO87U3LKJASFO9834IKASFDLIJHSFDLK


