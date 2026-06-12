import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;
struct Fourth;

using PrefixList = type_list::from_pack_t<Fst, Snd>;
using SuffixList = type_list::from_pack_t<Trd, Fourth>;
using ConcatenatedList = type_list::concat_t<PrefixList, SuffixList>;
using ExpectedList = type_list::from_pack_t<Fst, Snd, Trd, Fourth>;

using WithoutFstList = type_list::pop_front_t<ConcatenatedList>;
using WithoutFstSndList = type_list::pop_front_t<WithoutFstList>;
using ThirdType = type_list::front_t<WithoutFstSndList>;

static_assert(type_list::size_v<ConcatenatedList> == 4);
static_assert(std::same_as<ThirdType, Trd>);
static_assert(std::same_as<ConcatenatedList, ExpectedList>);

auto main() -> int { return 0; }
