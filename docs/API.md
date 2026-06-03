# API reference

All operations are compile-time. Import:

```cpp
import type_list;
```

## Core types

- **`Nil`** — empty list.
- **`Cons<Head, Tail>`** — cell; `Tail` must satisfy `type_list`.
- **`type_list<T>`** — `true` for `Nil` or well-formed `Cons`.
- **`non_empty_type_list<T>`** — `type_list<T> and not same_as<T, Nil>`.

## Building lists

```cpp
using L = from_pack_t<int, char, void>;  // Cons<int, Cons<char, Cons<void, Nil>>>
using E = from_pack_t<>;                 // Nil
```

Template alias over a pack:

```cpp
template <typename... Ts>
using list_t = from_pack_t<Ts...>;
```

## Queries

| Alias | Semantics |
|-------|-----------|
| `is_nil_v<List>` | `true` iff `List` is `Nil` |
| `length_v<List>` | element count (`size_t`) |
| `head_t<List>` | first type (`non_empty_type_list`) |
| `tail_t<List>` | rest (`non_empty_type_list`) |

## Single-element insert

| Alias | Order |
|-------|--------|
| `prepend_t<Elem, List>` | front |
| `append_t<List, Elem>` | back |

## List algebra

| Alias | Semantics |
|-------|-----------|
| `concat_t<Lhs, Rhs>` | append all of `Rhs` after `Lhs` |
| `flatten_t<List>` | list of lists → one list; non-list heads stay as cells |

## Higher-order

**Map** — unary type alias template `Op`:

```cpp
template <typename T>
using Op = T*;

using Out = map_t<Op, from_pack_t<int, char>>;
```

**Filter** — predicate class template with `static constexpr bool value` (via `integral_constant`):

```cpp
template <typename T>
struct is_int : integral_constant<bool, same_as<T, int>> {};

using Out = filter_t<is_int, from_pack_t<int, char, int>>;
```

**Fold** — binary metafunction class `F` with nested `type`:

```cpp
template <typename Acc, typename Elem>
struct append_type {
    using type = concat_t<Acc, from_pack_t<Elem>>;
};

using Out = fold_left_t<Nil, append_type, from_pack_t<int, char>>;
```

`fold_right_t` folds from the right with the same `F` shape.

**Zip** — pairs heads with `std::pair`; stops at the shorter list:

```cpp
using Z = zip_t<from_pack_t<int, char>, from_pack_t<float, double, void>>;
// Cons<pair<int,float>, Cons<pair<char,double>, Nil>>
```

**Reverse**

```cpp
using R = reverse_t<from_pack_t<int, char, void>>;
```

## Module partitions

Implementation lives under `modules/type_list/*.cppm`, aggregated by `modules/type_list.cppm`. Only `:std` uses `#include`; other partitions `import` siblings.
