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

#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace vg;
using namespace std;

int main()
{
    variate_generator<unsigned long long, vg::uniform> vg_key( 0, -1 );
    variate_generator<char, vg::uniform> vg_char('!', '~', vg_key()); //passwd    
    variate_generator<char, vg::uniform> vg_dig('0', '9', vg_key()); //id 
    variate_generator<char, vg::uniform> vg_az('a', 'z', vg_key()); //id A-Za-z
    variate_generator<int, vg::uniform> vg_int( 13, 31, vg_key() );  //length of passwd
    variate_generator<int, vg::uniform> vg_id( 3, 7, vg_key() );  //length of id 1 and 2

    const int l_pwd = vg_int();
    const int l_az = vg_id();
    const int l_dig = vg_id();

    std::cout << "Generated (id ---- passwd) is:\n"; 
    std::copy( vg_az.begin(), vg_az.begin()+l_az, ostream_iterator<char>(std::cout, ""));
    std::copy( vg_dig.begin(), vg_dig.begin()+l_dig, ostream_iterator<char>(std::cout, ""));
    std::cout << " ---- ";
    std::copy( vg_char.begin(), vg_char.begin()+l_pwd, ostream_iterator<char>(std::cout, ""));
    std::cout << "\n";

    return 0;
}

