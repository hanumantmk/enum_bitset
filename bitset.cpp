#include "enum_bitset.hpp"

#include <iostream>

enum class Bits : uint32_t {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
};

constexpr size_t enum_bitset_size(Bits) { return static_cast<size_t>(Bits::G) + 1; }
using namespace enum_bitset::operators;

int main() {
    enum_bitset::enum_bitset<Bits> myBits;

    myBits[Bits::B] = true;
    std::cout << "A: " << myBits.test(Bits::A) << "\n";
    std::cout << "B: " << myBits.test(Bits::B) << "\n";
    std::cout << "A|C: " << (Bits::A | Bits::C).to_string() << "\n";
    std::cout << "(E|F|G)&(F|G): "
              << ((Bits::E | Bits::F | Bits::G) & (Bits::F | Bits::G)).to_string() << "\n";
}
