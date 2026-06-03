export module type_list:fold_right;

import :core;

template <typename State, template <typename, typename> class F, type_list List>
struct FoldRight;

template <typename State, template <typename, typename> class F>
struct FoldRight<State, F, Nil> : type_identity<State> {};

template <typename State, template <typename, typename> class F, typename Head, type_list Tail>
struct FoldRight<State, F, Cons<Head, Tail>>
    : type_identity<typename F<Head, typename FoldRight<State, F, Tail>::type>::type> {};

export {
    template <typename State, template <typename, typename> class F, type_list List>
    using fold_right_t = typename FoldRight<State, F, List>::type;
}
