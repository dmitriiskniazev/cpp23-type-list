import type_list;

using List = from_pack_t<int>;
using Expected = from_pack_t<int, char>;

static_assert(same_as<append_t<List, char>, Expected>);

int main() { return 0; }
