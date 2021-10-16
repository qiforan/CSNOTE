#include <iostream>
using namespace std;

void outOfMemory()
{
    std::cout << "Unable to mem\n";
    std::abort();
}

int main()
{
    std::set_new_handler(outOfMemory);
    while(true)
    int* p = new int[100000000L];
    return 0;
}