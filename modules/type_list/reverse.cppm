export module type_list:reverse;

import :append;
import :core;

template <type_list List>
struct Reverse;

template <>
struct Reverse<Nil> : type_identity<Nil> {};

template <typename Head, type_list Tail>
struct Reverse<Cons<Head, Tail>>
    : type_identity<append_t<typename Reverse<Tail>::type, Head>> {};

export {
    template <type_list List>
    using reverse_t = typename Reverse<List>::type;
}
