# bitset `<bitset>`
- <https://en.cppreference.com/w/cpp/utility/bitset.html>
- 固定長のビット列
  - CopyConstruct 可能で、CopyAssign 可能
  - 右側のビットが最下位ビット

- **Definition**
  ```C++
  template< std::size_t N >
  class bitset;
  ```

- see: [./tests/bitset.cpp](./tests/bitset.cpp)


## Member types
- reference
  - ネストされた型で、特定の 1 ビットを参照する


## Member functions
- (constructor)
  - 整数値から構築する場合
    - bitset の方が小さい場合、下位ビットのみを使用する
    - bitset の方が大きい場合、上位ビットは 0 で埋める
- operator==
  - ビット数が同じ場合に限り、ビット列を比較する
  - 値の無いビットは 0 として扱う


## Element access
- operator[]
  - const な文脈では `bool`
  - non-const な文脈では `std::bitset<N>::reference`
- test
  - 指定したビットが 1 かどうかを返す
- all / any / none
  - 全てのビットを検査して返す
- count
  - 1 のビット数を返す


## Capacity
- size
  - ビット数を返す


## Modifiers
- operator&= / |= / ^= / ~
- operator<<= / >>= / << / >>
- set
  - 全ビットを true にする or 特定ビットの値を設定する
- reset
  - 全ビットを false にする or 特定ビットを false にする
- flip
  - 全ビットを反転する or 特定ビットを反転する


## Conversions
- to_string
- to_ulong
  - 表現できない場合は `std::overflow_error` 例外を投げる
- to_ullong


## Non-member functions
- operator & | ^
  - bitset 同士で計算した結果を返す
- operator << >>
  - ostream への出力
  - istream からの入力


## Helper classes
- std::hash
