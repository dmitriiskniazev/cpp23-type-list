import std;

import type_list;

struct Fst;
struct Snd;
struct Alpha;
struct Beta;
struct Gamma;

using FirstList = type_list::from_pack_t<Fst, Snd>;
using SecondList = type_list::from_pack_t<Alpha, Beta, Gamma>;
using PairsList = type_list::zip_t<FirstList, SecondList>;

using PairFstAlpha = std::pair<Fst, Alpha>;
using PairSndBeta = std::pair<Snd, Beta>;
using FrontPair = type_list::front_t<PairsList>;
using BackPair = type_list::back_t<PairsList>;

static_assert(type_list::size_v<PairsList> == 2);
static_assert(std::same_as<FrontPair, PairFstAlpha>);
static_assert(std::same_as<BackPair, PairSndBeta>);

auto main() -> int { return 0; }
