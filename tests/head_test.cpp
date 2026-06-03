import type_list;

using List = from_pack_t<int, char>;

static_assert(same_as<head_t<List>, int>);

int main() { return 0; }
