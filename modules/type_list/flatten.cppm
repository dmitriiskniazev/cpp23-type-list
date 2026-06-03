export module type_list:flatten;

import :concat;
import :core;

template <type_list List>
struct Flatten;

template <>
struct Flatten<Nil> : type_identity<Nil> {};

template <typename Head, type_list Tail>
    requires(not type_list<Head>)
struct Flatten<Cons<Head, Tail>>
    : type_identity<Cons<Head, typename Flatten<Tail>::type>> {};

template <type_list Inner, type_list Tail>
struct Flatten<Cons<Inner, Tail>>
    : type_identity<
          concat_t<typename Flatten<Inner>::type, typename Flatten<Tail>::type>> {};

export {
    template <type_list List>
    using flatten_t = typename Flatten<List>::type;
}
