import type_list;

using One = from_pack_t<int>;
using Two = from_pack_t<int, char>;
using Three = from_pack_t<int, char, double>;

static_assert(is_nil_v<from_pack_t<>>);
static_assert(same_as<head_t<One>, int>);
static_assert(same_as<tail_t<Two>, from_pack_t<char>>);
static_assert(length_v<Three> == 3);

int main() { return 0; }
