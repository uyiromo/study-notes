# Ranges
- <https://en.cppreference.com/w/cpp/ranges.html>
- シーケンス、及びイテレータ範囲を抽象化して扱う
  - <https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4128.html#introduction>
- `views`
  - シーケンスを間接的に表現する lightweight object で、**要素を保有しない**
    - コピー可能
  - <https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p2415r2.html>
- ranges は次のものを抽象化する
  - `[begin, end)`
  - `begin + [0, size)` => `views::counted` など
  - `[begin, predicate)` => `views::take_while` など
  - `[begin, ...)` => `views::iota` など
- range algorithms
  - view に対して lazily に適用される
- `std::views`
  - `std::ranges::views` のエイリアス
  ```C++
  namespace std {
      namespace views = ranges::views;
  }
  ```


## RangeAdaptorObject (NamedRequirement)
- <https://en.cppreference.com/w/cpp/named_req/RangeAdaptorObject.html>
- 第一引数に `viewable_range` を取り、`view` を返す CPO
  - `viewable_range` のみを取るものは `RangeAdaptorClosure` として定義される
  - `viewable_range` 以外の引数を `std::forward<E>(e)` として後ろから値バインドした RangeAdaptorObject を返す


## RangeAdaptorClosure (NamedRequirement)
- <https://en.cppreference.com/w/cpp/named_req/RangeAdaptorClosure.html>
- pipe を用いて呼び出し可能な関数オブジェクト
  - `C` が range adaptor closure で `R` が range の場合、次の2つは同じ
  ```C++
  C(R)

  R | C
  ```
- `C` と `D` を chain する場合、それが `E` になるなら、全て同じ意味
  - `E` は直接初期化した C のコピー `c = std::forward<C>(c)` と D のコピー `d = std::forward<D>(d)` を持つ
  ```C++
  d(c(R))

  R | c | d

  E(R)

  R | E

  ```


## Range access
- `#include <ranges>` or `#include <iterator>`
- 全て CPO

- `std::ranges::begin`
- `std::ranges::end`
- `std::ranges::cbegin`
- `std::ranges::cend`
- `std::ranges::rbegin`
- `std::ranges::rend`
- `std::ranges::crbegin`
- `std::ranges::crend`
- `std::ranges::reserve_hint`
  - 要素数を返す(?)
  - TBD
- `std::ranges::size`
- `std::ranges::ssize`
- `std::ranges::empty`
- `std::ranges::data`
- `std::ranges::cdata`


## Range primitives

| primitive                             | description                                           |
| ------------------------------------- | ----------------------------------------------------- |
| `ranges::iterator_t<T>`               | `ranges::begin(std::declval<T&>());`                  |
| `ranges::const_iterator_t<R>`         | `ranges::cbegin(...)`                                 |
| `ranges::sentinel_t<R>`               | `ranges::end(...)`                                    |
| `ranges::const_sentinel_t<R>`         | `ranges::cend(...)`                                   |
| `ranges::range_size_t<R>`             | `ranges::size(...)`                                   |
| `ranges::range_difference_t<R>`       | `std::iter_difference_t<ranges::iterator_t<R>>`       |
| `ranges::range_value_t<R>`            | `std::iter_value_t<ranges::iterator_t<R>>`            |
| `ranges::range_reference_t<R>`        | `std::iter_reference_t<ranges::iterator_t<R>>`        |
| `ranges::range_const_reference_t<R>`  | `std::iter_const_reference_t<ranges::iterator_t<R>>`  |
| `ranges::range_rvalue_reference_t<R>` | `std::iter_rvalue_reference_t<ranges::iterator_t<R>>` |
| `ranges::range_common_reference_t<R>` | `std::iter_common_reference_t<ranges::iterator_t<R>>` |


## Dangling iterator handling
- `ranges:dangling`
  - `ranges::borrowed_iterator_t` と `ranges::borrowed_subrange_t` と組み合わせて使用される
  - Constrained Algorithm が range を受け取って一部の rvalue を返す場合、borrow 不可能な場合にこの型を返す
    - <https://en.cppreference.com/w/cpp/algorithm/ranges.html>
- `ranges::borrowed_iterator_t` `ranges::borrowed_subrange_t`
  - borrow した range を返す


## Other utilities
- `ranges::elements_of`
  - `ranges::elements_of<R>` で range の要素を分解した要素を返す


## Range concepts
- `ranges::range`
  1. `ranges::begin` と `ranges::end` が適用可能
- `ranges::borrowed_range`
  1. `ranges::range` かつ
     a. lvalue reference または
     b. `ranges::enable_borrowed_range` (イテレータが range の lifetime に依存しない)
- `ranges::approximately_sized_range`
  1. `ranges::range` かつ
  2. `range::reserve_hint` が適用可能 (amortized constant-time complexity)
- `ranges::sized_range`
  1. `ranges::range` かつ
  2. `ranges::size` が適用可能
- `ranges::view<T>`
  1. `ranges::range<T>` かつ
  2. `movable<T>` かつ
  3. `enable_view<T>` (= `derived_from<T, view_base>`)
