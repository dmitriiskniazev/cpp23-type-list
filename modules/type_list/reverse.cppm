export module type_list:reverse;

import std;

import :push_back;
import :types;
import :type_list;

namespace type_list {

    template <type_list list>
    struct reverse;

    template <>
    struct reverse<nil> : std::type_identity<nil> {};

    template <typename head_type, type_list tail>
    struct reverse<cons<head_type, tail>> : std::type_identity<push_back_t<typename reverse<tail>::type, head_type>> {};

    export {
        template <type_list list>
        using reverse_t = typename reverse<list>::type;
    }

}  // namespace type_list
