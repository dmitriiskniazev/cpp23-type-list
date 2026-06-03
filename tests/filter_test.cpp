import type_list;

template <typename T>
struct is_int : integral_constant<bool, same_as<T, int>> {};

template <typename T>
struct is_int_or_char : integral_constant<bool, same_as<T, int> or same_as<T, char>> {};

using IntChar = from_pack_t<int, char>;
using Mixed = from_pack_t<int, double, char>;
using IntOnly = from_pack_t<int>;
using IntCharOnly = from_pack_t<int, char>;

static_assert(same_as<filter_t<is_int, Nil>, Nil>);
static_assert(same_as<filter_t<is_int, IntChar>, IntOnly>);
static_assert(same_as<filter_t<is_int_or_char, Mixed>, IntCharOnly>);

int main() { return 0; }
