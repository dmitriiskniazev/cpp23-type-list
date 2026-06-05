import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using FstSndList = type_list::from_pack_t<Fst, Snd>;
using TrdList = type_list::from_pack_t<Trd>;
using EmptyTail = type_list::nil;

using NestedLists = type_list::from_pack_t<FstSndList, TrdList, EmptyTail>;
using FlattenedList = type_list::flatten_t<NestedLists>;
using ExpectedList = type_list::from_pack_t<Fst, Snd, Trd>;

static_assert(std::same_as<FlattenedList, ExpectedList>);

auto main() -> int { return 0; }
