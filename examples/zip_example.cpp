import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;
struct Frh;
struct Fth;

using FirstList = type_list::from_pack_t<Fst, Snd>;
using SecondList = type_list::from_pack_t<Trd, Frh, Fth>;
using PairsList = type_list::zip_t<FirstList, SecondList>;

using PairFstTrd = std::pair<Fst, Trd>;
using PairSndFrh = std::pair<Snd, Frh>;
using FrontPair = type_list::front_t<PairsList>;
using BackPair = type_list::back_t<PairsList>;

static_assert(type_list::size_v<PairsList> == 2);
static_assert(std::same_as<FrontPair, PairFstTrd>);
static_assert(std::same_as<BackPair, PairSndFrh>);

auto main() -> int { return 0; }
