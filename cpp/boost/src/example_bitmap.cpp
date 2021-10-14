#include <boost/bimap.hpp>
#include <boost/function.hpp>
#include <iostream>
using namespace boost;

typedef boost::function<void(void)> f;

void fun() { std::cout << "fun" << std::endl; }

typedef void (*fp)();

int main() {
  using boost::bimap;
  bimap<std::string, int> b;
  b.insert({"cat", 1});
  b.insert({"dog", 2});
  std::cout << b.left.count("dog") << std::endl;
  fp fp0 = fun;
  f f1 = fp0;
  f1();
  return 0;
}
