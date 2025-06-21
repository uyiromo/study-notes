# Iterator library
- <https://en.cppreference.com/w/cpp/iterator.html>
- イテレータ ＝ Container / Range で統一された方式でデータにアクセスするための、一般化されたポインタ


## Iterator categories
- イテレータは、可能な操作によって 6 種類のカテゴリに分類される
  1. LegacyInputIterator
  2. LegacyOutputIterator
  3. LegacyForwardIterator
  4. LegacyBidirectionalIterator
  5. LegacyRandomAccessIterator
  6. LegacyContiguousIterator
- LegacyOutputIterator を除いて包含関係にあり、これを満たすなら `mutable`、満たさないなら `constant` として扱われる

<!-- markdownlint-disable -->
| | write | read | increment (w/o multiple) | increment (w multiple) | decrement | random access | contiguous storage |
| | ----- | ---- | ------------------------ | ---------------------- | --------- | ------------- | ------------------ |
<!--                            w     r    iw    i    d     ra    c    -->
| LegacyIterator              | ❌ | ❌ | ✅ | ❌ | ❌ | ❌ | ❌ |
| LegacyOutputIterator        | ✅ | ❌ | ✅ | ❌ | ❌ | ❌ | ❌ |
| LegacyInputIterator         | ❌ | ✅ | ✅ | ❌ | ❌ | ❌ | ❌ |
| LegacyForwardIterator       | ❌ | ✅ | ✅ | ✅ | ❌ | ❌ | ❌ |
| LegacyBidirectionalIterator | ❌ | ✅ | ✅ | ✅ | ✅ | ❌ | ❌ |
| LegacyRandomAccessIterator  | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ | ❌ |
| LegacyContiguousIterator    | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
<!--                            w     r    iw    i    d     ra    c    -->
<!-- markdownlint-enable -->

## Definitions


### Types and writeability

- イテレータ `i` が `*i` をサポートするとき、その返り値の型は `iterator_traits<i>::value_type`
- `i` が `indirectly_writable` なら、`*i = t;` が可能
- 全てのイテレータは、integer-like な `iterator_traits<i>::difference_type` を持つ


### Dereferenceability and validity

- 配列に対するポインタと同様に、最後の次の要素 `past-the-end` は参照できる
- `*i` は dereferenceable を示す
  - ただし、STL は `past-the-end` の dereference を許可しない
- `i` は、シーケンスに紐づかない singular value を持てるが、次の例外を除いて UB
  - singular value を持つイテレータへの non-singular value の代入
  - singular value を持つイテレータの破棄
  - `DefaultConstructible` イテレータへの値代入初期化


### Ranges

- range の表現方法
  1. `[i, s)`：イテレータの先頭と終端 sentinel
  2. `i + [0, n)`：イテレータの先頭と長さ
- `iterator-sentinel range`
  - `[i, s)`：`i` から `s` までの範囲
  - `s` は `++i` で到達できる最初のイテレータ
- `counted range`
  - `i + [0, n)`：`i` から `n` 個の要素を持つ範囲
  - 次の場合に有効
    - `n == 0`
    - もしくは次のすべてを満たす
      - `n > 0`
      - `*i`  が有効
      - `++i + [0, --n)` が有効


## Iterator concepts

| concept                    | description                                                                           |
| -------------------------- | ------------------------------------------------------------------------------------- |
| `indirectly_readable`      | `*i` が有効                                                                           |
| `indirectly_writable`      | `*i = t` が有効                                                                       |
| `weakly_incrementable`     | `++i -> I&` と `i++` が有効                                                           |
| `incrementable`            | `weakly_incrementable` かつ `i++ -> I` かつ `(i++ == j)` (equality preserving)        |
| `input_or_output_iterator` | `*i` が有効で、`weakly_incrementable`                                                 |
| `sentinel_for`             | semiregular かつ `input_or_output_iterator` かつ `s == i` を比較可能                  |
| `sized_sentinel_for`       | `sentinel_for` かつ `s - i` と `i - s` が `difference_type` を返す                    |
| `input_iterator`           | `input_or_output_iterator` かつ `indirectly_readable` かつ `iterator_traits` を満たす |
| `output_iterator`          | `input_or_output_iterator` かつ `indirectly_writable`                                 |
| `forward_iterator`         | `input_iterator` かつ `incrementable` かつ `sentinel_for<I, I>`                       |
| `bidirectional_iterator`   | `forward_iterator` かつ `--i -> I&` かつ `i-- -> I` が有効                            |
| `random_access_iterator`   | `bidirectional_iterator` かつ大小関係を比較できて、定数移動が可能                     |
| `contiguous_iterator`      | `random_access_iterator` かつポインタ取得が可能                                       |


## Iterator associated types

<!-- markdownlint-disable -->
| Type                            | Description                                         |
| ------------------------------- | --------------------------------------------------- |
| `incrementable_traits<T>`       | `incrementable_traits<I>::difference_type` を導出   |
| `indirectly_readable_traits<T>` | `indirectly_readable_traits<I>::value_type` を導出  |
| `iter_value_t<T>`               | `value_type` 相当                                   |
| `iter_reference_t<T>`           | `reference_type` 相当                               |
| `iter_const_reference_t<T>`     | `const reference_type` 相当                         |
| `iter_difference_t<T>`          | `difference_type` 相当                              |
| `iter_rvalue_reference_t<T>`    | 右辺値参照 `reference_type` 相当                    |
| `iter_common_reference_t<T>`    | `reference_type` と `lvalue reference` の共通参照型 |

<!-- markdownlint-enable -->


## Iterator primitives

