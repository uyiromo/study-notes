# Function objects
- <https://en.cppreference.com/w/cpp/functional.html>

- `INVOKE(f, arg_0, arg_1, arg_2, ..., arg_N)` 要件は次のように考える
  - `f` が pointer-to-member function なら、
    ```C++
    // pointer-to-member function
    struct C{
        void f(int n) { std::cout << n << '\n'; }
    };
    C c;
    void (C::* p)(int) = &C::f;
    (c.*p)(42); // c.f(42) と同じ


    // obj が C 型だとして、
    // INVOKE(f, obj, arg_1, arg_2, ..., arg_N)
    (obj.*f)(arg_1, arg_2, ..., arg_N)

    // obj が reference wrapper なら
    (obj.get().*f)(arg_1, arg_2, ..., arg_N)

    // 参照なら
    ((*obj).*f)(arg_1, arg_2, ..., arg_N)
    ```
  - `f` が pointer-to-data member なら、(TBD)
  - それ以外なら
    ```C++
    INVOKE(f, arg_0, arg_1, arg_2, ..., arg_N)
    ```

- `std::invoke` / `std::invoke_r` は上記のルールにおいて呼び出し可能なら well-formed
  - 返り値の型は `std::invoke_result_t<F, Args...>` で決まる


## Function wrappers
- function
- move_only_function
  - copy 不可能な function
- copyable_function
- function_ref
- bad_function_call
- mem_fn
  - メンバ関数用 function object
  - function でもバインド可能


## Identity
- identity
  - 引数をそのまま返す（デフォルト値として用いられる）
    ```C++
    template< class T >
    constexpr T&& operator()( T&& t ) const noexcept;
    ```


## Partial function application
- bind_front
  - 前から順にバインド
- bind_back
  - 後ろから順にバインド
- bind
  - 引数をバインドした関数オブジェクトを生成
- is_bind_expression
- is_placeholder
- _1, _2, _3, _4, _5, _6, _7, _8, _9, ... <!--markdownlint-disable-line MD037-->
  - `std::bind` 用のプレースホルダ
  - `_1` は、bounded expression 実行時の第一引数を表す


## Negators
- not_fn
  - 関数オブジェクトの返り値を反転した関数を返す


## Searchers
- `std::search` 用の関数オブジェクト
- default_searcher
- boyer_moore_searcher
- boyer_moore_horspool_searcher


## Reference wrappers
- reference_wrapper
- ref / cref
- unwrap_reference / unwrap_ref_decay
  - reference wrapper を外す


## Operator function objects
- 基本的な演算子を関数オブジェクトとして提供
- 二項演算子の場合、`f(x, y)` は `x op y` と同じ意味

- Atirhmetic
  - `std::plus<T>`
  - `std::minus<T>`
  - `std::multiplies<T>`
  - `std::divides<T>`
  - `std::modulus<T>`
  - `std::negate<T>`
- Comparisons
  - `std::equal_to<T>`
  - `std::not_equal_to<T>`
  - `std::greater<T>`
  - `std::less<T>`
  - `std::greater_equal<T>`
  - `std::less_equal<T>`
- Logical operations
  - `std::logical_and<T>`
  - `std::logical_or<T>`
  - `std::logical_not<T>`
- Bitwise operations
  - `std::bit_and<T>`
  - `std::bit_or<T>`
  - `std::bit_xor<T>`
  - `std::bit_not<T>`


## Constrained comparison function objects
- ２つの型 `T` と `U` を取り、演算子に制約を付けたもの
  - equality は `std::equality_comparable_with<T, U>` を満たす
  - relational は `std::totally_ordered_with<T, U>` を満たす
  - `std::three_way_comparable_with<T, U>` を満たす
- `ranges::equal_to<T, U>`
- `ranges::not_equal_to<T, U>`
- `ranges::less<T, U>`
- `ranges::greater<T, U>`
- `ranges::less_equal<T, U>`
- `ranges::greater_equal<T, U>`
- `ranges::compare_three_way<T, U>`
