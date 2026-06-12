import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using List = type_list::from_pack_t<Snd, Trd>;
using ExtendedList = type_list::push_front_t<Fst, List>;
using ExpectedList = type_list::from_pack_t<Fst, Snd, Trd>;

static_assert(std::same_as<ExtendedList, ExpectedList>);

auto main() -> int { return 0; }
