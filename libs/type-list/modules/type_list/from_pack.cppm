export module type_list:from_pack;

import std;

import :types;
import :type_list;

namespace type_list {

    template <typename... types>
    struct from_pack;

    template <>
    struct from_pack<> : std::type_identity<nil> {};

    template <typename head, typename... tail>
    struct from_pack<head, tail...> : std::type_identity<cons<head, typename from_pack<tail...>::type>> {};

    export {
        template <typename... types>
        using from_pack_t = typename from_pack<types...>::type;
    }

}  // namespace type_list
