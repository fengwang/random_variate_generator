#include <vg.hpp>
#include <iostream>

int main()
{
    unsigned long int N = 10;
    vg::variate_generator<int> vg( 0, 10 );
    for ( unsigned long int index = 0; index != N; ++index )
        std::cout << vg() << "\t";
    std::cout << "\t";

    return 0;
}

