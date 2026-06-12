import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

template <typename Elem, type_list::type_list Accumulator>
struct PushFrontOne : std::type_identity<type_list::push_front_t<Elem, Accumulator>> {};

using EmptyList = type_list::nil;
using SourceList = type_list::from_pack_t<Fst, Snd, Trd>;
using FoldedList = type_list::fold_right_t<EmptyList, PushFrontOne, SourceList>;
using FoldedEmptyList = type_list::fold_right_t<EmptyList, PushFrontOne, EmptyList>;

static_assert(std::same_as<FoldedList, SourceList>);
static_assert(std::same_as<FoldedEmptyList, EmptyList>);

auto main() -> int { return 0; }
