import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using List = type_list::from_pack_t<Fst, Snd, Trd>;
using ReversedList = type_list::reverse_t<List>;
using ExpectedList = type_list::from_pack_t<Trd, Snd, Fst>;

static_assert(std::same_as<ReversedList, ExpectedList>);

auto main() -> int { return 0; }
