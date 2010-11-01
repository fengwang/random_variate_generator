#ifndef _PARETO_HPP_INCLUDED_ASFLDKJO3RUI9LASFIKJ38U9ALFISFJOIUWERLKJFSDLKJASFLK
#define _PARETO_HPP_INCLUDED_ASFLDKJO3RUI9LASFIKJ38U9ALFISFJOIUWERLKJFSDLKJASFLK

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
				 typename Engine
             >
    struct pareto
    {
        typedef Return_Type                         return_type;
        typedef Engine                              engine_type;

        typedef typename engine_type::final_type    final_type;
        typedef typename engine_type::seed_type     seed_type;

        return_type a_;
        return_type b_;
        engine_type e_;

        explicit pareto(  	const return_type a = 1,
							const return_type b = 2,
							const seed_type sd = 0)
            : a_( a ), b_(b), e_( sd )
        {
			assert( a_ > 0 );
        }

        return_type
        operator ()()
        {
            const final_type u = e_();
			const final_type tmp = std::pow( u, final_type(1)/a_ );
			const final_type ans = b_ / tmp;

			return static_cast<return_type>( ans );
        }
    };

}//vg


#endif//_PARETO_HPP_INCLUDED_ASFLDKJO3RUI9LASFIKJ38U9ALFISFJOIUWERLKJFSDLKJASFLK

