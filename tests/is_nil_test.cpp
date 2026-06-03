import type_list;

using NonEmpty = from_pack_t<int>;

static_assert(is_nil_v<Nil>);
static_assert(not is_nil_v<NonEmpty>);

int main() { return 0; }
