# any `<any>`
- <https://en.cppreference.com/w/cpp/utility/any.html>
- コピーコンストラクト可能な任意の型を保持する type-safe なコンテナ
- 型は decay されるので、配列・関数・参照は保持できない


- see: [./tests/any.cpp](./tests/any.cpp)


## Member functions
- (constructor)
- operator=
- (destructor)


## Modifiers
- emplace
  - 値の変更 or 直接構築
  - 構築する型の明示が必要
- reset
  - 保持している型を破棄
- swap


## Observers
- has_value
  - 値を保持しているかどうか
- type
  - 保持している型を `std::type_info&` で返す
  - 保持していない場合は `typeid(void)` を返す


## Non-member functions
- std::swap
- any_cast
  - 型を指定して `T` を取得
  - 不正な処理は `bad_any_cast` 例外を投げる
- make_any
  - `std::any` を直接構築する


## Helper classes
- bad_any_cast

