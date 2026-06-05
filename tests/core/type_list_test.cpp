import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using EmptyList = type_list::nil;
using WellFormedList = type_list::from_pack_t<Fst, Snd, Trd>;
using BadCons = type_list::cons<Fst, Snd>;

static_assert(type_list::type_list<EmptyList>);
static_assert(type_list::type_list<WellFormedList>);
static_assert(type_list::non_empty<WellFormedList>);
static_assert(not type_list::non_empty<EmptyList>);
static_assert(not type_list::type_list<BadCons>);

auto main() -> int { return 0; }
