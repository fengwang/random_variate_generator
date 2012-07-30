/*
vg -- random variate generator library 
Copyright (C) 2010-2011  Feng Wang (wanng.fenng@gmail.com) 

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

#include <cmath>
#include <map>
#include <iostream>

int main()
{
    //generate double gaussian random numbers with argument (0,4), i.e. N(0,4)
    //using mt19937 as uniform random generator engine
    vg::variate_generator<double, vg::gaussian, vg::mt19937> vg(0, 4);    
    std::map< int, int > sample;

    //generate 500 gaussian numbers and store it in a map
    for ( auto i = vg.begin(); i != vg.begin()+500; ++i )
        sample[std::round(*i)]++;

    //show the number generated
    for ( auto i = sample.begin(); i != sample.end(); ++i )
    {
        std::cout << (*i).first << "\t";
        for ( auto j = 0; j < (*i).second; ++j )
            std::cout << "*";
        std::cout << "\n";
    }

    return 0;
}

