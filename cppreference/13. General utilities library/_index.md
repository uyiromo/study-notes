# Utility library
- <https://en.cppreference.com/w/cpp/utility.html>


## Language support


### Type support
- size_t
  - sizeof で返される unsigned integer 型
- ptrdiff_t
  - ポインタの差を表す signed integer 型
- nullptr_t
- NULL
- max_align_t
- offset_of
  - `#define offsetof(type, member)` で `type` の `member` のオフセットを取得する
- byte
- Fixed width integer types
- Fixed width floating-point types (C++23)
- numeric_limits
- type_info
- bad_typeid
- bad_cast
- type_index
  - type_info のハッシュ値を取得するための型


### Program utilities
- abort
- exit
- quick_exit
- _EXit
- atexit
- at_quick_exit
- EXIT_SUCCESS / EXIT_FAILURE
- unreachable
- system
- getenv
- signal
- raise
-


### Dynamic memory management
- see: `Memory Management Library`


### Error handling
- see: `Diagnostics Library`


### Variadic functions
- va_start
- va_arg
- va_copy
- va_end
- va_list


### Initializer lists
- initializer_list
  - read-only な std::array proxy


### Source code information and capture
- source_location


### Three-way comparison
- three_way_comparable / three_way_comparable_with
- partial_ordering
- weak_ordering
- strong_ordering
- ordering から bool への変換
  - is_eq
  - is_neq
  - is_lt
  - is_lteq
  - is_gt
  - is_gteq
- compare_three_way
  - 3-way comparison を行う関数オブジェクト
- compare_three_way_result
- common_comparison_category
- 3-way CPO
  - strong_order
  - weak_order
  - partial_order
- fallback
  - compare_strong_order_fallback
  - compare_weak_order_fallback
  - compare_partial_order_fallback


### Coroutine support
- (TBD)


### Contract support
- (TBD)


## General-purpose utilities


### Swap
- swap
- exchange
- ranges::swap


### Type operations
- forward
- forward_like
  - forward とほぼ同じだが、型推論が働く
- move
- move_if_noexcept
- as_const
  - `T&` を `const T&` に変換する
- declval
- to_underlying


### Integer comparison functions
- cmp_equal
- cmp_not_equal
- cmp_less
- cmp_greater
- cmp_less_equal
- cmp_greater_equal
- in_range


### Relational operators
- (deprecated in C++20)


### Construction tags
- piecewise_construct
  - pair の要素を直接構築する
- inplace
  - expected, optional の要素を直接構築する
- inplace_type
  - any, variant(型指定) の型を直接構築する
- inplace_index
  - variant(位置指定) の型を直接構築する


### Pairs and tuples
- pair
- tuple
- apply
  - tuple の要素を分解して関数に渡して実行
- make_from_tuple
  - tuple の要素を分解してコンストラクトする


### Sum types and type erased wrappers
- optional
- expected
- variant
- any
  - 任意の型。any_cast で取り出す


### Bitset
- bitset


### Bit manipulation
- ビット列の操作
- bit_cast
- byteswap
- has_single_bit
- bit_ceil
- bit_floor
- bit_width
- rotl
- rotr
- countl_zero
- countl_one
- countr_zero
- countr_one
- popcount
- endian


### Function objects
- function
- move_only_function
- copyable_function
- function_ref
- bad_function_call
- mem_fn
- identity
- bind_front / bind_back
- bind
- placeholder
- not_fn
- reference_wrapper
- ref / cref
- unwrap_reference / unwrap_ref_decay
- 算術関数オブジェクト
  - plus
  - minus
  - multiplies
  - divides
  - modulus
  - negate
- 比較関数オブジェクト
  - equal_to
  - not_equal_to
  - greater
  - less
  - greater_equal
  - less_equal
- 論理関数オブジェクト
  - logical_and
  - logical_or
  - logical_not
- bitwise
  - bit_and
  - bit_or
  - bit_xor
  - bit_not
- Concept 付き関数オブジェクト
  - ranges::equal_to
  - ranges::not_equal_to
  - ranges::less
  - ranges::greater
  - ranges::less_equal
  - ranges::greater_equal
  - ranges::three_way


### Hash support

