#ifndef _PEARSON_VI_HPP_INCLUDED_SDFOISDLK4O8USFADLKJ4OIAFSLKJEROIJSDFLKJSLFKJ4OIUSFLDFGKLJDGKLJDFGKLJHSDLAIOUYEJKHGSFDHK
#define _PEARSON_VI_HPP_INCLUDED_SDFOISDLK4O8USFADLKJ4OIAFSLKJEROIJSDFLKJSLFKJ4OIUSFLDFGKLJDGKLJDFGKLJHSDLAIOUYEJKHGSFDHK

#include <vg/distribution/gamma.hpp>

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct pearson_vi : private gamma<Return_Type, Engine>
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

            explicit pearson_vi(	const value_type a = value_type( 1 ),
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
                const final_type ga = gamma_type::do_generation(A);
                const final_type gb = gamma_type::do_generation(B);
                return ga/gb;
            }

    };

}//vg

#endif//_PEARSON_VI_HPP_INCLUDED_SDFOISDLK4O8USFADLKJ4OIAFSLKJEROIJSDFLKJSLFKJ4OIUSFLDFGKLJDGKLJDFGKLJHSDLAIOUYEJKHGSFDHK

