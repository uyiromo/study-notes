# Algorithms library
- <https://en.cppreference.com/w/cpp/algorithm.html>


## Constrained algorithms (C++20)
- <https://en.cppreference.com/w/cpp/algorithm/ranges.html>
- `std::ranges` で定義された range を取るアルゴリズム
- AFO (Algorithm Function Object)
  - template list を明示的に指定できない
  - ADL では発見されない
  - function call の left-most にある時、ADL は働かない

- (TBD)


## Execution policies (C++17)
- STL の並列実行を指定する引数
  - STL によって任意の Execution policy がサポートされる可能性がある
- overload resolution に用いられる
- data race の回避はプログラマの責任
- ある型 `T` が execution policy か否かは `std::is_execution_policy_v<T>` で判定できる


```C++
#include <execution>

// 並列実行しない
class sequenced_policy { /* unspecified */ };
inline constexpr std::execution::sequenced_policy seq{ /* unspecified */ };

// スレッドを使って並列実行する
class parallel_policy { /* unspecified */ };
inline constexpr std::execution::parallel_policy par { /* unspecified */ };

// スレッドを使って並列・ベクトル実行する
// work-stealing 方式で順序を保証しない
class parallel_unsequenced_policy { /* unspecified */ };
inline constexpr std::execution::parallel_unsequenced_policy par_unseq { /* unspecified */ };

// シングルスレッドでベクトル実行する
class unsequenced_policy { /* unspecified */ };
inline constexpr std::execution::unsequenced_policy unseq { /* unspecified */ };
```


## Non-modifying sequence operations


### Batch operations

| Operation         | Execution Policy | Description                                            |
| ----------------- | ---------------- | ------------------------------------------------------ |
| for_each   | ✅                | UnaryFunction を `[first, last)` の範囲に適用する      |
| for_each_n | ✅                | UnaryFunction を `[first, first + n)` の範囲に適用する |


### Search operations

| Operation     | Execution Policy | Description                                                                  |
| ------------- | ---------------- | ---------------------------------------------------------------------------- |
| all_of        | ✅                | UnaryPredicate が `[first, last)` 全てで true なら true                      |
| any_of        | ✅                | UnaryPredicate が `[first, last)` のいずれかで true なら true                |
| none_of       | ✅                | UnaryPredicate が `[first, last)` 全てで false なら true                     |
| find          | ✅                | `*it == value` になる iterator or `last`                                     |
| find_if       | ✅                | `p(*it)` になる iterator or `last`                                           |
| find_if_not   | ✅                | `!p(*it)` になる iterator or `last`                                          |
| find_end      | ✅                | `[first, last)` の中で `[s_first, s_last)` に等しい範囲の最初の iterator     |
| find_first_of | ✅                | `[first, last)` の中で `[s_first, s_last)` のいずれかに等しい最初の iterator |
| adjacent_find | ✅                | `[first, last)` の中で、隣接する同じ値の iterator                            |
| count         | ✅                | `[first, last)` の中で `*it == value` を満たす要素数                         |
| count_if      | ✅                | `[first, last)` の中で `p(*it)` を満たす要素数                               |
| mismatch      | ✅                | `[first, last)` の中で `*it` or `[first2, last2)` と異なる最初の iterator    |
| equal         | ✅                | `[first, last)` が `[first2, last2)` に一致するか否か                        |
| search        | ✅                | `[first, last)` の中で `[s_first, s_last)` に一致する最初の iterator         |
| search_n      | ✅                | `[first, last)` の中で `value` が `count` 個連続する最初の iterator          |


### Fold operations
- (TBD)


## Modifying sequence operations


### Copy operations
- `*it` の loop でコピーするため、要素数が足りない場合はエラー
  - vector などは `std::back_inserter` で解決可能

| Operation     | Policy | Description                                                                      |
| ------------- | ------ | -------------------------------------------------------------------------------- |
| copy          | ✅      | `[first, last)` の要素を `d_first` から始まる範囲にコピー。領域に被りがあると UB |
| copy_if       | ✅      | copy に同じで、`pred(*it)` が true になるもののみ stable コピー                  |
| copy_n        | ✅      | `[first, first + n)` の要素を `d_first` から始まる領域にコピー             |
| copy_backward | ❌      | `[first, last)` `d_last` から逆順コピーする。領域に被りがあっても OK                  |
| move          | ✅      | `[first, last)` の要素を `d_first` から始まる範囲にムーブする。領域に被りがあると UB |
| move_backward | ❌      | `[first, last)` `d_last` から逆順ムーブする。領域に被りがあっても OK                  |


