// Escape
// UCF HSPT Online 2019
// Brett Fazio

#include <iostream>

int main() {
  int cases, a, b, c, i;

  std::cin >> cases;

  for (i = 0; i < cases; i++) {
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    // Cube each of the numbers.
    a = a*a*a;
    b = b*b*b;
    c = c*c*c;

    // Output the sum and a blank line.
    std::cout << a + b + c << std::endl;
  }

  return 0;
}
