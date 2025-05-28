# Concepts Library (C++20)
- <https://en.cppreference.com/w/cpp/concepts>
- fundamental concepts を定義する
  - template の compile-time validation と function dispatch
- requirements は **syntactic** と **semantic** に分けられる
  - コンパイラがチェックするのは **syntactic**
  - 実際の文脈で **semantic** が満たされない時、ill-formed (no diagnostic required)
  - **syntactic requirements**
    - 満たす時、concept は **satisfied**
  - **semantic requirements**
    - 満たす時、concept は **modeled**
- **Equality preservation**
  - 等しい input に対して、等しい output を返す
  - 加えて、**stable** (同じ入力に対して複数回評価しても同じ出力を返す) ことが求められる
  - `requires` で使用される expression は equality preservation を満たす
  - ただし、次の concept は equality-preserving を満たさない (同じ変数でも結果が異なる可能性がある)
    - `std::output_iterator`
    - `std::indirectly_writable`
    - `std::invocable`
    - `std::weakly_incrementable`
    - `std::range`
- **Implicit expression variations**
  - 値を変更しない lvalue operand を持つ `requires` は、`T&` `T&&` も受け入れるような variation が発生する
  - この variation も semantic requirements を満たす必要があり、満たさない場合は UB
  ```C++
  template<class T>
  concept C = requires(T a, T b, const T c, const T d)
  {
      c == d;           // expression #1: does not modify the operands
      a = std::move(b); // expression #2: modifies both operands
      a = c;            // expression #3: modifies the left operand `a`
  };

  // Expression #1 implicitly requires additional expression variations that
  // meet the requirements for c == d (including non-modification),
  // as if the following expressions had been declared as well:

  // ------ const == const ------- ------ const == non-const ---
  //                                         c  ==           b;
  //            c == std::move(d);           c  == std::move(b);
  // std::move(c) ==           d;  std::move(c) ==           b;
  // std::move(c) == std::move(d); std::move(c) == std::move(b);

  // -- non-const == const ------- -- non-const == non-const ---
  //           a  ==           d;            a  ==           b;
  //           a  == std::move(d);           a  == std::move(b);
  // std::move(a) ==           d;  std::move(a) ==           b;
  // std::move(a) == std::move(d); std::move(a) == std::move(b);

  // Expression #3 implicitly requires additional expression variations that
  // meet the requirements for a = c
  // (including non-modification of the second operand),
  // as if the expressions a = b (non-constant lvalue variation)
  // and a = std::move(c) (const rvalue variation) had been declared.

  // Note: Since expression #2 already requires the non-constant rvalue variation
  // (a == std::move(b)) explicitly, expression #3 does not implicitly require it anymore.

  // The type T meets the explicitly stated syntactic requirements of
  // concept C above, but does not meet the additional implicit requirements
  // (i.e., T satisfies but does not model C):
  // a program requires C<T> is ill-formed (no diagnostic required).
  struct T
  {
      bool operator==(const T&) const { return true; }
      bool operator==(T&) = delete;
  };
  ```


## Standard library concepts


### Core language concepts `<concepts>`


#### `std::same_as`
- <https://en.cppreference.com/w/cpp/concepts/same_as>
- **Definition**
  ```C++
  template< class T, class U >
  concept same_as = /* see below */;
  ```
- **Description**
  - `T` と `U` が同じ型、かつ、`T` と `U` が同じ型
  - cv-qualifier を考慮する
    - `std::same_as<T, const T>` は false


#### `std::derived_from`
- <https://en.cppreference.com/w/cpp/concepts/derived_from>
- **Definition**
  ```C++
  template< class Derived, class Base >
  concept derived_from =
      std::is_base_of_v<Base, Derived> &&
      std::is_convertible_v<const volatile Derived*, const volatile Base*>;
  ```
- **Description**
  - `Derived` が `Base` を継承しているか、同じ型
  - private / protected inheritance の場合は false


#### `std::common_reference_with`
- <https://en.cppreference.com/w/cpp/concepts/common_reference_with>
- **Definition**
  ```C++
  template< class T, class U >
  concept common_reference_with =
      std::same_as<std::common_reference_t<T, U>, std::common_reference_t<U, T>> &&
      std::convertible_to<T, std::common_reference_t<T, U>> &&
      std::convertible_to<U, std::common_reference_t<T, U>>;
  ```
