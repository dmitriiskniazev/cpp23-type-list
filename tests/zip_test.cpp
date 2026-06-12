import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;
struct Frh;
struct Fth;

using EmptyList = type_list::nil;
using FirstList = type_list::from_pack_t<Fst, Snd>;
using SecondList = type_list::from_pack_t<Trd, Frh>;
using ShortFirst = type_list::from_pack_t<Fst>;
using LongSecond = type_list::from_pack_t<Trd, Frh, Fth>;

using PairFstTrd = std::pair<Fst, Trd>;
using PairSndFrh = std::pair<Snd, Frh>;
using ExpectedList = type_list::from_pack_t<PairFstTrd, PairSndFrh>;
using ShortExpected = type_list::from_pack_t<PairFstTrd>;

using EmptyZip = type_list::zip_t<EmptyList, EmptyList>;
using ZippedList = type_list::zip_t<FirstList, SecondList>;
using ShortZip = type_list::zip_t<ShortFirst, LongSecond>;

static_assert(std::same_as<EmptyZip, EmptyList>);
static_assert(std::same_as<ZippedList, ExpectedList>);
static_assert(std::same_as<ShortZip, ShortExpected>);

auto main() -> int { return 0; }
