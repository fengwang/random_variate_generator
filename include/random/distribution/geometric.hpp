#ifndef _GEOMETRIC_HPP_INCLUDED_SO8IU298ALKJSDLKJCNO8UJA98Y3OLIAFDPOIHJSDALKJ344
#define _GEOMETRIC_HPP_INCLUDED_SO8IU298ALKJSDLKJCNO8UJA98Y3OLIAFDPOIHJSDALKJ344


#include <cassert>

namespace vg
{

    template <
                typename Return_Type = unsigned long,
                typename Engine = mitchell_moore
             >
    struct geometric
    {
        typedef typename Engine::final_type     final_type;
        typedef Return_Type                     return_type;
        typedef Return_Type                     value_type;
        typedef typename Engine::seed_type      seed_type;

        final_type p_;
        Engine e_;

        explicit geometric( final_type p = final_type( 0.5 ),
                            const seed_type s = seed_type( 0 ) )
            : p_( p ), e_( s )
        {}

        return_type
        operator()()
        {
            assert( p_ > final_type( 0 ) );
            assert( p_ < final_type( 1 ) );

            return polar_method();
        }

    protected:
        return_type
        coin_flip_method()
        {
            value_type ans = 1;

            while ( e_() > p_ )
                { ++ans; }

            return ans;
        }

        return_type
        polar_method()
        {
            const final_type u = e_();
            const final_type n = std::ceil( log( u ) / log( final_type( 1 ) - p_ ) );
            return static_cast<return_type>( n );
        }

    };

}//namespace vg



#endif//_GEOMETRIC_HPP_INCLUDED_SO8IU298ALKJSDLKJCNO8UJA98Y3OLIAFDPOIHJSDALKJ344


