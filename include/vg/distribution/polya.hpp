#ifndef _POLYA_HPP_INCLUDED_SDOIU39ASFD98UY348OAUYSFD98Y34897ASFDOI348OUYAFSDIKH34IOUAFSDOIU349Y8ASFDKLJ
#define _POLYA_HPP_INCLUDED_SDOIU39ASFD98UY348OAUYSFD98Y34897ASFDOI348OUYAFSDIKH34IOUAFSDOIU349Y8ASFDKLJ 

#include <vg/distribution/negative_binomial.hpp>

#include <cassert>
#include <cstddef>
#include <cmath>


namespace vg
{

    template <
                typename Return_Type,
                typename Engine
             >
    struct polya :  private negative_binomial<Return_Type, Engine>
    {
            typedef negative_binomial<Return_Type, Engine>     negative_binomial_type;
            typedef typename Engine::final_type                final_type;
            typedef Return_Type                                return_type;
            typedef Return_Type                                value_type;
            typedef typename Engine::seed_type                 seed_type;
            typedef std::size_t                                size_type;
            typedef Engine                                     engine_type;

            size_type           n_;
            final_type          p_;
            engine_type         e_;

            explicit polya(     size_type n = size_type( 1 ),
                                final_type p = final_type( 0.5 ),
                                const seed_type s = seed_type( 0 ) )
                : n_( n ), p_( p ), e_( s )
            {
                assert( n != size_type( 0 ) );
                assert( p > final_type( 0 ) );
                assert( p < final_type( 1 ) );
            }

            return_type
            operator()()
            {
                return do_generation( n_, p_ );
            }

        protected:
            return_type
            do_generation( const size_type N, const final_type P )
            {
                return direct_impl( N, P );
            }

        private:
            return_type
            direct_impl( const size_type N, const final_type P )
            {
                const final_type ans = negative_binomial_type::do_generation( N, P );
                return ans;
            }
    };

}//namespace vg

#endif//_POLYA_HPP_INCLUDED_SDOIU39ASFD98UY348OAUYSFD98Y34897ASFDOI348OUYAFSDIKH34IOUAFSDOIU349Y8ASFDKLJ

