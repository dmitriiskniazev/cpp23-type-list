import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using EmptyList = type_list::nil;
using FstList = type_list::from_pack_t<Fst>;
using List = type_list::from_pack_t<Fst, Snd, Trd>;
using ExpectedList = type_list::from_pack_t<Trd, Snd, Fst>;

using ReversedEmptyList = type_list::reverse_t<EmptyList>;
using ReversedFstList = type_list::reverse_t<FstList>;
using ReversedList = type_list::reverse_t<List>;

static_assert(std::same_as<ReversedEmptyList, EmptyList>);
static_assert(std::same_as<ReversedFstList, FstList>);
static_assert(std::same_as<ReversedList, ExpectedList>);

auto main() -> int { return 0; }