- `ranges::input_range<T>`
  1. `ranges::range<T>` かつ
  2. `input_iterator<ranges::iterator_t<T>>`
- `ranges::output_range`
- `ranges::forward_range`
- `ranges::bidirectional_range`
- `ranges::random_access_range`
- `ranges::contiguous_range`
  - 上に同じ
- `ranges::common_range<T>`
  1. `ranges::range<T>` かつ
  2. `same_as<ranges::begin<T>, ranges::end<T>>`
- `ranges::viewable_range`
  - `ranges::view_all` で view に変換可能な range
- `ranges::constant_range`
  1. `ranges::range<T>` かつ
  2. `constant_iterator<ranges::iterator_t<T>>`


## Range conversions
- `ranges::to`
  - `view` ではない要素を Construct する

- (1)
  ```C++
  template< class C, ranges::input_range R, class... Args >
      requires (!ranges::view<C>)
  constexpr C to( R&& r, Args&&... args );
  ```
  1. `C` が input_range を満たさない場合
     1. `C(std::forward<R>(r), std::forward<Args>(args)...)` を返す
     2. `C(std::from_range_t, std::forward<R>(r), std::forward<Args>(args)...)` を返す
     3. `C(std::ranges::begin(r), std::ranges::end(r), std::forward<Args>(args)...)` を返す
     4. `C(std::forward<Args>(args)...)` して R の要素を append して返す
  2. 満たす場合、各要素と `std::forward<Args>(args)...` を `C` に Construct して返す
- (2)
  ```C++
  template< template< class... > class C,
            ranges::input_range R, class... Args >
  constexpr auto to( R&& r, Args&&... args );
  ```
  - `to<declval(...)>(std::forward<R>(r), std::forward<Args>(args)...)` に同じ
- (3) (4)
  ```C++
  template< class C, class... Args >
      requires (!ranges::view<C>)
  constexpr /*range adaptor closure*/ to( Args&&... args );

  template< template< class... > class C, class... Args >
  constexpr /*range adaptor closure*/ to( Args&&... args );
  ```


## Views
- `ranges::view_interface`
  - CRTP を使用した `view` のインターフェース
  - これを継承したクラスは、`view` として扱われる
    - `enable_view` を満たす
- `ranges::subrange`
  - `view` かつ `borrowed_range` な型
  - イテレータ `I` と番兵 `S` を持つ、長さ 2 の tuple-like な型


## Range factories
- `ranges::empty_view` / `views::empty`
  - 空の view を返す
  - `ranges::views::empty_view<T>` が型名
  - `views::empty<T>` で `empty_view<T>` 型の変数テンプレートを展開


- `ranges::single_view` / `views::single`
  - 指定された単一の要素を持つ view を返す
- `ranges::iota_view` / `views::iota`
  - 指定された値からインクリメントされる view を返す
- `ranges::repeat_view` / `views::repeat`
  - 指定された値を無限に繰り返す view を返す
- `ranges::basic_istream_view` / `views::istream`
  - `operator>>` を適用した値から構成される view を返す


## Range adaptors
- `ranges::range_adaptor_closure`
  - RangeAdaptorClosureObject を定義するためのテンプレート
  - CRTP でこれを継承し、次の要件を満たせば RangeAdaptorClosureObject になる
    1. `viewable_range` **のみ** を取る `operator()` を持つ
    2. 唯一の親クラスは public 継承した `ranges::range_adaptor_closure`
    3. `range` ではない
       - つまり begin と end を持たない
- `ranges::views::all_t`
  - `all` の返り値の型で、次の順で優先
    1. `decay_t<R>` が view なら `decay_t<R>`
    2. `ranges::ref_view{e}`
    3. `ranges::owing_view{e}`
- `ranges::ref_view<R>`
  - `R` を参照する view
  - 実体としては `R* r_` を持つ
- `ranges::owning_view<R>`
  - `R` を唯一所有する view
  - 作成時に range を move する
- filter の Pred は
  - `std::indirect_unary_predicate<ranges::iterator_t<V>> Pred`
    - `V` の value_t と `std::reference_t` を両方受け取れて bool を返す


