import std;

import type_list;

struct Fst;
struct Snd;
struct Trd;
struct Frh;

using FirstList = type_list::from_pack_t<Fst, Snd>;
using SecondList = type_list::from_pack_t<Trd, Frh>;
using ZippedList = type_list::zip_t<FirstList, SecondList>;

using Unzipped = type_list::unzip_t<ZippedList>;
using UnzippedFirst = Unzipped::first_type;
using UnzippedSecond = Unzipped::second_type;

static_assert(std::same_as<UnzippedFirst, FirstList>);
static_assert(std::same_as<UnzippedSecond, SecondList>);

auto main() -> int { return 0; }
