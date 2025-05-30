# optional `<optional>`
- <https://en.cppreference.com/w/cpp/utility/optional.html>
- 値を保持しているかもしれない型
- optional は、参照、関数、配列、void は保持できない

- see: [./tests/optional.cpp](./tests/optional.cpp)


## Template parameters
- `T`
  - 値の型
  - Destructible


## Nested types
- `value_type` = `T`


## Data members
- `T* val`


## Member functions
- (constructor)
- (destructor)
- operator=


## Iterators
- TODO


## Observers
- operator-> / operator*
  - `->` は pointer を返す
  - `*` は reference を返す
  - 値を持っていない場合、UB
- operator bool / has_value
  - 値を持っていれば true
- value
  - 値を持っていない場合、`std::bad_optional_access`
- value_or
  - 値を持っていない場合、デフォルト値を返す
  ```C++
  template< class U = std::remove_cv_t<T> >
  constexpr T value_or( U&& default_value ) const&;
  ```


## Monadic operations
- and_then
  - 値を持つ場合、関数に値を渡して結果 optional で返す
  - 値を持たない場合、関数の返り値の型を持つ空の optional を返す
  ```C++
  template< class F >
  constexpr auto and_then( F&& f ) &;
  ```
- transform
  - `and_then` と同じだが、関数 `F` が optional を返す必要はない
- or_else
  - 値を持つ場合、その値を返す
  - 値を持たない場合、`F` の呼び出し結果を返す
    - `std::remove_cvref_t<std::invoke_result_t<F>>` が `std::optional<T>` でない場合は ill-formed
  ```C++
  template< class F >
  constexpr optional or_else( F&& f ) const&;
  ```


## Modifiers
- swap
  - 値を交換する
  - MoveCtor と MoveAssign が必要
- reset
  - 値を解放して destruct する
- emplace
  - 値を直接構築して、構築した要素の参照を返す
  - `std::optional<T>(T())` は値を move するので、MoveCtor が必要


## Non-member functions
- operator==
- make_optional
  - `std::decay<T>` もしくは `T` を完全転送で直接構築
- std::swap
