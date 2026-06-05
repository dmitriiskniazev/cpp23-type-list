export module type_list:construct.push_back;

import std;

import :core;

namespace type_list {

    template <type_list list, typename type>
    struct push_back;

    template <typename type>
    struct push_back<nil, type> : std::type_identity<cons<type, nil>> {};

    template <typename front_type, type_list tail, typename type>
    struct push_back<cons<front_type, tail>, type>
        : std::type_identity<cons<front_type, typename push_back<tail, type>::type>> {};

    export {
        template <type_list list, typename type>
        using push_back_t = typename push_back<list, type>::type;
    }

}  // namespace type_list
