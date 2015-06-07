#include <vg.hpp>
#include <iostream>

int main()
{
    for ( unsigned long int index = 1; index != 13; ++index )
    {
        vg::variate_generator<double, vg::burr> v{ index, 1.0, 2.0, 3.0 };

        std::cout << "Burr--[" << index << "]:\n";
        for ( unsigned long int i = 0; i != 10; ++i )
            std::cout << v() << "\t";

        std::cout << "\n";
    }

    return 0;
}

