# std::apply `<tuple>`
- <https://en.cppreference.com/w/cpp/utility/apply.html>
- 関数 `F` に対して tuple `T` の要素を分解して呼び出す
  - 関数 `F` は template の型推論は発生しない
  - lambda / 関数オブジェクトも指定可能

- **Definition**
  ```C++
  template< class F, tuple-like Tuple >
  constexpr decltype(auto) apply( F&& f, Tuple&& t ) noexcept(/*see below*/);
  ```

- see: [./tests/apply.cpp](./tests/apply.cpp)
