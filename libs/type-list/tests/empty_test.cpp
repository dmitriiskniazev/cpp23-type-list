import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using EmptyList = type_list::nil;
using List = type_list::from_pack_t<Fst, Snd, Trd>;

static_assert(type_list::empty<EmptyList>);
static_assert(not type_list::empty<List>);

auto main() -> int { return 0; }
