export module type_list:fold_left;

import :core;

template <typename State, template <typename, typename> class F, type_list List>
struct FoldLeft;

template <typename State, template <typename, typename> class F>
struct FoldLeft<State, F, Nil> : type_identity<State> {};

template <typename State, template <typename, typename> class F, typename Head, type_list Tail>
struct FoldLeft<State, F, Cons<Head, Tail>>
    : FoldLeft<typename F<State, Head>::type, F, Tail> {};

export {
    template <typename State, template <typename, typename> class F, type_list List>
    using fold_left_t = typename FoldLeft<State, F, List>::type;
}
