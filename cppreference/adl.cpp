#include <iostream>

namespace test
{
struct S // NOLINT
{
};

constexpr bool empty(const S&) noexcept // NOLINT
{
    std::cout << "constexpr bool empty(S&) noexcept" << "\n";
    return true;
}

struct S2 // NOLINT
{
  private:
    bool b = false;

  public:
    [[nodiscard]] constexpr auto empty() const noexcept -> bool
    {
        std::cout << "a" << '\n';
        return this->b;
    }
};

} // namespace test

int main()     // NOLINT
{
    test::S s; // NOLINT

    // qualified name lookup なので ADL 無効
    // std::cout << "std::empty(s) = " << std::empty(s) << "\n";

    // ADL 有効
    // ただし S は Container ではないので不正な制約回避
    using std::size;
    std::cout << "     empty(s) = " << empty(s) << "\n";

    // ADL 有効だが、requires を回避しない
    // std::cout << "std::ranges::empty(s) = " << std::ranges::empty(s) << "\n";

    // ADL 有効かつ、requires を満たす
    std::cout << "std::ranges::empty(s2) = " << std::ranges::empty(test::S2{}) << "\n";

    std::cout << ">> All done!" << "\n";
    return 0;
}
