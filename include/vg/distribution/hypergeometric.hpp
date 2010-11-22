#ifndef _HYPERGEOMETRIC_HPP_INCLUDED_SODFIJ4OU89ASFLKJ4U89AFSKLIJH48YASFLIU498UYFDKLJ
#define _HYPERGEOMETRIC_HPP_INCLUDED_SODFIJ4OU89ASFLKJ4U89AFSKLIJH48YASFLIU498UYFDKLJ

#include <cassert>
#include <cstddef>
#include <cmath>

namespace vg
{

    template <
                typename Return_Type,
                typename Engine
             >
    struct hypergeometric
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef Return_Type                     value_type;
            typedef typename Engine::seed_type      seed_type;
            typedef std::size_t                     size_type;
            typedef Engine                          engine_type;

#if 0
            Let there be [n1] ways for a "good" selection and [n2] ways for a "bad" selection out of a total of [n1+n2] possibilities.
            Take [k] samples and let x_i equal 1 if selection i is successful and 0 if it is not.
            Return the total number of successful selections.
#endif

        size_type           n1_; // good  
        size_type           n2_; // bad 
        size_type           k_;  // samples 
        engine_type         e_;

        explicit hypergeometric( size_type n1 = 1, size_type n2 = 0, size_type k = 1 , seed_type s = 0 )
                : n1_( n1 ), n2_( n2 ), k_( k ), e_( s ) {}

        return_type
        operator()()
        {
            return do_generation( n1_, n2_, k_ );
        }

        protected:
            return_type
            do_generation( const size_type n1, const size_type n2, const size_type k )
            {
                const size_type n = n1 + n2;

                if ( k >= n )
                    { return n1; }

                if ( 0 == n1 )
                    { return 0; }

                if ( 0 == n2 )
                    { return k; }

                if ( k < ( n >> 1 ) )
                    { return direct_impl( n1, n2, k ); }

                return n1 - direct_impl( n1, n2, n - k );
            }

        private:
            return_type
            direct_impl( const size_type n1, const size_type n2, const size_type k )
            {
                size_type b = n1 + n2;
                size_type a = n1;
                size_type ans = 0;

                for ( size_type i = 0; i < k; ++i )
                {
                    if ( e_() * final_type( b-- ) < final_type( a ) )
                    {
                        ++ans;
                        --a;

                        if ( ans ==  n1 )
                            { break; }
                    }
                }

                return ans;
            }
    };

}//namespace vg



#endif//_HYPERGEOMETRIC_HPP_INCLUDED_SODFIJ4OU89ASFLKJ4U89AFSKLIJH48YASFLIU498UYFDKLJ 

