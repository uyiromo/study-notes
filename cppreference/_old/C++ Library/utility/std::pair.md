# std::pair
- <https://en.cppreference.com/w/cpp/utility/pair>
- 2つの値を保持するためのクラス


## Definition

```C++
template< class T1, class T2 >
struct pair;
```


## Member types

| Member type   | Definition |
| ------------- | ---------- |
| `first_type`  | `T1`       |
| `second_type` | `T2`       |


## Member objects

| Member object | Definition |
| ------------- | ---------- |
| `first`       | `T1`       |
| `second`      | `T2`       |


## Member functions


### (constructor)
- 要素をそれぞれ construct する
- 対応するコンストラクタが無い場合、overload resolution に参加しない

```C++
// (1)
// t1 = T1()
// t2 = T2()
pair();

// (2)
// t1 = T1(const T1& x)
// t2 = T2(const T2& y)
pair( const T1& x, const T2& y );

// (3)
// t1 = T1(std::forward<U1>(x))
// t2 = T2(std::forward<U2>(y))
template< class U1 = T1, class U2 = T2 >
constexpr pair( U1&& x, U2&& y );

// (4)
// t1 = T1(U1& p.first)
// t2 = T2(U2& p.second)
template< class U1, class U2 >
constexpr pair( pair<U1, U2>& p );

// (5)
// t1 = T1(const U1& p.first)
// t2 = T2(const U2& p.second)
template< class U1, class U2 >
pair( const pair<U1, U2>& p );

// (6)
// t1 = T1(std::forward<U1>(p.first))
// t2 = T2(std::forward<U2>(p.second))
template< class U1, class U2 >
pair( pair<U1, U2>&& p );

// (7)
// t1 = T1(std::forward<const U1>(p.first))
// t2 = T2(std::forward<const U2>(p.second))
template< class U1, class U2 >
constexpr pair( const pair<U1, U2>&& p );

// (8)
// t1 = std::get<0>(std::forward<U1>(p.first))
// t2 = std::get<1>(std::forward<U2>(p.second))
template< pair-like P >
constexpr pair( const pair<U1, U2>&& p );

// (9)
// tuple の要素を分解して、各コンストラクタに転送する
template< class... Args1, class... Args2 >
pair( std::piecewise_construct_t,
           std::tuple<Args1...> first_args,
           std::tuple<Args2...> second_args);

// (10)
pair(const pair& p) = default;

// (11)
pair(pair&& p) = default;
```


### `operator=`
- <https://en.cppreference.com/w/cpp/utility/pair/operator%3D>

```C++
// (1)
constexpr pair& operator=( const pair& other );

// (2)
constexpr const pair& operator=( const pair& other ) const;

// (3)
template< class U1, class U2 >
constexpr pair& operator=( const pair<U1, U2>& other );

// (4)
// 要素ごとにコピー代入
template< class U1, class U2 >
constexpr const pair& operator=( const pair<U1, U2>& other ) const;

// (5)
// 全要素をムーブ代入
constexpr pair& operator=( pair&& other ) noexcept(/* see below*/);

// (6)
constexpr const pair& operator=( pair&& other ) const;

// (7)
template< class U1, class U2 >
constexpr pair& operator=( pair<U1, U2>&& p );

// (8)
template< class U1, class U2 >
constexpr const pair& operator=( pair<U1, U2>&& p ) const;

// (9)
template< pair-like P >
constexpr pair& operator=( P&& u );

// (10)
template< pair-like P >
constexpr const pair& operator=( P&& u ) const;
```


### `swap`
- <https://en.cppreference.com/w/cpp/utility/pair/swap>
- 要素ごとに swap する

```C++
// (1)
constexpr void swap( pair& other ) noexcept(/* see below */);

// (2)
// C++23
// const は要素に伝播しない
constexpr void swap( const pair& other ) const noexcept(/* see below */);
```


## Non-member functions


### `std::make_pair`
- <https://en.cppreference.com/w/cpp/utility/pair/make_pair>
- `std::decay` するため、配列はポインタになる

```C++
// std::decay した後、reference を外す
template< class T1, class T2 >
constexpr std::pair<std::unwrap_ref_decay_t<T1>,
                    std::unwrap_ref_decay_t<T2>>
    make_pair( T1&& x, T2&& y );
```


### `operator`
- <https://en.cppreference.com/w/cpp/utility/pair/operator_cmp>

```C++
template< class T1, class T2, class U1, class U2 >
constexpr bool operator==( const std::pair<T1, T2>& lhs,
                           const std::pair<U1, U2>& rhs );

template< class T1, class T2, class U1, class U2 >
constexpr std::common_comparison_category_t<synth-three-way-result<T1, U1>,
                                            synth-three-way-result<T2, U2>>
    operator<=>( const std::pair<T1, T2>& lhs, const std::pair<U1, U2>& rhs );
```


### `std::swap<std::pair>`
- <https://en.cppreference.com/w/cpp/utility/pair/swap2>

```C++
template< class T1, class T2 >
constexpr void swap( std::pair<T1,T2>& x, std::pair<T1,T2>& y )
    noexcept(/* see below */);

template< class T1, class T2 >
constexpr void swap( const std::pair<T1,T2>& x, const std::pair<T1,T2>& y )
    noexcept(/* see below */);
```


### `std::get`
- <https://en.cppreference.com/w/cpp/utility/pair/get>

```C++
// I = 0 なら first、I = 1 なら second の参照を返す
template< std::size_t I, class T1, class T2 >
typename std::tuple_element<I, std::pair<T1,T2> >::type&
    get( std::pair<T1, T2>& p ) noexcept;

// type-base で、型に対応する要素の参照を返す
// T = U の場合は ill-formed
template< class T, class U >
constexpr T& get( std::pair<T, U>& p ) noexcept;
```


## Helper classes


### `std::tuple_size<std::pair>`
- <https://en.cppreference.com/w/cpp/utility/pair/tuple_size>

```C++
template< class T1, class T2 >
struct tuple_size<std::pair<T1, T2>>
    : std::integral_constant<std::size_t, 2> { };
```


### `std::tuple_element<std::pair>`
- <https://en.cppreference.com/w/cpp/utility/pair/tuple_element>
- 指定されたインデックスに対応する要素の型を返す


```C++
template< std::size_t I, class T1, class T2 >
struct tuple_element<I, std::pair<T1, T2>>
{
    using type = typename std::conditional<I == 0, T1, T2>;
};
```


### `std::basic_common_reference<std::pair>`
- <https://en.cppreference.com/w/cpp/utility/pair/basic_common_reference>
- 各要素の共通参照型のペアを返す


```C++
template< class T1, class T2, class U1, class U2,
          template<class> class TQual, template<class> class UQual >
  requires requires { typename std::pair<std::common_reference_t<TQual<T1>, UQual<U1>>,
                                         std::common_reference_t<TQual<T2>, UQual<U2>>>; }
struct basic_common_reference<std::pair<T1, T2>, std::pair<U1, U2>, TQual, UQual>;
```


### `std::common_type<std::pair>`
- <https://en.cppreference.com/w/cpp/utility/pair/common_type>
- 各要素の共通型のペアを返す


```C++
template< class T1, class T2, class U1, class U2 >
  requires requires { typename std::pair<std::common_type_t<T1, U1>,
                                         std::common_type_t<T2, U2>>; }
struct common_type<std::pair<T1, T2>, std::pair<U1, U2>>;
```


### `std::formatter<std::pair>`
- <https://en.cppreference.com/w/cpp/utility/format/tuple_formatter>
- `std::formatter` の pair/tuple 特殊化

