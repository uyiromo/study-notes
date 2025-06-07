# array `<array>`
- 固定サイズの配列をカプセル化したもので、`T[N]` をメンバとして持つ
- 次の requirements を満たす
  - `Container`
  - `ReversibleContainer`
  - `ContiguousContainer`
  - `SequenceContainer`

- **Definition**
  ```C++
  template<

      class T,
      std::size_t N
  > struct array;
  ```
  - `int`, `const int`, `int*` のような型は取れる
  - `int&` のような参照型は取れない（typename C::pointer を定義できない）


- see: [./tests/array.cpp](./tests/array.cpp)


## Member types

| Member type              | Definition                                   |
| ------------------------ | -------------------------------------------- |
| `value_type`             | `T`                                          |
| `size_type`              | `std::size_t`                                |
| `difference_type`        | `std::ptrdiff_t`                             |
| `reference`              | `value_type&`                                |
| `const_reference`        | `const value_type&`                          |
| `pointer`                | `value_type*`                                |
| `const_pointer`          | `const value_type*`                          |
| `iterator`               | `std::contiguous_iterator<value_type>`       |
| `const_iterator`         | `std::contiguous_iterator<const value_type>` |
| `reverse_iterator`       | `std::reverse_iterator<iterator>`            |
| `const_reverse_iterator` | `std::reverse_iterator<const_iterator>`      |


## Member functions


### Implicitly-defined member functions
- (constructor)
- (destructor)
- operator=
  - それぞれの要素を上書きする


## Element access
- at / operator[] / front / back
  - `T&` もしくは `const T&` を返す
  - at は範囲外アクセス時に `std::out_of_range` 例外を投げる
  - operator[] は範囲外アクセス時に UB
- data
  - `T*` を返す


## Iterators
- begin / cbegin
- end / cend
- rbegin / crbegin
- rend / crend


## capacity
- empty
- size
  - 返り値 `std::size_t`
  - `std::distance(begin(), end())` と同じ
- max_size
  - size に同じ


## Operations
- fill
  - 要素を全埋めする
  - `void fill( const T& value );` なので、`T` は CopyAssignable
- swap
  - 型 `T` は Swappable (MoveAssinable) である必要がある


## Non-member functions
- operator== / operator <=>
- std::get
  - std::get の特殊化なので、返り値の const と LR reference は引数に与えた array に依存
- std::swap
- std::to_array
  - 配列から std::array に変換する
  - 初期化は CopyConstruct or MoveConstruct される

