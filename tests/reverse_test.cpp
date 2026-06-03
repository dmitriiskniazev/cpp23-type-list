import type_list;

using One = from_pack_t<int>;
using Input = from_pack_t<int, char, double>;
using Expected = from_pack_t<double, char, int>;

static_assert(same_as<reverse_t<Nil>, Nil>);
static_assert(same_as<reverse_t<One>, One>);
static_assert(same_as<reverse_t<Input>, Expected>);

int main() { return 0; }
