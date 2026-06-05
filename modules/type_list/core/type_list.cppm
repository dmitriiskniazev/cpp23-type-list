export module type_list:core.type_list;

import std;

import :core.types;

namespace type_list
{

    template <typename type>
    struct is_type_list : std::false_type {};

    template <>
    struct is_type_list<nil> : std::true_type {};

    template <typename head, typename tail>
        requires is_type_list<tail>::value
    struct is_type_list<cons<head, tail>> : std::true_type {
    };

    export {
        template <typename type>
        concept type_list = is_type_list<type>::value;
    }

}  // namespace type_list
