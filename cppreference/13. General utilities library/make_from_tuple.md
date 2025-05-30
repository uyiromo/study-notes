# make_from_tuple `<tuple>`
- <https://en.cppreference.com/w/cpp/utility/make_from_tuple.html>
- tuple の要素を分解して型のコンストラクタに渡す
  - 各要素は `std::get` しているため、型は tuple の cv LR に依存

- **Definition**
  ```C++
  template< class T, tuple-like Tuple >
  constexpr T make_from_tuple( Tuple&& t );
  ```

- see: [./tests/make_from_tuple.cpp](./tests/make_from_tuple.cpp)
