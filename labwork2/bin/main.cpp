#include <iostream>
#include "../lib/number.h"

int main() {
    uint2022_t a = from_string("12345678901111123434676543357456755621115444465432245688977865656665667890");
    uint2022_t b = from_string("98765432111544446543224568897788778821115444465432245688977877979111");
    uint2022_t sum = a + b;
    uint2022_t prod = a * b;
    uint2022_t del = a / b;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "sum = " << sum << std::endl;
    std::cout << "prod = " << prod << std::endl;
    std::cout << "del = " << del << std::endl;

    return 0;
}
