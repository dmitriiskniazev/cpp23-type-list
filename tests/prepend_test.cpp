import type_list;

using List = from_pack_t<char>;
using Expected = from_pack_t<int, char>;

static_assert(same_as<prepend_t<int, List>, Expected>);

int main() { return 0; }
