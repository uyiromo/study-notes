# std::vector `<vector>`
- <https://en.cppreference.com/w/cpp/container/vector.html>

- 可変長コンテナで、ランダムアクセスを O(1) で可能
- `std::vector<bool>` 特殊化を除き、データが必ず連続して配置される (contiguous)
- 割り当て済みメモリ情報は `capacity()` で取得可能
  - 余計なメモリは `shrink_to_fit()` で解放可能
  - `reserve()` であらかじめメモリを確保できる

- **Definition**
  ```C++
  template<
      class T,
      class Allocator = std::allocator<T>
  > class vector;
  ```
  - `T[N]` を定義できるような型は取れる。つまり、参照型は取れない

- see: [./tests/vector.cpp](./tests/vector.cpp)


## Member types
- array と同じなので省略


## Member functions
- (constructor)
- (destructor)
- operator=
- assign
- assign_range
- get_allocator


## Element access
- array と同じ


## Iterators
- array と同じ


## Capacity
- empty
- size
- max_size
- reserve
  - capacity を増やし、必要ならメモリを再割り当てする
  - `size()` は増加しないため、範囲外アクセスに注意が必要
- capacity
- shrink_to_fit
  - `capacity()` を `size()` に合わせる
  - 実装依存で、必ずしもメモリを解放するとは限らない


## Modifiers
- clear
- insert
- insert_range
- emplace
- erase
- push_back
- emplace_back
- append_range
- pop_back
- resize
- swap


## Non-member functions
- operator== / operator <=>
- std::swap
- std::erase / std::erase_if
  - 指定した値や条件 (Unary Pred) に合致する要素を削除

