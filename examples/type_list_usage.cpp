// Compile-time examples for cpp23-type-list.
// Build: cmake --build build --target type_list_usage
// All checks are static_assert; main() is only to form an executable.

import type_list;

// --- Core --------------------------------------------------------------------

using Empty = Nil;
using Numbers = from_pack_t<int, double, char>;
using One = Cons<bool, Nil>;

static_assert(type_list<Numbers>);
static_assert(non_empty_type_list<Numbers>);
static_assert(not type_list<Cons<int, int>>);

// --- Queries -----------------------------------------------------------------

static_assert(is_nil_v<Nil>);
static_assert(not is_nil_v<Numbers>);
static_assert(length_v<Numbers> == 3);
static_assert(same_as<head_t<Numbers>, int>);
static_assert(same_as<tail_t<Numbers>, Cons<double, Cons<char, Nil>>>);

// --- prepend / append --------------------------------------------------------

using Front = prepend_t<short, Numbers>;
static_assert(same_as<head_t<Front>, short>);
static_assert(length_v<Front> == 4);

using Back = append_t<One, void>;
static_assert(same_as<head_t<tail_t<Back>>, void>);

// --- concat ------------------------------------------------------------------

using ABC = from_pack_t<int, char>;
using XYZ = from_pack_t<double, void>;
using Merged = concat_t<ABC, XYZ>;
static_assert(length_v<Merged> == 4);
static_assert(same_as<head_t<tail_t<tail_t<Merged>>>, double>);

// --- map ---------------------------------------------------------------------

template <typename T>
using add_const = const T;

using Consts = map_t<add_const, Numbers>;
static_assert(same_as<Consts, from_pack_t<const int, const double, const char>>);

// --- filter ------------------------------------------------------------------

template <typename T>
struct is_integral : integral_constant<bool, same_as<T, int> or same_as<T, char>> {};

using IntsOnly = filter_t<is_integral, Numbers>;
static_assert(same_as<IntsOnly, from_pack_t<int, char>>);

// --- fold_left (build list by appending one type at a time) ------------------

template <typename Acc, typename Elem>
struct append_one {
    using type = append_t<Acc, Elem>;
};

using Folded = fold_left_t<Nil, append_one, from_pack_t<int, char, void>>;
static_assert(same_as<Folded, from_pack_t<int, char, void>>);

// --- zip ---------------------------------------------------------------------

using Zipped = zip_t<from_pack_t<int, char>, from_pack_t<float, double, void>>;
static_assert(length_v<Zipped> == 2);
static_assert(same_as<head_t<Zipped>, pair<int, float>>);

// --- reverse -----------------------------------------------------------------

static_assert(same_as<reverse_t<Numbers>, from_pack_t<char, double, int>>);

// --- flatten (list of lists) -------------------------------------------------

using Nested = from_pack_t<
    from_pack_t<int, char>,
    from_pack_t<double>,
    Nil
>;
static_assert(same_as<flatten_t<Nested>, from_pack_t<int, char, double>>);

int main() { return 0; }
