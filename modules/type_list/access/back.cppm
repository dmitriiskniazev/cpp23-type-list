export module type_list:access.back;

import std;

import :core;
import :traits.non_empty;

namespace type_list
{

    template <non_empty list>
    struct back;

    template <typename front_type>
    struct back<cons<front_type, nil>> : std::type_identity<front_type> {};

    template <typename front_type, non_empty tail>
    struct back<cons<front_type, tail>> : back<tail> {};

    export {
        template <non_empty list>
        using back_t = typename back<list>::type;
    }

}  // namespace type_list
