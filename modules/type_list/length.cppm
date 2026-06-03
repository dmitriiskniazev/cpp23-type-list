export module type_list:length;

import :core;

template <type_list List>
struct Length;

template <>
struct Length<Nil> : integral_constant<size_t, 0> {};

template <typename Head, type_list Tail>
struct Length<Cons<Head, Tail>>
    : integral_constant<size_t, 1 + Length<Tail>::value> {};

export {
    template <type_list List>
    inline constexpr size_t length_v = Length<List>::value;
}
