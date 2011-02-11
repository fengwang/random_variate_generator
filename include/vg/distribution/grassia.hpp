#ifndef _GRASSIA_HPP_INCLUDED_SDKLJSLKJ4O88UISDFLK4OIUSDFKLJGFLSJASKJHSDFJ34O8USFKL4OUISDFKLU4OIUSFOIUEISFKLJFJKSLKJDLKJF
#define _GRASSIA_HPP_INCLUDED_SDKLJSLKJ4O88UISDFLK4OIUSDFKLJGFLSJASKJHSDFJ34O8USFKL4OUISDFKLU4OIUSFOIUEISFKLJFJKSLKJDLKJF

#include <vg/distribution/gamma.hpp>

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct grassia : private gamma<Return_Type, Engine>
    {
            typedef gamma<Return_Type, Engine>                  gamma_type;
            typedef Return_Type                         		return_type;
            typedef Engine                              		engine_type;
            typedef return_type                                 value_type;
            typedef typename engine_type::size_type          	size_type;
            typedef typename engine_type::final_type    	    final_type;
            typedef typename engine_type::seed_type     	    seed_type;

            value_type          a_;
            value_type          b_;
            engine_type         e_;

            explicit grassia(	const value_type a = value_type( 1 ),
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
                return direct_impl_method( A, B );
            }

        private:
            return_type
            direct_impl_method( const final_type A, const final_type B )
            {
                const final_type x = gamma_type::do_generation( A, B );
                const final_type ans = std::exp( -x );
                return ans;
            }

    };

}//vg

#endif//_GRASSIA_HPP_INCLUDED_SDKLJSLKJ4O88UISDFLK4OIUSDFKLJGFLSJASKJHSDFJ34O8USFKL4OUISDFKLU4OIUSFOIUEISFKLJFJKSLKJDLKJF

