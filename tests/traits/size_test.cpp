import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using EmptyList = type_list::nil;
using List = type_list::from_pack_t<Fst, Snd, Trd>;
using FstList = type_list::from_pack_t<Fst>;

static_assert(type_list::size_v<EmptyList> == 0);
static_assert(type_list::size_v<List> == 3);
static_assert(type_list::size_v<FstList> == 1);

auto main() -> int { return 0; }
