module;

#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

export module type_list:std;

export {
    using std::false_type;
    using std::true_type;
    using std::integral_constant;
    using std::conditional_t;
    using std::pair;
    using std::size_t;
    using std::same_as;
    using std::type_identity;
}
