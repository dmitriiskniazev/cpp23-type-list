import type_list;

template <type_list Acc, typename Elem>
struct ListAppend : type_identity<append_t<Acc, Elem>> {};

using List = from_pack_t<int, char, double>;

static_assert(same_as<fold_left_t<Nil, ListAppend, List>, List>);
static_assert(same_as<fold_left_t<Nil, ListAppend, Nil>, Nil>);

int main() { return 0; }
