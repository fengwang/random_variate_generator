#ifndef _LAPLACE_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK
#define _LAPLACE_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK

#include <cmath>


namespace vg
{

    template <   typename Return_Type,
				 typename Engine
             >
    struct laplace
    {
        typedef typename Engine::final_type     final_type;
        typedef Return_Type                     return_type;
        typedef typename Engine::seed_type      seed_type;
        typedef Engine                          engine_type;

        return_type a_;
        engine_type e_;

        explicit laplace( const seed_type sd = 0, const return_type a = 1 ) 
            : a_(a), e_( sd )
        {}
        
        return_type
        operator ()()
        {
            return do_generation( a );
        }

    protected:
        return_type 
        do_generation( a )
        {
        }

    private:
        return_type
        direct_invertion_method( const return_type a )
        {
            for ( ;; )
            {
                const final_type u = e_() * return_type(2) - return_type(1);
                if ( return_type(0) == u )
                    continue;
                if ( u < 0 )
                    return a * std::log(-u);
                return - a * std::log(u);
            }    
        }
    };


}//namespace vg




#endif//_LAPLACE_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK



