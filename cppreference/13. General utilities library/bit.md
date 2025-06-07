# Bit manipulation
- <https://en.cppreference.com/w/cpp/utility/bit.html>


## cast/swap
- bit_cast
  - 型 `From` の値を示すビット列を、型 `To` として解釈した値を返す
  ```C++
  template< class To, class From >
  constexpr To bit_cast( const From& from ) noexcept;
  ```
- byteswap
  - バイト単位で値を逆順に並べ替える
  ```C++
  template< class T >
  constexpr T byteswap( T n ) noexcept;
  ```


## Integral powers of 2
- has_single_bit
  - `std::has_single_bit(x)` は `x` が 2 の累乗なら `true` を返す
- bit_ceil
  - `std::bit_ceil(x)` は `x` 以上の最小の 2 の累乗を返す
  - `x` と同じ型で表現できない場合は UB
- bit_floor
  - `std::bit_floor(x)` は `x` 以下の最大の 2 の累乗を返す
  - `x = 0` なら `0` を返す
- bit_width
  - `std::bit_width(x)` は `x` を表現するのに必要なビット数 `1 + floor(log2(x))` を返す
  - `x = 0` なら `0` を返す


## Rotating
- rotl
  - `std::rotl(x, k)` は `x` を左に `k` ビット巡回シフトした値を返す
  - `k` が負なら右に回転
- rotr
  - `std::rotr(x, k)` は `x` を右に `k` ビット巡回シフトした値を返す


## Counting
- countl_zero
  - 最上位ビットから連続する 0 のビット数を返す
- countl_one
  - 最上位ビットから連続する 1 のビット数を返す
- countr_zero
  - 最下位ビットから連続する 0 のビット数を返す
- countr_one
  - 最下位ビットから連続する 1 のビット数を返す
- popcount
  - ビット列に含まれる 1 のビット数を返す


## Endian
- endian
  - `std::endian` は列挙型で、システムのエンディアンを表す
  ```C++
  enum class endian

  {
      little = /* implementation-defined */,
      big    = /* implementation-defined */,
      native = /* implementation-defined */,
  };
  ```

