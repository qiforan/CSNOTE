#include <iostream>
using namespace std;
void print() { ; }
template <typename T, typename... Types>
void print(const T& firArg, Types... args) {
  cout << firArg << endl;
  print(args...);
}

int main() {
  print("hello", "world");
  return 0;
}