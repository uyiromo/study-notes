# Memory management library `<memory>`
- <https://en.cppreference.com/w/cpp/memory>


## Smart pointers (since C++11)


### Pointer categories


#### `std::unique_ptr`
- <https://en.cppreference.com/w/cpp/memory/unique_ptr>
- **Definition**
  ```C++
  template<
      class T,
      class Deleter = std::default_delete<T>
  > class unique_ptr;

  template <
      class T,
      class Deleter
  > class unique_ptr<T[], Deleter>;
  ```
- **Description**
  - ポインタを介して要素を所有し、スコープを抜けるときに自動的に解放する
    - つまり `T*` が well-formed でなければならない
  - `const unique_ptr<T>` は、所有権の移動が不可能になる
- **Member functions**
  | Name          | Description                              |
  | :------------ | :--------------------------------------- |
  | (constructor) | **move 可能で、copy 不可**               |
  | (destructor)  | -                                        |
  | `operator=`   | **move assign 可能で、copy assign 不可** |
- **Modifiers**
  | Name        | Description                                  |
  | :---------- | :------------------------------------------- |
  | `release()` | 所有しているポインタを返して所有権を放棄する |
  | `reset()`   | 所有しているポインタを解放して、再設定する   |
  | `swap()`    | ポインタを swap する                         |
- **Observers**
  | Name            | Description                                     |
  | :-------------- | :---------------------------------------------- |
  | `get()`         | 所有しているポインタを返す (所有権は放棄しない)  |
  | `get_deleter()` | deleter を返す                                  |
  | `operator bool` | 所有しているポインタが nullptr かどうかを返す    |
- **operator**
  | Name            | Description                                     |
  | :-------------- | :---------------------------------------------- |
  | `operator*`     | `*get()` に同じで `T&` を返す        |
  | `operator->`    | `get()` に同じで `pointer` を返す         |
  | `operator[]`    | i 番目の要素の参照を返す         |
- **Non-member functions**
  | Name          | Description                         |
  | :------------ | :---------------------------------- |
  | `make_unique` | `std::unique_ptr<T>` を構築して返す |
  | (比較)        | ポインタを比較する                  |
  | `operator<<`  | ポインタの出力                      |
  | `swap`        | **Modifiers** の `swap()` 呼び出し  |


#### `std::shared_ptr`
- <https://en.cppreference.com/w/cpp/memory/shared_ptr>
- **Definition**
  ```C++
  template< class T > class shared_ptr;
  ```
- **Description**
  - ポインタを介して要素を**共有**し、スコープを抜けるときに自動的に解放する
    - つまり `T*` が well-formed でなければならない
    - 最後の所有者が破壊されるか、`=` `reset()` で代入されるときに解放される（所有カウント）
  - 複数の threads が、同一の `shared_ptr` に対して、同期無しで操作可能
    - ただし、non-const member function を実行した場合、data race が発生しうる
      - `std::atomic<shared_ptr>>` で防止可能
    - use_count は thread-safe なことが保証されている
  - 多くの場合、control block と pointer を持つ
    - control block
      - object pointer
      - deleter
      - allocator
      - shared_ptrs の所有カウント
      - weak_ptrs の所有カウント
- **Member functions**
  | Name          | Description                         |
  | :------------ | :---------------------------------- |
  | (constructor) | **move も copy も可能**             |
  | (destructor)  | -                                   |
  | `operator=`   | **move assign も copy assign 可能** |
- **Modifiers**
  | Name      | Description                                |
  | :-------- | :----------------------------------------- |
  | `reset()` | 所有しているポインタを解放して、再設定する |
  | `swap()`  | ポインタを swap する                       |
- **Observers**
  | Name             | Description                                                             |
  | :--------------- | :---------------------------------------------------------------------- |
  | `get()`          | 所有しているポインタを返す                                               |
  | `operator*`      | `*get()` に同じで `T&` を返す                                           |
  | `operator->`     | `get()` に同じで `T*` を返す                                            |
  | `operator[]`     | idx 番目の要素の参照 `get()[idx]` を返す                                |
  | `use_count()`    | 所有カウントを返す <br> マルチスレッド環境では必ずしも正しくない        |
  | `operator bool`  | 所有しているポインタが nullptr かどうかを返す                           |
  | `owner_before()` | owner の前後関係を返す <br> 多くの場合、control block の address を比較 |
  | `owner_hash()`   | owner のハッシュ値を返す                                                |
  | `owner_equal()`  | ownership が同一か返す                                                  |
