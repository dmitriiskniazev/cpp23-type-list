export module type_list:zip_with;

import :types;
import :type_list;

namespace type_list {

    template <template <typename, typename> typename binary_op, type_list left, type_list right>
    struct zip_with;

    template <template <typename, typename> typename binary_op>
    struct zip_with<binary_op, nil, nil> : std::type_identity<nil> {};

    template <template <typename, typename> typename binary_op, type_list right>
    struct zip_with<binary_op, nil, right> : std::type_identity<nil> {};

    template <template <typename, typename> typename binary_op, type_list left>
    struct zip_with<binary_op, left, nil> : std::type_identity<nil> {};

    template <
        template <typename, typename> typename binary_op,
        typename left_head,
        type_list left_tail,
        typename right_head,
        type_list right_tail
    >
    struct zip_with<binary_op, cons<left_head, left_tail>, cons<right_head, right_tail>>
        : std::type_identity<cons<
              typename binary_op<left_head, right_head>::type,
              typename zip_with<binary_op, left_tail, right_tail>::type
          >> {};

    export {
        template <template <typename, typename> typename binary_op, type_list left, type_list right>
        using zip_with_t = typename zip_with<binary_op, left, right>::type;
    }

}  // namespace type_list
