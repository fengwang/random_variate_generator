#ifndef _UNIFORM_HPP_INCLUDED_98U3LKJFASD98IHJ3WLKJNASF98YU12LAKFJ289UJAWOIJUW2I
#define _UNIFORM_HPP_INCLUDED_98U3LKJFASD98IHJ3WLKJNASF98YU12LAKFJ289UJAWOIJUW2I

#include <cassert>

namespace vg
{

    template <
				typename Return_Type = long double,
				typename Engine = mitchell_moore
             >
    struct uniform
    {
        typedef typename Engine::final_type     final_type;
        typedef Return_Type                     return_type;
        typedef Return_Type                     value_type;
        typedef typename Engine::seed_type      seed_type;

        value_type      lower_;
        value_type      upper_;
        Engine          e_;

        explicit uniform(   const value_type lower = value_type( 0 ),
                            const value_type upper = value_type( 1 ),
                            const seed_type s = seed_type( 0 ) )
            : lower_( lower ), upper_( upper ), e_( s )
        {
            assert( upper > lower );
        }

        return_type
        operator()()
        {
            return do_generation( lower_, upper_ );
        }

        protected:
        return_type
        do_generation( const value_type lower, const value_type upper )
        {
            return direct_impl( lower, upper );
        }

        private:
        return_type
        direct_impl( const value_type lower, const value_type upper )
        {
			const final_type lower_f    =   static_cast<final_type>(lower);
			const final_type upper_f    =   static_cast<final_type>(upper);
			const final_type ans_f      =   lower_f + e_() * ( upper_f - lower_f );
			const return_type ans       =   static_cast<return_type>( ans_f );

			return ans;
        }
    };

}//namespace vg

#endif//_UNIFORM_HPP_INCLUDED_98U3LKJFASD98IHJ3WLKJNASF98YU12LAKFJ289UJAWOIJUW2I

