# Metaprogramming library
- <https://en.cppreference.com/w/cpp/meta>
- **Definition**
  - 次に当てはまる型 `T` は、参照を作成可能な referenceable 型
    - object type
    - function type without cv and ref
    - reference type
      - (reference collapsing)
- **Type traits**
  - コンパイル時に template argument の properties を検査する
  - `<type_traits>` ヘッダ specialization は UB
    - `std::common_type` 及び `std::basic_common_reference` は例外
  - **Base classes**
    - non-transforming type traits は `std::integral_constant` を継承する
      - see: `UnaryTypeTrait` `BinaryTypeTrait`
    - `true_type = std::integral_constant<bool, true>`
    - `false_type = std::integral_constant<bool, false>`


## Unary type traits
- `std::true_type` か `std::false_type` から派生する
- 次の Helper を持つ
  ```C++
  template <typename T>
  constexpr bool is_XXX_v = std::is_XXX<T>::value;
  ```


### Primary type categories `<type_traits>`
- cv qualifier, sign を無視して判定する

| trait                             | check する型                     |
| :-------------------------------- | :------------------------------- |
| `std::is_void`                    | void                             |
| `std::is_null_pointer`            | nullptr_t                        |
| `std::is_integral`                | integral type                    |
| `std::is_floating_point`          | floating point type              |
| `std::is_array`                   | array type (`std::array` は除く) |
| `std::is_enum`                    | enumeration type                 |
| `std::is_union`                   | union type                       |
| `std::is_class`                   | class type                       |
| `std::is_function`                | function type                    |
| `std::is_pointer`                 | pointer type                     |
| `std::is_lvalue_reference`        | lvalue reference type            |
| `std::is_rvalue_reference`        | rvalue reference type            |
| `std::is_member_object_pointer`   | member object pointer type       |
| `std::is_member_function_pointer` | member function pointer type     |


### Composite type categories `<type_traits>`
- cv qualifier, sign を無視して判定する


| trait                    | check する型                                   |
| :----------------------- | :--------------------------------------------- |
| `std::is_fundamental`    | fundamental type (arithmetic, void, nullptr_t) |
| `std::is_arithmetic`     | arithmetic type                                |
| `std::is_scalar`         | scalar type (ビット列で表される型)             |
| `std::is_object`         | object type                                    |
| `std::is_compound`       | compound type                                  |
| `std::is_reference`      | reference type                                 |
| `std::is_member_pointer` | member pointer type                            |


### Type properties `<type_traits>`
- 型の性質判定

| trait                                    | check する型                                      |
| :--------------------------------------- | :------------------------------------------------ |
| `std::is_const`                          | const                                             |
| `std::is_volatile`                       | volatile                                          |
| `std::is_trivially_copyable`             | trivial copyable                                  |
| `std::is_standard_layout`                | standard layout                                   |
| `std::has_unique_object_representations` | unique object representations                     |
| `std::is_empty`                          | empty                                             |
| `std::is_polymorphic`                    | polymorphic                                       |
| `std::is_abstract`                       | abstract                                          |
| `std::is_final`                          | final                                             |
| `std::is_aggregate`                      | aggregate                                         |
| `std::is_implicit_lifetime`              | implicit lifetime (destructor が無い場合は false) |
| `std::is_signed`                         | signed arithmetic                                 |
| `std::is_unsigned`                       | unsigned arithmetic                               |
| `std::is_bounded_array`                  | bounded array                                     |
| `std::is_unbounded_array`                | unbounded array                                   |
| `std::is_scoped_enum`                    | scoped enum                                       |


## Supported operations `<type_traits>`
- 型が指定の操作をサポートしているか
- `std::reference_constructs_from_temporary<T, U>`
  - `U` が scalar なら `V = std::remove_cv_t<U>`、それ以外なら `V = U`
  - `T` が参照型で、`decltype(e) = V` で、`T ref(e)` が well-formedなら true
  - `std::reference_converts_from_temporary<int&&, int&&>` は `int&& ref(int&&)` になるので false


