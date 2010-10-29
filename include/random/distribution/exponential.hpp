#ifndef _EXPONENTIAL_HPP_INCLUDED_98JKLJHWE8UHSFDWE98HSFDIUHEUHSAKUHAIUHWEIUHASF
#define _EXPONENTIAL_HPP_INCLUDED_98JKLJHWE8UHSFDWE98HSFDIUHEUHSAKUHAIUHWEIUHASF

#include <cmath>
#include <cassert>

namespace feng
{

    template <   typename Return_Type,
				 typename Engine
             >
    struct exponential
    {
        typedef Return_Type                         return_type;
        typedef Engine                              engine_type;

        typedef typename engine_type::final_type    final_type;
        typedef typename engine_type::seed_type     seed_type;

        return_type         lambda_;
        engine_type         e_;

        explicit exponential(  	const return_type lambda = 1,
								const seed_type sd = 0 )
            : lambda_( lambda ), e_( sd )
        {
			assert( lambda_ > 0 );
        }

        return_type
        operator ()()
        {
            return direct_exponential_impl( lambda_ );
        }

    protected:
        return_type
        direct_exponential_impl( const final_type Lambda )
        {
            const final_type ans =  - std::log( - e_() ) / Lambda;
            
			return static_cast<return_type>( ans );
        }

    };

}//feng


#endif//_EXPONENTIAL_HPP_INCLUDED_98JKLJHWE8UHSFDWE98HSFDIUHEUHSAKUHAIUHWEIUHASF


