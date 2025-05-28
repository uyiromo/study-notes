# Initialization

- <https://en.cppreference.com/w/cpp/language/initialization>

1. `= ...`
   - copy-initialization
2. `= { ... }`
   - list-initialization
3. `(...)`
   - direct-initialized
4. `{ ... }`
   - 2. と同じ意味

- `std::string s2()` は、syntax 上、初期化ではなく関数宣言として扱われる

- **Initializer semantics**
  - initializer が未指定の場合、default-initialized。参照の初期化が無い場合、ill-formed
  - object が `()` で初期化される場合、value-initialized。
  - initializer semantics
    - reference の初期化の場合、reference initialization に従う
    - そうでない場合、オブジェクトの型が `T` とする
      - `obj = ...` の場合、copy-initialized
      - `obj = {...}` の場合、
        - `T` が集成体の場合、aggregate initialization
        - `T` が scalar の場合、`T x = {a};` は `T x = a;` に等しい
        - そうでないなら、ill-formed
      - `{...}` で初期化されるなら、list-initialized
      - `T x()` は direct-initialized
- **Non-local variables**
  - static storage duration を持つ変数は、startup の一部、つまり `main` の前に初期化される
  - Thread-local storage duration を持つ変数は、スレッド起動の一部、つまり thread function の前に初期化される
  - **Static initialization**
    - 可能なら、constant-initialization
    - 不可能なら、zero-initialized
  - **Dynamic initialization**
    - Unordered dynamic initialization
    - Partially-ordered dynamic initialization
    - Ordered dynamic initialization
  - **Early dynamic initialization**
  - **Deferred dynamic initialization**


## Default-initialization

- <https://en.cppreference.com/w/cpp/language/default_initialization>
- **Syntax**
  - `T obj;`
  - `new T;`
- 以下のように動作する
  - class の場合、デフォルトコンストラクタを適用する
  - array の場合、各要素に対して Default-initialization
  - それ以外の場合、初期化は発生しない
- **Default-initialization of const object**
  - const 変数が Default-initialized される場合、`const-default-constructible` でなければならない
- **Indeterminate and erroneous values**
  - automatic / dynamic storage duration を獲得した時、該当領域は以下に示す初期値を持つ
    - dynamic か `[[indeterminate]]` 変数は、indeterminate value
    - それ以外なら erroneous value
  - indeterminate value が参照された場合、動作は undefined
  - erroneous value が参照された場合、動作は erroneous
- **Special cases**
  - std::byte / unsigned char / char は、uninitialized-friendly
  - これらの型は indeterminate / erroneous value が参照されても well-defined


## Value-initialization

- <https://en.cppreference.com/w/cpp/language/value_initialization>
- `()` もしくは `{}` は、Value-initialization
  - aggregate の場合は aggregate-initialization になる
- Value-initialization の効果
  - class なら、デフォルトコンストラクタ。なければ Zero-initialization
  - array なら、各要素に対して value-initialization
  - それ以外なら、zero-initialization


## Copy-initialization

- <https://en.cppreference.com/w/cpp/language/copy_initialization>
- 次の場合に発生
  - `T obj = other;`
  - pass by value
  - return by value
  - catch
  - aggregate initialization
- Copy-Initialization の効果
  - class で prvalue を受けた時、同じ型なら materialize せずに copy elision で直接初期化する
  - class で、型を変換可能な (derived or `T`) non-explicit コンストラクタがあるなら、それを呼ぶ
  - 右辺の型を `T` に変換可能な場合、オーバーロード解決してからそれを利用する
  - それ以外なら、必要に応じて standard-conversion を行う
- `explicit` コンストラクタは、Copy-Initialization のオーバーロード解決に参加しない
- Copy-Initialization の暗黙の型変換では、直接 `T` に変換可能でなければならない


## Direct-initialization

- <https://en.cppreference.com/w/cpp/language/direct_initialization>
- Direct-initialization の効果
  - array の場合、aggregate initialization が適用できなければ ill-formed
  - class の場合
    - prvalue なら、直接構築する
    - コンストラクタを呼ぶ
    - 条件付きで aggregate initialization 可能
  - オーバーロード解決で変換を行う
  - `bool` に `std::nullptr_t` が与えられた場合、`false`
  - その他の場合、standard conversion に従う


## Aggregate initialization

- <https://en.cppreference.com/w/cpp/language/aggregate_initialization>
- **Aggregate**
- **Element**
  - array, class は宣言順に対応
- **Appertainment**
- **Initialization process**
  - Explicitly initialized elements を抽出してマッチする
    - designate initializer list のように、明示的に指定される要素を抽出してマッチする
  - その後、残りの要素を element order で処理する
- **Explicitly initialized elements**
- **Implicitly initialized elements**
  - initializer が無く、default member initializer があるなら、それで初期化される
  - default member initializer が無く、reference でないなら、空の initializer list から copy-initialize される
- **Arrays with unknown bounds**
- **Designated initializers**


## List-initialization

