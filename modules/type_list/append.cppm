export module type_list:append;

import :core;

template <type_list List, typename Elem>
struct Append;

template <typename Elem>
struct Append<Nil, Elem> : type_identity<Cons<Elem, Nil>> {};

template <typename Head, type_list Tail, typename Elem>
struct Append<Cons<Head, Tail>, Elem>
    : type_identity<Cons<Head, typename Append<Tail, Elem>::type>> {};

export {
    template <type_list List, typename Elem>
    using append_t = typename Append<List, Elem>::type;
}
