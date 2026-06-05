export module type_list:traits.empty;

import std;

import :core;

export namespace type_list {

    template <typename type>
    concept empty = type_list<type> and std::same_as<type, nil>;

}  // namespace type_list
