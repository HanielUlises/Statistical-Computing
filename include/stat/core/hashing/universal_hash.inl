#pragma once

namespace stat::core::hashing {

// Prime selection
template <typename Key>
constexpr std::uint64_t UniversalHash<Key>::prime() {
    // Largest 61-bit prime (Mersenne-likey)
    return 2305843009213693951ULL; // 2^61 - 1
}


// Constructor
template <typename Key>
UniversalHash<Key>::UniversalHash(std::size_t seed) noexcept {
    a_ = static_cast<std::uint64_t>(seed | 1ULL);
    b_ = static_cast<std::uint64_t>(seed >> 1);

    // Reduce into field
    a_ %= prime();
    b_ %= prime();

    if (a_ == 0)
        a_ = 1;
}


// Hash evaluation
template <typename Key>
typename UniversalHash<Key>::result_type
UniversalHash<Key>::operator()(key_type x) const noexcept {

    std::uint64_t v = static_cast<std::uint64_t>(x);

    // Carter–Wegman polynomial hash
    std::uint64_t h =
        (a_ * v + b_) % prime();

    return static_cast<result_type>(h);
}

} // namespace stat::core::hashing
