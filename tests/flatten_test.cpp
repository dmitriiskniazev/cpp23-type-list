import type_list;

using OneNested = from_pack_t<from_pack_t<int>>;
using Nested = from_pack_t<from_pack_t<int, char>, from_pack_t<double>>;
using WithEmpty = from_pack_t<Nil, from_pack_t<int>>;

using FlatInt = from_pack_t<int>;
using FlatAll = from_pack_t<int, char, double>;

static_assert(same_as<flatten_t<Nil>, Nil>);
static_assert(same_as<flatten_t<OneNested>, FlatInt>);
static_assert(same_as<flatten_t<Nested>, FlatAll>);
static_assert(same_as<flatten_t<WithEmpty>, FlatInt>);

int main() { return 0; }
