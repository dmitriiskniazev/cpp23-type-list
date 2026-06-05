import std;

import type_list;

struct Fst;
struct Snd;
struct Alpha;
struct Beta;

using FirstList = type_list::from_pack_t<Fst, Snd>;
using SecondList = type_list::from_pack_t<Alpha, Beta>;

using PairFstAlpha = std::pair<Fst, Alpha>;
using PairSndBeta = std::pair<Snd, Beta>;
using PairsList = type_list::from_pack_t<PairFstAlpha, PairSndBeta>;

using Unzipped = type_list::unzip_t<PairsList>;
using UnzippedFirst = Unzipped::first_type;
using UnzippedSecond = Unzipped::second_type;

static_assert(std::same_as<UnzippedFirst, FirstList>);
static_assert(std::same_as<UnzippedSecond, SecondList>);

using ZippedList = type_list::zip_t<FirstList, SecondList>;
using RoundTrip = type_list::unzip_t<ZippedList>;

static_assert(std::same_as<RoundTrip::first_type, FirstList>);
static_assert(std::same_as<RoundTrip::second_type, SecondList>);

auto main() -> int { return 0; }
