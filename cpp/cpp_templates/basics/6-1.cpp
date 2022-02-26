#include <iostream>

template <typename T>
void
foo(){
	typename std::enable_if<sizeof(T) >= 2, T>::type x = 1;
	std::cout << typeid(x).name() << std::endl;
}

int main(){ 
	foo<int>();
	foo<char>();
	return 0;
}