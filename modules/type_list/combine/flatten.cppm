export module type_list:combine.flatten;

import std;

import :construct.concat;
import :core;

namespace type_list
{

    template <type_list list>
    struct flatten;

    template <>
    struct flatten<nil> : std::type_identity<nil> {};

    template <typename head_type, type_list tail>
        requires(not type_list<head_type>)
    struct flatten<cons<head_type, tail>> : std::type_identity<cons<head_type, typename flatten<tail>::type>> {};

    template <type_list nested, type_list tail>
    struct flatten<cons<nested, tail>>
        : std::type_identity<concat_t<typename flatten<nested>::type, typename flatten<tail>::type>> {};

    export {
        template <type_list list>
        using flatten_t = typename flatten<list>::type;
    }

}  // namespace type_list
