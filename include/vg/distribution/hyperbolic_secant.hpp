#ifndef _HYPERBOLIC_SECANT_HPP_INCLUDED_SOFDIJKOI43UJKLGJKLDIUJDFGOIU4598UDGOIUDFGJKDFKLJGLKJSDLKJDOIVLKJVLIDFOIUR5IIOGDU
#define _HYPERBOLIC_SECANT_HPP_INCLUDED_SOFDIJKOI43UJKLGJKLDIUJDFGOIU4598UDGOIUDFGJKDFKLJGLKJSDLKJDOIVLKJVLIDFOIUR5IIOGDU

#include <cmath>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct hyperbolic_secant
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef Engine                          engine_type;

            engine_type e_;

            explicit hyperbolic_secant( const seed_type sd = 0 ) : e_( sd )
            {}

            return_type
            operator()()
            {
                return do_generation();
            }

        protected:
            return_type
            do_generation()
            {
                return direct_impl_method();
            }

        private:
            return_type
            direct_impl_method()
            {
                const final_type u = e_();
                const final_type pi_2 = 3.1415926535897932384626433L / 2.0L;
                const final_type ans = std::log( std::tan( u * pi_2 ) );
                return ans;
            }

    };

}//namespace vg

#endif//_HYPERBOLIC_SECANT_HPP_INCLUDED_SOFDIJKOI43UJKLGJKLDIUJDFGOIU4598UDGOIUDFGJKDFKLJGLKJSDLKJDOIVLKJVLIDFOIUR5IIOGDU

