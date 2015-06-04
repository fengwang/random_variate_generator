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
#ifndef _KURTOSIS_HPP_INCLUDED_SDOASFO9Y839Y8AFUHFASDO9Y8WE9Y8AFSIOUH4398YAFKLJB
#define _KURTOSIS_HPP_INCLUDED_SDOASFO9Y839Y8AFUHFASDO9Y8WE9Y8AFSIOUH4398YAFKLJB

#include <vg/utility/mean.hpp>

#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>

namespace vg 
{
#if 0
    In probability theory and statistics, kurtosis (from the Greek word κυρτός, 
    kyrtos or kurtos, meaning bulging) is any measure of the "peakedness" of the 
    probability distribution of a real-valued random variable. In a similar 
    way to the concept of skewness, kurtosis is a descriptor of the shape of a 
    probability distribution and, just as for skewness, there are different ways 
    of quantifying it for a theoretical distribution and corresponding ways of 
    estimating it from a sample from a population.
                                    --http://en.wikipedia.org/wiki/Excess_kurtosis
#endif
    template< typename Input_Iterator >
    typename std::iterator_traits<Input_Iterator>::value_type 
    kurtosis( Input_Iterator first, Input_Iterator last ) noexcept
    {
        typedef typename std::iterator_traits<Input_Iterator>::value_type value_type;
        std::vector<value_type> x2( first, last );
        std::for_each( x2.begin(), x2.end(), []( value_type& v ) { v *= v; } );
        std::vector<value_type> x4 = x2;
        std::for_each( x4.begin(), x4.end(), []( value_type& v ) { v *= v; } );
        value_type const mu_2 = mean( x2.begin(), x2.end() );
        value_type const mu_4 = mean( x4.begin(), x4.end() );
        return mu_4 / (mu_2*mu_2) - value_type(3);
    }

}//namespace vg

#endif//_KURTOSIS_HPP_INCLUDED_SDOASFO9Y839Y8AFUHFASDO9Y8WE9Y8AFSIOUH4398YAFKLJB

