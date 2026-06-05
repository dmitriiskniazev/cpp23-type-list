export module type_list:access.pop_back;

import std;

import :core;
import :traits.non_empty;

namespace type_list
{

    template <non_empty list>
    struct pop_back;

    template <typename front_type>
    struct pop_back<cons<front_type, nil>> : std::type_identity<nil> {};

    template <typename front_type, non_empty tail>
    struct pop_back<cons<front_type, tail>> : std::type_identity<cons<front_type, typename pop_back<tail>::type>> {};

    export {
        template <non_empty list>
        using pop_back_t = typename pop_back<list>::type;
    }

}  // namespace type_list
