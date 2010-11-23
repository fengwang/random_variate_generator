#ifndef _PLANCK_HPP_INCLUDED_SDFO9U3498UYASFDKLJ4H98UY3498AFSDLIJ43908UASFDOIJKSFDLKJASFDO8JI34KLXJSFDLKJAFSD
#define _PLANCK_HPP_INCLUDED_SDFO9U3498UYASFDKLJ4H98UY3498AFSDLIJ43908UASFDOIJKSFDLKJASFDO8JI34KLXJSFDLKJAFSD 

#include <vg/distribution/gamma.hpp>
#include <vg/distribution/zipf.hpp>

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct planck : private gamma<Return_Type, Engine>,
                    private zipf<Return_Type, Engine>
    {
            typedef gamma<Return_Type, Engine>                  gamma_type;
            typedef zipf<Return_Type, Engine>                   zipf_type;
            typedef Return_Type                         		return_type;
            typedef Engine                              		engine_type;
            typedef return_type                                 value_type;
            typedef typename engine_type::size_type          	size_type;
            typedef typename engine_type::final_type    	    final_type;
            typedef typename engine_type::seed_type     	    seed_type;

            value_type          a_;
            value_type          b_;
            engine_type         e_;

            explicit planck(	const value_type a = value_type( 1 ),
                                const value_type b = value_type( 1 ),
                                const seed_type sd = 0 )
                : a_( a ), b_( b ), e_( sd )
            {
                assert( a > 0 );
                assert( b > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( a_, b_ );
            }

        protected:
            return_type
            do_generation( const final_type A, const final_type B )
            {
                return direct_impl( A, B );
            }

        private:
            return_type
            direct_impl( const final_type A, const final_type B )
            {
                const final_type A_1 = A + final_type(1);
                const final_type G = gamma_type::do_generation( A_1 );
                const final_type Z = zipf_type::do_generation( A_1 );

                return G / B / Z;
            }

    };
}//vg



#endif//_PLANCK_HPP_INCLUDED_SDFO9U3498UYASFDKLJ4H98UY3498AFSDLIJ43908UASFDOIJKSFDLKJASFDO8JI34KLXJSFDLKJAFSD 

