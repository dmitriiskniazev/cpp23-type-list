export module type_list:transform.filter;

import std;

import :core;

namespace type_list {

    template <template <typename> typename unary_op, type_list list>
    struct filter;

    template <template <typename> typename unary_op>
    struct filter<unary_op, nil> : std::type_identity<nil> {};

    template <template <typename> typename unary_op, typename head_type, type_list tail>
    struct filter<unary_op, cons<head_type, tail>> : std::type_identity<std::conditional_t<
                                                         unary_op<head_type>::value,
                                                         cons<head_type, typename filter<unary_op, tail>::type>,
                                                         typename filter<unary_op, tail>::type
                                                     >> {};

    export {
        template <template <typename> typename unary_op, type_list list>
        using filter_t = typename filter<unary_op, list>::type;
    }

}  // namespace type_list
