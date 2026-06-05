export module type_list:traits.non_empty;

import std;

import :core;

export namespace type_list
{

    template <typename type>
    concept non_empty =
        type_list<type> and not std::same_as<type, nil>;

}  // namespace type_list
