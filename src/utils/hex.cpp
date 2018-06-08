#include "hex.hpp"

bool Hex::InRange(char x, char a, char b) {
    return x >= a && x <= b;
}

int Hex::GetBits(char x) {
    if (InRange((char) (x & (~0x20)), 'A', 'F')) {
        return (x & (~0x20)) - 'A' + 0xa;
    } else if (InRange(x, '0', '9')) {
        return x - '0';
    }

    return 0;
}

int Hex::GetBytes(const char* x) {
    return GetBits(x[0]) << 4 | GetBits(x[1]);
}
