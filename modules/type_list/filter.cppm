export module type_list:filter;

import :core;

template <template <typename> class Pred, type_list List>
struct Filter;

template <template <typename> class Pred>
struct Filter<Pred, Nil> : type_identity<Nil> {};

template <template <typename> class Pred, typename Head, type_list Tail>
struct Filter<Pred, Cons<Head, Tail>>
    : type_identity<conditional_t<
          Pred<Head>::value,
          Cons<Head, typename Filter<Pred, Tail>::type>,
          typename Filter<Pred, Tail>::type>> {};

export {
    template <template <typename> class Pred, type_list List>
    using filter_t = typename Filter<Pred, List>::type;
}