| trait                                      | operation                       |
| :----------------------------------------- | :------------------------------ |
| `std::is_constructible`                    | constructor                     |
| `std::is_trivially_constructible`          | -                               |
| `std::is_nothrow_constructible`            | -                               |
| `std::is_default_constructible`            | default constructor             |
| `std::is_trivially_default_constructible`  | -                               |
| `std::is_nothrow_default_constructible`    | -                               |
| `std::is_copy_constructible`               | copy constructor                |
| `std::is_trivially_copy_constructible`     | -                               |
| `std::is_nothrow_copy_constructible`       | -                               |
| `std::is_move_constructible`               | move constructor                |
| `std::is_trivially_move_constructible`     | -                               |
| `std::is_nothrow_move_constructible`       | -                               |
| `std::is_assignable`                       | assignment operator             |
| `std::is_trivially_assignable`             | -                               |
| `std::is_nothrow_assignable`               | -                               |
| `std::is_copy_assignable`                  | copy assignment operator        |
| `std::is_trivially_copy_assignable`        | -                               |
| `std::is_nothrow_copy_assignable`          | -                               |
| `std::is_move_assignable`                  | move assignment operator        |
| `std::is_trivially_move_assignable`        | -                               |
| `std::is_nothrow_move_assignable`          | -                               |
| `std::is_destructible`                     | destructor                      |
| `std::is_trivially_destructible`           | -                               |
| `std::is_nothrow_destructible`             | -                               |
| `std::has_virtual_destructor`              | virtual destructor              |
| `std::is_swappable`                        | swap                            |
| `std::is_swappable_with`                   | swap                            |
| `std::is_nothrow_swappable`                | -                               |
| `std::is_nothrow_swappable_with`           | -                               |
| `std::reference_constructs_from_temporary` | temporary reference constructor |
| `std::reference_converts_from_temporary`   | temporary reference conversion  |


## Property queries `<type_traits>`
- *UnaryTypeTrait* で `std::integral_constant<std::size_t, Value>` を継承する

| trait               | property                         |
| :------------------ | :------------------------------- |
| `std::alignment_of` | alignment                        |
| `std::rank`         | rank (配列の次元数)              |
| `std::extent`       | extent (配列の N 次元目の要素数) |


## Type relationships `<type_traits>`
- *BinaryTypeTrait* で relationship を検査する
- `std::true_type` か `std::false_type` を継承する

| trait                                                       | relationship                                   |
| :---------------------------------------------------------- | :--------------------------------------------- |
| `std::is_same<T, U>`                                        | `T` と `U` が cv 含めて同じ型                  |
| `std::is_base_of<Base, Derived>`                            | `Base` が `Derived` の base class か           |
| `std::is_virtually_base_of<Base, Derived>`                  | `Base` が `Derived` の virtual base class か   |
| `std::is_convertible<From, To>`                             | `From` が `To` に変換可能か                    |
| `std::is_nothrow_convertible<From, To>`                     | -                                              |
| `std::is_layout_compatible<T, U>`                           | `T` と `U` が layout compatible か             |
| `std::is_pointer_interconvertible_base_of<Base, Derived>`   | `T` と `U` が pointer interconvertible base か |
| `std::is_invocable<class Fn, class... ArgTypes>`            | `std::invoke_result` が valid か               |
| `std::is_nothrow_invocable<class Fn, class... ArgTypes>`    | -                                              |
| `std::is_invocable_r<class R, class Fn, class... ArgTypes>` | `std::invoke_result` が valid か               |
| `std::is_nothrow_invocable_r`                               | -                                              |


## Type transformations `<type_traits>`
- *TransformationTrait* で変換した型を返す
- Helper
  ```C++
  template< class T >
  using XXX_t= typename XXX<T>::type;
  ```


### Const-volatility specifiers

| trait                  | transformation            |
| :--------------------- | :------------------------ |
| `std::remove_cv`       | remove cv qualifier       |
| `std::remove_const`    | remove const qualifier    |
| `std::remove_volatile` | remove volatile qualifier |
| `std::add_cv`          | add cv qualifier          |
| `std::add_const`       | add const qualifier       |
| `std::add_volatile`    | add volatile qualifier    |


