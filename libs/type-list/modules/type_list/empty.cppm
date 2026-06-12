export module type_list:empty;

import std;

import :types;
import :type_list;

export namespace type_list {

    template <typename type>
    concept empty = type_list<type> and std::same_as<type, nil>;

}  // namespace type_list
