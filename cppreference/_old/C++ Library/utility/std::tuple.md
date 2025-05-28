# std::tuple
- <https://en.cppreference.com/w/cpp/utility/tuple>
- 任意の定数個数の型を保持するクラス

- **Definition**
  ```C++
  template< class... Types >
  struct tuple;
  ```


## Member functions


### (constructor)

```C++
// (1)
constexpr tuple();

// (2)
tuple( const Types&... args );

// (3)
template< class... UTypes >
tuple( UTypes&&... args );

// (4)
template< class... UTypes >
constexpr tuple( tuple<UTypes...>& other );

// (5)
template< class... UTypes >
tuple( const tuple<UTypes...>& other );

// (6)
template< class... UTypes >
tuple( tuple<UTypes...>&& other );

// (7)
template< class... UTypes >
constexpr tuple( const tuple<UTypes...>&& other );

// (8)
template< class U1, class U2 >
constexpr tuple( std::pair<U1, U2>& p );

// (9)
template< class U1, class U2 >
tuple( const std::pair<U1, U2>& p );

// (10)
template< class U1, class U2 >
tuple( std::pair<U1, U2>&& p );

// (11)
template< class U1, class U2 >
constexpr tuple( const std::pair<U1, U2>&& p );

// (12)
template< tuple-like UTuple >
constexpr tuple( UTuple&& u );

// (13)
tuple( const tuple& other ) = default;

// (14)
tuple( tuple&& other ) = default;
```


### `operator=`
- <https://en.cppreference.com/w/cpp/utility/tuple/operator%3D>


### `swap`
- <https://en.cppreference.com/w/cpp/utility/tuple/swap>

```C++
// (1)
constexpr void swap( tuple& other ) noexcept( /* see below */ );

// (2)
constexpr void swap( const tuple& other ) noexcept(/* see below */) const;
```


## Non-member functions


### `make_tuple`


### `tie`


### `forward_as_tuple`


### `tuple_cat`


### `get`


### `operator==`


### `std::swap`
