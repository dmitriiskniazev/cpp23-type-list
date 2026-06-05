export module type_list:construct.insert;

import std;

import :core;
import :construct.push_back;
import :construct.push_front;
import :traits.size;

namespace type_list
{

    template <
        type_list list,
        std::size_t index,
        typename type
    >
    struct insert;

    template <type_list list, typename type>
    struct insert<list, 0, type>
        : std::type_identity<push_front_t<type, list>> {};

    template <type_list list, typename type>
        requires(size_v<list> > 0)
    struct insert<list, size_v<list>, type>
        : std::type_identity<push_back_t<list, type>> {};

    template <
        std::size_t index,
        typename type,
        typename front_type,
        type_list tail
    >
        requires(
            index > 0
            and index < size_v<cons<front_type, tail>>)
    struct insert<cons<front_type, tail>, index, type>
        : std::type_identity<cons<
              front_type,
              typename insert<tail, index - 1, type>::type
          >> {};

    export {
        template <
            type_list list,
            std::size_t index,
            typename type
        >
        using insert_t =
            typename insert<list, index, type>::type;
    }

}  // namespace type_list
