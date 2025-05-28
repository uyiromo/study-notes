# Diagnostic library
- <https://en.cppreference.com/w/cpp/error>


## Exception handling `<exception>`


### `std::exception`
- <https://en.cppreference.com/w/cpp/error/exception>
- 各種例外の基底クラス
- **Member functions**
  - `exception()`
  - `exception(const exception& other)`
    - `std::exception` は throw 内で copy 禁止なので、文字列は copy-on-write で実装されている
  - `virtual ~exception()`
    - virtual
  - `operator=(const exception& other)`
  - `virtual const char* what() const noexcept`
    - 例外の説明を返す
- **Requirements**
  - 次の関数を `noexcept` で実装すること
    - default constructor
    - copy constructor
    - copy assignment operator
  - copy の際は、`what()` が `strcmp(...) = 0` になる
- **Standard exceptions**
  - `std::logic_error`
    - 論理違反 (事前条件違反など)
    | error              | description                               |
    | :----------------- | :---------------------------------------- |
    | `invalid_argument` | 引数が無効                                |
    | `domain_error`     | domain error (定義域外)                   |
    | `length_error`     | length error (reserve など)               |
    | `out_of_range`     | 引数が許容範囲外 (値域外、範囲外アクセス) |
    | `future_error`     | `std::future` での非同期エラー            |
  - `std::runtime_error`
    - 実行時エラー（実行してみないと分からない）
    | error                                         | description                                           |
    | :-------------------------------------------- | :---------------------------------------------------- |
    | `range_error`                                 | 内部計算の結果、異常な値になった                      |
    | `overflow_error`                              | overflow error                                        |
    | `underflow_error`                             | underflow error                                       |
    | `regex_error`                                 | regex error                                           |
    | `system_error`                                | system error                                          |
    | `system_error < ios_base::failure`            | I/O error                                             |
    | `system_error < filesystem::filesystem_error` | filesystem error                                      |
    | `nonexistent_local_time`                      | 存在しないローカル時間を UTC に変換した (summer time) |
    | `ambiguous_local_time`                        | 曖昧なローカル時間を UTC に変換                       |
    | `format_error`                                | `std::format` 関連のエラー                            |
- `std::bad_*`
  - `std::exception` を直接継承
  | error                              | description                                                    |
  | :--------------------------------- | :------------------------------------------------------------- |
  | `bad_typeid`                       | `typeid` が null を deref した                                 |
  | `bad_cast`                         | `dynamic_cast` に失敗した                                      |
  | `bad_cast < bad_any_cast>`         | `std::any_cast` に失敗した                                     |
  | `bad_optional_access`              | `std::optional::value` が値を持たない                          |
  | `bad_expected_access`              | `std::expected::value` が値を持たない                          |
  | `bad_weak_ptr`                     | `shared_ptr` の引数 `weak_ptr` の参照先が無効                  |
  | `bad_function_call`                | `std::function` が nullptr を呼び出した                        |
  | `bad_alloc`                        | メモリ確保に失敗                                               |
  | `bad_alloc < bad_array_new_length` | `new[]` のサイズが不正 (負数など)                              |
  | `bad_exception`                    | `std::exception` を継承したクラスの基底クラス (throw されない) |
- その他
  - `std::bad_variant_access`
    - `std::variant` で、存在しない要素に対する `std::get`


### Capture and storage of exception objects
- **uncaught exceptions**
  - <https://en.cppreference.com/w/cpp/error/uncaught_exception>
  - まだ catch されていない例外の数を返す
- **exception_ptr**
  - <https://en.cppreference.com/w/cpp/error/exception_ptr>
  - `std::current_exception` で生成される、nullable で pointer-like な型
- **make_exception_ptr**
  - <https://en.cppreference.com/w/cpp/error/make_exception_ptr>
  - `std::current_exception` に同じ
- **current_exception**
  - <https://en.cppreference.com/w/cpp/error/current_exception>
  - 現在の例外をキャッチして、`std::exception_ptr` を返す
- **rethrow_exception**
  - <https://en.cppreference.com/w/cpp/error/rethrow_exception>
  - `std::exception_ptr` を受け取って、例外を再スローする
