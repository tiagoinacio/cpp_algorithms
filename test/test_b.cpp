#include <cpp_algorithms/test_header.hpp>

using namespace cpp_algorithms;

int main() {
  A a{0, 1};

  if (foo(a) == 1) {
    return 0;
  } else {
    return 1;
  }
}
