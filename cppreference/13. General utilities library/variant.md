# variant `<variant>`
- <https://en.cppreference.com/w/cpp/utility/variant.html>
- 型安全な union
  - union と同じく、一つの型をネストして保持する
- 参照・配列・void は保持できない
- 同じ型を複数保持したり、CV が異なる同じ型を保持できる
- `std::monostate`

- **Definition**
  ```C++
  template< class... Types >
  class variant;
  ```

- see: [./tests/variant.cpp](./tests/variant.cpp)


## Member functions
- (constructor)
  - default construct した場合、最初の型を保持する
  - copy/move construct した場合、保持している型をコピー/ムーブする
  - 型 `T` を move construct 可能
  - 直接構築する場合、`std::inplace_type_t<T>` を使用する
    - 要素を指定する場合は `std::inplace_index_t<N>` を使用する
- (destructor)
- operator=
  - 全ての型が Copy/Move 可能な場合に限り、Copy/Move 可能


## Observers
- index
  - 現在保持している型の index を `std::size_t` で返す
- valueless_by_exception
  - 値を保持していない場合のみ `true` を返す
  - コピー代入・代入・型変換 emplace で例外が発生した場合など


## Modifiers
- emplace
  - 型指定で直接構築する
    ```C++
    template< class T, class... Args >
    T& emplace( Args&&... args );
    ```
  - 位置指定で直接構築
    ```C++
    template< std::size_t I, class... Args >
    std::variant_alternative_t<I, variant<Types...>>& emplace( Args&&... args );
    ```
- swap
  - 現在の値と引数の値を交換する


## Visitation
- visit
  - (TBD)


## Non-member functions
- visit
  - variant の全ての型に対するオーバーロードを持つ関数 `Visitor` に variant を与えた結果を取得する
    - 返り値の型は、取りうる型全てに対応する型
  - 一つの Visitor で全ての型に対応するため、次の 2 つの方法を使う
    - `auto&&` で変数を受ける
    - ラムダ式オーバーロードを使う
- holds_alternative
  - 型 `T` を現在保持しているか判定する
  - `T` が複数回指定された場合、ill-formed
- get
  - 位置指定 or 型指定で参照を取得
  - &/&&, const は引数の属性を引き継ぐ
- get_if
  - 位置指定 or 型指定で参照を取得
  - ポインタを渡してポインタを返す
    - 取得できない場合は `nullptr`
  - 例外を投げない
- operator==
  - `==` は、インデックスが同じかつ要素が同じ
    - `GET<I>(lhs) == GET<I>(rhs)`
  `<` は、インデックスが同じなら要素同士、違うならインデックスで比較
    - `GET<I>(lhs) < GET<I>(rhs)`
    - `lfs.index() < rhs.index()`
- std::swap


## Helper classes
- monostate
  - デフォルト構築可能な型
  - variant の最初の型として使うと variant がデフォルト構築可能になる
- bad_variant_access
  - `get` で発生する例外
- variant_size
  - variant の保持している型の数を `std::size_t` で取得する
  - `variant_size_v`
- variant_alternative
  - variant の保持している型を index で取得する
- std::hash


## Helper objects
- variant_npos
  - `std::size_t` の max
  - 値を持たないときの index として使用される
