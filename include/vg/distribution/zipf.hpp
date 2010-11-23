#ifndef _ZIPF_HPP_INCLUDED_SDO8UJ3498UASFASFDOIJHSLKJ3QP4OUJSDFOIJ4OPIAS23RIJASFOIJ498ASFDKLJ4UIOAJFLIJKASFDAFS089JIO34AFSD
#define _ZIPF_HPP_INCLUDED_SDO8UJ3498UASFASFDOIJHSLKJ3QP4OUJSDFOIJ4OPIAS23RIJASFOIJ498ASFDKLJ4UIOAJFLIJKASFDAFS089JIO34AFSD 

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct zipf
    {
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;
            typedef typename engine_type::final_type    final_type;
            typedef typename engine_type::seed_type     seed_type;

            return_type         a_;
            engine_type         e_;

            explicit zipf(	const return_type a = 2,
                            const seed_type sd = 0 )
                : a_( a ), e_( sd )
            {
                assert( a > 1 );
            }

            return_type
            operator()()
            {
                return do_generation( a_ );
            }

        protected:
            return_type
            do_generation( const final_type A )
            {
                return rejection_method( A );
            }

        private:
            return_type
            rejection_method( const final_type A )
            {
                const final_type a_1 = A - final_type(1);
                const final_type b = std::pow( 2, a_1 );
                const final_type b_1 = b - final_type(1);

                for ( ;; )
                {
                    const final_type u = e_();
                    const final_type v = e_();
                    const final_type x = std::pow( u, -final_type(1) / a_1 );
                    const final_type X = std::ceil( x );
                    const final_type T = std::pow( (X+final_type(1))/X, a_1 );
                    const final_type T_1 = T - final_type(1);
                    const final_type lhs = v * X * T_1 / b_1;
                    const final_type rhs = T / b;

                    if ( lhs <= rhs ) return X;
                }

                assert( !"zipf: should never reach here!" );

                return return_type();
            }

    };

}//vg


#endif//_ZIPF_HPP_INCLUDED_SDO8UJ3498UASFASFDOIJHSLKJ3QP4OUJSDFOIJ4OPIAS23RIJASFOIJ498ASFDKLJ4UIOAJFLIJKASFDAFS089JIO34AFSD 

