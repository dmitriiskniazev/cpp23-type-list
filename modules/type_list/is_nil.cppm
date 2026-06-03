export module type_list:is_nil;

import :core;

template <type_list List>
struct IsNil;

template <>
struct IsNil<Nil> : true_type {};

template <typename Head, type_list Tail>
struct IsNil<Cons<Head, Tail>> : false_type {};

export {
    template <type_list List>
    inline constexpr bool is_nil_v = IsNil<List>::value;
}
