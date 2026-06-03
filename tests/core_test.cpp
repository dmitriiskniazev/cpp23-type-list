import type_list;

using Valid = from_pack_t<int>;

static_assert(type_list<Nil>);
static_assert(type_list<Valid>);
static_assert(non_empty_type_list<Valid>);
static_assert(not non_empty_type_list<Nil>);
static_assert(not type_list<Cons<int, int>>);

int main() { return 0; }
