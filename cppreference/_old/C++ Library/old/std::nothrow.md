# std::nothrow <new>
- <https://en.cppreference.com/w/cpp/memory/new/nothrow>


## Syntax
1. `struct nothrow_t { explicit nothrow_t() = default; };`
2. `extern const std::nothrow_t nothrow;`


## Description
- `std::nothrow` の方を呼び出すための tag
  - 失敗した場合に `std::bad_alloc` ではなく nullptr を返す


## Parameters
- (none)


## Return value
- (none)


## Exceptions
- (none)


## Notes
- (none)
