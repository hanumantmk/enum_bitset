#include "enum_bitset.hpp"

#include <iostream>

enum class Bits : uint32_t {
    A,
    B,
    C,
};

constexpr std::true_type is_enum_bitset(Bits) { return {}; }
using namespace enum_bitset::operators;

int main() {
    enum_bitset::enum_bitset<Bits> myBits;

    myBits[Bits::B] = 1;
    std::cout << "A: " << myBits.test(Bits::A) << "\n";
    std::cout << "B: " << myBits.test(Bits::B) << "\n";
    std::cout << "C: " << (Bits::A | Bits::C).to_string() << "\n";
}
