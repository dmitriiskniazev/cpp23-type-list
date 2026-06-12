import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

template <typename Type> struct Boxed;

template <typename Type> using Box = Boxed<Type>;

using List = type_list::from_pack_t<Fst, Snd, Trd>;
using EmptyList = type_list::nil;
using MappedList = type_list::map_t<Box, List>;
using MappedEmptyList = type_list::map_t<Box, EmptyList>;
using ExpectedList = type_list::from_pack_t<Boxed<Fst>, Boxed<Snd>, Boxed<Trd>>;

static_assert(std::same_as<MappedList, ExpectedList>);
static_assert(std::same_as<MappedEmptyList, EmptyList>);

auto main() -> int { return 0; }
