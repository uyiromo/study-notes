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
- `assign`
  - コンテナの要素を指定値で埋める
  ```C++
  // n 個の value で埋める
  void assign(size_type n, const T& value);

  // range [first, last) の要素で埋める
  template< class InputIt >
  void assign(InputIt first, InputIt last);

  // initializer_list で埋める
  void assign(std::initializer_list<T> ilist);
  ```
- `assign_range (C++23)`
  - コンテナの要素を range で埋める
  ```C++
  template< container-compatible-range<T> R >
  constexpr void assign_range( R&& rg );
  ```


### Element Access
- at
  - 要素の参照を返す。範囲外アクセス時は `std::out_of_range` 例外を投げる
  ```C++
  reference at( size_type pos );
  const_reference at( size_type pos ) const;
  ```
- operator[]
  - 要素の参照を返す。範囲外アクセス時は未定義動作
  ```C++
  reference operator[]( size_type pos );
  const_reference operator[]( size_type pos ) const;
  ```
- front
  - 最初の要素の参照を返す。empty の場合は未定義動作
  ```C++
  reference front();
  const_reference front() const;
  ```
- back
  - 最後の要素の参照を返す。empty の場合は未定義動作
  ```C++
  reference back();
  const_reference back() const;
  ```
- data
  - 要素のポインタを返す
  ```C++
  pointer data();
  const_pointer data() const;
  ```


### Iterators
- `begin` / `end` / `cbegin` / `cend`
  - コンテナの先頭と末尾のイテレータを返す
  ```C++
  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;

  iterator end();
  const_iterator end() const;
  const_iterator cend() const;
  ```
- `rbegin` / `rend` / `crbegin` / `crend`
  - コンテナの末尾と先頭の逆イテレータを返す
  ```C++
  reverse_iterator rbegin();
  const_reverse_iterator rbegin() const;
  const_reverse_iterator crbegin() const;

  reverse_iterator rend();
  const_reverse_iterator rend() const;
  const_reverse_iterator crend() const;
  ```


### Capacity
- `empty`
  - コンテナが空かどうかを返す
  ```C++
  bool empty() const;
  ```
- `size`
  - コンテナが保持している要素数を返す
  ```C++
  size_type size() const;
  ```
- `max_size`
  - コンテナが保持可能な最大要素数を返す
  ```C++
  size_type max_size() const;
  ```


## Modifiers
- `clear`
  - コンテナの要素を全て削除する
  ```C++
  void clear();
  ```
- `insert`
  - 指定位置に要素を挿入する
  ```C++
  // pos の前にコピー
  iterator insert(const_iterator pos, const T& value);

  // pos の前にムーブ
  iterator insert(const_iterator pos, T&& value);

  // pos の前に n 個コピー
  iterator insert(const_iterator pos, size_type count, const T& value);

  // pos の前に range から move
  template< class InputIt >
  iterator insert(const_iterator pos, InputIt first, InputIt last);

  // pos の前に initializer_list からコピー
  iterator insert(const_iterator pos, std::initializer_list<T> ilist);
  ```
- `insert_range (C++23)`
  - 指定位置に range から要素を挿入する
  ```C++
  template< container-compatible-range<T> R >
  constexpr iterator insert_range( const_iterator pos, R&& rg );
  ```
- `emplace`
  - 指定位置に要素を構築する
  ```C++
  // pos の前に要素を構築
  template< class... Args >
  iterator emplace(const_iterator pos, Args&&... args);
  ```
- `erase`
  - 指定位置の要素を削除する
  ```C++
  // pos の前の要素を削除
  iterator erase(const_iterator pos);

  // [first, last) の要素を削除
  iterator erase(const_iterator first, const_iterator last);
  ```
- `push_back`
  - 要素を末尾に追加する
  ```C++
  void push_back(const T& value);
  void push_back(T&& value);
  ```
- `emplace_back`
  - 要素を末尾に構築する
  ```C++
  template< class... Args >
  reference emplace_back(Args&&... args);
  ```
- `append_range (C++23)`
  - range から要素を末尾に追加/moveする
  ```C++
  template< container-compatible-range<T> R >
  constexpr void append_range( R&& rg );
  ```
- `pop_back`
  - 末尾の要素を削除する
  ```C++
  void pop_back();
  ```
- `resize`
  - コンテナのサイズを変更する。capacity は変化しない
  ```C++
  // 新しいサイズに合わせて要素を追加/削除
  void resize(size_type count);

  // 新しいサイズに合わせて要素を追加/削除し、初期値で埋める
  void resize(size_type count, const T& value);
  ```
