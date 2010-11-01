#ifndef _TRIANGULAR_HPP_INCLUDED_WOIJALDKJ4OIUASFLKJ34OUAFSLKJ4OIJAFLKJ3OIJAFSLA
#define _TRIANGULAR_HPP_INCLUDED_WOIJALDKJ4OIUASFLKJ34OUAFSLKJ4OIJAFLKJ3OIJAFSLA

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
				 typename Engine
             >
    struct triangular
    {
        typedef Return_Type                         return_type;
        typedef Engine                              engine_type;

        typedef typename engine_type::final_type    final_type;
        typedef typename engine_type::seed_type     seed_type;

        return_type delta_;
        engine_type e_;

        explicit triangular(  	const return_type delta = 1,
								const seed_type sd = 0)
            : delta_( delta ), e_( sd )
        {
			assert( delta_ > 0 );
        }

        return_type
        operator ()()
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
            const final_type u      =       e_();
			const final_type tmp    =       1 - std::log( u );
			const final_type ans    =       delta * tmp;

			return static_cast<return_type>( ans );
        }
    };

}//vg

#endif//_TRIANGULAR_HPP_INCLUDED_WOIJALDKJ4OIUASFLKJ34OUAFSLKJ4OIJAFLKJ3OIJAFSLA

