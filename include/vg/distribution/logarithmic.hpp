#ifndef _LOGARITHMIC_HPP_INCLUDED_SODFJIN4ELIJASFO9I8U4AJSFDLKJ4OIJASFLIJ3OASIFJ
#define _LOGARITHMIC_HPP_INCLUDED_SODFJIN4ELIJASFO9I8U4AJSFDLKJ4OIJASFLIJ3OASIFJ

#include <cmath>
#include <cassert>
#include <cstddef>

namespace vg
{

    template <
                typename Return_Type,
                typename Engine
             >
    struct logarithmic
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef Return_Type                     value_type;
            typedef typename Engine::seed_type      seed_type;
            typedef std::size_t 					size_type;

            final_type p_;
            Engine e_;

            explicit logarithmic( final_type p = final_type( 0.5 ),
                                  const seed_type s = seed_type( 0 ) )
                : p_( p ), e_( s )
            {
                assert( p_ > final_type( 0 ) );
                assert( p_ < final_type( 1 ) );
            }

            return_type
            operator()()
            {
                return do_generation( p_ );
            }

        protected:
            return_type
            do_generation( const final_type P )
            {
                return direct_impl( P );
            }

        private:
            return_type
            direct_impl( const final_type P )
            {
                final_type v = e_();

                while ( final_type( 0 ) == v )
                {
                    v = e_();
                }

                final_type u = e_();

                while ( final_type( 0 ) == u )
                {
                    u = e_();
                }

                const final_type c = std::log( final_type( 1 ) - P );

                const final_type q = final_type( 1 ) - std::exp( c * u );

                if ( v >= P )
                    { return 1; }

                if ( q * q > v )
                    { return final_type( 1 ) + std::log( v ) / std::log( q ); }

                if ( q >= v )
                    { return 2; }

                return 1;
            }


    };

}//namespace vg

#endif//_LOGARITHMIC_HPP_INCLUDED_SODFJIN4ELIJASFO9I8U4AJSFDLKJ4OIJASFLIJ3OASIFJ

