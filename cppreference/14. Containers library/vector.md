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
  - 要素を copy/move assign して、`*this` を返す
- assign
  - 値を先頭から指定個数埋めるか、別の vector からコピー
  - 値はコピーされる
- assign_range
  - range からコピー
- get_allocator


## Element access
- array と同じ


## Iterators
- array と同じ


## Capacity
- empty
- size
  - 現在格納されている要素数
- max_size
  - system / runtime によって決まる最大要素数
- reserve
  - capacity を増やし、必要ならメモリを再割り当てする
  - `size()` は増加しないため、範囲外アクセスに注意が必要
- capacity
  - 現在格納可能な最大要素数
- shrink_to_fit
  - `capacity()` を `size()` に合わせる
  - 実装依存で、必ずしもメモリを解放するとは限らない


## Modifiers
- clear
  - 要素を全削除して `size()` を 0 にする
- insert
  - `const_iterator pos` の位置に要素を挿入
- insert_range
  - `const_iterator pos` の位置に range から要素を move で挿入
- emplace
  - `const_iterator pos` の位置に要素を直接構築
- erase
  - iterator の位置/範囲の要素を削除して、後ろの要素を前に詰める
- push_back
  - 値を末尾に copy or move で追加
- emplace_back
  - 値を末尾に直接構築して追加
- append_range
  - 末尾に range から要素を move で追加
- pop_back
  - 末尾の要素を削除
- resize
  - size を切り詰める or 拡張する
  - capacity は変化しない
- swap


## Non-member functions
- operator== / operator <=>
- std::swap
- std::erase / std::erase_if
  - 指定した値や条件 (Unary Pred) に合致する要素を削除