### Swap operations

| Operation   | Policy | Description                                           |
| ----------- | ------ | ----------------------------------------------------- |
| swap        | ❌      | `a` と `b` の値を MOVE で交換                         |
| swap_ranges | ✅      | `[first1, last1)` と `first2` から始まる範囲をを swap |
| iter_swap   | ❌      | `*a` と `*b` の値を swap                              |


### Transform operations

| Operation       | Policy | Description                                                                  |
| --------------- | ------ | ---------------------------------------------------------------------------- |
| transform       | ✅      | `[first, last)` の範囲を `d_first` から始まる範囲に unary_op してコピー      |
| replace         | ✅      | `[first, last)` の範囲を `old_value` を `new_value` に置換                   |
| replace_if      | ✅      | `[first, last)` の要素を `pred(*it)` が true なら `new_value` に置換         |
| replace_copy    | ✅      | replace に同じだが、元の要素を置換せず `d_first` の範囲にコピー              |
| replace_copy_if | ✅      | replace_if に同じだが、`pred(*it)` が true なら `new_value` に置換してコピー |


### Generation operations

| Operation  | Policy | Description                                          |
| ---------- | ------ | ---------------------------------------------------- |
| fill       | ✅      | `[first, last)` の範囲を `value` で埋める            |
| fill_n     | ✅      | `[first, first + n)` の範囲を `value` で埋める       |
| generate   | ✅      | `[first, last)` の範囲を `generator` で生成する      |
| generate_n | ✅      | `[first, first + n)` の範囲を `generator` で生成する |


### Removing operations

| Operation      | Policy | Description                                                                          |
| -------------- | ------ | ------------------------------------------------------------------------------------ |
| remove         | ✅      | `[first, last)` の範囲から `value` を削除してシフト                                  |
| remove_if      | ✅      | `[first, last)` の範囲から `pred(*it)` が true なら削除してシフト                    |
| remove_copy    | ✅      | `[first, last)` の範囲から `value` を無視して `d_first` の範囲にコピー               |
| remove_copy_if | ✅      | `[first, last)` の範囲から `pred(*it)` が true なら無視して `d_first` の範囲にコピー |
| unique         | ✅      | `[first, last)` の範囲から連続する重複を削除してシフト                               |
| unique_copy    | ✅      | `[first, last)` の範囲から連続する重複を削除して `d_first` の範囲にコピー            |


### Order-changing operations

| Operation    | Policy | Description                                                                             |
| ------------ | ------ | --------------------------------------------------------------------------------------- |
| reverse      | ✅      | `[first, last)` の範囲を逆順に並べ替える                                                |
| reverse_copy | ✅      | `[first, last)` の範囲を逆順に並べ替えて `d_first` の範囲にコピーする                   |
| rotate       | ✅      | `[first, last)` の範囲を `middle` から始まるように回転する                              |
| rotate_copy  | ✅      | `[first, last)` の範囲を `middle` から始まるように回転して `d_first` の範囲にコピーする |
| shift_left   | ✅      | `[first, last)` の範囲を `n` 個左にシフトする                                           |
| shift_right  | ✅      | `[first, last)` の範囲を `n` 個右にシフトする                                           |
| shuffle      | ✅      | `[first, last)` の範囲をランダムに並べ替える                                            |


### Sampling operations

| Operation | Policy | Description                                                                              |
| --------- | ------ | ---------------------------------------------------------------------------------------- |
| sample    | ✅      | `[first, last)` の範囲から `n` 個の要素をランダムに選択して `d_first` の範囲にコピーする |


## Sorting and related operations
- `sorted`
  - ある範囲について、比較関数 `comp` と射影関数 `proj` に対して、非負の整数 `n` に対して
  ```C++
  bool(std::invoke(comp, std::invoke(proj, *(iter + n)),
                        std::invoke(proj,*iter)))        == false.
  ```
- `partitioned`
  - ある範囲の要素 `e` について、関数 `f(e) == true`


### Partitioning operations

| Operation        | Policy | Description                                                                     |
| ---------------- | ------ | ------------------------------------------------------------------------------- |
| is_partitioned   | ✅      | `[first, last)` が `pred(*it)` で partitioned されているか否か                  |
| partition        | ✅      | `[first, last)` を `pred(*it)` で二分割する                                     |
| partition_copy   | ✅      | `[first, last)` を `pred(*it)` で二分割して、2 つの範囲にコピーする             |
| stable_partition | ✅      | `[first, last)` を `pred(*it)` で stable に二分割する                           |
| partition_point  | ✅      | `[first, last)` で `pred(*it)` が true になる最初の iterator (partitioned 前提) |


