import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using List = type_list::from_pack_t<Fst, Snd, Trd>;
using FrontType = type_list::front_t<List>;

static_assert(std::same_as<FrontType, Fst>);

auto main() -> int { return 0; }
