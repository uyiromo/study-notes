# std::set_new_handler <new>
- <https://en.cppreference.com/w/cpp/memory/new/set_new_handler>


## Syntax
1. `std::new_handler set_new_handler( std::new_handler new_p ) noexcept;`


## Description
1. `new_p` をセットして、それまでセットされていた new-handler を返す


## Parameters
- `new_p`
  - new-handler (nullable)


## Return value
- 現在 install されている new-handler (nullable)


## Exceptions
- (none)


## Notes
- (none)
