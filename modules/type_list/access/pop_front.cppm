export module type_list:access.pop_front;

import std;

import :core;
import :traits.non_empty;

namespace type_list {

    template <non_empty list>
    struct pop_front;

    template <typename front_type, type_list tail>
    struct pop_front<cons<front_type, tail>> : std::type_identity<tail> {};

    export {
        template <non_empty list>
        using pop_front_t = typename pop_front<list>::type;
    }

}  // namespace type_list
