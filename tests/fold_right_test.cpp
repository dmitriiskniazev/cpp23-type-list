import type_list;

template <typename Elem, type_list Acc>
struct ListPrepend : type_identity<prepend_t<Elem, Acc>> {};

using List = from_pack_t<int, char, double>;

static_assert(same_as<fold_right_t<Nil, ListPrepend, List>, List>);
static_assert(same_as<fold_right_t<Nil, ListPrepend, Nil>, Nil>);

int main() { return 0; }
