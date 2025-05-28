# std::launder <new>
- <https://en.cppreference.com/w/cpp/utility/launder>


## Syntax
1. `template< class T > constexpr T* launder( T* p ) noexcept;`


## Description
1. `p` に対して Devirtualization を行う


## Parameters
- (none)


## Return value
- (none)


## Exceptions
- (none)


## Notes
- 典型的なユースケース
  1. 同じ型の既存 object 内に作成された object へのポインタを取得する
     - 新旧いずれかが base class subobject など、old object へのポインタが使えない場合
  2. 既存 object へのポインタを介して placement new で作成された object へのポインタ取得
- コンパイラに対して、その時点での最適化無しで正確なポインタを返させる

