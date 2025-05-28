
# Lambda expressions (C++11)
- <https://en.cppreference.com/w/cpp/language/lambda>
- **Syntax**
  - `*` は optional を示す
  - **captures**
    - キャプチャリスト
  - **tparams**
  - **t-requires**
    - template 要件
  - **front-attr**
    - 前置属性
    - `[[noreturn]]` を適用可能
  - **params**
    - 引数リスト
  - **specs**
    - `mutable`
      - copy capture したオブジェクトの変更と、non-const メンバ関数の呼び出しを許可する
    - `constexpr`
      - `constexpr` を明示指定
    - `consteval`
      - `consteval` を明示指定
    - `static`
      - `static` メンバ関数として定義
  - **except**
    - 例外指定
  - **back-attr**
    - 後置属性
    - `[[noreturn]]` を適用可能
  - **trailing**
    - `-> ret` で返り値属性を指定
  - **requires**
    - `operator()` に対する制約
  - **contract-specs**
    - contract specification
  - **body**
    - 本体

  ```C++
  // テンプレート無し
  // params は省略可能
  [captures] front-attr* (params) specs* except*
  back-attr* trailing* requires* contract-specs* { body }

  // テンプレート有り
  [captures] <tparams> t-requires*
  front-attr* (params) specs* except*
  back-attr* trailing* requires* contract-specs* { body }
  ```


## Closure type
- lambda 式は、unique unnamed な型 (closure type) を持つ
- captures が空な場合、structural type になる
- 次のメンバを持つ
  - `ClosureType::operator()(params)`
    - body を実行する
    - 返り値の型は、trailing で未指定なら return 式から推論する
    - non-reference な変数を reference capture した場合、Dangling reference に注意
  - `ClosureType::operator ret(*)(params)()`
    - capture しない場合、関数ポインタへの変換が可能
  - `ClosureType::operator=(const ClosureType&)`
    - C++20 から、capture が無い場合のみ、copy / move assign 可能
  - `ClosureType::Captures`
    - copy capture した場合、lambda 式評価時に初期化される
- lambda は unevaluated expression, template argument, alias declaration, typedef, function declamation では使用できない
  - default argument では使用できる


## Lambda capture
- lambda からアクセスする外部変数を定義する
- `captures` は以下のいずれか
  ```C++
  // (1)
  // デフォルトキャプチャ
  // `&` = 参照キャプチャ
  // `=` = 値キャプチャ
  capture-default

  // (2)
  capture-list

  // (3)
  capture-default, capture-list
  ```
- `capture` の定義
  - `capture-default` が `&` の場合、以降の変数は参照キャプチャ不可
  - `capture-default` が `=` の場合、以降の変数は this に限りコピー可能
  - 一変数につき一回までキャプチャ可能で、`capture` と `params` で名前重複不可
  ```C++
  // (1)
  // コピーキャプチャ
  // コピーコンストラクタで初期化される
  // mutable 指定が無い場合、Closure 内の const 変数として振る舞う
  identifier

  // (2)
  // コピーキャプチャ (pack)
  identifier...

  // (3)
  // コピーキャプチャ (初期化子)
  identifier initializer

  // (4)
  &identifier

  // (5)
  &identifier...

  // (6)
  &identifier initializer

  // (7)
  // 参照キャプチャ (this)
  this

  // (8)
  // コピーキャプチャ (this)
  *this

  // (9)
  // コピーキャプチャ (initializer + pack)
  ... identifier initializer

  // (10)
  // 参照キャプチャ (initializer + pack)
  &... identifier initializer
  ```
- 次の条件を満たす時、キャプチャ不要
  - non-local 変数 / static 変数 / TLS 変数
  - constant expression (コンパイル時定数)
- ODR-use でない場合、キャプチャを介さず、元変数に直接アクセスする
  - 定数など
  - `decltype` / `typeid` などの unevaluated expression
- reference `A` を reference capture した場合、元変数 `A` に直接アクセスする
- ODR-use する変数かつ automatic duration の場合、変数はキャプチャされなければならない
- class member をキャプチャする場合、initializer が必要
  - `=` でデフォルトキャプチャする場合、実際にはコピーせず `*(this).member` のようにアクセスされる
- `capture-default` がある場合、this は常に参照キャプチャされる
- `identifier` は、最内側スコープから探索され、automatic duration の変数でなければならない
- default argument で使用される場合、キャプチャできない
- 無名 union のメンバはキャプチャできない
- bit-field はコピーキャプチャしかできない
