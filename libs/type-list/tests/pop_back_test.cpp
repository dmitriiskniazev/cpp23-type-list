import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using List = type_list::from_pack_t<Fst, Snd, Trd>;
using PoppedList = type_list::pop_back_t<List>;
using ExpectedList = type_list::from_pack_t<Fst, Snd>;

static_assert(std::same_as<PoppedList, ExpectedList>);

auto main() -> int { return 0; }