- **nested_exception**
  - <https://en.cppreference.com/w/cpp/error/nested_exception>
  - 例外を nest するクラス
- **rethrow_with_nested**
  - <https://en.cppreference.com/w/cpp/error/rethrow_with_nested>
  - `std::nested_exception` なら、例外を再スローする
- **rethrow_if_nested**
  - <https://en.cppreference.com/w/cpp/error/rethrow_if_nested>
  - `std::nested_exception` なら、例外を再スローする


### Handling of failures in exception handling
- **terminate**
  - <https://en.cppreference.com/w/cpp/error/terminate>
  - セットされているなら `std::terminate_handler` を呼び出す
    - デフォルトでは `std::abort` を呼び出す
- **terminate_handler**
  - <https://en.cppreference.com/w/cpp/error/terminate_handler>
  - `std::terminate` を呼び出す関数の型
    - `void (terminate_handler)()`
- **get_terminate**
  - <https://en.cppreference.com/w/cpp/error/get_terminate>
  - `std::terminate_handler` を取得する
- **set_terminate**
  - <https://en.cppreference.com/w/cpp/error/set_terminate>
  - terminate handler を設定する
  - `std::terminate_handler` を設定する
- **bad_exception**
  - <https://en.cppreference.com/w/cpp/error/bad_exception>
  - `std::current_exception` で、例外のコピーに失敗した場合にスローされる


## Error numbers `<cerrno>`
- **errno**
  - <https://en.cppreference.com/w/cpp/error/errno>
  - エラー番号を保持する TLS lvalue int
  - マクロ定数は `<cerrno>` に定義


## System error `<system_error>`
- OS 由来のエラーを表すクラスと関数
- **error_category**
  - <https://en.cppreference.com/w/cpp/error/error_category>
  - 基底クラス
  - `::default_error_condition` で errno を error_condition に変換できる
  - virtual になっている箇所が多いため、後述の `***_category` を使う
- **generic_category**
  - <https://en.cppreference.com/w/cpp/error/generic_category>
  - **error_category** の lvalue reference を返す
    - `.name()` が "generic" に設定済み
- **system_category**
  - <https://en.cppreference.com/w/cpp/error/system_category>
  - **error_category** の lvalue reference を返す
    - `.name()` が "system" に設定済み
- **error_condition**
  - <https://en.cppreference.com/w/cpp/error/error_condition>
  - OS 非依存なエラーコードと `std::error_category` を保持するクラス
- **errc**
  - <https://en.cppreference.com/w/cpp/error/errc>
  - POSIX エラーコードを表す Scoped Enum
- **error_code**
  - <https://en.cppreference.com/w/cpp/error/error_code>
  - OS 依存なエラーコードと `std::error_category` を保持するクラス


## Assertion `<cassert>`
- **assert**
  - <https://en.cppreference.com/w/cpp/error/assert>
  - `<cassert>` が include された時点で `NDEBUG` が定義されている場合は無効


## Stacktrace `<stacktrace>`


### `std::stacktrace_entry`
- <https://en.cppreference.com/w/cpp/error/stacktrace_entry>
- stacktrace の各 entry を表すクラス


### `std::basic_stacktrace`
- <https://en.cppreference.com/w/cpp/error/basic_stacktrace>
- stacktrace を表すクラス
  - Allocator を template で指定する
  - `::current()` で現在の stacktrace を取得する
  - `begin` / `end` で iterate 可能


## debugging support (C++26) `<debugging>`


### `std::breakpoint`
- <https://en.cppreference.com/w/cpp/utility/breakpoint>
- デバッガが有効か否かに関わらず、実行を停止して debugger に制御を渡す


### `std::breakpoint_if_debugging`
- <https://en.cppreference.com/w/cpp/utility/breakpoint_if_debugging>
- デバッガが有効な場合のみ、実行を停止して debugger に制御を渡す
  ```C++
  if (std::is_debugger_present()) {
      std::breakpoint();
  }
  ```


### `std::is_debugger_present`
- `https://en.cppreference.com/w/cpp/utility/is_debugger_present`
- デバッガがアタッチされているかどうかを判定する

