export module type_list:map;

import std;

import :types;
import :type_list;

namespace type_list {

    template <template <typename> typename unary_op, type_list list>
    struct map;

    template <template <typename> typename unary_op>
    struct map<unary_op, nil> : std::type_identity<nil> {};

    template <template <typename> typename unary_op, typename head_type, type_list tail>
    struct map<unary_op, cons<head_type, tail>>
        : std::type_identity<cons<unary_op<head_type>, typename map<unary_op, tail>::type>> {};

    export {
        template <template <typename> typename unary_op, type_list list>
        using map_t = typename map<unary_op, list>::type;
    }

}  // namespace type_list
