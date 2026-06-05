export module type_list:construct.concat;

import std;

import :core;

namespace type_list
{

    template <type_list left, type_list right>
    struct concat;

    template <type_list right>
    struct concat<nil, right> : std::type_identity<right> {};

    template <
        typename head_type,
        type_list tail,
        type_list right
    >
    struct concat<cons<head_type, tail>, right>
        : std::type_identity<cons<
              head_type,
              typename concat<tail, right>::type
          >> {};

    export {
        template <type_list left, type_list right>
        using concat_t = typename concat<left, right>::type;
    }

}  // namespace type_list
