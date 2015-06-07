#include <vg.hpp>
#include <iostream>

int main()
{
    vg::variate_generator<int, vg::binomial> v{ 10, 0.4 };

    for ( unsigned long int i = 0; i != 10; ++i )
        std::cout << v() << "\t";

    std::cout << "\n";

    return 0;
}

