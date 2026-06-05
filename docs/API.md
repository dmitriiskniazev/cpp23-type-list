# API reference

All operations are compile-time. Import the module and qualify symbols with `type_list::`:

```cpp
import std;
import type_list;
```

## Core types

- **`type_list::nil`** — empty list.
- **`type_list::cons<head, tail>`** — cell; `tail` must satisfy `type_list::type_list`.
- **`type_list::type_list<type>`** — `true` for `nil` or well-formed `cons`.
- **`type_list::non_empty<type>`** — `type_list::type_list<type> and not std::same_as<type, type_list::nil>`.
- **`type_list::empty<type>`** — `true` iff `type` is `type_list::nil`.

## Building lists

```cpp
struct Fst;
struct Snd;
struct Trd;

using List = type_list::from_pack_t<Fst, Snd, Trd>;
using EmptyList = type_list::from_pack_t<>;  // type_list::nil
```

Template alias over a pack:

```cpp
template <typename... Types>
using ListT = type_list::from_pack_t<Types...>;
```

## Queries

| Alias | Semantics |
|-------|-----------|
| `type_list::empty<list>` | `true` iff `list` is `type_list::nil` |
| `type_list::size_v<list>` | element count (`size_t`) |
| `type_list::front_t<list>` | first type (`non_empty`) |
| `type_list::back_t<list>` | last type (`non_empty`) |
| `type_list::pop_front_t<list>` | list without first element (`non_empty`) |
| `type_list::pop_back_t<list>` | list without last element (`non_empty`) |

## Single-type insert

| Alias | Semantics |
|-------|-----------|
| `type_list::push_front_t<type, list>` | insert at front |
| `type_list::push_back_t<list, type>` | insert at back |
| `type_list::insert_t<list, index, type>` | insert at compile-time index |

## List algebra

| Alias | Semantics |
|-------|-----------|
| `type_list::concat_t<left, right>` | push all of `right` after `left` |
| `type_list::flatten_t<list>` | list of lists → one list; non-list heads stay as cells |

## Higher-order

**map** — unary metafunction `unary_op`:

```cpp
template <typename Type>
struct Boxed;

template <typename Type>
using Box = Boxed<Type>;

using List = type_list::from_pack_t<Fst, Snd, Trd>;
using MappedList = type_list::map_t<Box, List>;
using ExpectedList = type_list::from_pack_t<Boxed<Fst>, Boxed<Snd>, Boxed<Trd>>;
```

**filter** — unary metafunction `unary_op` with `static constexpr bool value` (via `std::integral_constant`):

```cpp
template <typename Type>
struct Keep : std::integral_constant<bool, std::same_as<Type, Fst> or std::same_as<Type, Snd>> {};

using List = type_list::from_pack_t<Fst, Trd, Snd>;
using FilteredList = type_list::filter_t<Keep, List>;
using ExpectedList = type_list::from_pack_t<Fst, Snd>;
```

**Fold** — binary metafunction `binary_op` inheriting `std::type_identity`:

```cpp
template <typename Accumulator, typename Elem>
struct PushBackOne : std::type_identity<type_list::push_back_t<Accumulator, Elem>> {};

using EmptyList = type_list::nil;
using SourceList = type_list::from_pack_t<Fst, Snd>;
using FoldedList = type_list::fold_left_t<EmptyList, PushBackOne, SourceList>;
```

`type_list::fold_right_t` folds from the right with the same `binary_op` shape.

**zip** — pairs heads with `std::pair`; stops at the shorter list:

```cpp
using FirstList = type_list::from_pack_t<Fst, Snd>;
using SecondList = type_list::from_pack_t<Alpha, Beta>;
using ZippedList = type_list::zip_t<FirstList, SecondList>;
// type_list::cons<std::pair<Fst, Alpha>, type_list::cons<std::pair<Snd, Beta>, type_list::nil>>
```

**zip_with** — same rule as `zip` (shorter list wins); element type from `binary_op` (`typename binary_op<Left, Right>::type` via `std::type_identity`):

```cpp
template <typename Left, typename Right>
struct MakePair : std::type_identity<std::pair<Left, Right>> {};

using FirstList = type_list::from_pack_t<Fst, Snd>;
using SecondList = type_list::from_pack_t<Alpha, Beta>;
using ZippedList = type_list::zip_with_t<MakePair, FirstList, SecondList>;
```

**unzip** — split a list of `std::pair` into a `std::pair` of type lists:

```cpp
using FirstList = type_list::from_pack_t<Fst, Snd>;
using SecondList = type_list::from_pack_t<Alpha, Beta>;
using ZippedList = type_list::zip_t<FirstList, SecondList>;

using Unzipped = type_list::unzip_t<ZippedList>;
using UnzippedFirst = Unzipped::first_type;
using UnzippedSecond = Unzipped::second_type;
```

**reverse**

```cpp
using List = type_list::from_pack_t<Fst, Snd, Trd>;
using ReversedList = type_list::reverse_t<List>;
```

## Template parameter conventions

Library metafunctions use lowercase template parameter names (`list`, `type`, `left`, `right`, …). In `examples/` and `tests/`, user-defined types and template parameters use **PascalCase** (`List`, `Type`, `Boxed`, `MakePair`, …).

| Parameter | Role |
|-----------|------|
| `list`, `left`, `right` | type-list operands |
| `head`, `tail` | `cons` cell (type template parameters on `cons`) |
| `front_type`, `tail` | destructure a `cons` list in algorithms |
| `type` | single type to insert (`push_front`, `push_back`, `insert`) |
| `index` | compile-time position for `insert_t` |
| `init` | fold initial value |
| `accumulator`, `elem` | fold step arguments (`binary_op` inherits `std::type_identity`) |
| `unary_op` | `template <typename> typename` transform for `map`; trait with `::value` for `filter` |
| `binary_op` | `template <typename, typename> typename` step for folds and `zip_with` (inherits `std::type_identity`; use `Left`/`Right` or `Accumulator`/`Elem` in consumer code) |
| `nested` | nested list head in `flatten` |

## Module partitions

Implementation lives under `modules/type_list/` — one `.cppm` per partition. `modules/type_list.cppm` re-exports all of them.

| Partition | Contents |
|-----------|----------|
| `:types` | `nil`, `cons` |
| `:type_list` | `type_list` concept |
| `:empty`, `:non_empty`, `:size` | predicates and `size_v` |
| `:front`, `:back`, `:pop_front`, `:pop_back` | element access |
| `:push_front`, `:push_back`, `:insert`, `:concat`, `:from_pack` | construction |
| `:map`, `:filter`, `:fold_left`, `:fold_right` | transforms |
| `:zip`, `:zip_with`, `:unzip`, `:reverse`, `:flatten` | combine |

Partitions use `import std` and qualify standard types with `std::`.
