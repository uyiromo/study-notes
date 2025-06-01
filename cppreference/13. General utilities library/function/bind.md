# bind / bind_front / bind_back `<functional>`
- <https://en.cppreference.com/w/cpp/utility/functional/bind.html>
- 引数を固定した関数オブジェクトを生成する


- **Definition**
  ```C++
  template< class F, class... Args >
  /* unspecified */ bind( F&& f, Args&&... args );

  template< class R, class F, class... Args >
  /* unspecified */ bind( F&& f, Args&&... args );
  ```

- see: [./tests/bind.cpp](./tests/bind.cpp)


## Bounded arguments
- `bind` 引数の型は次のように決定
  1. `std::reference_wrapper<T>` の場合、`T&`
     - `std::ref`, `std::cref` を使用した場合
  2. bind expression の場合、`std::invoke_result_t<T cv&, ...>`
  3. placeholder の場合、渡される型
  4. lvalue argument の場合、`T cv&`
- placeholder の扱い
  - 次のように宣言すると、「`b1()` の第一引数を `_1`、第二引数を `_2` として `f` を呼び出す」ように bind される
    ```C++
      auto b1 = std::bind(f, std::placeholders::_2, 34, std::placeholders::_1, x, 90);
    ```
