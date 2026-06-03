export module type_list:head;

import :core;

template <non_empty_type_list List>
struct Head;

template <typename Head_, type_list Tail>
struct Head<Cons<Head_, Tail>> : type_identity<Head_> {};

export {
    template <non_empty_type_list List>
    using head_t = typename Head<List>::type;
}
