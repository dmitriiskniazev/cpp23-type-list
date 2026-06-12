# API reference

Public API lives in `namespace type_list`. Import everything with `import type_list;` or pull in individual partitions (`import type_list:map;`).

## Naming

### Library symbols

| Kind | Rule | Examples |
|------|------|----------|
| Core types | lowercase | `nil`, `cons` |
| Concepts | lowercase | `type_list`, `empty`, `non_empty` |
| Result aliases | `<operation>_t<...>` | `front_t<List>`, `map_t<List, F>` |
| Constants | `<operation>_v<...>` | `size_v<List>` |
| Class templates | lowercase | `from_pack`, `fold_left`, `unzip` |
| Algorithm functors | template-template parameter | see [Transform](#transform) and [Combine](#combine) |

Implementations inherit `std::type_identity<Result>` (directly or through a small wrapper struct), not a bare `using type =` on the algorithm struct itself.

Functor parameter names in the source (`unary_op`, `binary_op`) are **template-template parameter placeholders**, not exported base types.

### Parameter order

| Operation | Template arguments | Notes |
|-----------|-------------------|--------|
| `push_front_t` | `<Type, List>` | new element first |
| `push_back_t` | `<List, Type>` | list first |
| `insert_t` | `<List, Index, Type>` | `Index` is a `std::size_t` value |
| `map_t` | `<Unary, List>` | `Unary` is `template <typename> class` |
| `filter_t` | `<Predicate, List>` | `Predicate<T>::value` must be valid |
| `fold_left_t`, `fold_right_t` | `<State, Binary, List>` | `Binary<Acc, Elem>::type` |
| `zip_t` | `<Left, Right>` | stops at shorter list |
| `zip_with_t` | `<Binary, Left, Right>` | `Binary<L, R>::type` |
| `concat_t` | `<Lhs, Rhs>` | left list first |

### Consumer code (tests / examples)

Use **PascalCase** for stand-in types and functors (`Fst`, `Snd`, `Boxed`, `Twice`, `MakePair`) to distinguish them from library names.

### Files and CMake targets

| Role | Path / target pattern |
|------|------------------------|
| Partition module | `modules/type_list/<name>.cppm` |
| Partition import | `import type_list:<name>;` |
| Unit test source | `tests/<name>_test.cpp` |
| Example source | `examples/<name>_example.cpp` |
| Test executable | `type_list_<name>_test` |
| Example executable | `type_list_<name>_example` |

`<name>` is the operation stem (`front`, `push_back`, `fold_left`, …).

---

## Core types and concepts

```cpp
struct nil {};

template <typename Head, typename Tail>
    requires type_list<Tail>
struct cons {
    using head = Head;
    using tail = Tail;
};

template <typename T>
concept type_list = /* cons spine ending in nil */;

template <typename T>
concept empty = type_list<T> and std::same_as<T, nil>;

template <typename T>
concept non_empty = type_list<T> and not empty<T>;

template <type_list List>
struct size;  // ::value

template <type_list List>
inline constexpr std::size_t size_v = size<List>::value;
```

**Partition:** `type_list:types`, `type_list:type_list`, `type_list:empty`, `type_list:non_empty`, `type_list:size`

---

## Symbol index

| Symbol | Kind | Partition |
|--------|------|-----------|
| `nil` | type | `:types` |
| `cons` | template | `:types` |
| `type_list` | concept | `:type_list` |
| `empty` | concept | `:empty` |
| `non_empty` | concept | `:non_empty` |
| `size`, `size_v` | struct / variable | `:size` |
| `front`, `front_t` | struct / alias | `:front` |
| `back`, `back_t` | struct / alias | `:back` |
| `pop_front`, `pop_front_t` | struct / alias | `:pop_front` |
| `pop_back`, `pop_back_t` | struct / alias | `:pop_back` |
| `push_front`, `push_front_t` | struct / alias | `:push_front` |
| `push_back`, `push_back_t` | struct / alias | `:push_back` |
| `insert`, `insert_t` | struct / alias | `:insert` |
| `concat`, `concat_t` | struct / alias | `:concat` |
| `from_pack`, `from_pack_t` | struct / alias | `:from_pack` |
| `map`, `map_t` | struct / alias | `:map` |
| `filter`, `filter_t` | struct / alias | `:filter` |
| `fold_left`, `fold_left_t` | struct / alias | `:fold_left` |
| `fold_right`, `fold_right_t` | struct / alias | `:fold_right` |
| `zip`, `zip_t` | struct / alias | `:zip` |
| `zip_with`, `zip_with_t` | struct / alias | `:zip_with` |
| `unzip`, `unzip_t` | struct / alias | `:unzip` |
| `reverse`, `reverse_t` | struct / alias | `:reverse` |
| `flatten`, `flatten_t` | struct / alias | `:flatten` |

---

## Access

Requires `non_empty<List>` where noted.

```cpp
template <non_empty type_list List>
struct front;  // ::type
template <non_empty type_list List>
using front_t = front<List>::type;

template <non_empty type_list List>
struct back;
template <non_empty type_list List>
using back_t = back<List>::type;

template <non_empty type_list List>
struct pop_front;
template <non_empty type_list List>
using pop_front_t = pop_front<List>::type;

template <non_empty type_list List>
struct pop_back;
template <non_empty type_list List>
using pop_back_t = pop_back<List>::type;
```

**Example**

```cpp
using List = from_pack_t<A, B, C>;
static_assert(std::same_as<front_t<List>, A>);
static_assert(std::same_as<back_t<List>, C>);
static_assert(std::same_as<pop_front_t<List>, from_pack_t<B, C>>);
```

---

## Construction

```cpp
template <typename Type, type_list List>
struct push_front;
template <typename Type, type_list List>
using push_front_t = push_front<Type, List>::type;

template <type_list List, typename Type>
struct push_back;
template <type_list List, typename Type>
using push_back_t = push_back<List, Type>::type;

template <type_list List, std::size_t Index, typename Type>
struct insert;
template <type_list List, std::size_t Index, typename Type>
using insert_t = insert<List, Index, Type>::type;

template <type_list Lhs, type_list Rhs>
struct concat;
template <type_list Lhs, type_list Rhs>
using concat_t = concat<Lhs, Rhs>::type;

template <typename... Types>
struct from_pack;
template <typename... Types>
using from_pack_t = from_pack<Types...>::type;
```

**Example**

```cpp
using L = from_pack_t<A, B>;
using Extended = push_back_t<L, C>;           // A, B, C
using Prepended = push_front_t<D, Extended>;  // D, A, B, C
using Merged = concat_t<from_pack_t<A>, from_pack_t<B, C>>;
static_assert(std::same_as<Merged, from_pack_t<A, B, C>>);
```

---

## Transform

### `map_t<Unary, List>`

`Unary` is a class template invoked as `Unary<T>` for each element. The result type is whatever `Unary<T>` denotes (often a specialization such as `Boxed<T>`).

```cpp
template <typename T> struct Boxed;
template <typename T> using Box = Boxed<T>;

using Mapped = map_t<Box, from_pack_t<int, char>>;
// cons<Boxed<int>, cons<Boxed<char>, nil>>
```

### `filter_t<Predicate, List>`

`Predicate` is a class template with a `static constexpr` (or enum) `value` member, typically via `std::bool_constant` / `std::integral_constant`.

```cpp
template <typename T>
struct IsInt : std::bool_constant<std::same_as<T, int>> {};

using Filtered = filter_t<IsInt, from_pack_t<int, char, int>>;
// from_pack_t<int, int>
```

### `fold_left_t<State, Binary, List>` / `fold_right_t<State, Binary, List>`

`Binary` is `template <typename, typename> class` with a nested `type` alias (e.g. inherit `std::type_identity<...>`).

```cpp
template <typename Acc, typename Elem>
struct PushBackOne : std::type_identity<push_back_t<Acc, Elem>> {};

using Built = fold_left_t<nil, PushBackOne, from_pack_t<A, B, C>>;
// from_pack_t<A, B, C>
```

Signatures in source:

```cpp
template <template <typename> class Unary, type_list List>
using map_t = /* ... */;

template <template <typename> class Unary, type_list List>
using filter_t = /* ... */;

template <typename State, template <typename, typename> class Binary, type_list List>
using fold_left_t = /* ... */;

template <typename State, template <typename, typename> class Binary, type_list List>
using fold_right_t = /* ... */;
```

---

## Combine

Pair lists for `zip` store `std::pair<First, Second>` in each `cons` head.

```cpp
template <type_list Left, type_list Right>
using zip_t = /* ... */;

template <template <typename, typename> class Binary, type_list Left, type_list Right>
using zip_with_t = /* ... */;

template <type_list List>
using unzip_t = /* std::pair<FirstList, SecondList> */;

template <type_list List>
using reverse_t = /* ... */;

template <type_list List>
using flatten_t = /* element types of List must be type_list */;
```

**Example**

```cpp
template <typename L, typename R>
struct MakePair : std::type_identity<std::pair<L, R>> {};

using Pairs = zip_with_t<MakePair, from_pack_t<A, B>, from_pack_t<1, 2>>;
using Unzipped = unzip_t<Pairs>;
using Firsts = Unzipped::first_type;    // from_pack_t<A, B>
using Seconds = Unzipped::second_type;  // from_pack_t<1, 2>

using Nested = from_pack_t<from_pack_t<A, B>, from_pack_t<C>>;
using Flat = flatten_t<Nested>;  // from_pack_t<A, B, C>
```

---

## Module partitions

Umbrella module: `modules/type_list.cppm` → `import type_list;`

| Partition | File | Primary exports |
|-----------|------|-----------------|
| `type_list:types` | `types.cppm` | `nil`, `cons` |
| `type_list:type_list` | `type_list.cppm` | `type_list` concept |
| `type_list:empty` | `empty.cppm` | `empty` |
| `type_list:non_empty` | `non_empty.cppm` | `non_empty` |
| `type_list:size` | `size.cppm` | `size`, `size_v` |
| `type_list:front` | `front.cppm` | `front`, `front_t` |
| `type_list:back` | `back.cppm` | `back`, `back_t` |
| `type_list:pop_front` | `pop_front.cppm` | `pop_front`, `pop_front_t` |
| `type_list:pop_back` | `pop_back.cppm` | `pop_back`, `pop_back_t` |
| `type_list:push_front` | `push_front.cppm` | `push_front`, `push_front_t` |
| `type_list:push_back` | `push_back.cppm` | `push_back`, `push_back_t` |
| `type_list:insert` | `insert.cppm` | `insert`, `insert_t` |
| `type_list:concat` | `concat.cppm` | `concat`, `concat_t` |
| `type_list:from_pack` | `from_pack.cppm` | `from_pack`, `from_pack_t` |
| `type_list:map` | `map.cppm` | `map`, `map_t` |
| `type_list:filter` | `filter.cppm` | `filter`, `filter_t` |
| `type_list:fold_left` | `fold_left.cppm` | `fold_left`, `fold_left_t` |
| `type_list:fold_right` | `fold_right.cppm` | `fold_right`, `fold_right_t` |
| `type_list:zip` | `zip.cppm` | `zip`, `zip_t` |
| `type_list:zip_with` | `zip_with.cppm` | `zip_with`, `zip_with_t` |
| `type_list:unzip` | `unzip.cppm` | `unzip`, `unzip_t` |
| `type_list:reverse` | `reverse.cppm` | `reverse`, `reverse_t` |
| `type_list:flatten` | `flatten.cppm` | `flatten`, `flatten_t` |

---

## Tests and examples map

Each operation partition uses the same `<name>` stem in sources and CMake targets (`type_list_<name>_test`, `type_list_<name>_example`).

| `<name>` | Test | Example |
|----------|------|---------|
| `types` | `tests/types_test.cpp` | `examples/types_example.cpp` |
| `type_list` | `tests/type_list_test.cpp` | `examples/type_list_example.cpp` |
| `empty` | `tests/empty_test.cpp` | `examples/empty_example.cpp` |
| `size` | `tests/size_test.cpp` | `examples/size_example.cpp` |
| `front` | `tests/front_test.cpp` | `examples/front_example.cpp` |
| `back` | `tests/back_test.cpp` | `examples/back_example.cpp` |
| `pop_front` | `tests/pop_front_test.cpp` | `examples/pop_front_example.cpp` |
| `pop_back` | `tests/pop_back_test.cpp` | `examples/pop_back_example.cpp` |
| `push_front` | `tests/push_front_test.cpp` | `examples/push_front_example.cpp` |
| `push_back` | `tests/push_back_test.cpp` | `examples/push_back_example.cpp` |
| `insert` | `tests/insert_test.cpp` | `examples/insert_example.cpp` |
| `concat` | `tests/concat_test.cpp` | `examples/concat_example.cpp` |
| `from_pack` | `tests/from_pack_test.cpp` | `examples/from_pack_example.cpp` |
| `map` | `tests/map_test.cpp` | `examples/map_example.cpp` |
| `filter` | `tests/filter_test.cpp` | `examples/filter_example.cpp` |
| `fold_left` | `tests/fold_left_test.cpp` | `examples/fold_left_example.cpp` |
| `fold_right` | `tests/fold_right_test.cpp` | `examples/fold_right_example.cpp` |
| `zip` | `tests/zip_test.cpp` | `examples/zip_example.cpp` |
| `zip_with` | `tests/zip_with_test.cpp` | `examples/zip_with_example.cpp` |
| `unzip` | `tests/unzip_test.cpp` | `examples/unzip_example.cpp` |
| `reverse` | `tests/reverse_test.cpp` | `examples/reverse_example.cpp` |
| `flatten` | `tests/flatten_test.cpp` | `examples/flatten_example.cpp` |

The `non_empty` concept is covered in `type_list_test` / `type_list_example`; it has no dedicated partition test file.
