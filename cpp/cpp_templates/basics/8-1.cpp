#include <iostream>
#include <chrono>
using namespace std::chrono;
constexpr bool isPrime(unsigned long long p)
{
	for (unsigned i = 0; i < p/2; ++i){
		if(p % i == 0) return false;
	}
	return true;
}
int main(int argc, char* argv[])
{
}