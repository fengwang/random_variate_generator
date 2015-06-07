#include <vg.hpp>

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
    char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    //char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()_+\\|[]{}'\";:/?>.<,";
    vg::variate_generator<unsigned long> v{ 0UL, sizeof(chars)/sizeof(char) };
    unsigned long const password_length = std::max( v(), 10UL );
    std::vector<char> password( password_length );
    std::generate( password.begin(), password.end(), [&](){ return chars[v()]; } );
    std::copy( password.begin(), password.end(), std::ostream_iterator<char>( std::cout, "" ) );
    std::cout << "\n";

    return 0;
}

