#ifndef _CHI_SQUARE_HPP_INCLUDED_MBSDLKJ98USIJEIJHFD984KJHSDFIOUHJS98E3D8EOIUHS9
#define _CHI_SQUARE_HPP_INCLUDED_MBSDLKJ98USIJEIJHFD984KJHSDFIOUHJS98E3D8EOIUHS9

#if 0

COMMENT:
The chi-square distribution with k degrees of freedom is the distribution of 
a sum of the squares of k independent standard normal random variables.

#endif 

#include "gamma.hpp"

namespace vg
{

    template <   typename Return_Type,
				 typename Engine
             >
    struct chi_square : private gamma<Return_Type, Engine>
    {
        typedef Return_Type                         return_type;
        typedef Engine                              engine_type;


        typedef typename engine_type::final_type    final_type;
        typedef typename engine_type::seed_type     seed_type;
        typedef typename engine_type::size_type     size_type;

        size_type       k_;
        engine_type     e_;

        explicit chi_square(    const size_type k = 10,
                                const seed_type sd = 0 )
            : k_( k ), e_( sd )
        {}

        return_type
        operator ()()
        {
            return chi_square_direct_impl( k_ );
        }

        protected:
        return_type
        chi_square_direct_impl( const size_type K )
        {
            const final_type ans = gamma<Return_Type, Engine>::marsaglia_tsang_method(final_type(K)/final_type(2), final_type(1));

            return static_cast<return_type>( ans + ans );
        }

    };

}//vg


#endif//_CHI_SQUARE_HPP_INCLUDED_MBSDLKJ98USIJEIJHFD984KJHSDFIOUHJS98E3D8EOIUHS9


