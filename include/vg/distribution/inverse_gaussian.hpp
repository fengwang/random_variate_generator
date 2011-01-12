#ifndef _GAUSSIAN_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3
#define _GAUSSIAN_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3

#include <vg/distribution/normal.hpp>

#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct gaussian : private normal<Return_Type, Engine>
    {
            typedef normal<Return_Type, Engine>         normal_type;
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;
            typedef typename normal_type::final_type    final_type;
            typedef typename normal_type::seed_type     seed_type;

            return_type mu_;
            return_type lambda_;
            engine_type e_;

            explicit gaussian( const return_type mu = 1,
                               const return_type lambda = 1,
                               const seed_type sd = 0 )
                : mu_( mu ), lambda_( lambda ), e_( sd )
            {
                assert( mu > 0 );
                assert( lambda > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( lambda_, mu_ );
            }

        protected:
            return_type
            do_generation( const final_type Lambda, const final_type Mu )
            {
                return michael_schucany_haas_impl( Lambda, Mu );
            }
        private:
            //Luc Devroye (1986). Non-Uniform Random Variate Generation. New York: Springer-Verlag, p. 163.
            return_type
            michael_schucany_haas_impl( const final_type Lambda, const final_type Mu )
            {
                const final_type N = normal_type::do_generation();
                const final_type Y = N * N ;
                const final_type MY = Mu * Y;
                const final_type X = Mu + ( MY - std::sqrt( MY * ( Lambda * final_type( 4 ) + MY ) ) ) * Mu / ( Lambda + Lambda );
                const final_type U = e_();
                const final_type ans = ( Mu >= ( Mu + X ) * U ) ? X : ( Mu * Mu / X );
                return ans;
            }
    };

}//vg


#endif//_GAUSSIAN_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3


