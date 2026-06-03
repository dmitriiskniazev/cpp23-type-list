import type_list;

using Lhs = from_pack_t<int, char>;
using Rhs = from_pack_t<double, float>;
using Expected = from_pack_t<pair<int, double>, pair<char, float>>;

using ShortLhs = from_pack_t<int>;
using LongRhs = from_pack_t<double, float, short>;
using ShortExpected = from_pack_t<pair<int, double>>;

static_assert(same_as<zip_t<Nil, Nil>, Nil>);
static_assert(same_as<zip_t<Lhs, Rhs>, Expected>);
static_assert(same_as<zip_t<ShortLhs, LongRhs>, ShortExpected>);

int main() { return 0; }
