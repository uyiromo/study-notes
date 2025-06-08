# deque `<deque>`
- <https://en.cppreference.com/w/cpp/container/deque.html>
- 二重リンクリスト
- vector と異なり、拡張時のコストが安い


- **Definition**
  ```C++
  template<
      class T,
      class Allocator = std::allocator<T>
  > class deque;
  ```

- see: [./tests/deque.cpp](./tests/deque.cpp)


## Member types
- sequence container 参照


## Member functions
- sequence container 参照


## Element access
- sequence container 参照


## Iterators
- sequence container 参照


## Capacity
- sequence container 参照
- `shrink_to_fit` も使用可能


## Modifiers
- sequence container 参照
- `push_front`
  - 先頭に要素を copy/move する
  ```C++
  void push_front( const T& value );
  void push_front( T&& value );
  ```
- `emplace_front`
  - 先頭に要素を in-place で生成する
  ```C++
  template< class... Args >
  reference emplace_front( Args&&... args );
  ```
- `prepend_range (C++23)`
  - 先頭に range の要素を追加する
  ```C++
  template< container-compatible-range<T> R >
  constexpr void prepend_range( R&& rg );
  ```
- `pop_front`
  - 先頭の要素を削除する
  ```C++
  void pop_front();
  ```


## Non-member functions
- sequence container 参照
