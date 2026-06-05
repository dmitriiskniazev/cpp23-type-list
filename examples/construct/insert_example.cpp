import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using List = type_list::from_pack_t<Fst, Trd>;
using ExtendedList = type_list::insert_t<List, 1, Snd>;
using ExpectedList = type_list::from_pack_t<Fst, Snd, Trd>;

using EmptyList = type_list::nil;
using InsertedIntoEmptyList = type_list::insert_t<EmptyList, 0, Fst>;
using ExpectedFstList = type_list::from_pack_t<Fst>;

static_assert(std::same_as<ExtendedList, ExpectedList>);
static_assert(std::same_as<InsertedIntoEmptyList, ExpectedFstList>);

auto main() -> int { return 0; }
