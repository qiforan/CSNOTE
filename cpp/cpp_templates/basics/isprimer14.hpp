/**
 * can use most of control structure
 */
constexpr bool isPrime(unsigned int p)
{
	for (unsigned int d = 2; d <= p/2; ++d){
		if(p % d == 0) return false;
	}
	return true;
}