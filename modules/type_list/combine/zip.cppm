export module type_list:combine.zip;

import std;

import :core;

namespace type_list {

    template <type_list left, type_list right>
    struct zip;

    template <>
    struct zip<nil, nil> : std::type_identity<nil> {};

    template <type_list right>
    struct zip<nil, right> : std::type_identity<nil> {};

    template <type_list left>
    struct zip<left, nil> : std::type_identity<nil> {};

    template <typename left_head, type_list left_tail, typename right_head, type_list right_tail>
    struct zip<cons<left_head, left_tail>, cons<right_head, right_tail>>
        : std::type_identity<cons<std::pair<left_head, right_head>, typename zip<left_tail, right_tail>::type>> {};

    export {
        template <type_list left, type_list right>
        using zip_t = typename zip<left, right>::type;
    }

}  // namespace type_list
