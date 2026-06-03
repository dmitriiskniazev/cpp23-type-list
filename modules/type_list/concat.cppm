export module type_list:concat;

import :core;

template <type_list Lhs, type_list Rhs>
struct Concat;

template <type_list Rhs>
struct Concat<Nil, Rhs> : type_identity<Rhs> {};

template <typename Head, type_list Tail, type_list Rhs>
struct Concat<Cons<Head, Tail>, Rhs>
    : type_identity<Cons<Head, typename Concat<Tail, Rhs>::type>> {};

export {
    template <type_list Lhs, type_list Rhs>
    using concat_t = typename Concat<Lhs, Rhs>::type;
}
