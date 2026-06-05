export module type_list:non_empty;

import std;

import :types;
import :type_list;

export namespace type_list {

    template <typename type>
    concept non_empty = type_list<type> and not std::same_as<type, nil>;

}  // namespace type_list