### Sorting operations

- `void nth_element( RandomIt first, RandomIt nth, RandomIt last );`
  - `[first, last)` の範囲を並び替える
  - `nth` 番目の要素は必ず正しいが、それ以外の要素は不定
    - `std::less{}` の場合、終了後に `*nth` 番目の要素は必ず `N` 番目に小さい
    - `0 <= i < N` の要素は `*nth` より小さいか等しいが、その中の順序は保証されない


| Operation         | Policy | Description                                                                      |
| ----------------- | ------ | -------------------------------------------------------------------------------- |
| sort              | ✅      | `[first, last)` の範囲を比較関数 `comp` でソートする                             |
| stable_sort       | ✅      | `[first, last)` の範囲を比較関数 `comp` で stable にソートする                   |
| partial_sort      | ✅      | `[first, first + N)` の範囲をソートする                                          |
| partial_sort_copy | ✅      | partial sort に同じだが、`d_first` の範囲にコピーする                            |
| is_sorted         | ✅      | `[first, last)` の範囲が比較関数 `comp` でソートされているか否か                 |
| is_sorted_until   | ✅      | `[first, it)` の範囲が比較関数 `comp` でソートされているような最大の it 取得       |
| nth_element       | ✅      | `[first, last)` の範囲を並び変える。比較関数 `comp` でソートして、`nth` 番目の要素を決定する |


### Binary search operations (or partitioned ranges)
- `lower_bound`
  - ソートされていると仮定して、`value` の**前にはならない**最初の要素
- `upper_bound`
- ソートされていると仮定して、`value` より大きい最初の要素


| Operation     | Policy | Description                                                             |
| ------------- | ------ | ----------------------------------------------------------------------- |
| lower_bound   | ❌      | `[first, last)` の範囲で `*it` が `value` より小さくない最初の iterator |
| upper_bound   | ❌      | `[first, last)` の範囲で `*it` が `value` より大きい最初の iterator     |
| equal_range   | ❌      | `[first, last)` の範囲で `*it == value` になる iterator 範囲            |
| binary_search | ❌      | `[first, last)` の範囲で `*it == value` になるか否か                    |


### Set operations (on sorted ranges)

| Operation                | Policy | Description                                                               |
| ------------------------ | ------ | ------------------------------------------------------------------------- |
| includes                 | ✅      | `[first1, last1)` が `[first2, last2)` を包含するか否か                   |
| set_union                | ✅      | `[first1, last1)` と `[first2, last2)` の OR を `d_first` の範囲にコピー  |
| set_intersection         | ✅      | `[first1, last1)` と `[first2, last2)` の AND を `d_first` の範囲にコピー |
| set_difference           | ✅      | `[first1, last1)` と `[first2, last2)` の - を `d_first` の範囲にコピー   |
| set_symmetric_difference | ✅      | `[first1, last1)` と `[first2, last2)` の XOR を `d_first` の範囲にコピー |


### Merge operations (on sorted ranges)

| Operation     | Policy | Description                                                                 |
| ------------- | ------ | --------------------------------------------------------------------------- |
| merge         | ✅      | `[first1, last1)` と `[first2, last2)` の範囲を `d_first` の範囲にマージ |
| inplace_merge | ✅      | `[first, middle)` と `[middle, last)` の範囲をマージしてソート         |


### Heap operations

| Operation     | Policy | Description                                                             |
| ------------- | ------ | ----------------------------------------------------------------------- |
| push_heap     | ❌      | `*(last-1)` の要素を追加して `[first, last)` の範囲をヒープに直す       |
| pop_heap      | ❌      | `*first` と `*(last-1)` を交換して `[first, last)` の範囲をヒープに直す |
| make_heap     | ❌      | `[first, last)` の範囲をヒープにする                                    |
| sort_heap     | ❌      | `[first, last)` の範囲をソートする。この操作の後はヒープ判定されない    |
| is_heap       | ❌      | `[first, last)` の範囲がヒープになっているか否か                        |
| is_heap_until | ❌      | `[first, it)` の範囲がヒープになっているような最大の it 取得            |


### Minimum/maximum operations

