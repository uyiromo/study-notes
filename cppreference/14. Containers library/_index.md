# Container Library
- <https://en.cppreference.com/w/cpp/container.html>


## Sequence containers
- 要素を sequence にアクセス可能なコンテナ
  - `std::array`
  - `std::vector`
  - `std::inplace_vector`
  - `std::hive`
  - `std::deque`
  - `std::forward_list`
  - `std::list`


### Member types

| Member type              | Definition                                   |
| ------------------------ | -------------------------------------------- |
| `value_type`             | `T`                                          |
| `size_type`              | `std::size_t`                                |
| `difference_type`        | `std::ptrdiff_t`                             |
| `reference`              | `value_type&`                                |
| `const_reference`        | `const value_type&`                          |
| `pointer`                | `value_type*`                                |
| `const_pointer`          | `const value_type*`                          |
| `iterator`               | `std::contiguous_iterator<value_type>`       |
| `const_iterator`         | `std::contiguous_iterator<const value_type>` |
| `reverse_iterator`       | `std::reverse_iterator<iterator>`            |
| `const_reverse_iterator` | `std::reverse_iterator<const_iterator>`      |


### Member functions

| function     | array | vector | inplace_vector | deque | forward_list | list |
| ------------ | ----- | ------ | -------------- | ----- | ------------ | ---- |
| assign       | ❌     | ✅      | ✅              | ✅     | ❌            | ✅    |
| assign_range | ❌     | ✅      | ✅              | ✅     | ❌            | ✅    |


### Element access

| function   | array | vector | inplace_vector | deque | forward_list | list |
| ---------- | ----- | ------ | -------------- | ----- | ------------ | ---- |
| at         | ✅     | ✅      | ✅              | ✅     | ❌            | ❌    |
| operator[] | ✅     | ✅      | ✅              | ✅     | ❌            | ❌    |
| front      | ✅     | ✅      | ✅              | ✅     | ✅            | ✅    |
| back       | ✅     | ✅      | ✅              | ✅     | ❌            | ✅    |
| data       | ✅     | ✅      | ✅              | ❌     | ❌            | ❌    |


### Iterators

| function         | array | vector | inplace_vector | deque | forward_list | list |
| ---------------- | ----- | ------ | -------------- | ----- | ------------ | ---- |
| begin / cbegin   | ✅    | ✅      | ✅              | ✅     | ✅            | ✅    |
| end / cend       | ✅    | ✅      | ✅              | ✅     | ✅            | ✅    |
| rbegin / crbegin | ✅    | ✅      | ✅              | ✅     | ❌            | ✅    |
| rend / crend     | ✅    | ✅      | ✅              | ✅     | ❌            | ✅    |


### Capacity

| function      | array | vector | inplace_vector | deque | forward_list | list |
| ------------- | ----- | ------ | -------------- | ----- | ------------ | ---- |
| empty         | ✅     | ✅      | ✅              | ✅     | ✅            | ✅    |
| size          | ✅     | ✅      | ✅              | ✅     | ❌            | ✅    |
| max_size      | ✅     | ✅      | ✅              | ✅     | ✅            | ✅    |
| reserve       | ❌     | ✅      | ✅              | ❌     | ❌            | ❌    |
| capacity      | ❌     | ✅      | ✅              | ❌     | ❌            | ❌    |
| resize        | ❌     | ✅      | ✅              | ❌     | ❌            | ✅    |
| shrink_to_fit | ❌     | ✅      | ✅              | ✅     | ❌            | ❌    |


### Modifiers

| function         | array | vector | inplace_vector | deque | forward_list | list |
| ---------------- | ----- | ------ | -------------- | ----- | ------------ | ---- |
| fill             | ✅     | ❌      | ❌              | ❌     | ❌            | ❌    |
| clear            | ❌     | ✅      | ✅              | ✅     | ✅            | ✅    |
| erase            | ❌     | ✅      | ✅              | ✅     | ❌            | ✅    |
| insert           | ❌     | ✅      | ✅              | ✅     | ❌            | ✅    |
| insert_range     | ❌     | ✅      | ✅              | ✅     | ❌            | ✅    |
| emplace          | ❌     | ✅      | ✅              | ✅     | ❌            | ✅    |
| emplace_back     | ❌     | ✅      | ✅              | ✅     | ❌            | ❌    |
| push_back        | ❌     | ✅      | ✅              | ✅     | ❌            | ❌    |
| append_range     | ❌     | ✅      | ✅              | ✅     | ❌            | ❌    |
| pop_back         | ❌     | ✅      | ✅              | ✅     | ❌            | ❌    |
| push_front       | ❌     | ❌      | ❌              | ✅     | ✅            | ✅    |
| emplace_front    | ❌     | ❌      | ❌              | ✅     | ✅            | ✅    |
| prepend_range    | ❌     | ❌      | ❌              | ✅     | ✅            | ✅    |
| pop_front        | ❌     | ❌      | ❌              | ✅     | ✅            | ✅    |

- 挿入系操作は、iterator `pos` の**前**に要素を挿入する
- forward_list はiterator の前の要素を取得できないため、`insert_after` 系の関数を使用する
  - `insert_after`
  - `emplace_after`
  - `insert_range_after`
  - `erase_after`


## Associative containers
- Tree を用いて探索を O(log n) で行えるコンテナ
- (TBD)


## Unordered associative containers
- ハッシュテーブルを用いて探索を平均で O(1) で行えるコンテナ
- unordered_set
- unordered_map
- unordered_multiset
- unordered_multimap


<!-- markdownlint-disable-next-line -->
### Member types

| Member type          | Definition                                        |
| -------------------- | ------------------------------------------------- |
| `key_type`           | key の型                                          |
| `value_type`         | value の型 (set なら `key_type` と同じ)           |
| `size_type`          | `std::size_t`                                     |
| `difference_type`    | `std::ptrdiff_t`                                  |
| `hasher`             | ハッシュ関数の型                                  |
| `key_equal`          | キーの等価比較関数の型                            |
| `allocator_type`     | アロケータの型                                    |
| reference            | `value_type&`                                     |
| const_reference      | `const value_type&`                               |
| pointer              | `std::allocator_traits<Allocator>::pointer`       |
| const_pointer        | `std::allocator_traits<Allocator>::const_pointer` |
| iterator             | `LegacyForwardIterator for value_type`            |
| const_iterator       | `LegacyForwardIterator for const value_type`      |
| local iterator       | (bucket 内のイテレータ)                           |
| const_local_iterator | (bucket 内の const イテレータ)                    |
| node_type            | (TBD)                                             |
| insert_return_type   | node_type を insert したときの返り値              |


## Container adaptors
