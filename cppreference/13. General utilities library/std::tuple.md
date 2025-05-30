# `std::tuple` `<tuple>`
- <https://en.cppreference.com/w/cpp/utility/tuple.html>
- 任意の定数個数の型を保持するクラス
- shape が型名になるため、個数・型などは compile-time に決定されなければならない

- **Definition**
  ```C++
  template< class... Types >
  struct tuple;
  ```

- see: [tuple.cpp](../tests/tuple.cpp)


## Member functions
- `(constructor)`
- `operator=`
- `swap`
  - 同じ型の要素を持つ `tuple` 同士は交換可能


## Non-member functions
- 各関数で、引数の tuple の要素型がどうなるか

  | Function         | `T&` | `T&&` | `const T&` | `const T&&` |
  | ---------------- | ---- | ----- | ---------- | ----------- |
  | make_tuple       | T    | T     | T          | T           |
  | tie              | T&   | T&    | const T&   | const T&    |
  | forward_as_tuple | T&   | T&&   | const T&   | -           |


- `make_tuple`
  - `std::decay` を適用した型の `tuple` を生成
  - rvalue reference を与えた場合、参照は剥がれる
  - CopyCtor が必要
- `tie`
  - 引数の lvalue reference を保持する `tuple` を生成
- `forward_as_tuple`
  - 引数の Forwarding reference を保持する `tuple` を生成
  - lvalue なら `tuple<T&...>`, rvalue なら `tuple<T&&...>` になる
- `tuple_cat`
  - 引数の tuple を decay して結合
  - rvalue reference `T&&` を持つ tuple は基本的に不可 (direct-construct に CopyCtor が必要)
- `get`
  - tuple の要素の参照を取得
  - tuple の lvalue/rvalue 及び const を引き継ぐ
- `operator==`


## Helper concepts
- `tuple-like`
  - `std::array`
  - `std::complex`
  - `std::pair`
  - `std::tuple`
  - `std::ranges::subrange`


## Helper classes
- `tuple_size`
  - 要素数を取得
- `tuple_element`
  - 要素の型を取得
- `uses_allocator`
- `basic_common_reference`
- `common_type`
- `formatter`
- `ignore`
  - `std::tie` で受ける時、その変数は使わないことを示す placeholder

