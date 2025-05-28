# std::ger_new_handler <new>
- <https://en.cppreference.com/w/cpp/memory/new/get_new_handler>


## Syntax
1. `std::new_handler get_new_handler() noexcept;`


## Description
1. 現在の new-handler を返す。nullptr である可能性がある。
   - この関数は Thread-safe


## Parameters
- (none)


## Return value
- 現在 install されている new-handler (nullable)


## Exceptions
- (none)


## Notes
- (none)
