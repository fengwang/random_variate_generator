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
#ifndef _SKEWNESS_HPP_INCLUDED_SDOASOSFDPOIHJ498YUASFKLJH439YAFLKHFASYUH498Y98YA
#define _SKEWNESS_HPP_INCLUDED_SDOASOSFDPOIHJ498YUASFKLJH439YAFLKHFASYUH498Y98YA

#include <vg/utility/mean.hpp>
#include <vg/utility/variance.hpp>

#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>
#include <cmath>

namespace vg 
{
    #if 0
    In probability theory and statistics, skewness is a measure of the asymmetry of 
    the probability distribution of a real-valued random variable. The skewness value 
    can be positive or negative, or even undefined. Qualitatively, a negative skew 
    indicates that the tail on the left side of the probability density function is 
    longer than the right side and the bulk of the values (possibly including the 
    median) lie to the right of the mean. A positive skew indicates that the tail on 
    the right side is longer than the left side and the bulk of the values lie to the 
    left of the mean. A zero value indicates that the values are relatively evenly 
    distributed on both sides of the mean, typically (but not necessarily) implying a 
    symmetric distribution.
                                                --http://en.wikipedia.org/wiki/Skewness
    #endif
    template< typename Input_Iterator >
    typename std::iterator_traits<Input_Iterator>::value_type 
    skewness( Input_Iterator first, Input_Iterator last ) noexcept
    {
        typedef typename std::iterator_traits<Input_Iterator>::value_type value_type;
        value_type const mu = mean( first, last );
        value_type const va = std::sqrt(variance( first, last ));
        value_type const n = std::distance( first, last );
        std::vector<value_type> arr( first, last );
        std::for_each( arr.begin(), arr.end(), [mu, va]( value_type& v ) { v -= mu; v /= va; v *= v*v; } );
        return std::accumulate( arr.begin(), arr.end(), value_type() ) / n;
    }

}//namespace vg

#endif//_SKEWNESS_HPP_INCLUDED_SDOASOSFDPOIHJ498YUASFKLJH439YAFLKHFASYUH498Y98YA

