export module type_list:core;

export import :std;

export {
    struct Nil {};

    template <typename Head, typename Tail>
    struct Cons;
}

template <typename T>
struct TypeList : false_type {};

template <>
struct TypeList<Nil> : true_type {};

template <typename Head, typename Tail>
    requires TypeList<Tail>::value
struct TypeList<Cons<Head, Tail>> : true_type {};

export {
    template <typename T>
    concept type_list = TypeList<T>::value;

    template <typename T>
    concept non_empty_type_list = type_list<T> and not same_as<T, Nil>;
}