| RangeAdaptor              | CPO (RangeAdaptorObject) | Description                                                 |
| ------------------------- | ------------------------ | ----------------------------------------------------------- |
| `ranges::*`               | `views::*`               | (namespace prefix)                                          |
| -                         | `all`                    | 全ての要素を含む view                                       |
| `as_rvalue_view`          | `as_rvalue<R>`           | rvalue として扱う view                                      |
| `filter_view`             | `filter<R, Pred>`        | 要素を predicate でフィルタリングする view                  |
| `transform_view`          | `transform<R, Proj>`     | 要素をプロジェクションで変換する view                       |
| `take_view`               | `take<R>`                | 先頭から指定された数の要素を含む view                       |
| `take_while_view`         | `take_while<R, Pred>`    | 先頭から predicate が false になるまでの要素を含む view     |
| `drop_view`               | `drop<R>`                | 先頭から指定された数の要素を除外する view                   |
| `drop_while_view`         | `drop_while<R, Pred>`    | 先頭から predicate が false になるまでの要素を除外する view |
| `join_view`               | `join<R>`                | 要素を 1 段階 flatten して結合したview              |
| `join_with_view`          | `join_with<R, Pattern>`  | 要素を join した後 Pattern で処理した view                  |
| `lazy_split_view`         | `lazy_split<R, Pattern>` | 要素を Pattern で分割した view                              |
| `split_view`              | `split<R, Pattern>`      | 要素を Pattern で lazy に分割した view                      |
| `concat_view`             | `concat<R...>`           | 要素を順に生成するview                                      |
| -                         | `counted<R, N>`          | 先頭から N 個の要素を含む view                              |
| `common_view`             | `common<R>`              | begin/end を共通型にする view                               |
| `reverse_view`            | `reverse<R>`             | 要素を逆順にする view                                       |
| `as_const_view`           | `as_const<R>`            | 要素を const として扱う view                                |
| `elements_view`           | `elements<R, I>`         | tuple-like を内包する range で、N-th 要素を抽出する view    |
| `keys_view`               | `keys<R>`                | pair-like を内包する range で、1st 要素を抽出する view      |
| `values_view`             | `values<R>`              | pair-like を内包する range で、2nd 要素を抽出する view      |
| `enumerate_view`          | `enumerate<R>`           | 要素にインデックスを付与した view                           |
| `zip_view`                | `zip<R...>`              | 要素を zip した view                                        |
| `zip_transform_view`      | `zip_transform<F>`       | 各要素を zip した後 transform した view                     |
| `adjacent_view`           | `adjacent<N>(R)`         | 要素を N 個ずつ含む tuple にする view                       |
| -                         | `pairwise<R>`            | 要素を隣接するペアにする view                               |
| `adjacent_transform_view` | `adjacent_transform<N>`  | 要素を N 個ずつ含む tuple に transform した view            |
| `chunk_view`              | `chunk<N>`               | 要素を N 個ずつの重複しない chunk に分割する view           |
| `slide_view`              | `slide<N>`               | 要素を N 個ずつの重複する chunk に分割する view             |
| `chunk_by_view`          | `chunk_by<Pred>`         | 要素を predicate で分割した chunk にする view              |
| `stride_view`             | `stride<N>`               | 要素を N 個ずつの stride で取得する view                    |
| `cartesian_product_view` | `cartesian_product<R...>` | 要素を直積にする view                                      |


| RangeAdaptor              | `*begin` の型                                                                   |
| ------------------------- | ------------------------------------------------------------------------------- |
| `as_rvalue_view`          | 元になる view に対して `*std::move_iterator(view.begin())`                      |
| `filter_view`             | 元になる view に対して `*ranges::iterator_t<V>`                                 |
| `transform_view`          | Transform の返り値の型 `std::invoke_t(...)`                                     |
| `take_view`               | 元になる view に対して `*std::counted_iterator` or `*ranges::iterator_t<V>`     |
| `drop_view`               | 元になる view に対して `*std::ranges::next(std::ranges::begin(...))`            |
| `join_view`               | 元になる view に対して `*ranges::iterator_t<ranges::range_reference_t<V>>`      |
| `split_view`              | 元になる view に対して `subrange<ranges::iterator_t<V>>`                        |
| `lazy_split_view`         | 元になる view に対して `inner_iterator`                                         |
| `lazy_split_view`         | `inner_iterator.begin()` で元の要素への参照                                     |
| `reverse_view`            | 元になる view に対して `*std::reverse_iterator`                                 |
| `as_const_view`           | 元になる view に対して `*std:ranges::cbegin`                                    |
| `elements_view`           | 元になる view に対して `*std::get<I>(...)`                                      |
| `keys_view`               | 元になる view に対して `*std::get<0>(...)`                                      |
| `values_view`             | 元になる view に対して `*std::get<1>(...)`                                      |
| `enumerate_view`          | 元になる view に対して `std::tuple<difference_t, ranges::range_reference_t<V>>` |
| `zip_view`                | 元になる view に対して `tuple<views...> に ranges::begin を apply` した tuple   |
| `zip_transform_view`      | `zip_view` した結果に対して Transform の返り値                                  |
| `adjacent_view`           | `std::array<ranges::iterator_t<Base>, N>` の各要素のイテレータを剥がした tuple  |
| `adjacent_transform_view` | `adjacent_view` の各要素に対して Transform の返り値                             |
| `chunk_view`              | `subrange(ranges::iterator_t<Base>, ...)`  |
| `slide_view`              | `span<T>`  |
| `chunk_by_view`           | `chunk_view` に同じ |
| `stride_view`             | 元となる view に対して `*ranges::iterator_t<Base>` |
| `cartesian_product_view` | `tuple<ranges::iterator_t<R>...>` の各要素のイテレータを剥がした tuple |


## Range generators
- `ranges::generator`
  - coroutine 関係
