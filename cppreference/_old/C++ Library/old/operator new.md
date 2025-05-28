# operator new, operator new[] <new>
- <https://en.cppreference.com/w/cpp/memory/new/operator_new>


## Syntax
 1. `void* operator new  ( std::size_t count );`
 2. `void* operator new[]( std::size_t count );`
 3. `void* operator new  ( std::size_t count, std::align_val_t al );`
 4. `void* operator new[]( std::size_t count, std::align_val_t al );`
 5. `void* operator new  ( std::size_t count, const std::nothrow_t& tag ) noexcept;`
 6. `void* operator new[]( std::size_t count, const std::nothrow_t& tag ) noexcept;`
 7. `void* operator new  ( std::size_t count, std::align_val_t al, const std::nothrow_t& tag ) noexcept;`
 8. `void* operator new[]( std::size_t count, std::align_val_t al, const std::nothrow_t& tag ) noexcept;`
 9. `void* operator new  ( std::size_t count, void* ptr );`
10. `void* operator new[]( std::size_t count, void* ptr );`
11. `void* operator new  ( std::size_t count, /* args... */ );`
12. `void* operator new[] ( std::size_t count, /* args... */ );`
13. `void* operator new  ( std::size_t count, std::align_val_t al, /* args... */ );`
14. `void* operator new[] ( std::size_t count, std::align_val_t al, /* args... */ );`
15. `void* T::operator new  ( std::size_t count );`
16. `void* T::operator new[]( std::size_t count );`
17. `void* T::operator new  ( std::size_t count, std::align_val_t al );`
18. `void* T::operator new[]( std::size_t count, std::align_val_t al );`
19. `void* T::operator new  ( std::size_t count, /* args... */ );`
20. `void* T::operator new[]( std::size_t count, /* args... */ );`
21. `void* T::operator new  ( std::size_t count, std::align_val_t al, /* args... */ );`
22. `void* T::operator new[]( std::size_t count, std::align_val_t al, /* args... */ );`


## Description
- 分類
  - 1- 4: Replaceable allocation functions
  - 5- 8: Replaceable non-throwing allocation functions
  - 9-10: Non-allocating placement allocation functions
  - 11-14: User-defined placement allocation functions
  - 15-18: Class-specific allocation functions
  - 19-22: Class-specific placement allocation functions
- 1-8 はデフォルト実装があり、replace 可能
- 9-10 は placement new で、何もせずに `ptr` を返す
  - `ptr` が nullptr なら UB
- 11-22 は User-defined


## Parameters
- `count`
  - allocation bytes
- `ptr`
  - pointer to memory area
- `tag`
  - non-throwing overload を選択するためのタグ
- `al`
  - alignment
  - 不正な値なら UB


## Return value
- 1-4
  - 成功した場合、`size` を格納できる non-null pointer
  - 失敗したら例外が出るので返り値無し
- 5-8
  - 1-4 に同じだが、失敗時は null pointer を返す
- 9-10
  - `ptr`
- 1-4 に同じ


## Exceptions
- 1-4
  - 失敗時に `std::bad_alloc`
- 11-22
  - 1-4 に同じ


## Global replacements
- 1-8 は overload 可能で、デフォルト挙動は次の通り
1. メモリを割り当てる
   - 成功したらポインタを返す
   - 失敗して new-handler が登録されていないなら `std::bad_alloc` を投げる
   - 失敗して new-handler があるならそれを試す
2. `operator new(count)`
3. 1 に同じ
4. `operator new(count, al)`
- 5-8 は `tag` がある以外 1-4 と同じ
- 11-14 は任意の引数を加えて overload 可能
- 9-10 は replace 不可能
  - つまり `::new` (global scope) 以外の形で参照されなければならない


## Class-specific overloads
- public static member function の形で宣言可能
  - `T::new` の形で呼び出せる
    - `::new` は強制的に global scope
  - static は付けなくともよいが、暗黙的に static になる
- alignment が `__STDCPP_DEFAULT_NEW_ALIGNMENT__` を超えた場合、alignment 有り=>無しの順で探索される
  - 常に `T::new` が優先


## Notes
- placement new は overload できないが、class scope で同じシグネチャの関数は定義できる
- 以下の関数は Thread-safe でなければならない
  - library version の operator new / operator delete
  - User replacement された global operator new / operator delete
  - `std::calloc`, `std::malloc`, `std::realloc`, `std::aligned_alloc`, and `std::free`