- **Description**
  - `T` と `U` の共通の参照型を持ち、instance が共通参照型にバインド可能
- **Semantic requirements**
  - equality preservation


#### `std::common_with`
- <https://en.cppreference.com/w/cpp/concepts/common_with>
- **Definition**
  ```C++
  template< class T, class U >
  concept common_with =
      std::same_as<std::common_type_t<T, U>, std::common_type_t<U, T>> &&
      requires {
          static_cast<std::common_type_t<T, U>>(std::declval<T>());
          static_cast<std::common_type_t<T, U>>(std::declval<U>());
      } &&
      std::common_reference_with<
          std::add_lvalue_reference_t<const T>,
          std::add_lvalue_reference_t<const U>> &&
      std::common_reference_with<
          std::add_lvalue_reference_t<std::common_type_t<T, U>>,
          std::common_reference_t<
              std::add_lvalue_reference_t<const T>,
              std::add_lvalue_reference_t<const U>>>;
  ```
- **Description**
  - `T` と `U` から共通型を導出可能で、その参照型も同じ
- **Semantic requirements**
  - equality preservation


#### `std::integral`
- <https://en.cppreference.com/w/cpp/concepts/integral>
- **Definition**
  ```C++
  template< class T >
  concept integral = std::is_integral_v<T>;
  ```
- **Description**
  - 整数型


#### `std::signed_integral`
- <https://en.cppreference.com/w/cpp/concepts/signed_integral>
- **Definition**
  ```C++
  template< class T >
  concept unsigned_integral = std::integral<T> && std::signed_integral<T>;
  ```
- **Description**
  - 符号付き整数型


#### `std::unsigned_integral`
- <https://en.cppreference.com/w/cpp/concepts/unsigned_integral>
- **Definition**
  ```C++
  template< class T >
  concept unsigned_integral = std::integral<T> && !std::signed_integral<T>;
  ```
- **Description**
  - 符号なし整数型


#### `std::floating_point`
- <https://en.cppreference.com/w/cpp/concepts/floating_point>
- **Definition**
  ```C++
  template< class T >
  concept floating_point = std::is_floating_point_v<T>;
  ```
- **Description**
  - 浮動小数点型


#### `std::assignable_from`
- <https://en.cppreference.com/w/cpp/concepts/assignable_from>
- **Definition**
  ```C++
  template< class LHS, class RHS >
  concept assignable_from =
      std::is_lvalue_reference_v<LHS> &&
      std::common_reference_with<
          const std::remove_reference_t<LHS>&,
          const std::remove_reference_t<RHS>&> &&
      requires(LHS lhs, RHS&& rhs) {
          { lhs = std::forward<RHS>(rhs) } -> std::same_as<LHS>;
      };
  ```
- **Description**
  - `LHS` 型に `RHS` に代入可能


#### `std::swappable` / `std::swappable_with`
- <https://en.cppreference.com/w/cpp/concepts/swappable>
- **Definition**
  ```C++
  template< class T >
  concept swappable =
      requires(T& a, T& b) {
          ranges::swap(a, b);
      };

  template< class T, class U >
  concept swappable_with =
      std::common_reference_with<T, U> &&
      requires(T&& t, U&& u) {
          ranges::swap(std::forward<T>(t), std::forward<T>(t));
          ranges::swap(std::forward<U>(u), std::forward<U>(u));
          ranges::swap(std::forward<T>(t), std::forward<U>(u));
          ranges::swap(std::forward<U>(u), std::forward<T>(t));
      };
  ```
- **Description**
  - 共通の型をもち、`std::ranges::swap` 可能


#### `std::destructible`
- <https://en.cppreference.com/w/cpp/concepts/destructible>
- **Definition**
  ```C++
  template< class T >
  concept destructible = std::is_destructible_v<T>;
  ```
- **Description**
- 例外を投げない destructor を持つ


