import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

template <typename Type> struct KeepFst : std::integral_constant<bool, std::same_as<Type, Fst>> {};

template <typename Type>
struct KeepFstSnd
    : std::integral_constant<bool, std::same_as<Type, Fst> or std::same_as<Type, Snd>> {};

using EmptyList = type_list::nil;
using FstSndList = type_list::from_pack_t<Fst, Snd>;
using MixedList = type_list::from_pack_t<Fst, Trd, Snd>;
using FstOnlyList = type_list::from_pack_t<Fst>;

using FilteredEmptyList = type_list::filter_t<KeepFst, EmptyList>;
using FilteredFstSndList = type_list::filter_t<KeepFst, FstSndList>;
using FilteredMixedList = type_list::filter_t<KeepFstSnd, MixedList>;

static_assert(std::same_as<FilteredEmptyList, EmptyList>);
static_assert(std::same_as<FilteredFstSndList, FstOnlyList>);
static_assert(std::same_as<FilteredMixedList, FstSndList>);

auto main() -> int { return 0; }
