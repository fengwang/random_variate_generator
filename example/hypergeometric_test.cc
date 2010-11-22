#include <vg.hpp>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace vg;
using namespace std;

int main()
{
    variate_generator<int, vg::hypergeometric, vg::mt19937> vg(200, 200, 200);    

    copy( vg.begin(), vg.begin()+1000, ostream_iterator<int>(cout, "\n"));

    auto sum = accumulate( vg.begin(), vg.begin()+1000, 0 );

    cout << sum << endl;

    return 0;
}
