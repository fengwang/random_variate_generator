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
#ifndef _VARIANCE_HPP_INCLUDED_FSDOJ34Y89ASFKLJNASDSUH43OUISHDFKLJAFKLJAHSFILJHS
#define _VARIANCE_HPP_INCLUDED_FSDOJ34Y89ASFKLJNASDSUH43OUISHDFKLJAFKLJAHSFILJHS

#include <vg/utility/mean.hpp>

#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>

namespace vg 
{

    template< typename Input_Iterator >
    typename std::iterator_traits<Input_Iterator>::value_type 
    variance( Input_Iterator first, Input_Iterator last ) noexcept
    {
        typedef typename std::iterator_traits<Input_Iterator>::value_type value_type;
        value_type const mu = mean( first, last );
        value_type const n = std::distance( first, last );
        std::vector<value_type> arr( first, last );
        std::for_each( arr.begin(), arr.end(), [mu]( value_type& v ) { v -= mu; } );
        return std::inner_product( arr.begin(), arr.end(), arr.begin(), value_type() ) / n;
    }

}//namespace vg

#endif//_VARIANCE_HPP_INCLUDED_FSDOJ34Y89ASFKLJNASDSUH43OUISHDFKLJAFKLJAHSFILJHS

