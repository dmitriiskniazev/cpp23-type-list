import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using List = type_list::from_pack_t<Fst, Snd>;
using ExtendedList = type_list::push_back_t<List, Trd>;
using ExpectedList = type_list::from_pack_t<Fst, Snd, Trd>;
using BackType = type_list::back_t<ExtendedList>;

static_assert(std::same_as<BackType, Trd>);
static_assert(std::same_as<ExtendedList, ExpectedList>);

auto main() -> int { return 0; }
