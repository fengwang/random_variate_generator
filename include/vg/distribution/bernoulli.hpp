#ifndef _BERNOULLI_HPP_INCLUDED_2I8HJAFLKHJFSDKMNVCLKJNAJIHEIUAO9HWE9U8HYSDFIHJ2
#define _BERNOULLI_HPP_INCLUDED_2I8HJAFLKHJFSDKMNVCLKJNAJIHEIUAO9HWE9U8HYSDFIHJ2

#if 0

COMMENT:
The Bernoulli distribution is a discrete distribution having two possible 
outcomes labelled by n=0 and n=1 in which n=1 ("success") occurs with probability 
p and n=0 ("failure") occurs with probability q=1-p, where 0<p<1. 

#endif

#include <cassert>
#include <cstddef>

namespace vg
{

    template <
				typename Return_Type,
				typename Engine
             >
    struct bernoulli
    {
        typedef typename Engine::final_type     final_type;
        typedef Return_Type                     return_type;
        typedef Return_Type                     value_type;
        typedef typename Engine::seed_type      seed_type;
		typedef std::size_t 					size_type;

        final_type p_;
        Engine e_;

        explicit bernoulli( final_type p = final_type( 0.5 ),
                            const seed_type s = seed_type( 0 ) )
            : p_( p ), e_( s )
        {
			assert( p_ >= final_type(0) );
			assert( p_ <= final_type(1) );
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
            return coin_flip_method( P );
        }

    private:
        return_type 
        coin_flip_method( const final_type P )
        {
			if ( e_() < p_ )
                return 1;

            return 0;
        }


    };

}//namespace vg


#endif//_BERNOULLI_HPP_INCLUDED_2I8HJAFLKHJFSDKMNVCLKJNAJIHEIUAO9HWE9U8HYSDFIHJ2



