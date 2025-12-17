#pragma once

namespace stat::core::hashing {

namespace detail {

template <typename H, typename Tuple, std::size_t... Is>
std::size_t hash_tuple_impl(const H& h,
                            const Tuple& t,
                            std::size_t seed,
                            std::index_sequence<Is...>) noexcept {
    std::size_t result = seed;
    ((result = hash_combine(h, result, std::get<Is>(t))), ...);
    return result;
}

} // namespace detail

template <typename H, typename... Ts>
requires (Hash<H, Ts> && ...)
std::size_t hash_tuple(const H& h,
                       const std::tuple<Ts...>& t,
                       std::size_t seed) noexcept {
    return detail::hash_tuple_impl(
        h, t, seed, std::index_sequence_for<Ts...>{});
}

} // namespace stat::core::hashing
