import type_list;

template <typename T>
using add_pointer = T*;

using Input = from_pack_t<int, char>;
using Expected = from_pack_t<int*, char*>;

static_assert(same_as<map_t<add_pointer, Input>, Expected>);
static_assert(same_as<map_t<add_pointer, Nil>, Nil>);

int main() { return 0; }
