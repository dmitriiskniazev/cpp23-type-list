export module type_list:prepend;

import :core;

template <typename Elem, type_list List>
struct Prepend;

template <typename Elem>
struct Prepend<Elem, Nil> : type_identity<Cons<Elem, Nil>> {};

template <typename Elem, typename Head, type_list Tail>
struct Prepend<Elem, Cons<Head, Tail>>
    : type_identity<Cons<Elem, Cons<Head, Tail>>> {};

export {
    template <typename Elem, type_list List>
    using prepend_t = typename Prepend<Elem, List>::type;
}
