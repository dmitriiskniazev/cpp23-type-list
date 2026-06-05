export module type_list:combine.unzip;

import std;

import :core;

namespace type_list {

    template <type_list list>
    struct unzip;

    template <>
    struct unzip<nil> : std::type_identity<std::pair<nil, nil>> {
        using first = nil;
        using second = nil;
    };

    template <typename first_type, typename second_type, type_list tail>
    struct unzip<cons<std::pair<first_type, second_type>, tail>>
        : std::type_identity<
              std::pair<cons<first_type, typename unzip<tail>::first>, cons<second_type, typename unzip<tail>::second>>
          > {
        using first = cons<first_type, typename unzip<tail>::first>;
        using second = cons<second_type, typename unzip<tail>::second>;
    };

    export {
        template <type_list list>
        using unzip_t = typename unzip<list>::type;
    }

}  // namespace type_list