- **Non-member functions**
  | Name              | Description                                                                 |
  | :---------------- | :-------------------------------------------------------------------------- |
  | `make_shared`     | `std::shared_ptr<T>` を構築して返す                                         |
  | `allocate_shared` | 指定された Allocator で確保した `std::shared_ptr<T>` を構築して返す         |
  | `*_pointer_cast`  | 所有しているポインタをキャストして、所有権を共有する `shared_ptr<T>` を返す |
  | `get_deleter`     | deleter を返す                                                              |
  | (比較)            | ポインタを比較する                                                          |
  | `operator<<`      | ポインタの出力                                                              |
  | `swap`            | **Modifiers** の `swap()` 呼び出し                                          |
- **Helper functions**
  | Name                      | Description                                |
  | :------------------------ | :----------------------------------------- |
  | `std::atomic<shared_ptr>` | `std::atomic` で `shared_ptr` をラップする |


#### `std::weak_ptr`
- <https://en.cppreference.com/w/cpp/memory/weak_ptr>
- **Definition**
  ```C++
  template< class T > class weak_ptr;
  ```
- **Description**
  - `std::shared_ptr` によって管理される object に対して、参照を持つが所有しないポインタ
    - アクセスするには、`std::shared_ptr` に変換する必要がある
  - 存在する場合のみアクセスする一時所有権を表す
- **Member functions**
  | Name          | Description                         |
  | :------------ | :---------------------------------- |
  | (constructor) | `shared_ptr` から作成可能          |
  | (destructor)  | -                                   |
  | `operator=`   | `shared_ptr` から作成可能          |
- **Modifiers**
  | Name      | Description                                |
  | :-------- | :----------------------------------------- |
  | `reset()` | 所有しているポインタを解放する |
  | `swap()`  | ポインタを swap する                       |
- **Observers**
  | Name             | Description                                                                 |
  | :--------------- | :-------------------------------------------------------------------------- |
  | `use_count()`    | 参照している shared_ptr の所有カウントを返す                                |
  | `expired()`      | `use_count() == 0` に同じ                                                   |
  | `lock()`         | `shared_ptr` に変換して返す <br> Constructor と異なり、空でも例外を投げない |
  | `owner_before()` | owner の前後関係を返す <br> 多くの場合、control block の address を比較     |
  | `owner_hash()`   | owner のハッシュ値を返す                                                    |
  | `owner_equal()`  | ownership が同一か返す                                                      |


### Helper classes
| Name                           | Description                                                                      |
| :----------------------------- | :------------------------------------------------------------------------------- |
| `std::owner_less`              | shared/weak ptr を control block で比較する関数オブジェクト                      |
| `std::owner_hash`              | shared/weak ptr の control block ハッシュ値を計算する関数オブジェクト            |
| `std::owner_equal`             | shared/weak ptr を control block で比較を行う関数オブジェクト                    |
| `std::enable_shared_from_this` | `std::shared_ptr` で共有可能なことを示す基底クラス                               |
| `std::bad_weak_ptr`            | deleted な要素を指す `std::weak_ptr` から `std::shared_ptr` を作成したときの例外 |
| `std::default_delete`          | `std::unique_ptr` のデフォルト deleter                                           |


### Smart pointer adaptors (since C++23)
| Name               | Description                                                                                |
| :----------------- | :----------------------------------------------------------------------------------------- |
| `std::out_ptr_t`   | 二重ポインタで値を出力する関数に対して、smart pointer を指定する際のアダプタテンプレート   |
| `std::out_ptr`     | `std::out_ptr_t` を返す関数                                                                |
| `std::inout_ptr_t` | 二重ポインタで値を入出力する関数に対して、smart pointer を指定する際のアダプタテンプレート |
| `std::inout_ptr`   | `std::inout_ptr_t` を返す関数                                                              |


## Allocators
- (T.B.D.)


## Memory resources (since C++17)
- (T.B.D.)


## Uninitialized memory algorithms
- uninitialized memory に対して操作を行う
  - `malloc` 直後のメモリ等は未初期化なので deref が UB になる
  - この領域に対して placement new を行い、その領域に object を構築する
- `ExecutionPolicy` 対応

