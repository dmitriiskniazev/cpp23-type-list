export module type_list:transform.fold_left;

import std;

import :core;

namespace type_list
{

    template <
        typename init,
        template <typename, typename> typename binary_op,
        type_list list
    >
    struct fold_left;

    template <
        typename init,
        template <typename, typename> typename binary_op
    >
    struct fold_left<init, binary_op, nil>
        : std::type_identity<init> {};

    template <
        typename init,
        template <typename, typename> typename binary_op,
        typename head_type,
        type_list tail
    >
    struct fold_left<init, binary_op, cons<head_type, tail>>
        : fold_left<
              typename binary_op<init, head_type>::type,
              binary_op,
              tail
          > {};

    export {
        template <
            typename init,
            template <typename, typename> typename binary_op,
            type_list list
        >
        using fold_left_t =
            typename fold_left<init, binary_op, list>::type;
    }

}  // namespace type_list
