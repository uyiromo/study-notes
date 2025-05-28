# Language support library
- <https://en.cppreference.com/w/cpp/utility#Language_support>

- [Language support library](#language-support-library)
  - [Implementation properties (C++20)](#implementation-properties-c20)
  - [Type support](#type-support)
    - [Additional basic types and macros `cstddef`](#additional-basic-types-and-macros-cstddef)
    - [Fixed width integer types](#fixed-width-integer-types)
    - [Fixed width floating types (C++23)](#fixed-width-floating-types-c23)
  - [numeric limits](#numeric-limits)
  - [Runtime identification](#runtime-identification)
    - [type\_info](#type_info)
    - [bad\_typeid](#bad_typeid)
    - [bad\_cast](#bad_cast)
    - [type\_index](#type_index)
  - [Program utilities](#program-utilities)
  - [Dynamic memory management](#dynamic-memory-management)
  - [Error handling](#error-handling)
  - [Variadic functions](#variadic-functions)
  - [Initializer lists](#initializer-lists)
  - [Source code information capture (C++20)](#source-code-information-capture-c20)
  - [Three-way comparison (C++20)](#three-way-comparison-c20)
  - [Coroutine support (C++20)](#coroutine-support-c20)
  - [Contract support (C++26)](#contract-support-c26)


## Implementation properties (C++20)
- <https://en.cppreference.com/w/cpp/utility/feature_test>
- C++ の各機能実装有無は `<version>` ヘッダで確認できる
  - `__cpp_lib_*`
- `<version>` ヘッダは C++20 から導入
  - それ以外に、各機能が対応するヘッダに定義がある


## Type support
- <https://en.cppreference.com/w/cpp/types>


### Additional basic types and macros `cstddef`
- `size_t`
  - 最低でも 16 bit 以上の符号無し整数型
- `ptrdiff_t`
  - pointer arithmetic 及び array indexing で用いる
  - 最低でも 17 bit 以上の符号有り整数型
- `nullptr_t`
  - `nullptr` literal の型で、任意のポインタに変換可能な型
- `NULL`
  - null pointer を表すマクロ
- `max_align_t`
  - 任意の scalar より大きいアラインメントを必要とする型
- `offsetof`
  - あるオブジェクト内のメンバオフセットを `std::size_t` で返すマクロ
- `byte`
  - バイトを表す型 (Scoped enum)
  - 本質的に `unsigned char` だが、算術演算の対象にはできない（bitshift, bitwise は可能）


### Fixed width integer types `cstdint`
- <https://en.cppreference.com/w/cpp/types/integer>
- `int_fast*_t`
  - 指定のビット幅を持ち、fastest な integer
- `int_least*_t`
  - 最低でも指定ビット幅を持つ integer
- `intmax_t`
  - 最大のビット幅を持つ integer
- `intptr_t`
  - pointer to void を保持できる符号付き integer


### Fixed width floating types (C++23) `<stdfloat>`
- <https://en.cppreference.com/w/cpp/types/floating-point>
- 対応するマクロが定義されている場合に限り、定義される
- `float16_t`
- `float32_t`
- `float64_t`
- `float128_t`
- `bfloat16_t`
- literal の場合は `0.1f64` のように宣言する


### numeric limits `<limits>`
- `<limits>`
  - <https://en.cppreference.com/w/cpp/types/numeric_limits>
  - `std::numeric_limits<T>` で取得
  - `::digits()` でビット数取得
  - `::digits10()` で 10 進数のビット数取得
  - `::min()` `::max()` で最小・最大値取得


### Runtime identification `<typeinfo>`


#### type_info
- <https://en.cppreference.com/w/cpp/types/type_info>
- `typeid` で返される implementation-specific な型情報を保持する
  - construct 不可
- `bool before( const type_info& rhs ) const;`
  - implementation で `*this < rhs` なら true
- `std::size_t hash_code() const noexcept;`
  - type のハッシュを返す
- `const char* name() const;`
  - 型名を返す
  - gcc や clang は mangled name を返すため、demangle が必要


#### bad_typeid
- <https://en.cppreference.com/w/cpp/types/bad_typeid>
- `typeid` が nullptr を剥がした時に発生する例外


#### bad_cast
- <https://en.cppreference.com/w/cpp/types/bad_cast>
- `dynamic_cast` が継承関係外のキャストなどで失敗した場合に発生する例外


#### type_index `<typeindex>`
- <https://en.cppreference.com/w/cpp/types/type_index>
  - `type_info` を associative container の key として使うための wrapper class


<!----------------------------------------------------------------------------------->


## Program utilities
- <https://en.cppreference.com/w/cpp/program>


## Program termination `<cstdlib>`
- Program termination と resource cleanup を管理する

| Function   | signal  | resource cleanup | exit functions | notes |
|------------|---------|------------------|----------------|-------|
| abort      | SIGABRT | no               | -              | - |
| exit       | -       | yes (stack 除く) | atexit         | `main()` は automatic を Dtor して `std::exit()` |
| quick_exit | -       | no               | at_quick_exit   | 正常終了したら `std::_Exit` <br> 処理中に例外が発生したら `std::terminate` |
| _Exit      | -       | no               | -              | - |


### std::abort
- <https://en.cppreference.com/w/cpp/utility/program/abort>
- **Signature**
  - `[[noreturn]] void abort() noexcept;`

- **Description**
  - プログラムを異常終了させる
    - `SIGABRT` で補足可能
  - automatic, TLS, static object の destructor は呼ばれない
  - `std::atexit()`, `std::at_quick_exit` に登録された処理も呼ばれない
  - 各種リソースの close は implementation defined

- **Notes**
- POSIX 仕様では、`abort()` は SIGABRT の blocking/nonblocking を上書きする
- コンパイラによってはプログラムを高速に終了させる intrinsics が存在する
  - `__builtin_trap` (gcc, clang, icc)
  - `__fastfail` / `__debugbreak` (msvc)


### std::exit
- <https://en.cppreference.com/w/cpp/utility/program/exit>
- **Signature**
  - `[[noreturn]] void exit( int exit_code );`
- **Description**
  - 以下のステップを踏む
  1. TLS の Dtor、static storage duration object の Dtor、`std::atexit` の処理を並列に行う。ただし、以下は保証されている
     1. 最後の TLS Dtor は、最初の static object の Dtor に対して sequenced-before
     2. TLS/static Ctor が、別の Ctor に対して sequenced-before な場合、Dtor はその逆順で sequenced-before
     3. static object の初期化が `std::atexit` の関数に対して sequenced-before な場合、逆順で sequenced-before
     4. 3 の逆順
     5. `std::atexit` 内の関数に対して sequenced-before なら、逆順で sequenced-before
     - 上記の処理中で
       - 例外が発生した場合、`std::terminate` を実行する
       - コンパイラが dynamic initialization を static initialization に最適化した場合、それに従う
       - ある関数で宣言された static object が Dtor され、別の Dtor がその関数を再度呼んだ場合は UB
       - block-scope な static object が、別の object Ctor で初期化されていた場合、全て破棄されてから Dtor される
  2. 全ての C streams は flush & close される
  3. `std::tmpfile` で作成されたファイルは削除される
  4. host にコントロールを返す。`exit_code` が 0 (EXIT_SUCCESS) or 1 (EXIT_FAILURE) に従って implementation-defined な値を返す
  - stack は unwind されないため、Dtor は呼ばれない
  - `main()` がの末尾に到達した時、automatic storage を Dtor してから `std::exit` を呼ぶ


### std::quick_exit
- <https://en.cppreference.com/w/cpp/utility/program/quick_exit>
- **Signature**
  - `[[noreturn]] void quick_exit( int exit_code ) noexcept;`

- **Description**
  - 正常終了させるが、リソースのクリーンアップは行わない
    - `std::at_quick_exit` は実行する
    - `std::atexit` も実行しない
  - 例外が発生したら `std::terminate` を実行する
  - 全て終了後に `std::_Exit` を実行する


### std::_Exit
- <https://en.cppreference.com/w/cpp/utility/program/_Exit>


- **Signature**
  1. `[[noreturn]] void _Exit( int exit_code ) noexcept;`

- **Description**
  - クリーンアップ処理を一切行わない
    - opened resources の処理は implementation-defined
  - freestanding 環境では `std::_Exit` の実装は必須 (since C++23)


### std::atexit
- <https://en.cppreference.com/w/cpp/utility/program/atexit>
- **Signature**
  1. `int atexit( /* c-atexit-handler */* func ) noexcept;` <br>
     `int atexit( /* atexit-handler */* func ) noexcept;`
  2. `extern "C" using /*c-atexit-handler */ = void();` <br>
     `extern "C++" using /* atexit-handler*/ = void();`

- **Description**
  - 関数ポインタ `func` を登録する
    - 登録された関数ポインタは、通常終了 `std::exit()` もしくは main の return で実行される
  - Thread-Safe
  - 最低でも 32 個登録可能。最大数は implementation-defined


### std::at_quick_exit
- <https://en.cppreference.com/w/cpp/utility/program/at_quick_exit>
- **Signature**
  1. `int atexit( /* c-atexit-handler */* func ) noexcept;` <br>
     `int atexit( /* atexit-handler */* func ) noexcept;`
  2. `extern "C" using /*c-atexit-handler */ = void();` <br>
     `extern "C++" using /* atexit-handler*/ = void();`

- **Description**
  - 関数ポインタを登録する
    - 登録された関数ポインタは、通常終了 `std::quick_exit()` で実行される
    - `std::atexit` と異なり、main の return では実行されない
  - Thread-Safe
  - 最低でも 32 個登録可能。最大数は implementation-defined


### EXIT_SUCCESS, EXIT_FAILURE
- <https://en.cppreference.com/w/cpp/utility/program/EXIT_status>

- **Signature**
  1. `#define EXIT_SUCCESS /*implementation defined*/`
  2. `#define EXIT_FAILURE /*implementation defined*/`
- **Description**
  - integral constant に展開されるマクロ
  - `std::exit` の返り値として使用できる
- **Notes**
  - 多くの場合、`EXIT_SUCCESS = 0` `EXIT_FAILURE = 1` だが、implementation-defined


## Unreachable control flow `<utility>`


### std::unreachable
- <https://en.cppreference.com/w/cpp/utility/unreachable>

- **Signature**
  - `[[noreturn]] void unreachable();`
- **Description**
  - UB を明示的に引き起こす
    - 処理継続を行わないなど
  - コンパイラは optimization build では不要 branch 削除、debug build では trap などに最適化可能


## Communicating with the environment `<cstdlib>`


### std::system
- <https://en.cppreference.com/w/cpp/utility/program/system>

- **Signature**
  1. `int system( const char* command );`
- **Description**
  1. ホスト環境でコマンドを実行し、返り値を受け取る
     - `command` が NULL の場合、コマンドプロセッサの存在確認を行う
- **Return value**
  - Implementation-defined
  - `command` が NULL の場合、コマンドプロセッサが存在したら nonzero
- **Notes**
  - POSIX では、返り値を WEXITSTATUS / WSTOPSIG で分解可能
  - `popen` で output を取得できるようになる
  - 使用する前に `std::cout` の明示的な flush が必要。しない場合、`command` の入力として扱われる


### std::getenv
- <https://en.cppreference.com/w/cpp/utility/program/getenv>

- **Signature**
  1. `char* getenv( const char* env_var );`
- **Description**
  1. host environment から環境変数を取得する
     - 他の関数が環境変数をいじらない限り Thread-Safe
- **Return value**
  - 環境変数の値 or NULL
- **Notes**
- POSIX なら `extern char **environ <unistd.h>` もしくは main 関数の第三引数 `envp` からも取得可能


## Signals `<csignal>`


### signal
- <https://en.cppreference.com/w/cpp/utility/program/signal>

- **Signature**
  1. `/* signal-handler */* signal( int sig, /* signal-handler */* handler );`
  2. `extern "C" using /* signal-handler */ = void(int);`
- **Description**
  1. signal `sig` のハンドラを `handler` に変更する
     - `std::signal(sig, SIG_DFL)` が handler 前に実行されるかは implementation-defined
  - signal によって、startup 時の挙動は異なる
    - `std::signal(sig, SIG_IGN)` or `std::signal(sig, SIG_DFL)`
- **Parameters**
  - `sig`
    - 対象の signal で、以下のいずれか
      - `SIGABRT` `SIGFPE` `SIGILL` `SIGINT` `SIGSEGV` `SIGTERM`
  - `handler`
    - ハンドラで、以下のいずれか
    - `SIG_DFL`
      - デフォルトハンドラを示すマクロ
    - `SIG_IGN`
      - 無視を示すマクロ
    - `extern "C" void fun(int sig)`
      - 関数ポインタ
- **Return value**
  - 成功時は、あらかじめセットされていたハンドラ
  - 失敗時は、`SIG_ERR`
- **Signal handler**
  - 関数 `f` は `<atomic>` `<stdatomic.h>` による plain lock-free atomic operation
  - 次の操作を行った場合、UB
    - plain lock-free atomic operation かつ signal-safe function 以外の呼び出し
      - see: link
    - TLS duration object へのアクセス
    - `dynamic_cast`
    - `throw`
    - `try`
    - dynamic initialization を行うような static 変数初期化
    - 他スレッドによる static duration な変数の初期化を待機
  - `SIGFPE` `SIGILL` `SIGSEGV` など computational exception を示す signal handling 中に制御を返したら UB
  - handler が `std::abort` `std::raise` の結果呼ばれて、さらに `std::raise` したら UB
  - signal の呼び出しは、他の handler に対して synchronizes-with
- **Notes**
  - POSIX では `signal` は Thread-Safe
    - [async-signal-safe library function](https://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_04)
  - signal handler は C linkage が前提だが、一般的な実装では C++ linkage も許可されている


### std::raise
- <https://en.cppreference.com/w/cpp/utility/program/raise>
- **Signature**
  1. `int raise( int sig );`
- **Description**
  1. signal `sig` を送信する
     - handler がセットされていない場合のデフォルト挙動は implementation-defined
- **Parameters**
  - `sig`
    - `SIGABRT` `SIGFPE` `SIGILL` `SIGINT` `SIGSEGV` `SIGTERM`
- **Return value**
  - 成功したら 0
  - 失敗したら nonzero


### sig_atomic_t
- <https://en.cppreference.com/w/cpp/utility/program/sig_atomic_t>
- **Signature**
  1. `typedef /* unspecified */ sig_atomic_t;`
- **Description**
  1. integer で、非同期割り込みでも atomic に動作できる型
- **Parameters**
  - (none)
- **Return value**
  - (none)
- **Exceptions**
  - (none)
- **Notes**
  - `std::atomic`
  - `std::signal_fence`


### signal 関連の定数
- `SIG_DFL` `SIG_IGN`
  - `std::signal` のハンドラで、いかなる関数のアドレスとも一致しないマクロ
- `SIG_ERR`
  - `void (*)(int)`
  - `std::signal` の戻り値
- `SIGABRT` `SIGFPE` `SIGILL` `SIGINT` `SIGSEGV` `SIGTERM`
  - `SIGABRT`   `std::abort()` による異常終了
  - `SIGFPE`    erroneous arithmetic operation (e.g DIV0)
  - `SIGILL`    invalid program image (invalid instruction)
  - `SIGINT`    external interrupt
  - `SIGSEGV`   segmentation fault
  - `SIGTERM`   termination request


## Non-local jumps `<csetjmp>`
- (TODO)


<!----------------------------------------------------------------------------------->

## Dynamic memory management
- <https://en.cppreference.com/w/cpp/memory>
- [Memory management library](./Memory%20management.md)

<!----------------------------------------------------------------------------------->


## Error handling
- <https://en.cppreference.com/w/cpp/error>
- [Error handling library](./Error%20handling.md)

<!----------------------------------------------------------------------------------->


## Variadic functions `<cstdarg>`
- <https://en.cppreference.com/w/cpp/variadic>
- 可変長引数のサポート
  - `std::printf(const char *fmt, ...)` のように ellipsis で宣言
  - 関数内でそれらにアクセスするには、次の関数を使う
    - `va_start`
    - `va_arg`
    - `va_copy`
    - `va_end`
    - `va_list`


### va_start
- <https://en.cppreference.com/w/cpp/utility/variadic/va_start>
- **Signature**
  1. `void va_start( std::va_list ap, parm_n );`
- **Description**
  1. `parm_n` 引数から `ap` を作成する
     - 有効な `ap` に対して、`va_arg` より前に実行される必要がある
     - `parm_n` が pack extension もしくは lambda capture の場合は ill-formed (no diagnostic)
     - `parm_n` が reference などの場合は UB
- **Parameters**
  - `ap`
    - `va_list`
  - `parm_n`
    - ellipsis の前の引数名
- **Return value**
  - (none)
- **Exceptions**
  - (none)
- **Notes**
  - (none)


### va_arg
- <https://en.cppreference.com/w/cpp/utility/variadic/va_arg>
- **Signature**
  1. `T va_arg( std::va_list ap, T );`
- **Description**
  1. `ap` の次の要素を `T` 型として取り出す
     - `T` が非互換な型の場合、UB
       - signed / unsigned integer の場合は UB にはならない
       - pointer to void と pointer to other の場合は UB にならない
     - 次の引数が無い場合、UB
- **Parameters**
  - `ap`
  - `T`
    - 次の型
- **Return value**
  - (none)
- **Exceptions**
  - (none)
- **Notes**
  - (none)


### va_copy
- <https://en.cppreference.com/w/cpp/utility/variadic/va_copy>
- **Signature**
  1. `void va_copy( std::va_list dest, std::va_list src );`
- **Description**
  1. `src` を `dst` にコピーする
- **Parameters**
  - `dest`
  - `src`
- **Return value**
  - (none)
- **Exceptions**
  - (none)
- **Notes**
  - `va_arg` は一回読み込んだ引数は巻き戻せない
  - 引数を複数回チェックする際などに使う（必要なバッファ長計算 etc...）


### va_end
- <https://en.cppreference.com/w/cpp/utility/variadic/va_end>
- **Signature**
  1. `void va_end( std::va_list ap );`
- **Description**
  1. `ap` object の cleanup を行う
      - `va_start` / `va_copy` / `va_end` の前に呼び出された場合、UB
- **Parameters**
  - `ap`
- **Return value**
  - (none)
- **Exceptions**
  - (none)
- **Notes**
  - (none)


### va_list
- <https://en.cppreference.com/w/cpp/utility/variadic/va_list>

- **Signature**
  1. `typedef /* unspecified */ va_list;`
- **Description**
  1. `va_*` の情報を保持するための complete type
     - 一般的に built-in type か char*
     - `va_list` の pointer を取り、他の関数に渡すのは legal
- **Parameters**
  - (none)
- **Return value**
  - (none)
- **Exceptions**
  - (none)
- **Notes**
  - (none)


<!----------------------------------------------------------------------------------->


## Initializer lists `<initializer_list>`
- <https://en.cppreference.com/w/cpp/language/initializer_list>
- **Definition**
  ```C++
  template <class T>
  class initializer_list;
  ```
- **Description**
  - Read-only な `T` 型の array を保持する
  - `std::initializer_list` の specialization は ill-formed
- **Member types**
  | Name            | Definition    |
  | :-------------- | :------------ |
  | value_type      | `T`           |
  | reference       | `const T&`    |
  | const_reference | `const T&`    |
  | size_type       | `std::size_t` |
  | iterator        | `const T*`    |
  | const_iterator  | `const T*`    |
- **Member functions**
  - `(constructor)`
  | function  | return type | Description            |
  | :-------- | :---------- | ---------------------- |
  | `size()`  | size_type   | 要素数                 |
  | `begin()` | `const T*`  | 最初の要素へのポインタ |
  | `end()`   | `const T*`  | 最後の要素へのポインタ |
- **Non-member functions (<std::initializer_list>)**
  - `std::begin` `std::end` に対する overload
- **Free function templates overloaded for `std::initializer_list`**
  - `std::rbegin` `std:crbegin`
  - `std::rend` `std::crend`
  - `std::empty`
  - `std::data`


<!----------------------------------------------------------------------------------->


## Source code information capture (C++20) `<source_location>`
- <https://en.cppreference.com/w/cpp/source_location>


### source_location
- <https://en.cppreference.com/w/cpp/utility/source_location>
- **Signature**
  1. `struct source_location;`
- **Description**
  1. ソースコードの情報（ファイル名、行番号、関数名）を保持する型
     - 従来の `__LINE__` `__FILE__` の代替
     - 次の requirements を満たす
       - `DefaultConstructible`
       - `CopyConstructible`
       - `CopyAssignable`
       - `Destructible`
       - `Swappable`
       - `std::is_nothrow_move_constructible_v<std::source_location>`
       - `std::is_nothrow_move_assignable_v<std::source_location>`
       - `std::is_nothrow_swappable_v<std::source_location>`
- **Member functions**
  - **Creation**
    - `(constructor)`
    - `static current()`
      - 呼び出された箇所の情報を返す
  - **Field access**
    - `line()`
      - line number
    - `column()`
      - column number (1-origin)
    - `file_name()`
      - filename
    - `function_name()`
      - function name
      - 関数外なら empty string
- **Notes**
  - (none)

<!----------------------------------------------------------------------------------->


## Three-way comparison (C++20) `<compare>`
- <https://en.cppreference.com/w/cpp/language/three_way_comparison>

| ordering                | equivalent is equal | unordered |
| ----------------------- | ------------------- | --------- |
| `std::partial_ordering` | no                  | allow     |
| `std::weak_ordering`    | no                  | DISALLOW  |
| `std::strong_ordering`  | yes                 | DISALLOW  |


### std::three_way_comparable
- <https://en.cppreference.com/w/cpp/utility/compare/three_way_comparable>
- three-way comparison 可能なことを示す concept
  1. `==` による比較が可能
  2. partial ordering が可能
  3. 共通の参照型を導出可能で、それが `std::three_way_comparable`
  4. 指定された comparison category を導出可能


### std::partial_ordering
- <https://en.cppreference.com/w/cpp/utility/compare/partial_ordering>
- **Definition**
  - `class partial_ordering`
- **Description**
  - three-way comparison の結果を示す class で、次の性質を持つ
  - six relational operators `==` `!=` `<` `<=` `>` `>=` の結果を示せる
  - substitutability を示唆しない
    - equivalent な 2 個の要素は、区別できるかもしれない
  - 比較不能な値を示せる
    - `a < b` `a == b` `a > b` が全て false になる型
- **Constants**

  | Name                                | Definition   |
  | :---------------------------------- | :----------- |
  | `std::partial_ordering::less`       | less than    |
  | `std::partial_ordering::equivalent` | equivalent   |
  | `std::partial_ordering::greater`    | greater than |
  | `std::partial_ordering::unordered`  | incomparable |

- **Conversions**
  - `std::strong_ordering` と `std::weak_ordering` は、暗黙的に `std::partial_ordering` に変換可能
  - 逆は不可
- **Comparisons**
  - `std::partial_ordering` 同士、もしくは `0` と比較できる
    - つまり `a <=> b == 0` のように書ける
    - `std::is_eq` のような boolean relationship との互換性
- **Notes**
  - floating point はこれに該当する
    - `-0` と `0` は equivalent だが区別可能
    - `NaN` は unordered


### std::weak_ordering
- <https://en.cppreference.com/w/cpp/utility/compare/weak_ordering>
- **Definition**
  - `class weak_ordering`
- **Description**
  - three-way comparison の結果を示す class で、次の性質を持つ
  - six relational operators `==` `!=` `<` `<=` `>` `>=` の結果を示せる
  - substitutability を示唆しない
    - equivalent な 2 個の要素は、区別できるかもしれない
  - 比較不能な値は許可しない
    - `a < b` `a == b` `a > b` のいずれか一つが必ず true になる
- **Constants**

  | Name                             | Definition   |
  | :------------------------------- | :----------- |
  | `std::weak_ordering::less`       | less than    |
  | `std::weak_ordering::equivalent` | equivalent   |
  | `std::weak_ordering::greater`    | greater than |

- **Conversions**
  - `std::strong_ordering` => `std::weak_ordering` => `std::partial_ordering` の方向に暗黙的に変換可能
- **Comparisons**
  - `std::partial_ordering` 同士、もしくは `0` と比較できる
    - つまり `a <=> b == 0` のように書ける
    - `std::is_eq` のような boolean relationship との互換性
- **Notes**
  - (none)


### std::strong_ordering
- <https://en.cppreference.com/w/cpp/utility/compare/strong_ordering>
- **Definition**
  - `class strong_ordering`
- **Description**
  - three-way comparison の結果を示す class で、次の性質を持つ
    - six relational operators `==` `!=` `<` `<=` `>` `>=` の結果を示せる
    - substitutability を示唆する
      - equivalent な 2 個の要素は、区別できる
    - 比較不能な値は許可しない
      - `a < b` `a == b` `a > b` のいずれか一つが必ず true になる
- **Constants**

  | Name                               | Definition   |
  | :--------------------------------- | :----------- |
  | `std::strong_ordering::less`       | less than    |
  | `std::strong_ordering::equivalent` | = equal      |
  | `std::strong_ordering::equal`      | equal        |
  | `std::strong_ordering::greater`    | greater than |

- **Conversions**
  - `std::strong_ordering` => `std::weak_ordering` => `std::partial_ordering` の方向に暗黙的に変換可能
- **Comparisons**
  - `std::strong_ordering` 同士、もしくは `0` と比較できる
    - つまり `a <=> b == 0` のように書ける
    - `std::is_eq` のような boolean relationship との互換性
- **Notes**
  - (none)


### is_eq / is_neq / is_lt / is_lteq / is_gt / is_gteq
- <https://en.cppreference.com/w/cpp/utility/compare/named_comparison_functions>
- `std::partial_ordering` を bool に変換する関数群


### compare_three_way
- <https://en.cppreference.com/w/cpp/utility/compare/compare_three_way>
- **Definition**
  - `struct compare_three_way;`
- **Description**
  - 比較処理を行う関数オブジェクト
- **Member functions**
  - `operator()`
- **std::compare_three_way::operator()**
  ```C++
  template< class T, class U >
  constexpr auto operator()( T&& t, U&& u ) const;
  ```
  - pointer の比較は implementation-defined strict total order に従って `std::strong_ordering::*` を返す
  - それ以外の場合、three-way comparison の結果を返す
  - `std::three_way_comparable_with<T, U>` でない場合、UB
    - `==` `!=` が定義されていて、`<=>` が comparison category を返す


### compare_three_way_result
- <https://en.cppreference.com/w/cpp/utility/compare/compare_three_way_result>
- **Definition**
  ```C++
  template< class T, class U = T >
  struct compare_three_way_result;
  ```
- **Member types**
  - `type`
    - `<=>` の結果
- **Helper types**
  ```C++
  template< class T, class U = T >
  struct compare_three_way_result;
  ```


### common_comparison_category
- <https://en.cppreference.com/w/cpp/utility/compare/common_comparison_category>
- 全ての型に対して、strongest な comparison category を返す型
  - 全て comparison category でないなら `void`


### std::strong_order
- <https://en.cppreference.com/w/cpp/utility/compare/strong_order>
- **Definition**
  ```C++
  inline namespace /*unspecified*/ {
      inline constexpr /* unspecified */ strong_order = /* unspecified */;
  }
  ```
- **Call signature**
  ```C++
  template< class T, class U >
      requires /* see below */
  constexpr std::strong_ordering strong_order( T&& t, U&& u ) noexcept(/* see below */);
  ```

- **Strict total order of IEEE floating-point types**
  - TODO


### std::weak_order
- <https://en.cppreference.com/w/cpp/utility/compare/weak_order>
- `std::strong_order` の `weak_order` 版


### std::partial_order
- <https://en.cppreference.com/w/cpp/utility/compare/partial_order>
- `std::strong_order` の `partial_order` 版


## compare_strong_order_fallback
- <https://en.cppreference.com/w/cpp/utility/compare/compare_strong_order_fallback>
- `std::strong_order` で `<=>` が未定義の場合に `<` と `==` を用いる版


## compare_weak_order_fallback
- <https://en.cppreference.com/w/cpp/utility/compare/compare_weak_order_fallback>
- `std::weak_order` で `<=>` が未定義の場合に `<` と `==` を用いる版


## compare_partial_order_fallback
- <https://en.cppreference.com/w/cpp/utility/compare/compare_partial_order_fallback>
- `std::partial_order` で `<=>` が未定義の場合に `<` と `==` を用いる版


<!----------------------------------------------------------------------------------->

## Coroutine support (C++20)
- <https://en.cppreference.com/w/cpp/language/coroutines>
- TODO (coroutine)


<!----------------------------------------------------------------------------------->


## Contract support (C++26)
- <https://en.cppreference.com/w/cpp/contract>
- TODO (contract)