| Operation   | Policy | Description                                                      |
| ----------- | ------ | ---------------------------------------------------------------- |
| max         | ❌      | `max(*a, *b)` もしくは `max{ilist}` を返す                       |
| max_element | ✅      | `[first, last)` の範囲で最大の iterator を返す                   |
| min         | ❌      | `min(*a, *b)` もしくは `min{ilist}` を返す                       |
| min_element | ✅      | `[first, last)` の範囲で最小の iterator を返す                   |
| minmax      | ❌      | min/max の pair を返す                                           |
| clamp       | ❌      | `lo <= v <= hi` なら v、それ以外は lo/hi の内で v に近い方を返す |


### Lexicographical comparison operations

| Operation                         | Policy | Description                                                    |
| --------------------------------- | ------ | -------------------------------------------------------------- |
| lexicographical_compare           | ✅      | `[first1, last1)` が辞書順で `[first2, last2)` より前なら true |
| lexicographical_compare_three_way | ❌      | 辞書順比較を three-way comparator で行う                       |


### Permutation operations

| Operation        | Policy | Description                                                               |
| ---------------- | ------ | ------------------------------------------------------------------------- |
| next_permutation | ✅      | `[first, last)` の範囲を次の順列に並び替える。最後の順列なら false を返す |
| prev_permutation | ✅      | `[first, last)` の範囲を前の順列に並び替える。最初の順列なら false を返す |
| is_permutation   | ✅      | `[first, last)` の範囲が `d_first` の範囲の順列か否か                     |


## Numeric operations

| Operation                | Policy | Description                                                                 |
| ------------------------ | ------ | --------------------------------------------------------------------------- |
| iota                     | ❌      | `[first, last)` の範囲を `value` から始まる連続した値で埋める               |
| accumulate               | ❌      | `[first, last)` の範囲を `init` から始まる値で累積する                      |
| inner_product            | ❌      | `[first1, last1)` と `[first2, last2)` の範囲を内積計算する                 |
| adjacent_difference      | ✅      | `[first, last)` の範囲を隣接する要素の差分で置き換える                      |
| partial_sum              | ❌      | `[first, last)` の範囲を隣接する要素の累積和で置き換える                    |
| reduce                   | ✅      | `[first, last)` の範囲を畳み込む                                            |
| exclusive_scan           | ✅      | `[first, last)` の範囲をスキャンする。i 番目の結果に `*(init+i)` を含まない |
| inclusive_scan           | ✅      | `[first, last)` の範囲をスキャンする。i 番目の結果に `*(init+i)` を含む     |
| transform_reduce         |        | 2つの範囲を transform してから reduce する                                  |
| transform_exclusive_scan |        | transform してから exclusive_scan                                           |
| transform_inclusive_scan |        | transform してから inclusive_scan                                           |


## Operation on uninitialized memory

| Operation                         | Policy | Description                                                          |
| --------------------------------- | ------ | -------------------------------------------------------------------- |
| uninitialized_copy                | ✅      | `[first, last)` の範囲を `d_first` の範囲にコピー                    |
| uninitialized_copy_n              | ✅      | `[first, first + n)` の範囲を `d_first` の範囲にコピー               |
| uninitialized_fill                | ✅      | `[first, last)` の範囲を `value` で埋める                            |
| uninitialized_fill_n              | ✅      | `[first, first + n)` の範囲を `value` で埋める                       |
| uninitialized_move                | ✅      | `[first, last)` の範囲を `d_first` の範囲にムーブする                |
| uninitialized_move_n              | ✅      | `[first, first + n)` の範囲を `d_first` の範囲にムーブする           |
| uninitialized_default_construct   | ✅      | `[first, last)` の範囲をデフォルトコンストラクトする                 |
| uninitialized_default_construct_n | ✅      | `[first, first + n)` の範囲をデフォルトコンストラクトする            |
| uninitialized_value_construct     | ✅      | `[first, last)` の範囲を値でコンストラクトする                       |
| uninitialized_value_construct_n   | ✅      | `[first, first + n)` の範囲を値でコンストラクトする                  |
| destroy                           | ✅      | `[first, last)` の範囲を `destroy_at(std::addressof(*it))` する      |
| destroy_n                         | ✅      | `[first, first + n)` の範囲を `destroy_at(std::addressof(*it))` する |
| destroy_at                        | -      | `p` のデストラクタを呼び出す                                         |
| construct_at                      | -      | `p` を placement-new した領域に construct する                       |


## Random number generation
- TODO: TBD
