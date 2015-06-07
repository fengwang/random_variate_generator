#include <vg.hpp>
#include <iostream>

int main()
{
    vg::variate_generator<double, vg::balding_nichols> v{ 0.2, 0.7 };

    for ( unsigned long int i = 0; i != 10; ++i )
        std::cout << v() << "\t";

    std::cout << "\n";

    return 0;
}

