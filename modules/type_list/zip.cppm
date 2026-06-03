export module type_list:zip;

import :core;

template <type_list Lhs, type_list Rhs>
struct Zip;

template <>
struct Zip<Nil, Nil> : type_identity<Nil> {};

template <type_list Rhs>
struct Zip<Nil, Rhs> : type_identity<Nil> {};

template <type_list Lhs>
struct Zip<Lhs, Nil> : type_identity<Nil> {};

template <typename LHead, type_list LTail, typename RHead, type_list RTail>
struct Zip<Cons<LHead, LTail>, Cons<RHead, RTail>>
    : type_identity<Cons<pair<LHead, RHead>, typename Zip<LTail, RTail>::type>> {};

export {
    template <type_list Lhs, type_list Rhs>
    using zip_t = typename Zip<Lhs, Rhs>::type;
}
