export module type_list:construct.push_front;

import std;

import :core;

namespace type_list
{

    template <typename type, type_list list>
    struct push_front;

    template <typename type>
    struct push_front<type, nil>
        : std::type_identity<cons<type, nil>> {};

    template <
        typename type,
        typename front_type,
        type_list tail
    >
    struct push_front<type, cons<front_type, tail>>
        : std::type_identity<
              cons<type, cons<front_type, tail>>
          > {};

    export {
        template <typename type, type_list list>
        using push_front_t =
            typename push_front<type, list>::type;
    }

}  // namespace type_list
