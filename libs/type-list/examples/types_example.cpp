import std;

import type_list;

struct Fst;
struct Snd;

using EmptyList = type_list::nil;
using SndList = type_list::cons<Snd, EmptyList>;
using FstList = type_list::cons<Fst, EmptyList>;
using FstSndList = type_list::cons<Fst, SndList>;

using PackFstList = type_list::from_pack_t<Fst>;
using PackFstSndList = type_list::from_pack_t<Fst, Snd>;

static_assert(std::same_as<EmptyList, type_list::nil>);
static_assert(std::same_as<FstList, PackFstList>);
static_assert(std::same_as<FstSndList, PackFstSndList>);

auto main() -> int { return 0; }