#### `std::constructible_from`
- <https://en.cppreference.com/w/cpp/concepts/constructible_from>
- **Definition**
  ```C++
  template< class T, class... Args >
  concept constructible_from =
      std::destructible<T> && std::is_constructible_v<T, Args...>;
  ```
- **Description**
  - `T` が `Args...` から構築可能
  - destruct 可能


#### `std::default_initializable`
- <https://en.cppreference.com/w/cpp/concepts/default_initializable>
- **Definition**
  ```C++
  template< class T >
  concept default_initializable = std::constructible_from<T> && requires { T{}; } &&
  ```
- **Description**
  - `T` が default construct 可能 (value-initialization, direct-list-initialization, default initialization)


#### `std::move_constructible`
- <https://en.cppreference.com/w/cpp/concepts/move_constructible>
- **Definition**
  ```C++
  template< class T >
  concept move_constructible = std::constructible_from<T, T> && std::convertible_to<T, T>;
  ```
- **Description**
  - `T` が move construct 可能


#### `std::copy_constructible`
- <https://en.cppreference.com/w/cpp/concepts/copy_constructible>
- **Definition**
  ```C++
  template< class T >
  concept copy_constructible =
      std::move_constructible<T> &&
      std::constructible_from<T, T&> && std::convertible_to<T&, T> &&
      std::constructible_from<T, const T&> && std::convertible_to<const T&, T> &&
      std::constructible_from<T, const T> && std::convertible_to<const T, T>;
  ```
- **Description**
  - `T` が copy construct 可能
  - `std::move_constructible` を満たす
  - `T&` `const T&` `const T` から construct 可能


### Comparison concepts `<concepts>`


#### `std::equality_comparable` / `std::equality_comparable_with`
- <https://en.cppreference.com/w/cpp/concepts/equality_comparable>
- **Definition**
  ```C++
  template< class T >
  concept equality_comparable = __WeaklyEqualityComparableWith<T, T>;

  template< class T, class U >
  concept equality_comparable_with =
      std::equality_comparable<T> &&
      std::equality_comparable<U> &&
      __ComparisonCommonTypeWith<T, U> &&
      std::equality_comparable<
          std::common_reference_t<
              const std::remove_reference_t<T>&,
              const std::remove_reference_t<U>&>> &&
      __WeaklyEqualityComparableWith<T, U>;
  ```
- **Description**
  - Weakly に比較可能 (大小関係は不要)
  - `==` と `!=` を定義可能


### `std::totally_ordered` / `std::totally_ordered_with`
- <https://en.cppreference.com/w/cpp/concepts/totally_ordered>
- **Definition**
  ```C++
  template< class T >
  concept totally_ordered =
      std::equality_comparable<T> && __PartiallyOrderedWith<T, T>;

  template< class T, class U >

  concept totally_ordered_with =
      std::totally_ordered<T> &&
      std::totally_ordered<U> &&
      std::equality_comparable_with<T, U> &&
      std::totally_ordered<
          std::common_reference_t<
              const std::remove_reference_t<T>&,
              const std::remove_reference_t<U>&>> &&
      __PartiallyOrderedWith<T, U>;
  ```
- **Description**
  - Totally に比較可能 (大小関係が定義されている)


### `std::three_way_comparable` / `std::three_way_comparable_with` `<compare>`
- <https://en.cppreference.com/w/cpp/utility/compare/three_way_comparable>
- **Definition**
  ```C++
  template< class T, class Cat = std::partial_ordering >
  concept three_way_comparable =
      __WeaklyEqualityComparableWith<T, T> &&
      __PartiallyOrderedWith<T, T> &&
      requires(const std::remove_reference_t<T>& a,
              const std::remove_reference_t<T>& b) {
          { a <=> b } -> __ComparesAs<Cat>;
      };

  template< class T, class U, class Cat = std::partial_ordering >
  concept three_way_comparable_with =
      std::three_way_comparable<T, Cat> &&
      std::three_way_comparable<U, Cat> &&
      __ComparisonCommonTypeWith<T, U> &&
      std::three_way_comparable<
          std::common_reference_t<
              const std::remove_reference_t<T>&,
              const std::remove_reference_t<U>&>, Cat> &&
      __WeaklyEqualityComparableWith<T, U> &&
      __PartiallyOrderedWith<T, U> &&
      requires(const std::remove_reference_t<T>& t,
              const std::remove_reference_t<U>& u) {
          { t <=> u } -> __ComparesAs<Cat>;
          { u <=> t } -> __ComparesAs<Cat>;
      };
  ```
