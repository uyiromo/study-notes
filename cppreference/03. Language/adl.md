# ADL (Argument-dependent lookup)
- <https://en.cppreference.com/w/cpp/language/adl.html>
- **unqualified** な関数呼び出しの探索ルール
  - unqualified name lookup に加えて、引数の名前空間に対して探索される

```C++
// operator<<(std::ostream&, const char*) は global namespace には存在しない
// ADL によって第一引数の名前空間 std が探索されて、
// std::operator<<(std::ostream&, const char*) が見つかる
std::cout << "Test\n";
```


## Details
- unqualified name lookup (namespace 修飾無し) が次のものを発見した場合、ADL は動作しない
  1. クラスメンバ宣言
  2. block scope 内の関数宣言
  3. 関数ではない、名前の衝突する何らかの宣言
     - 関数オブジェクトは関数ではないので考慮されない（=> CPO が発見されたら ADL を行わない）
- 関数呼び出しの各引数について次のチェックを行い、namespace/class を探索候補に加える
  1. fundamental type なら、何もしない
  2. class type なら
     1. class 自身
     2. class が complete なら、全ての base class
     3. class が another class のメンバ (nested class) なら、その another class
     4. class が所属する、innermost な namespace
  3. class template specialization なら、その class に加えて、
     1. 全ての template の型 (constant template と template template は除外)
     2. template template が所属する namespace
     3. template template が所属する class
  4. enumeration type なら、
     1. 宣言された最内側 namespace
     2. class member なら、その class
  5. pointer to T / pointer to an array of T なら、`T` に対して検査
  6. function type なら、function parameter type と return type に対して検査
  7. pointer to member function なら、function と class に対して検査
  8. pointer to data member なら、member type と class に対して検査
  9. name or address-of-expression for a set of overloaded function なら、それを検査
- inline namespace なら、それを囲む namespace を追加
- 以降 TODO
- ADL による正しい呼び出しは
  ```C++
  using std::swap;
  swap(obj1, obj2);
  ```
  - `std::swap(obj1, obj2)` は、obj1 もしくは obj2 class で定義された `swap` を迂回する

