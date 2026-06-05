import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

template <typename Type>
struct Keep : std::integral_constant<bool, std::same_as<Type, Fst> or std::same_as<Type, Snd>> {};

using List = type_list::from_pack_t<Fst, Trd, Snd>;
using FilteredList = type_list::filter_t<Keep, List>;
using ExpectedList = type_list::from_pack_t<Fst, Snd>;

static_assert(std::same_as<FilteredList, ExpectedList>);

auto main() -> int { return 0; }
