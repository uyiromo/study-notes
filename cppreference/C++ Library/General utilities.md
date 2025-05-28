# General-purpose utilities `<utility>`
- <https://en.cppreference.com/w/cpp/utility#General-purpose_utilities>


## Swap


### `std::swap`
- <https://en.cppreference.com/w/cpp/algorithm/swap>
- **Definition**
  ```C++
  template< class T >
  void swap( T& a, T& b );

  template< class T2, std::size_t N >
  void swap( T2 (&a)[N], T2 (&b)[N] );
  ```
- **Description**
  - 値を交換する
  - 特殊化された `std::swap` の呼び出し
    ```C++
    std::pair<...> p1;
    std::pair<...> p2;
    std::swap(p1, p2);
    ```
  - ADL の呼び出し
    ```C++
    using std::swap;
    swap(p1, p2);
    ```


### `std::exchange`
- <https://en.cppreference.com/w/cpp/utility/exchange>
- **Definition**
  ```C++
  template< class T, class U = T >
  constexpr T exchange( T& obj, U&& new_value );
  ```
- **Description**
  - `obj` の値を `new_value` に置き換え、元の値を返す


### `std::ranges::swap`
- <https://en.cppreference.com/w/cpp/utility/ranges/swap>
- **Definition**
  ```C++
  // Call signature
  template< class T, class U >
  constexpr void ranges::swap( T&& t, U&& u ) noexcept(/*see below*/);
  ```
- **Description**
  - `ranges::swap(t, u)` は次と expression-equivalent
  1. `(void) swap(t, u)`
     - `t` or `u` が class か enum の場合
     - かつ、CPO を含む コンテキストで overload 解決に成功した場合
       - `std::ranges::swap(T&, T&) = delete`
  2. `(void) ranges::swap_ranges(t, u)`
     - `t` と `u` が同じ extent を持つ lvalue arrays の場合
     - かつ、`ranges::swap(*t, *u)` が valid である場合
  3. `std::swap(t, u)` 相当の処理を行う
     - `t` と `u` が同じ型 `V` のlvalue で、`std::move_constructible<V> && std::assignable_from<V&, V>` が有効な場合
  4. 上記のいずれでも無い場合、ill-formed


## Type operations `<utility>`


### `std::forward`
- <https://en.cppreference.com/w/cpp/utility/forward>
- **Definition**
  ```C++
  // (1)
  template< class T >
  constexpr T&& forward( typename std::remove_reference<T>::type& t ) noexcept;

  // (2)
  template< class T >
  constexpr T&& forward( typename std::remove_reference<T>::type&& t ) noexcept;
  ```
- **Description**
  - CV は保持される
  - non-deduced context なので、引数からの推論は不可（型が明示される必要がある）


### `std::forward_like`
- <https://en.cppreference.com/w/cpp/utility/forward_like>
- **Definition**
  ```C++
  template< class T, class U >
  constexpr auto&& forward_like( U&& x ) noexcept;
  ```
- **Description**
  - 基本は `std::forward` と同じで、返り値が `T` の性質を引き継ぐ
    - const なら、const
    - lvalue reference なら、lvalue reference、それ以外は rvalue reference


### `std::move`
- <https://en.cppreference.com/w/cpp/utility/move>
- **Definition**
  ```C++
  template< class T >
  constexpr std::remove_reference_t<T>&& move( T&& t ) noexcept;
  ```
- **Description**
  - `static_cast<T&&>(t)` と同じ効果
  - value category だけ変換


### `std::move_if_noexcept`
- <https://en.cppreference.com/w/cpp/utility/move_if_noexcept>
- **Definition**
  ```C++
  template< class T >
  /*see below*/ move_if_noexcept( T& x ) noexcept;
  ```
- **Description**
  - nothrow で move 構築可能 or move-only な場合に rvalue reference `T&&` を返す
  - それ以外の場合は、`const T&` を返す
- **Notes**
  - `std::vector::resize` のように「例外が発生したら発生する前の状態に戻す」必要がある場合に使用される
  - ただし、copy constructor が delete されている場合、noexcept **ではない** move constructor が使用される
  ```C++
  struct S
  {
      S() {};
      S(S&& s) = default;
      S(const S&) = delete;
  };

  // true
  static_assert(std::is_nothrow_move_constructible<S>::value || !std::is_copy_constructible<S>::value);
  ```


