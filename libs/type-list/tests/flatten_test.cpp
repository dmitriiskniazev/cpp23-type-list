import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;

using EmptyList = type_list::nil;
using InnerFstList = type_list::from_pack_t<Fst>;
using OneNested = type_list::from_pack_t<InnerFstList>;
using FstSndInner = type_list::from_pack_t<Fst, Snd>;
using TrdInner = type_list::from_pack_t<Trd>;
using NestedLists = type_list::from_pack_t<FstSndInner, TrdInner>;
using FstInner = type_list::from_pack_t<Fst>;
using WithEmpty = type_list::from_pack_t<EmptyList, FstInner>;

using FlatFst = type_list::from_pack_t<Fst>;
using FlatAll = type_list::from_pack_t<Fst, Snd, Trd>;

using FlattenedEmptyList = type_list::flatten_t<EmptyList>;
using FlattenedOneNested = type_list::flatten_t<OneNested>;
using FlattenedNestedLists = type_list::flatten_t<NestedLists>;
using FlattenedWithEmpty = type_list::flatten_t<WithEmpty>;

static_assert(std::same_as<FlattenedEmptyList, EmptyList>);
static_assert(std::same_as<FlattenedOneNested, FlatFst>);
static_assert(std::same_as<FlattenedNestedLists, FlatAll>);
static_assert(std::same_as<FlattenedWithEmpty, FlatFst>);

auto main() -> int { return 0; }
