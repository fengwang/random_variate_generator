#include <vg.hpp>
#include <iostream>

int main()
{
    vg::variate_generator<int, vg::beta_binomial, vg::linear_congruential> v{ 10, 0.4, 0.5, 98187638263287932ULL };

    for ( unsigned long int i = 0; i != 10; ++i )
        std::cout << v() << "\t";

    std::cout << "\n";

    return 0;
}