- <https://en.cppreference.com/w/cpp/language/list_initialization>
- **Direct-list-initialization**
  - `T obj{...}`
  - `T{...}`
  - `new T{...}`
- **Copy-list-initialization**
  - `T obj = {...}`
  - `function({...})`
  - `return {...}`
- list-initialization の効果
  - (initializer list が designated initializer list なら aggregate initialization を適用)
  - aggregate への代入の場合はそのまま適用
  - char array で、initializer list が適切なら、通常のように動作
  - aggregate なら aggregate initialization 適用
  - initializer list が空で、`T` がデフォルトコンストラクタを持つなら、value initialization 適用
  - `T` が `std::initializer_list` 特殊化を持つ場合、以下の動作を行う
    - `std::initializer_list<E>` は backing array `const std::array<E, N>` のように振る舞う
  - `T` が class なら、次の 2 phase でコンストラクタを探す
    - オーバーロード解決で `std::initializer_list` を持つコンストラクタが一つだけ見つかった場合、適用
      - `std::initializer_list` のみを引数に取る or `std::initializer_list` 以外はすべてデフォルト引数
    - non-explicit で、narrowing 無しのコンストラクタがあれば適用
  - `T` が class でなく、initializer list が互換なら direct-initialization 適用
  - `T` が initializer list と互換の無い reference なら、
    - prvalue を生成して初期化する
  - どれでもなく、initializer list が空なら、value initialization 適用
- **Narrowing conversions**
  - 以下の操作は許可されない
    - floating point から int への変換
    - rank の低い floating point への変換（オーバーフローが発生しないなら可能）
    - 定数で確実に floating point へ変換できる保証の無い int => floating point
    - int => unscoped enum への変換
    - pointer から bool への変換
- initializer list の場合、前から後ろへの sequenced before が保証される
- `template <typename T>` は initializer_list を推論しないが、`auto` は `std::initializer_list` を推論できる
- aggregate に対して `Q q2 = Q{q}` とした場合、initializer_list のコンストラクタが優先される


## Reference initialization

- <https://en.cppreference.com/w/cpp/language/reference_initialization>
- Reference initialization の効果
  - ordinary / designated list-initialization なら、list-initialization に従う
  - 右辺の型 `U` が Direct binding、Indirect binding 可能ならそれに従う。不可能なら ill-formed
- **Direct binding**
  - 以下全ての条件を満たした時に発生する
    - lvalue reference を初期化する
    - target (右辺) が bit-field ではない
    - 左辺の型 `T` が、右辺の型 `U` に reference-compatible
  - もしくは、`U` が class で、左辺の型 `T` に変換可能な場合
  - もしくは、`U` が rvalue な場合、`T` が lvalue なら、const でなければならない
  - reference binds to target (参照が右辺にバインドされる)、と表現する
  - TODO
- **Indirect binding**
  - Direct binding が不可能な場合、copy-initialization での変換を試みる
- **Lifetime of temporary**
  - temporary object の lifetime は、bind された reference の lifetime に依存して延長される
  - 以下のルールに従う
    - (~C++26) return value の lifetime は延長されない
    - 関数呼び出しの引数の lifetime は関数呼び出し終了まで延長される。関数が reference を返したら dangling
    - initializer list に含まれる reference は、initializer list を含む expression 終了まで延長される
    - temporary を、`list initialization {}` で用いた場合は aggregate 終了まで延長
      - `direct initialization ()` で用いた場合は dangling


## Zero-initialization

- <https://en.cppreference.com/w/cpp/language/zero_initialization>
- 変数が未初期化、デフォルトコンストラクタ、element が足りない array の場合、zero-initialization が発生する可能性がある
- zero-initialization の効果
  - scalar は 0 を型に合わせた値で埋まる
  - non-union は
    - padding bit、non-static data member、class object をゼロ埋め
  - union は、padding bit と、最初のメンバをゼロ埋め
  - array は、全要素をゼロ埋め
  - reference は、何もしない


## Constant initialization

- <https://en.cppreference.com/w/cpp/language/constant_initialization>
- コンパイル時に static variable で初期化を行う


## Copy elision

- <https://en.cppreference.com/w/cpp/language/copy_elision>
- 基準が満たされた時、元の object から対象 object の作成を省略する
  - コンストラクタ/デストラクタが side-effect を持つ場合でも無視される
- 以下の基準を満たした時
  - **NRVO (Named Return Value Optimization)**
    - return value が non-volatile で automatic storage duration を持つ class
  - **URVO (Unnamed Return Value Optimization)**
    - C++17 から mandatory になった
  - throw の parameter
  - coroutine
- Copy elision が発生した場合、2 つの参照が発生したように扱う
- **Prvalue semantics (guaranteed copy elision)**
  - prvalue は必要になるまで materialize されず、最終目的アドレスに直接構築される
  - `return` で構築される場合、適用される
  - `cv-qualification` は無視されるが、RVO が働かない時、`const` 有りだと move できない
