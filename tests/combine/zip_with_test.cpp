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
using ExpectedList = type_list::from_pack_t<PairFstAlpha, PairSndBeta>;

using ZippedList = type_list::zip_with_t<MakePair, FirstList, SecondList>;
using EmptyList = type_list::nil;
using EmptyZip = type_list::zip_with_t<MakePair, EmptyList, EmptyList>;

static_assert(std::same_as<ZippedList, ExpectedList>);
static_assert(std::same_as<EmptyZip, EmptyList>);

auto main() -> int { return 0; }
