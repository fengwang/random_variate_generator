#ifndef _CAUCHY_HPP_INCLUDED_SDOIFJ32OIJASF0O9UI34LIAFSO0U340U9AFSLIUJRLIJDFSLKJ
#define _CAUCHY_HPP_INCLUDED_SDOIFJ32OIJASF0O9UI34LIAFSO0U340U9AFSLIUJRLIJDFSLKJ

#if 0
    The Cauchy distribution, also called the Lorentzian distribution or Lorentz distribution, 
    is a continuous distribution describing resonance behavior. It also describes the distribution 
    of horizontal distances at which a line segment tilted at a random angle  cuts the x-axis. 
#endif 

#include <cmath>
#include <cassert>

namespace vg
{
    template <   typename Return_Type,
                 typename Engine
             >
    struct cauchy
    {
        typedef Return_Type                         return_type;
        typedef Engine                              engine_type;

        typedef typename engine_type::final_type    final_type;
        typedef typename engine_type::seed_type     seed_type;

        return_type delta_;
        engine_type e_;

        explicit cauchy(    const return_type delta = 1,
                            const seed_type sd = 0)
            : delta_( delta ), e_( sd ) 
        {
            assert( delta_ > 0 );
        }

        return_type
        operator ()()
        {
            return cauchy_direct_impl( delta_ );
        }

        protected:
        return_type
        cauchy_direct_impl( const final_type Delta )
        {
            const final_type pi = 3.1415926535897932384626433L;
            for (;;)
            {
                const final_type u = e_();
                if ( u != final_type(0.5) )
                {
                    return static_cast<return_type>(Delta * std::tan( pi * u ));
                }
            }
        }

    };

}//vg

#endif//_CAUCHY_HPP_INCLUDED_SDOIFJ32OIJASF0O9UI34LIAFSO0U340U9AFSLIUJRLIJDFSLKJ



