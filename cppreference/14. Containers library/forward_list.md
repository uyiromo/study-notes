# forward_list `<forward_list>`
- <https://en.cppreference.com/w/cpp/container/forward_list.html>
- 単方向リスト
  - `std::list` よりメモリ効率が良い


- **Definition**
  ```C++
  template<
      class T,
      class Allocator = std::allocator<T>
  > class forward_list;
  ```

- see: [./tests/forward_list.cpp](./tests/forward_list.cpp)


## Member types
- sequence container 参照


## Member functions
- sequence container 参照


## Element access
- `front` のみ


## Iterators
- `begin` / `cbegin` / `end` / `cend`
- `before_begin` / `cbefore_begin`
  - 先頭要素の前を指すイテレータを返す
  - **deref 不可**
  ```C++
  iterator before_begin();
  const_iterator before_begin() const;
  const_iterator cbefore_begin();
  ```


## Modifiers
- sequence container 参照
- `insert_after`
  - `pos` の次に要素を挿入する
  ```C++
  iterator insert_after( const_iterator pos, const T& value );

  iterator insert_after( const_iterator pos, T&& value );

  iterator insert_after( const_iterator pos, size_type n, const T& value );

  template< class InputIt >
  iterator insert_after( const_iterator pos, InputIt first, InputIt last );

  iterator insert_after( const_iterator pos, std::initializer_list<T> ilist );
  ```
- `emplace_after`
  - `pos` の次に要素を in-place で生成する
  ```C++
  template< class... Args >
  iterator emplace_after( const_iterator pos, Args&&... args );
  ```
- `insert_after_range (C++23)`
  - `pos` の次に range の要素を挿入する
  ```C++
  template< container-compatible-range<T> R >
  constexpr iterator insert_after_range( const_iterator pos, R&& rg );
  ```
- `erase_after`
  - `pos` の次の要素を削除する
  ```C++
  iterator erase_after( const_iterator pos );

  iterator erase_after( const_iterator first, const_iterator last );
  ```


## Operations
- `merge`
  - リストをマージして、一つのソートされたリストにする
  - `comp` に対してソートされていないリスト同士は UB
  ```C++
  // merge(other, std::less<>()) に同じ
  void merge( forward_list& other );
  void merge( forward_list&& other );

  template< class Compare >
  void merge( forward_list& other, Compare comp );
  template< class Compare >
  void merge( forward_list&& other, Compare comp );
  ```
- `splice_after`
  - `pos` の次に `other` の要素を挿入する

  ```C++
  // other の全要素
  void splice_after( const_iterator pos, forward_list& other );
  void splice_after( const_iterator pos, forward_list&& other );

  // other の [it, other.end()) の要素
  void splice_after( const_iterator pos, forward_list& other, const_iterator it );
  void splice_after( const_iterator pos, forward_list&& other, const_iterator it );

  // other の [first, last) の要素
  void splice_after( const_iterator pos, forward_list& other, const_iterator first, const_iterator last );
  void splice_after( const_iterator pos, forward_list&& other, const_iterator first, const_iterator last );
  ```
- `remove` / `remove_if`
- `reverse`
  - リストの要素を逆順にする
  ```C++
  void reverse();
  ```
- `unique`
  - **連続する**同じ値を削除する
  ```C++
  size_type unique();

  template< class BinaryPredicate >
  size_type unique( BinaryPredicate p );
  ```
- `sort`
  - リストをソートする
  ```C++
  // std::less<>() による昇順ソート
  void sort();

  template< class Compare >
  void sort( Compare comp );
  ```

