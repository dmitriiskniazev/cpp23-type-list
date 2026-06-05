export module type_list:transform.fold_right;

import std;

import :core;

namespace type_list {

    template <typename init, template <typename, typename> typename binary_op, type_list list>
    struct fold_right;

    template <typename init, template <typename, typename> typename binary_op>
    struct fold_right<init, binary_op, nil> : std::type_identity<init> {};

    template <typename init, template <typename, typename> typename binary_op, typename head_type, type_list tail>
    struct fold_right<init, binary_op, cons<head_type, tail>>
        : std::type_identity<typename binary_op<head_type, typename fold_right<init, binary_op, tail>::type>::type> {};

    export {
        template <typename init, template <typename, typename> typename binary_op, type_list list>
        using fold_right_t = typename fold_right<init, binary_op, list>::type;
    }

}  // namespace type_list
