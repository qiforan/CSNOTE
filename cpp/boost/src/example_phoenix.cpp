#include <boost/phoenix/phoenix.hpp>
#include <vector>
#include <algorithm>


int main()
{
    std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
    using boost::phoenix::placeholders::arg1;
    using boost::phoenix::placeholders::arg2;
    std::cout << std::count_if(v.begin(), v.end(), [](int x ) {return x > 0;});
    return 0;
}