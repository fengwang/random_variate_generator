#ifndef _MIZUTANI_HPP_INCLUDED904KLDJA1Q2W3E4RLKJFIUJ682LI4SAF89D8HFAIUYERIKASFDUIOH4AFSD98ASDFNVSSSSSSSSSSOIJWER
#define _MIZUTANI_HPP_INCLUDED904KLDJA1Q2W3E4RLKJFIUJ682LI4SAF89D8HFAIUYERIKASFDUIOH4AFSD98ASDFNVSSSSSSSSSSOIJWER 

#include <vg/distribution/generalized_hypergeometric_b3.hpp>

#include <cassert>

namespace vg
{

    template <
                typename Return_Type,
                typename Engine
             >
    struct mizutani : private generalized_hypergeometric_b3<Return_Type, Engine>
    {
        typedef generalized_hypergeometric_b3< Return_Type, Engine> GHgB3_type;
        typedef typename Engine::final_type     final_type;
        typedef Return_Type                     return_type;
        typedef Return_Type                     value_type;
        typedef typename Engine::seed_type      seed_type;
        typedef std::size_t                     size_type;
        typedef Engine                          engine_type;

        value_type           a_; 
        engine_type          e_;

        explicit mizutani(value_type a = 1 , seed_type s = 0 ) : a_( a ), e_( s ) 
        {
            assert( a > 0 );
        }

        return_type
        operator()()
        {
            return do_generation( a_ );
        }

    protected:
        return_type
        do_generation( const value_type a )
        {
            return direct_impl( a );
        }

    private:
        // S. Mizutani, Vocabulary in women's magazines, Kokken-Hokoku, National Language Research Institute, Tokyo, 1953.
        return_type
        direct_impl( const value_type a )
        {
            const final_type ans = GHgB3_type::do_generation( a, final_type(1), final_type(1) );
            return ans;
        }
    };

}//namespace vg

#endif//_MIZUTANI_HPP_INCLUDED904KLDJA1Q2W3E4RLKJFIUJ682LI4SAF89D8HFAIUYERIKASFDUIOH4AFSD98ASDFNVSSSSSSSSSSOIJWER 
