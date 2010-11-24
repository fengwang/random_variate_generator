#ifndef _FACTORIAL_HPP_INCLUDED_SDOIJ34OPIUASFDLKJ4OIUJSDLKJFFFFFFFFFFFFFFFFFFFFFFFFFFFFFSLKJDOAIJSLKJAJ
#define _FACTORIAL_HPP_INCLUDED_SDOIJ34OPIUASFDLKJ4OIUJSDLKJFFFFFFFFFFFFFFFFFFFFFFFFFFFFFSLKJDOAIJSLKJAJ 

#include <vg/distribution/generalized_hypergeometric_b3.hpp>

#include <cassert>

namespace vg
{

    template <
                typename Return_Type,
                typename Engine
             >
    struct factorial : private generalized_hypergeometric_b3<Return_Type, Engine>
    {
        typedef generalized_hypergeometric_b3< Return_Type, Engine> GHgB3_type;
        typedef typename Engine::final_type     final_type;
        typedef Return_Type                     return_type;
        typedef Return_Type                     value_type;
        typedef typename Engine::seed_type      seed_type;
        typedef std::size_t                     size_type;
        typedef Engine                          engine_type;

        value_type           k_; 
        value_type           r_; 
        engine_type          e_;

        explicit factorial(value_type k = 3, value_type r = 3, seed_type s = 0 ) : k_( k ), r_( r ), e_( s ) 
        {
            assert( k >= 2 );
            assert( r >= k );
        }

        return_type
        operator()()
        {
            return do_generation( k_, r_ );
        }

    protected:
        return_type
        do_generation( const value_type k, const value_type r )
        {
            return direct_impl( k, r );
        }

    private:
        // W. H. Marlow, "Factorial distributions", Annals of Mathematical Statistics, vol. 36, pp. 1066-1068, 1965
        return_type
        direct_impl( const value_type k, const value_type r )
        {
            const final_type r_1 = r - final_type(1);
            const final_type ans = GHgB3_type::do_generation( final_type(1), k - r_1, r_1 );
            return ans;
        }
    };

}//namespace vg

#endif//_FACTORIAL_HPP_INCLUDED_SDOIJ34OPIUASFDLKJ4OIUJSDLKJFFFFFFFFFFFFFFFFFFFFFFFFFFFFFSLKJDOAIJSLKJAJ 

