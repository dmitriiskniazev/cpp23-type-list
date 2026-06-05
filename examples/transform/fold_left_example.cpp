import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

template <typename Accumulator, typename Elem>
struct PushBackOne : std::type_identity<type_list::push_back_t<Accumulator, Elem>> {};

using EmptyList = type_list::nil;
using SourceList = type_list::from_pack_t<Fst, Snd, Trd>;
using FoldedList = type_list::fold_left_t<EmptyList, PushBackOne, SourceList>;
using FoldedEmptyList = type_list::fold_left_t<EmptyList, PushBackOne, EmptyList>;

static_assert(std::same_as<FoldedList, SourceList>);
static_assert(std::same_as<FoldedEmptyList, EmptyList>);

auto main() -> int { return 0; }