- **Description**
  - 比較可能
  - `<=>` 演算子が定義されていて、指定された比較カテゴリを返す


### Object concepts


#### `std::movable`
- <https://en.cppreference.com/w/cpp/concepts/movable>
- **Definition**
  ```C++
  template< class T >
  concept movable =
      std::is_object_v<T> &&
      std::move_constructible<T> &&
      std::assignable_from<T&, T> &&
      std::swappable<T>;
  ```
- **Description**
  - object 型
  - move construct 可能
  - move assign 可能
  - swappable


#### `std::copyable`
- <https://en.cppreference.com/w/cpp/concepts/copyable>
- **Definition**
  ```C++
  template< class T >
  concept copyable =
      std::copy_constructible<T> &&
      std::movable<T> &&
      std::assignable_from<T&, T&> &&
      std::assignable_from<T&, const T&> &&
      std::assignable_from<T&, const T>;
  ```
- **Description**
  - copy construct 可能
  - move 可能
  - copy assign 可能


#### `std::semiregular`
- <https://en.cppreference.com/w/cpp/concepts/semiregular>
- **Definition**
  ```C++
  template< class T >
  concept semiregular = std::copyable<T> && std::default_initializable<T>;
  ```
- **Description**
  - 準正則型
  - 比較できる必要はない
  - *Rules of five* を満たす型


#### `std::regular`
- <https://en.cppreference.com/w/cpp/concepts/regular>
- **Definition**
  ```C++
  template< class T >
  concept regular = std::semiregular<T> && std::equality_comparable<T>;
  ```
- **Description**
  - 正則型


### Callable concepts


#### `std::invocable` / `std::regular_invocable`
- <https://en.cppreference.com/w/cpp/concepts/invocable>
- **Definition**
  ```C++
  template< class F, class... Args >
  concept invocable =
      requires(F&& f, Args&&... args) {
          std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
              /*not required to be equality-preserving*/
      };

  template< class F, class... Args >
  concept regular_invocable = std::invocable<F, Args...>;
  ```
- **Description**
  - `F` が `Args...` を引数にとる callable object
  - `std::regular_invocable` は equality-preserving


#### `std::predicate`
- <https://en.cppreference.com/w/cpp/concepts/predicate>
- **Definition**
  ```C++
  template< class F, class... Args >
  concept predicate =
      std::regular_invocable<F, Args...> &&
      boolean-testable<std::invoke_result_t<F, Args...>>;
  ```
- **Description**
  - invoke 可能で、結果が boolean-testable


#### `std::relation`
- <https://en.cppreference.com/w/cpp/concepts/relation>
- **Definition**
  ```C++
  template< class R, class T, class U >
  concept relation =
      std::predicate<R, T, T> && std::predicate<R, U, U> &&
      std::predicate<R, T, U> && std::predicate<R, U, T>;
  ```
- **Description**
  - `R` が `T` と `U` の関係を定義する predicate


#### `std::equivalence_relation`
- <https://en.cppreference.com/w/cpp/concepts/equivalence_relation>
- **Definition**
  ```C++
  template< class R, class T, class U >
  concept equivalence_relation = std::relation<R, T, U>;
  ```
- **Description**
  - `R` が `T` と `U` の equivalence relation を定義する predicate
  - 反射律 reflexive
  - 対称律 symmetric
  - 推移律 transitive


#### `std::strict_weak_order`
- <https://en.cppreference.com/w/cpp/concepts/strict_weak_order>
- **Definition**
  ```C++
  template< class R, class T, class U >
  concept strict_weak_order = std::relation<R, T, U>;
  ```
- **Description**
  - `R` が `T` と `U` の strict weak order を定義する predicate
  - 非反射律 irreflexive
    - `r(x, x) = false`
  - 対称律 symmetric
  - 推移律 transitive
