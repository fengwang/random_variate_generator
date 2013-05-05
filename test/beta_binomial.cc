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
#include <vg.hpp>

#include "test.hpp"
#include <cmath>
#include <vector>
#include <cstddef>

int main()
{
    vg::variate_generator<double, vg::beta_binomial, vg::mt19937> vg_( 100, 0.1, 0.2 );

    std::size_t n = 10000000;
    std::vector<double> x(n);

    std::generate( x.begin(), x.end(), vg_ );

    auto const& mean = []( double n, double a, double b ){ return n * a / ( a+b ); };
    auto const& variance = []( double n, double a, double b ) { return n * a * b * (a+b+n)/((a+b)*(a+b)*(a+b+1)); };
    auto const& skewness = []( double n, double a, double b ) { return ( a+b+n+n)*(b-a)/(a+b+2)*std::sqrt((1+a+b)/(n*a*b*(a+b))); };

    test( x.begin(), x.end(), "beta_binomial with n = 100, alpha = 0.1, beta = 0.2", mean(100, 0.1, 0.2), variance(100, 0.1, 0.2), skewness(100, 0.1, 0.2), -1.5 ); 

    return 0;
}

