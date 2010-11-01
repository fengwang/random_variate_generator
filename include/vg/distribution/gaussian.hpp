#ifndef _GAUSSIAN_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3
#define _GAUSSIAN_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3

#include "normal.hpp"

#include <cassert>

namespace vg
{

    template <   typename Return_Type,
				 typename Engine
             >
    struct gaussian : private normal<Return_Type, Engine>
    {
        typedef Return_Type                         return_type;
        typedef Engine                              engine_type;

        typedef normal<return_type, engine_type>    normal_type;

        typedef typename normal_type::final_type    final_type;
        typedef typename normal_type::seed_type     seed_type;

        return_type mean_;
        return_type variance_;
        normal_type n_;

        explicit gaussian(  const return_type mean = 0,
                            const return_type variance = 1,
                            const seed_type sd = 0 )
            : mean_(mean), variance_( variance ), n_( sd )
        {
            assert( variance > 0 );
        }

        return_type
        operator ()()
        {
            return do_generation( variance_, mean_ );
        }

    protected:
        return_type 
        do_generation( const final_type Variance, const final_type Mean )
        {
            return gaussian_direct_impl( Variance, Mean );
        }
    private:
        return_type
        gaussian_direct_impl( const final_type Variance, const final_type Mean )
        {
            const final_type ans =  normal<Return_Type, Engine>::do_generation() * Variance + Mean;
            //const final_type ans =  normal<Return_Type, Engine>::kinderman_monahan_method() * Variance + Mean;
            return static_cast<return_type>( ans );
        }
    };

}//vg


#endif//_GAUSSIAN_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3


