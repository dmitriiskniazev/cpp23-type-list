import type_list;

using List = from_pack_t<int, char>;
using Expected = from_pack_t<char>;

static_assert(same_as<tail_t<List>, Expected>);

int main() { return 0; }
