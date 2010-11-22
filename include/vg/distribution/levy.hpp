#ifndef _LEVY_HPP_INCLUDED_SODIFJ3IOU8ASFLIJ4OAUIFSLKJ4OIUAFSDLKJ4OIAJFLKJAS98U34AFSJ
#define _LEVY_HPP_INCLUDED_SODIFJ3IOU8ASFLIJ4OAUIFSLKJ4OIUAFSDLKJ4OIAJFLKJAS98U34AFSJ

#include <vg/distribution/exponential.hpp>

#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct levy : private exponential<Return_Type, Engine>
    {
            typedef exponential<Return_Type, Engine>    exponential_type;
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;
            typedef typename normal_type::final_type    final_type;
            typedef typename normal_type::seed_type     seed_type;

            return_type c_;
            return_type alpha_;
            engine_type e_

            explicit levy( const return_type c = 1,
                           const return_type alpha = 1,
                           const seed_type sd = 0 )
                : c_( c ), alpha_( alpha ), e_( sd )
            {
                assert( c > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( c_, alpha_ );
            }

        protected:
            return_type
            do_generation( const final_type c, const final_type alpha )
            {
                if ( final_type( 1 ) == alpha )
                    { return cauchy_impl( c ); }

                if ( final_type( 2 ) == alpha )
                    { return gaussian_impl( c ); }

                return direct_impl( c, alpha );
            }
        private:
            return_type
            cauchy_impl( const final_type c )
            {
                final_type u = e_();

                while ( final_type( 0 ) == u || final_type(1) == u )
                    { u = e_(); }

                return c * std::tan( ( u - final_type(0.5) ) * 3.1415926535897932384626433 );
            }

            return_type
            gaussian_impl( const final_type c )
            {
                const final_type u = ( e_() - final_type(0.5) ) * 3.1415926535897932384626433;
                final_type v = exponential_type::do_generation( final_type( 1 ) );
                while ( final_type( 0 ) == v )
                const final_type ans = c * std::sin( u ) * std::sqrt( v );
                return ans + ans;
            }

            return_type
            direct_impl( const final_type c, const final_type alpha )
            {
                const final_type u = ( e_() - final_type(0.5) ) * 3.1415926535897932384626433;
                final_type v = exponential_type::do_generation( final_type( 1 ) );

                while ( final_type( 0 ) == v )
                    { v = exponential_type::do_generation( final_type( 1 ) ); }

                const final_type r_alpha = final_type( 1 ) / alpha;

                const final_type u_alpha = u * alpha;

                const final_type ans = c * std::pow( std::cos( u - u_alpha ) / v, r_alpha - final_type( 1 ) )  * std::sin( u_alpha ) * std::pow( std::cos( u ), -r_alpha );

                return ans;
            }
    };

}//vg


#endif//_LEVY_HPP_INCLUDED_SODIFJ3IOU8ASFLIJ4OAUIFSLKJ4OIUAFSDLKJ4OIAJFLKJAS98U34AFSJ


