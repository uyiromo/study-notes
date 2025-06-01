# function `<functional>`
- <https://en.cppreference.com/w/cpp/utility/functional/function.html>

- 任意の関数オブジェクトのラッパー（保存・コピー・invoke 可能）
  - 関数ポインタ
  - ラムダ式
  - bind expression
  - 関数オブジェクト
  - pointer-to-member function
  - pointer-to-data member
- 関数を保持していない場合に invoke すると `bad_function_call` 例外を投げる
- instantiate は `function<R(Args...)>;`
  - 返り値の型 `R` と引数の型 `Args...` を指定する


- **Definition**
  ```C++
  // 返り値未指定
  template< class >
  class function; /*undefined*/

  // 返り値指定
  template< class R, class... Args >
  class function<R(Args...)>;
  ```

- see: [./tests/function.cpp](./tests/function.cpp)


## Member types
- result_type
  - 関数の返り値の型


## Member functions
- (constructor)
  - default construct 可能で、関数を保持しない
  - copy / move 可能
  - 関数を Forwarding Reference で受け取ることも可能
- (destructor)
- operator=
- swap
- operator bool
  - 関数を保持しているかどうかを返す
- operator()
  - 関数を呼び出す


## Target access
- target_type
  - 関数の `typeid` を取得
- target
  - 関数のポインタを取得