| function name                       | Description                                                  |
| :---------------------------------- | :----------------------------------------------------------- |
| `uninitialized_copy`                | `[first, last]` を `d_first` から始まる範囲にコピーする      |
| `uninitialized_copy_n`              | `[first, first + n]` を `d_first` から始まる範囲にコピーする |
| `uninitialized_fill`                | `[first, last]` を指定した値で埋める                         |
| `uninitialized_fill_n`              | `[first, first + n]` を指定した値で埋める                    |
| `uninitialized_move`                | `[first, last]` を `d_first` から始まる範囲に move する      |
| `uninitialized_move_n`              | `[first, first + n]` を `d_first` から始まる範囲に move する |
| `uninitialized_default_construct`   | `[first, last]` を default construct する                    |
| `uninitialized_default_construct_n` | `[first, first + n]` を default construct する               |
| `uninitialized_value_construct`     | `[first, last]` を value construct する                      |
| `uninitialized_value_construct_n`   | `[first, first + n]` を value construct する                 |
| `destroy_at`                        | 指定したポインタの要素を破棄する                             |
| `destroy`                           | `[first, last]` の要素を破棄する                             |
| `destroy_n`                         | `[first, first + n]` の要素を破棄する                        |
| `construct_at`                      | 指定したポインタに placement new で要素を構築する            |


## Constrained uninitialized memory algorithms (since C++20)
- **Uninitialized memory algorithms** を `ranges::` 名前空間で宣言して、concept を追加したもの
- **std::uninitialized_copy**
  ```C++
  template< class InputIt, class NoThrowForwardIt >
  NoThrowForwardIt uninitialized_copy( InputIt first, InputIt last,
                                      NoThrowForwardIt d_first );
  ```
- **std::ranges::uninitialized_copy**
  ```C++
  template< std::input_iterator I, std::sentinel_for<I> S1,
            no-throw-forward-iterator O, no-throw-sentinel-for<O> S2 >
      requires std::constructible_from<std::iter_value_t<O>,
                                      std::iter_reference_t<I>>
  uninitialized_copy_result<I, O>
      uninitialized_copy( I ifirst, S1 ilast, O ofirst, S2 olast );
  ```


## Explicit lifetime management (since C++23)
- <https://en.cppreference.com/w/cpp/memory/start_lifetime_as>
- 既存のポインタが示す領域 `p` を示す型 `T` の object の lifetime を開始する
  ```C++
  template< class T >
  T* start_lifetime_as( void* p ) noexcept;
  ```
  - `reinterpret_cast` で型を変換した場合、変換先の型としての lifetime が保証されていない


## Types for composite class design (since C++26)


### `std::indirect`
- <https://en.cppreference.com/w/cpp/memory/indirect>
- 値を持たないかもしれない (valueless な可能性がある) object


### `std::polymorphic`
- <https://en.cppreference.com/w/cpp/memory/polymorphic>
- Polymorphic アロケータ


## Miscellaneous


### `std::pointer_traits`
- <https://en.cppreference.com/w/cpp/memory/pointer_traits>
- pointer-like な型の traits
- rebind は次のような型
  ```C++
  template< class Ptr >
  class pointer_traits {
    template <class U>
    using rebind = Ptr::rebind<U>;

    template <class U>
    using rebind = Ptr<U, Args...>
  }
  ```


### `std::to_address`
- <https://en.cppreference.com/w/cpp/memory/to_address>
- テンプレート型 `Ptr` を、生ポインタに変換する


### `std::addressof`
- <https://en.cppreference.com/w/cpp/memory/addressof>
- 型 `T` の object のアドレスを取得する
- 次のようなケースだと `&` が ADL になって、incomplete type を参照するので失敗
  ```C++
  template<class T>
  struct holder { T t; };

  struct incomp;

  int main()
  {
      holder<holder<incomp>*> x{};
      // &x; // error: argument-dependent lookup attempts to instantiate holder<incomp>
      std::addressof(x); // OK
  }
  ```


### `std::align`
- <https://en.cppreference.com/w/cpp/memory/align>
- アラインメントしたポインタを返す


### `std::assume_aligned`
- <https://en.cppreference.com/w/cpp/memory/assume_aligned>
- コンパイラに「このポインタは、指定したアラインメントでアラインされている」と伝える


### `std::is_sufficiently_aligned`
- <https://en.cppreference.com/w/cpp/memory/is_sufficiently_aligned>
- ポインタが、指定したアラインメントでアラインされているかを判定する


## Low level memory management
- (T.B.D.)


## C-style memory management
- (T.B.D.)


## Uninitialized storage (until C++20)
- 省略


## Garbage collector support (until C++23)
- 省略
