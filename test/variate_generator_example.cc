#include <vg.hpp>
#include <iostream>

int main()
{
    unsigned long int N = 10;
    vg::variate_generator<int> vg( 0, 10 );
    std::cout << "Uniform in [0,10):\n";
    for ( unsigned long int index = 0; index != N; ++index )
        std::cout << vg() << "\t";
    std::cout << "\n";

    vg::variate_generator<unsigned int, vg::poisson> vg_possion( 3 );
    std::cout << "possion(3):\n";
    for ( unsigned long int index = 0; index != N; ++index )
        std::cout << vg_possion() << "\t";
    std::cout << "\n";

    vg::variate_generator<unsigned int, vg::hypergeometric, vg::mt19937> vg_hypergeometric( 3, 4, 5 );
    std::cout << "hypergeometric(3, 4, 5):\n";
    for ( unsigned long int index = 0; index != N; ++index )
        std::cout << vg_hypergeometric() << "\t";
    std::cout << "\n";

    return 0;
}

