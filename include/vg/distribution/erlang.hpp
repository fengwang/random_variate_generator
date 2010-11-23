#ifndef _ERLANG_HPP_INCLUDED_MBSDLKJ98USIJEIJHFD984KJHSDFIOUHJS98E3D8EOIUHS9
#define _ERLANG_HPP_INCLUDED_MBSDLKJ98USIJEIJHFD984KJHSDFIOUHJS98E3D8EOIUHS9

#if 0

COMMENT:
The chi - square distribution with k degrees of freedom is the distribution of
a sum of the squares of k independent standard normal random variables.

#endif

#include <vg/distribution/gamma.hpp>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct erlang : private gamma<Return_Type, Engine>
    {
            typedef gamma<Return_Type, Engine>          gamma_type;
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;

            typedef typename engine_type::final_type    final_type;
            typedef typename engine_type::seed_type     seed_type;
            typedef typename engine_type::size_type     size_type;

            return_type     a_;
            return_type     n_;
            engine_type     e_;


            explicit erlang( const return_type a = return_type( 1 ),
                             const return_type n = return_type( 10 ),
                             const seed_type sd = 0 )
                : a_( a ), n_( n ), e_( sd )
            {}

            return_type
            operator()()
            {
                return do_generation( a_, n_ );
            }

        protected:
            return_type
            do_generation( const final_type A, const final_type N )
            {
                return erlang_direct_impl( a_, n_ );
            }

        private:
            return_type
            erlang_direct_impl( const final_type A, const final_type N )
            {
                const final_type ans = gamma_type::do_generation( N, A );
                return ans;
            }

    };

}//vg


#endif//_ERLANG_HPP_INCLUDED_MBSDLKJ98USIJEIJHFD984KJHSDFIOUHJS98E3D8EOIUHS9


