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
#ifndef _RADEMACHER_HPP_INCLUDED_DSFPONIASFD3HAFKLJNASFDKLJH39OHAFLSDKJHSDAFLJKH
#define _RADEMACHER_HPP_INCLUDED_DSFPONIASFD3HAFKLJNASFDKLJH39OHAFLSDKJHSDAFLJKH 

#include <vg/distribution/bernoulli.hpp>
#include <vg/utility/singleton.hpp>

#include <cassert>

namespace vg
{

    template < typename Return_Type, typename Engine >
    struct rademacher : private bernoulli<Return_Type, Engine>
    {
            typedef bernoulli<Return_Type, Engine>          bernoulli_type;
            typedef Return_Type                             return_type;
            typedef Engine                                  engine_type;
            typedef typename bernoulli_type::final_type     final_type;
            typedef typename bernoulli_type::seed_type      seed_type;

            engine_type&    e_;

            explicit rademacher( const seed_type sd = 0 ) : e_( singleton<engine_type>::instance() )
            {
                e_.reset_seed( sd );
            }

            /*
                 Testing [bernoulli] distribution with n = 10000000
                 |        |              Theory          |               Pseudo          |
                 |  Mean  |      0.00000000000000        |       0.000145200000000000    |
                 |Variance|      1.00000000000000        |       0.999999978937111       |
                 |Skewness|      0.00000000000000        |       -0.000290400003026988   |
             */

            return_type operator()() const 
            {
                return do_generation();
            }

        protected:
            return_type do_generation() const
            {
                return rademacher_direct_impl();
            }

        private:
            return_type rademacher_direct_impl() const
            {
                if ( bernoulli_type::do_generation(final_type(0.5)) )
                    return 1;
                return -1;
            }
    };

}//vg

#endif//_RADEMACHER_HPP_INCLUDED_DSFPONIASFD3HAFKLJNASFDKLJH39OHAFLSDKJHSDAFLJKH 