### References
| trait                       | transformation       |
| :-------------------------- | :------------------- |
| `std::remove_reference`     | remove reference     |
| `std::add_lvalue_reference` | add lvalue reference |
| `std::add_rvalue_reference` | add rvalue reference |


### Sign modifiers
| trait                | transformation |
| :------------------- | :------------- |
| `std::make_signed`   | make signed    |
| `std::make_unsigned` | make unsigned  |


### Arrays
| trait                     | transformation     |
| :------------------------ | :----------------- |
| `std::remove_extent`      | remove extent      |
| `std::remove_all_extents` | remove all extents |


### Pointers
| trait                 | transformation |
| :-------------------- | :------------- |
| `std::remove_pointer` | remove pointer |
| `std::add_pointer`    | add pointer    |


### Other transformations
- `std::decay<T>`
  - `T` 型の変数を pass-by-value した場合の推論された型を返す
  - `array of U` なら `U*`
  - `function F` なら `F*`
  - その他なら cvref を除去する
  ```C++
  template <class T>
  struct Test
  {
      Test(T v) : v(v) {}
      T v;
  };

  const int b[4] = { 1, 2, 3, 4 };
  // error
  // int[4] v = b; になり、配列の代入ができないため
  Test<int[4]> t2(b);
  ```

| trait                                            | transformation          |
| :----------------------------------------------- | :---------------------- |
| `std::decay`                                     | decay                   |
| `std::remove_cvref`                              | remove cv and reference |
| `std::enable_if`                                 | enable if               |
| `std::conditional<bool B, class T, class F>`     | conditional             |
| `std::common_type<class... T>`                   | common type             |
| `std::common_reference<class... T>`              | common reference        |
| `std::basic_common_reference`                    | basic common reference  |
| `std::underlying_type<class T>`                  | enum underlying type    |
| `std::invoke_result<class F, class... ArgTypes>` | invoke result           |
| `std::void_t`                                    | void type               |
| `std::type_identity<T>`                          | type identity           |


#### `std:common_reference`
- <https://en.cppreference.com/w/cpp/types/common_reference>
- **Definition**
  ```C++
  template< class... T >
  struct common_reference;
  ```
- **Description**
  - 全ての `T` を変換可能 or バインド可能な参照型の導出
  - 探索ルール
    1. `sizeof...(T) = 0` なら、存在しない
    2. `sizeof...(T) = 1` なら、`T` を返す
    3. `sizeof...(T) = 2` なら、
       - `S` を simple common reference type として、次の条件を全て満たすなら type =  s
         - `T1` `T2` が共に参照型
         - `S` が well-formed
         - `std::is_convertible_v<std::add_pointer_t<T1>, std::add_pointer_t<S>> = true`
         - `std::is_convertible_v<std::add_pointer_t<T2>, std::add_pointer_t<S>> = true`
       - `std::basic_common_reference<std::remove_cvref_t<T1>, std::remove_cvref_t<T2>, T1Q, T2Q>::type`
         - `TiQ<U>` は `U` を返す
       - `decltype(false? val<T1>() : val<T2>())` が有効ならそれ
         - `val` は `template<class T> T val();`
       - `std::common_type_t<T1, T2>` が有効ならそれ
    4. `sizeof...(T) > 2` なら、右から畳み込む
  - Simple common reference type
    - `T1` と `T2` が両方 lvalue reference なら、`decltype(false? std::declval<cv12 X&>() : std::declval<cv12 Y&>())`
    - `T1` と `T2` が両方 rvalue reference なら、上記に同じ


### Member operations

| trait                          | operation   |
| :----------------------------- | :---------- |
| `std::conjunction<class... B>` | conjunction |
| `std::disjunction<class... B>` | disjunction |
| `std::negation<class B>`       | negation    |


## Member relationships
| trait                                         | relationship                        |
| :-------------------------------------------- | :---------------------------------- |
| `std::is_pointer_interconvertible_with_class` | pointer interconvertible with class |
| `std::is_corresponding_member`                | corresponding member                |
