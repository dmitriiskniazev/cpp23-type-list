import type_list;

using Int = from_pack_t<int>;
using IntChar = from_pack_t<int, char>;
using Double = from_pack_t<double>;
using Expected = from_pack_t<int, char, double>;

static_assert(same_as<concat_t<Nil, Nil>, Nil>);
static_assert(same_as<concat_t<Nil, Int>, Int>);
static_assert(same_as<concat_t<Int, Nil>, Int>);
static_assert(same_as<concat_t<IntChar, Double>, Expected>);

int main() { return 0; }
