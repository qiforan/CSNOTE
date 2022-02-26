#include <iostream>
using namespace std;
void print() { ; }
template <typename T, typename... Types>
void print(const T& firArg, Types... args) {
  cout << firArg << endl;
  print(args...);
}

template<typename T>
void f(T&& val)
{
  std::cout << val << endl;
}

int main() {
  print("hello", "world");
  f(1);
  int a = 2;
  f(2);
  return 0;
}