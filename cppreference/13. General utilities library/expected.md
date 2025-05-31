# expected `<expected>`
- <https://en.cppreference.com/w/cpp/utility/expected.html>
- <https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p0323r12.html>
- expected value `T` もしくは unexpected value `E` を保持する型
  - 関数の返り値として用いる
  - 例外を投げる代わりに、エラーを返す
- `expected` は、参照、関数は保持できない


- **Definition**
  ```C++
  template< class T, class E >
  class expected;

  template< class T, class E >
      requires std::is_void_v<T>
  class expected<T, E>;
  ```

- see: [./tests/expected.cpp](./tests/expected.cpp)


## Member functions
- `expected` 自体の copy/move は、内包する型 `T` `E` の copy/move を行う
- (constructor)
- (destructor)
- operator=


## Observers
- operator-> / operator*
  - `T*` もしくは `T&` を返す
  - const と lvalue/rvalue reference は引数に依存
- operator bool / has_value
  - `T` が有効な要素を持つ場合に true を返す
  - 全く値を持たない場合も true
- value
  - `T&` `const T&` `T&&` を返す
  - `T` が有効な値を持たない場合は例外 `bad_expected_access` を投げる
- error
  - `E&` `const E&` `E&&` を返す
  - `E` が有効な値を持たない場合は UB
- value_or
  - 有効な値を持つ場合、`T` を返す
  - 有効な値を持たない場合、Forwarding Reference から `T` を生成して返す
    - つまり、`T` に変換可能な型
- error_or
  - 有効な値を持つ場合、`E` を返す
  - 有効な値を持たない場合、Forwarding Reference から `E` を生成して返す
    - つまり、`E` に変換可能な型


## Monadic operations
- and_then
  - `*this` が有効なら、関数 `F(*this)` を `T` に持つ型を返す
  - `*this` が無効なら、`E` を持つ型を返す
  - 関数 `F` の返り値は、`expected<T, E>` である必要がある
- transform
  - and_then と同じだが、関数 `F` が `expected` を返す必要はない
- or_else
  - `*this` が有効なら、`*this` を返す
  - `*this` が無効なら、関数 `F(error())` を呼び出して返す
  - 関数 `F` の返り値は、`expected<T, E>` である必要がある
- transform_error
  - or_else と同じだが、関数 `F` が `expected` を返す必要はない


## Modifiers
- emplace
  - `T` を直接構築して、`T&` を返す
- swap
  - `T` と `E` を入れ替える


## Non-member functions
- operator==
  - `*this` 同士、`error()` 同士を比較する
- swap


## Helper classes
- unexpected
  - `E` を保持する型
- bad_expected_access
  - `expected` の値を取得しようとしたが、値が無い場合に投げられる例外
  - `std::bad_expected_access<T>` は、`T` の型を保持する
  - `std::bad_expected_access<E>` は、`E` の型を保持する
  - `std::bad_expected_access<void>` は、`void` を保持する
- unexpect / unexpect_t
  - `E` を直接構築するためのタグ型
