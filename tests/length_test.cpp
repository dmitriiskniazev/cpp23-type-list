import type_list;

using List = from_pack_t<int, char, double>;

static_assert(length_v<Nil> == 0);
static_assert(length_v<List> == 3);

int main() { return 0; }