### `std::as_const`
- <https://en.cppreference.com/w/cpp/utility/as_const>
- **Definition**
  ```C++
  template< class T >
  constexpr std::add_const_t<T>& as_const( T& t ) noexcept;

  template< class T >
  void as_const( const T&& ) = delete;
  ```
- **Description**
  - lvalue reference なら `const T&` を返す
  - rvalue reference なら delete


### `std::declval`
- <https://en.cppreference.com/w/cpp/utility/declval>
- **Definition**
  ```C++
  template< class T >
  std::add_rvalue_reference_t<T> declval() noexcept;
  ```
- **Description**
  - `T&&` を返す
  - 型 `T` が construct されたように振る舞う
    - `T` のコンストラクタが無い場合でも利用できる


### `std::to_underlying`
- <https://en.cppreference.com/w/cpp/utility/to_underlying>
- **Definition**
  ```C++
  template< class Enum >
  constexpr std::underlying_type_t<Enum> to_underlying( Enum e ) noexcept;
  ```
- **Description**
  - enum の underlying type を返す


## Integer comparison functions `<utility>`


### `std::cmp_*`
- <https://en.cppreference.com/w/cpp/utility/intcmp>
- **Definition**
  ```C++
  template< class T, class U >
  constexpr bool cmp_equal( T t, U u ) noexcept;
  ```
- **Description**
  - Integer-type 同士の比較演算
  - 通常の比較と異なり、符号付き整数は、常に符号無し整数より小さい
    - `std::cmp_greater(-1, 0u) == false`
    - `-1 > 0u` は true になる
      - unsigned integer の rank の方が高いため、そっちに合わせて比較される


### `std::in_range`
- <https://en.cppreference.com/w/cpp/utility/in_range>
- **Definition**
  ```C++
  template< class R, class U >
  constexpr bool in_range( T t ) noexcept;
  ```
- **Description**
  - `R` の範囲で `T` が表現可能なら true


## Construction tags `<utility>`


### `std::piecewise_construct`
- <https://en.cppreference.com/w/cpp/utility/piecewise_construct>
- **Definition**
  ```C++
  // (1)
  struct piecewise_construct_t { explicit piecewise_construct_t() = default; };

  // (2)
  constexpr std::piecewise_construct_t piecewise_construct{};
  ```
- **Description**
  - `std::pair` のコンストラクタオーバーロード解決に使用される型
  - `std::pair<S, U> p(t1, t2)` のように書くと、`S(t1), U(t2)` のように要素を tuple から初期化する
  - `std::pair<S, U> p(std::piecewise_construct, t1, t2)` のように書くと、`t1` の要素を分解して `S` のコンストラクタに転送する


### `std::in_place`
- <https://en.cppreference.com/w/cpp/utility/in_place>
- **Definition**
  ```C++
  // (1)
  struct in_place_t { explicit in_place_t() = default; };

  // (2)
  inline constexpr std::in_place_t in_place {};

  // (3)
  template< class T >
  struct in_place_type_t { explicit in_place_type_t() = default; };

  // (4)
  template< class T >
  constexpr std::in_place_type_t<T> in_place_type {};

  // (5)
  template< std::size_t I >
  struct in_place_index_t { explicit in_place_index_t() = default; };

  // (6)
  template< std::size_t I >
  constexpr std::in_place_index_t<I> in_place_index {};
  ```
- **Description**
  - `std::optional` や `std::variant` のコンストラクタオーバーロード解決に使用される型
  - 引数を完全転送して、要素を直接構築する


### `std::nontype`
- <https://en.cppreference.com/w/cpp/utility/nontype>
- **Definition**
  ```C++
  // (1)
  template< auto V >
  struct nontype_t { explicit nontype_t() = default; };

  // (2)
  template< auto V >
  constexpr std::nontype_t<V> nontype {};
  ```
- **Description**
  - オーバーロード解決のためのタグ
  - see: `std::function_ref`


## Pairs and tuples


### `std::pair <utility>`
- <https://en.cppreference.com/w/cpp/utility/pair>
- see: [`std::pair.md`](./std::pair.md)


### `std::tuple <tuple>`
-


### `std::apply <tuple>`


### `std::make_from_tuple <tuple>`


### Tuple protocol


#### `std::tuple_size`


#### `std::tuple_element`


## Sum types and type erased wrappers


## Bitset


## Bit manipulation


## Function objects


## Hash support
