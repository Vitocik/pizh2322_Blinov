#include <iostream>
#include "../lib/number.h"

int main() {
    uint2022_t a = from_string("12345678901234567890");
    uint2022_t b = from_string("987654321");
    uint2022_t sum = a + b;
    uint2022_t prod = a * b;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "sum = " << sum << std::endl;
    std::cout << "prod = " << prod << std::endl;

    return 0;
}