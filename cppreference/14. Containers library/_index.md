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

| function         | array | vector    | inplace_vector   | deque  | forward_list   | list  |
| ---------------- | ----- | --------- | ---------------- | ------ | -------------- | ----- |
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
- Key の重複を許容しない
  - unordered_set
  - unordered_map
- Key の重複を許容する
  - unordered_multiset
  - unordered_multimap


<!-- markdownlint-disable-next-line -->
### Member types

| Member type            | Definition                                        |
| ---------------------- | ------------------------------------------------- |
| `key_type`             | key の型                                          |
| `value_type`           | value の型 (set なら `key_type` と同じ)           |
| `size_type`            | `std::size_t`                                     |
| `difference_type`      | `std::ptrdiff_t`                                  |
| `hasher`               | ハッシュ関数の型                                  |
| `key_equal`            | キーの等価比較関数の型                            |
| `allocator_type`       | アロケータの型                                    |
| `reference`            | `value_type&`                                     |
| `const_reference`      | `const value_type&`                               |
| `pointer`              | `std::allocator_traits<Allocator>::pointer`       |
| `const_pointer`        | `std::allocator_traits<Allocator>::const_pointer` |
| `iterator`             | `LegacyForwardIterator for value_type`            |
| `const_iterator`       | `LegacyForwardIterator for const value_type`      |
| `local iterator`       | (bucket 内のイテレータ)                           |
| `const_local_iterator` | (bucket 内の const イテレータ)                    |
| `node_type`            | (TBD)                                             |
| `insert_return_type`   | node_type を insert したときの返り値              |


<!-- markdownlint-disable-next-line -->
### Iterators

| function       | unordered_set | unordered_map | unordered_multiset | unordered_multimap |
| -------------- | ------------- | ------------- | ------------------ | ------------------ |
| begin / cbegin | ✅             | ✅             | ✅                  | ✅                  |
| end / cend     | ✅             | ✅             | ✅                  | ✅                  |


<!-- markdownlint-disable-next-line -->
### Capacity

| function      | unordered_set | unordered_map | unordered_multiset | unordered_multimap |
| ------------- | ------------- | ------------- | ------------------ | ------------------ |
| empty         | ✅             | ✅             | ✅                  | ✅                  |
| size          | ✅             | ✅             | ✅                  | ✅                  |
| max_size      | ✅             | ✅             | ✅                  | ✅                  |

<!-- markdownlint-disable-next-line -->
### Modifiers
- `insert` は要素に加えて `::node_type` を指定可能
- `extract` は Key を指定して `::node_type` を取り出す
  - 要素の所有権を持つ
  -


| function     | unordered_set | unordered_map | unordered_multiset | unordered_multimap |
| ------------ | ------------- | ------------- | ------------------ | ------------------ |
| clear        | ✅             | ✅             | ✅                  | ✅                  |
| insert       | ✅             | ✅             | ✅                  | ✅                  |
| insert_range | ✅             | ✅             | ✅                  | ✅                  |
| emplace      | ✅             | ✅             | ✅                  | ✅                  |
| emplace_hint | ✅             | ✅             | ✅                  | ✅                  |
| erase        | ✅             | ✅             | ✅                  | ✅                  |
| swap         | ✅             | ✅             | ✅                  | ✅                  |
| extract      | ✅             | ✅             | ✅                  | ✅                  |
| merge        | ✅             | ✅             | ✅                  | ✅                  |


### Lookup
- `at` は `T&` を返す。存在しない場合は `std::out_of_range`
- `operator[]` は `T&` を返す。存在しない場合は value を default construct する。Key は引数に応じて copy/move


| function    | unordered_set | unordered_map | unordered_multiset | unordered_multimap |
| ----------- | ------------- | ------------- | ------------------ | ------------------ |
| count       | ✅             | ✅             | ✅                  | ✅                  |
| find        | ✅             | ✅             | ✅                  | ✅                  |
| contains    | ✅             | ✅             | ✅                  | ✅                  |
| equal_range | ✅             | ✅             | ✅                  | ✅                  |
| at          | ❌             | ✅             | ❌                  | ✅                  |
| operator[]  | ❌             | ✅             | ❌                  | ✅                  |


### Bucket interface / Hash policy / Observers / Non-member functions 省略


## Container adaptors
- Sequence container のインターフェイスを用途に合わせるもの
- `stack`
  - LIFO
  - Container の末尾の要素を操作できるコンテナを使用可能
    - `std::deque`
    - `std::vector`
    - `std::inplace_vector`
- `queue`
  - FIFO
  - Container の先頭と末尾の要素を操作できるコンテナを使用可能
    - `std::deque`
    - `std::vector`
    - `std::inplace_vector`
- `priority_queue`
  - 要素がソートされたキュー
  - **`.top()` の返り値が必ず const_reference である**
    - つまり、move で要素を移動できない
  - Container の末尾の要素を操作できるコンテナを使用可能
    - `std::deque`
    - `std::vector`
    - `std::inplace_vector`
- `flat_set`
  - 要素がソートされた set
  - `std::set` / `std::unordered_set` と異なり、メモリ連続なコンテナを使用する
  - 使用可能なコンテナ
    - `std::vector`
    - `std::inplace_vector`
- `flat_map`
  - `flat_set` に同じ
- `flat_multiset`
  - `flat_set` に同じ
- `flat_multimap`
  - `flat_set` に同じ

- `flat_*` は TBD
