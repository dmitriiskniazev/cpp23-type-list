export module type_list:access.front;

import std;

import :core;
import :traits.non_empty;

namespace type_list
{

    template <non_empty list>
    struct front;

    template <typename front_type, type_list tail>
    struct front<cons<front_type, tail>> : std::type_identity<front_type> {};

    export {
        template <non_empty list>
        using front_t = typename front<list>::type;
    }

}  // namespace type_list
