#include <vg.hpp>
#include <iostream>

int main()
{
    vg::variate_generator<double, vg::beta, vg::mt19937> v{ 0.1, 0.2, 19876238763287ULL };

    for ( unsigned long int i = 0; i != 10; ++i )
        std::cout << v() << "\t";

    std::cout << "\n";

    return 0;
}

