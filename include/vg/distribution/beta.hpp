#ifndef _BETA_HPP_INCLUDED_SODFIJ34LKJASFODIJ3498UAFSLKJ4398UAFSLKJ498UAFSLKJ34D
#define _BETA_HPP_INCLUDED_SODFIJ34LKJASFODIJ3498UAFSLKJ4398UAFSLKJ498UAFSLKJ34D

#include "gamma.hpp"

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct beta : private gamma<Return_Type, Engine>
    {
            typedef Return_Type                         		return_type;
            typedef Engine                              		engine_type;
            typedef return_type                                 value_type;
            typedef typename engine_type::size_type          	size_type;
            typedef typename engine_type::final_type    	    final_type;
            typedef typename engine_type::seed_type     	    seed_type;

            value_type          a_;
            value_type          b_;
            engine_type         e_;

            explicit beta(	const value_type a = value_type( 1 ),
                            const value_type b = value_type( 1 ),
                            const seed_type sd = 0 )
                : a_( a ), b_( b ), e_( sd )
            {
                assert( a_ > 0 );
                assert( b_ > 0 );
            }

            return_type
            operator()()
            {
                return direct_beta_impl( a_, b_ );
            }

        protected:

            return_type
            direct_beta_impl( const final_type A, const final_type B )
            {
                const final_type a =  marsaglia_tsang_method( A, final_type( 1 ) );
                const final_type b =  marsaglia_tsang_method( B, final_type( 1 ) );
                return static_cast<return_type>( a / ( a + b ) );
            }
    };

}//vg

#endif//_BETA_HPP_INCLUDED_SODFIJ34LKJASFODIJ3498UAFSLKJ4398UAFSLKJ498UAFSLKJ34D


