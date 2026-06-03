export module type_list:from_pack;

import :core;

template <typename... Types>
struct FromPack;

template <>
struct FromPack<> : type_identity<Nil> {};

template <typename Head, typename... Tail>
struct FromPack<Head, Tail...>
    : type_identity<Cons<Head, typename FromPack<Tail...>::type>> {};

export {
    template <typename... Types>
    using from_pack_t = typename FromPack<Types...>::type;
}
