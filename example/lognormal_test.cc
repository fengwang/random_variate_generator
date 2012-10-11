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

#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>


using namespace std;

int main()
{
    vg::vg<double, lognormal> vg_(1.0, 2.0);    

    copy( vg_.begin(), vg_.begin()+1000, ostream_iterator<double>(cout, "\n"));

    auto sum = accumulate( vg_.begin(), vg_.begin()+1000, 0 );

    cout << sum << endl;

    return 0;
}

