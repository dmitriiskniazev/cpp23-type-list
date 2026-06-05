import std;

import type_list;

struct Fst;
struct Snd;
struct Alpha;
struct Beta;

template <typename Left, typename Right>
struct MakePair : std::type_identity<std::pair<Left, Right>> {};

using FirstList = type_list::from_pack_t<Fst, Snd>;
using SecondList = type_list::from_pack_t<Alpha, Beta>;

using PairFstAlpha = std::pair<Fst, Alpha>;
using PairSndBeta = std::pair<Snd, Beta>;
using ZippedList = type_list::zip_with_t<MakePair, FirstList, SecondList>;
using FrontPair = type_list::front_t<ZippedList>;
using BackPair = type_list::back_t<ZippedList>;

static_assert(type_list::size_v<ZippedList> == 2);
static_assert(std::same_as<FrontPair, PairFstAlpha>);
static_assert(std::same_as<BackPair, PairSndBeta>);

auto main() -> int { return 0; }
