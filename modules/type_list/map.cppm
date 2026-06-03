export module type_list:map;

import :core;

template <template <typename> typename Op, type_list List>
struct Map;

template <template <typename> typename Op>
struct Map<Op, Nil> : type_identity<Nil> {};

template <template <typename> typename Op, typename Head, type_list Tail>
struct Map<Op, Cons<Head, Tail>>
    : type_identity<Cons<Op<Head>, typename Map<Op, Tail>::type>> {};

export {
    template <template <typename> typename Op, type_list List>
    using map_t = typename Map<Op, List>::type;
}
