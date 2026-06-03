export module type_list:tail;

import :core;

template <non_empty_type_list List>
struct Tail;

template <typename Head, typename Tail_>
struct Tail<Cons<Head, Tail_>> : type_identity<Tail_> {};

export {
    template <non_empty_type_list List>
    using tail_t = typename Tail<List>::type;
}
