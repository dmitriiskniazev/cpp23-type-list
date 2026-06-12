import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using EmptyList = type_list::from_pack_t<>;
using FstList = type_list::from_pack_t<Fst>;
using List = type_list::from_pack_t<Fst, Snd, Trd>;
using TailList = type_list::from_pack_t<Snd, Trd>;

using FrontType = type_list::front_t<FstList>;
using PoppedList = type_list::pop_front_t<List>;

static_assert(std::same_as<EmptyList, type_list::nil>);
static_assert(std::same_as<FrontType, Fst>);
static_assert(std::same_as<PoppedList, TailList>);

auto main() -> int { return 0; }
