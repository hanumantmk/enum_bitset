#include <bitset>
#include <type_traits>

#pragma once

namespace enum_bitset {

template <typename T>
constexpr size_t enum_bitset_size(T t) { return 0; }

template <typename T, typename = std::enable_if_t<!!enum_bitset_size(T{})>>
class enum_bitset : private std::bitset<enum_bitset_size(T{})> {
    using Super = std::bitset<enum_bitset_size(T{})>;
    using Underlying = std::underlying_type_t<T>;

    static constexpr Underlying from_enum(T t) {
        return static_cast<Underlying>(t);
    }
public:
    using typename Super::reference;

    constexpr enum_bitset() = default;

    constexpr enum_bitset(T pos) : enum_bitset({pos}) {}

    constexpr enum_bitset(std::initializer_list<T> vals) {
        for (auto v : vals) {
            set(v);
        }
    }

    bool operator==(const enum_bitset& rhs) const {
        return static_cast<const Super&>(*this) == static_cast<const Super&>(rhs);
    };

    bool operator!=(const enum_bitset& rhs) const {
        return static_cast<const Super&>(*this) != static_cast<const Super&>(rhs);
    };

    constexpr bool operator[](T pos) const {
        return Super::operator[](from_enum(pos));
    }

    reference operator[](T pos) {
        return Super::operator[](from_enum(pos));
    }

    bool test(T pos) const {
        return Super::test(from_enum(pos));
    }

    using Super::all;
    using Super::any;
    using Super::none;
    using Super::count;
    using Super::size;

    enum_bitset& operator&=(const enum_bitset& other) {
        static_cast<Super&>(*this) &= static_cast<const Super&>(other);
        return *this;
    }

    enum_bitset& operator|=(const enum_bitset& other) {
        static_cast<Super&>(*this) |= static_cast<const Super&>(other);
        return *this;
    }

    enum_bitset& operator^=(const enum_bitset& other) {
        static_cast<Super&>(*this) ^= static_cast<const Super&>(other);
        return *this;
    }

    enum_bitset operator~() const {
        return enum_bitset(*this).flip();
    }

    enum_bitset& set() noexcept {
        Super::set();
        return *this;
    }

    enum_bitset& set(T pos, bool value = true) {
        Super::set(from_enum(pos), value);
        return *this;
    }

    enum_bitset& reset() noexcept {
        Super::reset();
        return *this;
    }

    enum_bitset& reset(T pos) noexcept {
        Super::reset(from_enum(pos));
        return *this;
    }

    enum_bitset& flip() noexcept {
        Super::flip();
        return *this;
    }

    enum_bitset& flip(T pos) noexcept {
        Super::flip(from_enum(pos));
        return *this;
    }

    friend enum_bitset operator&(const enum_bitset& lhs, const enum_bitset& rhs) noexcept {
        return enum_bitset(lhs) &= rhs;
    }

    friend enum_bitset operator|(const enum_bitset& lhs, const enum_bitset& rhs) noexcept {
        return enum_bitset(lhs) |= rhs;
    }

    friend enum_bitset operator^(const enum_bitset& lhs, const enum_bitset& rhs) noexcept {
        return enum_bitset(lhs) ^= rhs;
    }

    using Super::to_string;
    using Super::to_ulong;
    using Super::to_ullong;
};

namespace operators {

template <typename T>
std::enable_if_t<!!enum_bitset_size(T{}), enum_bitset<T>> operator|(T lhs, T rhs) {
    return enum_bitset<T>(lhs) | enum_bitset<T>(rhs);
}

template <typename T>
std::enable_if_t<!!enum_bitset_size(T{}), enum_bitset<T>> operator&(T lhs, T rhs) {
    return enum_bitset<T>(lhs) & enum_bitset<T>(rhs);
}

template <typename T>
std::enable_if_t<!!enum_bitset_size(T{}), enum_bitset<T>> operator^(T lhs, T rhs) {
    return enum_bitset<T>(lhs) ^ enum_bitset<T>(rhs);
}

} // namespace operators
} // namespace enum_bitset

