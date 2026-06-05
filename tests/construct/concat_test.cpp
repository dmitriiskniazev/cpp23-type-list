import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using EmptyList = type_list::nil;
using FstList = type_list::from_pack_t<Fst>;
using FstSndList = type_list::from_pack_t<Fst, Snd>;
using TrdList = type_list::from_pack_t<Trd>;
using ExpectedList = type_list::from_pack_t<Fst, Snd, Trd>;

using EmptyConcat = type_list::concat_t<EmptyList, EmptyList>;
using ConcatNilFst = type_list::concat_t<EmptyList, FstList>;
using ConcatFstNil = type_list::concat_t<FstList, EmptyList>;
using ConcatResult = type_list::concat_t<FstSndList, TrdList>;

static_assert(std::same_as<EmptyConcat, EmptyList>);
static_assert(std::same_as<ConcatNilFst, FstList>);
static_assert(std::same_as<ConcatFstNil, FstList>);
static_assert(std::same_as<ConcatResult, ExpectedList>);

auto main() -> int { return 0; }
