# Strings library
- <https://en.cppreference.com/w/cpp/string.html>
- 文字列操作は次のライブラリも参照
  - localization
  - input/output
  - regular expressions
- Strings / regular expression library は char-like object を扱う
  - 一部の STL は *character container types* をサポート


## Character traits
- `std::basic_string` のような character-related class template を満たすための typedef と function を定義したもの
- `CharTraits` を満たす
  - <https://en.cppreference.com/w/cpp/named_req/CharTraits.html>


## String classes (`std::string`...)
- String class は `std::basic_string` を特殊化している

| Type             | Definition                    |
| ---------------- | ----------------------------- |
| `std::string`    | `std::basic_string<char>`     |
| `std::wstring`   | `std::basic_string<wchar_t>`  |
| `std::u16string` | `std::basic_string<char16_t>` |
| `std::u32string` | `std::basic_string<char32_t>` |


## String view classes (`std::string_view`...)
- `std::basic_string_view` は、string の全体/一部を参照する read-only な軽量クラス
  - `std::basic_string` とほぼ同じ I/F を持つ

| Type                  | Definition                         |
| --------------------- | ---------------------------------- |
| `std::string_view`    | `std::basic_string_view<char>`     |
| `std::wstring_view`   | `std::basic_string_view<wchar_t>`  |
| `std::u16string_view` | `std::basic_string_view<char16_t>` |
| `std::u32string_view` | `std::basic_string_view<char32_t>` |

