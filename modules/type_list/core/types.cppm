export module type_list:core.types;

import std;

export namespace type_list
{

    struct nil {};

    template <typename head, typename tail>
    struct cons {};

}  // namespace type_list
