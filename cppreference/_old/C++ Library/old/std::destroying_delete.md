# std::destroying_delete <new>
- <https://en.cppreference.com/w/cpp/memory/new/destroying_delete>


## Syntax
1. `struct destroying_delete_t { explicit destroying_delete_t() = default; };`
2. `inline constexpr destroying_delete_t destroying_delete{};`


## Description
- destroying delete を呼び出すための tag
  - operator delete の前に destructor を実行しない delete
  - delete が直接 destructor を実行する
  - <https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0722r1.html>


## Parameters
- (none)


## Return value
- (none)


## Exceptions
- (none)


## Notes
- (none)
