import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;
struct Frh;

template <typename Left, typename Right>
struct MakePair : std::type_identity<std::pair<Left, Right>> {};

using FirstList = type_list::from_pack_t<Fst, Snd>;
using SecondList = type_list::from_pack_t<Trd, Frh>;

using PairFstTrd = std::pair<Fst, Trd>;
using PairSndFrh = std::pair<Snd, Frh>;
using ZippedList = type_list::zip_with_t<MakePair, FirstList, SecondList>;
using FrontPair = type_list::front_t<ZippedList>;
using BackPair = type_list::back_t<ZippedList>;

static_assert(type_list::size_v<ZippedList> == 2);
static_assert(std::same_as<FrontPair, PairFstTrd>);
static_assert(std::same_as<BackPair, PairSndFrh>);

auto main() -> int { return 0; }
