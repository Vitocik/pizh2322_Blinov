#include "number.h"
#include <cstring>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>



const int BASE = 1000000000; // 1e9
const int DIGITS = 9;


uint2022_t from_uint(uint32_t i) {
    uint2022_t res;
    res.data[0] = i;
    return res;
}

uint2022_t from_string(const char* buff) {
    std::string str(buff);
    uint2022_t res;

    for (size_t i = 0; i < str.size(); i++) {
        char c = str[i];
        if (c < '0' || c > '9') continue;

        uint2022_t digit = from_uint(c - '0');
        uint2022_t temp = res * from_uint(10);

        // Проверка на переполнение: если temp < res, значит, произошло переполнение
        assert(!(temp < res) && "Переполнение при умножении в from_string");

        temp = temp + digit;

        // Проверка на переполнение после сложения
        assert(!(temp < res) && "Переполнение при добавлении в from_string");

        res = temp;
    }

    return res;
}


uint2022_t operator+(const uint2022_t& a, const uint2022_t& b) {
    uint2022_t res;
    uint64_t carry = 0;
    for (int i = 0; i < uint2022_t::CAPACITY; ++i) {
        uint64_t sum = uint64_t(a.data[i]) + b.data[i] + carry;
        res.data[i] = sum & 0xFFFFFFFF;
        carry = sum >> 32;
    }

    assert(carry == 0 && "Переполнение при сложении");

    return res;
}

uint2022_t operator-(const uint2022_t& a, const uint2022_t& b) {

    uint2022_t res;
    int64_t borrow = 0;
    for (int i = 0; i < uint2022_t::CAPACITY; ++i) {
        int64_t diff = int64_t(a.data[i]) - b.data[i] - borrow;
        if (diff < 0) {
            diff += (1LL << 32);
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        res.data[i] = static_cast<uint32_t>(diff);
    }
    return res;
}

uint2022_t operator*(const uint2022_t& a, const uint2022_t& b) {
    uint2022_t res;
    for (int i = 0; i < uint2022_t::CAPACITY; ++i) {
        uint64_t carry = 0;
        for (int j = 0; j + i < uint2022_t::CAPACITY; ++j) {
            uint64_t mul = uint64_t(a.data[i]) * b.data[j] + res.data[i + j] + carry;
            res.data[i + j] = mul & 0xFFFFFFFF;
            carry = mul >> 32;
        }
        assert(carry == 0 && "Переполнение при умножении");
    }
    return res;
}

bool operator==(const uint2022_t& a, const uint2022_t& b) {
    for (int i = 0; i < uint2022_t::CAPACITY; ++i) {
        if (a.data[i] != b.data[i]) return false;
    }
    return true;
}

bool operator!=(const uint2022_t& a, const uint2022_t& b) {
    return !(a == b);
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    // Выводим число как строку
    uint2022_t temp = value;

    std::ostringstream oss;
    bool first = true;

    while (true) {
        uint64_t remainder = 0;
        bool is_zero = true;
        uint2022_t div_res;

        for (int i = uint2022_t::CAPACITY - 1; i >= 0; --i) {
            uint64_t cur = (remainder << 32) | temp.data[i];
            div_res.data[i] = static_cast<uint32_t>(cur / BASE);
            remainder = cur % BASE;
            if (div_res.data[i] != 0)
                is_zero = false;
        }

        if (first) {
            oss << remainder;
            first = false;
        }
        else {
            oss << std::setw(DIGITS) << std::setfill('0') << remainder;
        }

        if (is_zero) break;

        temp = div_res;
    }

    stream << oss.str();
    return stream;
}

// Деление на целое число
uint2022_t operator/(const uint2022_t& a, const uint2022_t& b) {
    if (b == from_uint(0)) return from_uint(0); // На 0 делить нельзя

    uint2022_t left = from_uint(0), right = a, mid, prod, res;

    while (left <= right) {
        mid = (left + right) / from_uint(2);
        prod = mid * b;
        if (prod == a || prod < a) {
            res = mid;
            left = mid + from_uint(1);
        }
        else {
            right = mid - from_uint(1);
        }
    }
    return res;
}

bool operator<(const uint2022_t& a, const uint2022_t& b) {
    for (int i = uint2022_t::CAPACITY - 1; i >= 0; --i) {
        if (a.data[i] != b.data[i])
            return a.data[i] < b.data[i];
    }
    return false;
}

bool operator<=(const uint2022_t& a, const uint2022_t& b) {
    return (a < b) || (a == b);
}

