#ifndef _GEOMETRIC_HPP_INCLUDED_SO8IU298ALKJSDLKJCNO8UJA98Y3OLIAFDPOIHJSDALKJ344
#define _GEOMETRIC_HPP_INCLUDED_SO8IU298ALKJSDLKJCNO8UJA98Y3OLIAFDPOIHJSDALKJ344


#include <cassert>

namespace vg
{

    template <
                typename Return_Type ,
                typename Engine
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
            return polar_method( P );
        }

    private:
        return_type
        coin_flip_method( const final_type P )
        {
            value_type ans = 1;

            while ( e_() > P )
                { ++ans; }

            return ans;
        }

        return_type
        polar_method( const final_type P )
        {
            const final_type u = e_();
            const final_type n = std::ceil( log( u ) / log( final_type( 1 ) - P ) );
            return static_cast<return_type>( n );
        }

    };

}//namespace vg



#endif//_GEOMETRIC_HPP_INCLUDED_SO8IU298ALKJSDLKJCNO8UJA98Y3OLIAFDPOIHJSDALKJ344


