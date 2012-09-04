/*
vg -- random variate generator library 
Copyright (C) 2010-2012  Feng Wang (feng.wang@uni-ulm.de) 

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by 
the Free Software Foundation, either version 3 of the License, or 
(at your option) any later version. 

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU General Public License for more details. 

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _PEARSON_HPP_INCLUDED_SODIU498SFKL48USDFLKJFJSDSLKAJDLSKJADSLKJSLKJSAFOIDUJ498SFD97849874987987ERIOUYDFSLKJFLKJAL
#define _PEARSON_HPP_INCLUDED_SODIU498SFKL48USDFLKJFJSDSLKAJDLSKJADSLKJSLKJSAFOIDUJ498SFD97849874987987ERIOUYDFSLKJFLKJAL

#include <vg/distribution/exponential.hpp>
#include <vg/distribution/gamma.hpp>
#include <vg/distribution/normal.hpp>
#include <vg/distribution/beta.hpp>
#include <vg/utility/singleton.hpp>

#include <cassert>
#include <cstddef>
#include <cmath>


namespace vg
{

    template < typename Return_Type, typename Engine >
    struct pearson :  private proxy<gamma<typename Engine::final_type, Engine>, 1 >,
                      private proxy<exponential<typename Engine::final_type, Engine>, 2 >,
                      private proxy<normal<typename Engine::final_type, Engine>, 3 >,
                      private proxy<beta<typename Engine::final_type, Engine>, 4 >
    {
            typedef proxy<gamma<typename Engine::final_type, Engine>, 1 >            gamma_type;
            typedef proxy<exponential<typename Engine::final_type, Engine>, 2 >      exponential_type;
            typedef proxy<normal<typename Engine::final_type, Engine>, 3 >           normal_type;
            typedef proxy<beta<typename Engine::final_type, Engine>, 4 >             beta_type;

            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef Return_Type                     value_type;
            typedef typename Engine::seed_type      seed_type;
            typedef std::size_t                     size_type;
            typedef Engine                          engine_type;

            size_type           n_;
            final_type          a_;
            final_type          b_;
            final_type          c_;
            final_type          d_;
            engine_type&        e_;

            explicit pearson( size_type  n = size_type(1),
                              final_type a = final_type(1),
                              final_type b = final_type(1),
                              final_type c = final_type(1),
                              final_type d = final_type(1),
                              const seed_type s = seed_type( 0 ) )
                : n_(n), a_(a), b_(b), c_(c), d_(d), e_( singleton<engine_type>::instance() ) 
            {
                assert( n > 0 );
                assert( n < 13);
                e_.reset_seed( s );
            }

            return_type
            operator()()
            {
                return do_generation( n_, a_, b_, c_, d_ );
            }

        protected:
            return_type
            do_generation( const size_type N, 
                           const final_type A, 
                           const final_type B, 
                           const final_type C, 
                           const final_type D )
            {
                return direct_impl( N, A, B, C, D );
            }

        private:
            return_type
            direct_impl(   const size_type N, 
                           const final_type A, 
                           const final_type B, 
                           const final_type C, 
                           const final_type D )
            {
                //Luc Devroye, ¡°Non-Uniform Random Variate Generation¡±, (Springer-
                //Verlag, New York, 1986), Chapter IX, page 480.
                //http://cgm.cs.mcgill.ca/~luc/rnbookindex.html
                typedef std::function<final_type(final_type, final_type, final_type, final_type)> function_type;
                static const function_type impl_function_list[12] =
                {
                    // pearson I
                    [](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( a > final_type(0) );
                        assert( b > final_type(-1) );
                        assert( c > final_type(0) );
                        assert( d > final_type(-1) );
                        const final_type X = gamma_type::do_generation(b+final_type(1));
                        const final_type Y = gamma_type::do_generation(d+final_type(1));
                        const final_type ans = ( a + c ) * X / ( X + Y ) - a;
                        return ans;
                    },
                    //pearson II
                    [](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( a > final_type(0) );
                        assert( b > final_type(-1) );
                        const final_type X = gamma_type::do_generation(b+final_type(1));
                        const final_type Y = gamma_type::do_generation(b+final_type(1));
                        const final_type ans = a * ( X - Y ) / ( X - Y );
                        return ans;
                    },
                    //pearson III
                    [](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( a * b > final_type(-1) );
                        assert( b > 0 );
                        const final_type X = gamma_type::do_generation(a*b+final_type(1));
                        const final_type ans = X / b - a;
                        return ans;
                    },
                    //pearson IV
                    [](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( a > 0 );
                        assert( b > final_type(0.5) );
                        const final_type X = gamma_type::do_generation(a);
                        const final_type Y = gamma_type::do_generation(b);
                        const final_type ans = X / Y;
                        return ans;
                    },
                    //pearson V
                    [](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( b > final_type(1) );
                        assert( c > 0 );
                        const final_type X = gamma_type::do_generation(b-final_type(1));
                        const final_type ans = final_type(1) / ( c * X );
                        return ans;
                    },
                    //pearson VI
                    [](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( c > b + final_type(1) );
                        assert( c > 0 );
                        assert( a > 0 );
                        const final_type X = gamma_type::do_generation(c-b-final_type(1));
                        const final_type Y = gamma_type::do_generation(b+final_type(1));
                        const final_type ans = a + a * Y / X;
                        return ans;
                    },
                    //pearson VII
                    [](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( b > final_type(0.5) );
                        assert( a > 0 );
                        const final_type N = normal_type::do_generation();
                        const final_type X = gamma_type::do_generation(b-final_type(0.5));
                        const final_type ans = N / std::sqrt( X / final_type(2) );
                        return ans;
                    },
                    //pearson VIII
                    [this](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( b >= 0 );
                        assert( b <= final_type(1) );
                        assert( a > 0 );
                        const final_type U = ((*this).e_)();
                        const final_type ans = a * (std::pow(U, -final_type(1)/(b-final_type(1))) - final_type(1));
                        return ans;
                    },
                    //pearson IX
                    [this](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( b > 0 );
                        assert( a > 0 );
                        const final_type U = ((*this).e_)();
                        const final_type ans = a * (std::pow(U, final_type(1)/(b+final_type(1))) - final_type(1));
                        return ans;
                    },
                    //pearson X
                    [](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( a > 0 );
                        const final_type E = exponential_type::do_generation(final_type(1));
                        const final_type ans = a * E;
                        return ans;
                    },
                    //pearson XI
                    [this](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( a > 0 );
                        assert( b > final_type(1) );
                        const final_type U = ((*this).e_)();
                        const final_type ans = a * std::pow(U, -final_type(1)/(b-final_type(1)));
                        return ans;
                    },
                    //pearson XII
                    [](final_type a, final_type b, final_type c, final_type d ) -> final_type 
                    {
                        assert( a > b );
                        assert( b > 0 );
                        assert( c >= 0 );
                        assert( c < final_type(1) );
                        const final_type X = beta_type::do_generation( c+final_type(1), final_type(1)-c );
                        const final_type ans = (a+b)*X -a;
                        return ans;
                    }
                };
                return impl_function_list[N-1]( A, B, C, D );
            }
    };

}//namespace vg

#endif//_PEARSON_HPP_INCLUDED_SODIU498SFKL48USDFLKJFJSDSLKAJDLSKJADSLKJSLKJSAFOIDUJ498SFD97849874987987ERIOUYDFSLKJFLKJAL