| Primitive                    | Description                             |
| ---------------------------- | --------------------------------------- |
| `iterator_traits<T>`         | イテレータの型に関する情報を提供する    |
| `input_iterator_tag`         | input_iterator なことを示すタグ         |
| `output_iterator_tag`        | output_iterator なことを示すタグ        |
| `forward_iterator_tag`       | forward_iterator なことを示すタグ       |
| `bidirectional_iterator_tag` | bidirectional_iterator なことを示すタグ |
| `random_access_iterator_tag` | random_access_iterator なことを示すタグ |
| `contiguous_iterator_tag`    | contiguous_iterator なことを示すタグ    |


## Iterator customization points

| Customization point      | Description                     |
| ------------------------ | ------------------------------- |
| `std::ranges::iter_move` | `*i` の値をムーブする           |
| `std::ranges::iter_swap` | `*i` と `*j` の値をスワップする |


## Algorithm concepts and utilities `<iterator>`

- (TBD)


## Iterator adaptors

- Container もしくは Iterator をラップして特定の機能をもたせる

- `reverse_iterator`
  - 与えられた iterator を起点として逆方向に進むイテレータ
    - つまり、`begin()` から生成すると不正
  - `*make_reverse_iterator(it)` は `*(it - 1)` を返す
- `back_inserter`
  - 与えられたコンテナの末尾に要素を挿入するイテレータ
  - `*back_inserter(c) = v` `back_inserter(c) = v` は `c.push_back(v)` に相当
    - これを持たないコンテナには適用不可
- `front_inserter`
  - 与えられたコンテナの先頭に要素を挿入するイテレータ
  - `*front_inserter(c) = v` `front_inserter(c) = v` は `c.push_front(v)` に相当
    - これを持たないコンテナには適用不可
- `insert_iterator`
  - 与えられたコンテナの指定位置に要素を挿入するイテレータ
  - `*inserter(c, it) = v` は `c.insert(it, v)` に相当
    - `it` は `c.begin()` から `c.end()` の間でなければならない
- `default_sentinel`
  - `default_sentinel_t` 型の定数で、counted_iterator などの「個数が既知」なイテレータの終端を示す
- `unreachable_sentinel_t`
  - `unreachable_sentinel_t` 型の定数で、個数が未知なイテレータの終端を示す


| adapter                  | Description                                                                  |
| ------------------------ | ---------------------------------------------------------------------------- |
| `reverse_iterator`       | イテレータを逆方向に走査するためのアダプタ                                   |
| `make_reverse_iterator`  | `reverse_iterator` を生成するための関数                                      |
| `back_insert_iterator`   | コンテナの末尾に要素を挿入するためのイテレータアダプタ                       |
| `back_inserter`          | `back_insert_iterator` を生成するための関数                                  |
| `front_insert_iterator`  | コンテナの先頭に要素を挿入するためのイテレータアダプタ                       |
| `front_inserter`         | `front_insert_iterator` を生成するための関数                                 |
| `insert_iterator`        | コンテナの指定位置に要素を挿入するためのイテレータアダプタ                   |
| `inserter`               | `insert_iterator` を生成するための関数                                       |
| `basic_const_iterator`   | const iterator への変換                                                      |
| `const_iterator`         | `const_iterator<I>` が有効なら `I`、そうでなければ `basic_const_iterator<I>` |
| `const_sentinel`         | `const_sentinel<I>` が有効なら `I`、そうでなければ `basic_const_iterator<I>` |
| `make_const_iterator`    | `const_iterator` を生成するための関数                                        |
| `make_const_sentinel`    | `const_sentinel` を生成するための関数                                        |
| `move_iterator`          | deref する時に値を move するイテレータを返すアダプタ                         |
| `move_sentinel`          | deref する時に値を move する sentinel を返すアダプタ                         |
| `make_move_iterator`     | `move_iterator` を生成するための関数                                         |
| `common_iterator`        | イテレータ `I` と sentinel `S` で表現される range を持つイテレータ型         |
| `default_sentinel`       | デフォルトの sentinel として振る舞う変数                                     |
| `counted_iterator`       | イテレータとカウンタを持つ range を表現するイテレータ型。`++` で減る         |
| `unreachable_sentinel_t` | `std::unreachable_sentinel_t` は、upper_bound を示す sentinel                |


## Stream iterators

- `istream_iterator`
  - 元になった `basic_istream` から値を `operator>>` で読み込むイテレータ
  - インクリメントすると次の値を読み込む
- `ostream_iterator`
  - 元になった `basic_ostream` に値を `operator<<` で書き込むイテレータ
- `istreambuf_iterator`
  - 元になった `basic_istreambuf` から単純に文字を読み込むイテレータ
  - インクリメントすると次の文字を読み込む
- `ostreambuf_iterator`
  - 元になった `basic_ostreambuf` に単純に文字を書き込むイテレータ


## Iterator operations

- `advance`
  - イテレータを指定された距離だけ進める
- `distance`
  - 2 つのイテレータ間の距離を計算する
- `next`
  - イテレータを指定された距離だけ進めた新しいイテレータを返す
- `prev`
  - イテレータを指定された距離だけ戻した新しいイテレータを返す


## Range access

- container / 配列 / initializer_list に適用可能
- `begin` / `end`
  - コンテナの先頭と終端を表すイテレータを返す
- `cbegin` / `cend`
  - コンテナの先頭と終端を表す const イテレータを返す
- `rbegin` / `rend`
  - コンテナの逆方向の先頭と終端を表すイテレータを返す
- `crbegin` / `crend`
  - コンテナの逆方向の先頭と終端を表す const イテレータを返す
- `size`  / `ssize`
  - コンテナの要素数を返す
- `empty`
  - コンテナが空かどうかを返す
- `data`
  - コンテナの要素へのポインタを返す

