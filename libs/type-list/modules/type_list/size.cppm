export module type_list:size;

import std;

import :types;
import :type_list;

namespace type_list {

    template <type_list list>
    struct size;

    template <>
    struct size<nil> : std::integral_constant<std::size_t, 0> {};

    template <typename head_type, type_list tail>
    struct size<cons<head_type, tail>> : std::integral_constant<std::size_t, 1 + size<tail>::value> {};

    export {
        template <type_list list>
        inline constexpr std::size_t size_v = size<list>::value;
    }

}  // namespace type_list
