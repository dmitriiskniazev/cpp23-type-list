import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using List = type_list::from_pack_t<Fst, Snd, Trd>;
using BackType = type_list::back_t<List>;

static_assert(std::same_as<BackType, Trd>);

auto main() -> int { return 0; }
