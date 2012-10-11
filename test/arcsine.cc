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

#include <vector>
#include <cstddef>

int main()
{
    vg::vg<double, vg::arcsine, vg::mt19937> vg_;    

    std::size_t n = 10000000;
    std::vector<double> x(n);

    std::generate( x.begin(), x.end(), vg_ );

    test( x.begin(), x.end(), "arcsine", 0.5, 0.125, 0, -1.5 ); 
#if 0
    std::cout << "\nTesting arcsine engine with n = " << n << "\n";
    std::cout << "\n|        | Theoretical Value |\tGenerated value\t|\n";
    std::cout << "\n|  Mean  |      0.5          |\t" << vg::mean( x.begin(), x.end() )     << "\t|\n";
    std::cout << "\n|Variance|     0.125         |\t" << vg::variance( x.begin(), x.end() ) << "\t|\n";
    std::cout << "\n|Skewness|       0           |\t" << vg::skewness( x.begin(), x.end() ) << "\t|\n";
    std::cout << "\n|Kurtosis|     -1.5          |\t" << vg::kurtosis( x.begin(), x.end() ) << "\t|\n";
#endif

    return 0;
}

