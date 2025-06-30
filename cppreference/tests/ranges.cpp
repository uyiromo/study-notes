#include "gtest/gtest.h"
#include <algorithm>
#include <array>
#include <concepts>
#include <deque>
#include <forward_list>
#include <iomanip>
#include <iterator>
#include <list>
#include <numeric>
#include <ranges>
#include <sstream>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace
{
using std::plus;
using std::string;

TEST(
    ranges, RangePrimitives
)
{
    constexpr size_t N = 5; // NOLINT

    /*
     * ranges::iterator_t
     */
    static_assert(std::is_same_v<std::ranges::iterator_t<std::vector<int>>, std::vector<int>::iterator>);
    static_assert(std::is_same_v<std::ranges::iterator_t<std::array<int, N>>, std::array<int, N>::iterator>);
    static_assert(std::is_same_v<std::ranges::iterator_t<std::deque<int>>, std::deque<int>::iterator>);
    static_assert(std::is_same_v<std::ranges::iterator_t<std::list<int>>, std::list<int>::iterator>);
    static_assert(std::is_same_v<std::ranges::iterator_t<std::forward_list<int>>, std::forward_list<int>::iterator>);

/*
 * ranges::const_iterator_t
 */
#if 0 // NOLINT
     static_assert(std::is_same_v<
                  std::ranges::const_iterator_t<std::vector<int>>,
                  std::const_iterator<std::vector<int>::iterator>>);
    static_assert(std::is_same_v<
                  std::ranges::const_iterator_t<std::array<int, N>>,
                  std::const_iterator<std::array<int, N>::iterator>>);
    static_assert(std::is_same_v<
                  std::ranges::const_iterator_t<std::deque<int>>,
                  std::const_iterator<std::deque<int>::iterator>>);
    static_assert(std::is_same_v<
                  std::ranges::const_iterator_t<std::list<int>>,
                  std::const_iterator<std::list<int>::iterator>>);
    static_assert(std::is_same_v<
                  std::ranges::const_iterator_t<std::forward_list<int>>,
                  std::const_iterator<std::forward_list<int>::iterator>>);
#endif

    /*
     * ranges::sentinel_t
     */
    static_assert(std::is_same_v<std::ranges::sentinel_t<std::vector<int>>, std::vector<int>::iterator>);
    static_assert(std::is_same_v<std::ranges::sentinel_t<std::array<int, N>>, std::array<int, N>::iterator>);
    static_assert(std::is_same_v<std::ranges::sentinel_t<std::deque<int>>, std::deque<int>::iterator>);
    static_assert(std::is_same_v<std::ranges::sentinel_t<std::list<int>>, std::list<int>::iterator>);
    static_assert(std::is_same_v<std::ranges::sentinel_t<std::forward_list<int>>, std::forward_list<int>::iterator>);

    /*
     * ranges::const_sentinel_t
     */
#if 0 // NOLINT
     static_assert(std::is_same_v<
                  std::ranges::const_sentinel_t<std::vector<int>>,
                  std::const_iterator<std::vector<int>::iterator>>);
    static_assert(std::is_same_v<
                  std::ranges::const_sentinel_t<std::array<int, N>>,
                  std::const_iterator<std::array<int, N>::iterator>>);
    static_assert(std::is_same_v<
                  std::ranges::const_sentinel_t<std::deque<int>>,
                  std::const_iterator<std::deque<int>::iterator>>);
    static_assert(std::is_same_v<
                  std::ranges::const_sentinel_t<std::list<int>>,
                  std::const_iterator<std::list<int>::iterator>>);
    static_assert(std::is_same_v<
                  std::ranges::const_sentinel_t<std::forward_list<int>>,
                  std::const_iterator<std::forward_list<int>::iterator>>);
#endif

    /*
     * ranges::range_difference_t
     */
    static_assert(std::is_same_v<std::ranges::range_difference_t<std::vector<int>>, std::ptrdiff_t>);
    static_assert(std::is_same_v<std::ranges::range_difference_t<std::array<int, N>>, std::ptrdiff_t>);
    static_assert(std::is_same_v<std::ranges::range_difference_t<std::deque<int>>, std::ptrdiff_t>);
    static_assert(std::is_same_v<std::ranges::range_difference_t<std::list<int>>, std::ptrdiff_t>);
    static_assert(std::is_same_v<std::ranges::range_difference_t<std::forward_list<int>>, std::ptrdiff_t>);

    /*
     * ranges::range_size_t
     */
    static_assert(std::is_same_v<std::ranges::range_size_t<std::vector<int>>, std::vector<int>::size_type>);
    static_assert(std::is_same_v<std::ranges::range_size_t<std::array<int, N>>, std::array<int, N>::size_type>);
    static_assert(std::is_same_v<std::ranges::range_size_t<std::deque<int>>, std::deque<int>::size_type>);
    static_assert(std::is_same_v<std::ranges::range_size_t<std::list<int>>, std::list<int>::size_type>);
    // static_assert(std::is_same_v<std::ranges::range_size_t<std::forward_list<int>>,
    // std::forward_list<int>::size_type>);

    /*
     * ranges::range_value_t
     */
    static_assert(std::is_same_v<std::ranges::range_value_t<std::vector<int>>, std::vector<int>::value_type>);
    static_assert(std::is_same_v<std::ranges::range_value_t<std::array<int, N>>, std::array<int, N>::value_type>);
    static_assert(std::is_same_v<std::ranges::range_value_t<std::deque<int>>, std::deque<int>::value_type>);
    static_assert(std::is_same_v<std::ranges::range_value_t<std::list<int>>, std::list<int>::value_type>);
    static_assert(std::is_same_v<
                  std::ranges::range_value_t<std::forward_list<int>>,
                  std::forward_list<int>::value_type>);

    /*
     * ranges::range_reference_t
     */
    static_assert(std::is_same_v<std::ranges::range_reference_t<std::vector<int>>, std::vector<int>::reference>);
    static_assert(std::is_same_v<std::ranges::range_reference_t<std::array<int, N>>, std::array<int, N>::reference>);
    static_assert(std::is_same_v<std::ranges::range_reference_t<std::deque<int>>, std::deque<int>::reference>);
    static_assert(std::is_same_v<std::ranges::range_reference_t<std::list<int>>, std::list<int>::reference>);
    static_assert(std::is_same_v<
                  std::ranges::range_reference_t<std::forward_list<int>>,
                  std::forward_list<int>::reference>);
    /*
     * ranges::range_const_reference_t
     */
#if 0 // NOLINT
     static_assert(std::is_same_v<
                  std::ranges::range_const_reference_t<std::vector<int>>,
                  std::vector<int>::const_reference>);
    static_assert(std::is_same_v<
                  std::ranges::range_const_reference_t<std::array<int, N>>,
                  std::array<int, N>::const_reference>);
    static_assert(std::is_same_v<
                  std::ranges::range_const_reference_t<std::deque<int>>,
                  std::deque<int>::const_reference>);
    static_assert(std::
                      is_same_v<std::ranges::range_const_reference_t<std::list<int>>, std::list<int>::const_reference>);
    static_assert(std::is_same_v<
                  std::ranges::range_const_reference_t<std::forward_list<int>>,
                  std::forward_list<int>::const_reference>);
#endif

    /*
     * ranges::range_rvalue_reference_t
     */
    static_assert(std::is_same_v<
                  std::ranges::range_rvalue_reference_t<std::vector<int>>,
                  std::vector<int>::value_type&&>);
    static_assert(std::is_same_v<
                  std::ranges::range_rvalue_reference_t<std::array<int, N>>,
                  std::array<int, N>::value_type&&>);
    static_assert(std::
                      is_same_v<std::ranges::range_rvalue_reference_t<std::deque<int>>, std::deque<int>::value_type&&>);
    static_assert(std::is_same_v<std::ranges::range_rvalue_reference_t<std::list<int>>, std::list<int>::value_type&&>);
    static_assert(std::is_same_v<
                  std::ranges::range_rvalue_reference_t<std::forward_list<int>>,
                  std::forward_list<int>::value_type&&>);
}

TEST(
    ranges, RangeConcepts
)
{
    constexpr size_t N = 5; // NOLINT

    /*
     * ranges::range
     */
    static_assert(std::ranges::range<std::vector<int>>);
    static_assert(std::ranges::range<std::array<int, N>>);
    static_assert(std::ranges::range<std::deque<int>>);
    static_assert(std::ranges::range<std::list<int>>);

    /*
     * ranges::borrowed_range
     */
    static_assert(!std::ranges::borrowed_range<std::vector<int>>);
    static_assert(std::ranges::borrowed_range<std::vector<int>&>);

    /*
     * ranges::sized_range
     */
    static_assert(std::ranges::sized_range<std::vector<int>>);
    static_assert(std::ranges::sized_range<std::array<int, N>>);
    static_assert(std::ranges::sized_range<std::deque<int>>);
    static_assert(std::ranges::sized_range<std::list<int>>);

    /*
     * ranges::view
     */
    static_assert(!std::ranges::view<std::vector<int>>);
    static_assert(!std::ranges::view<std::array<int, N>>);
    static_assert(!std::ranges::view<std::deque<int>>);
    static_assert(!std::ranges::view<std::list<int>>);
    static_assert(std::ranges::view<std::string_view>);

    /*
     * ranges::input_range
     */
    static_assert(std::ranges::input_range<std::vector<int>>);
    static_assert(std::ranges::input_range<std::array<int, N>>);
    static_assert(std::ranges::input_range<std::deque<int>>);
    static_assert(std::ranges::input_range<std::list<int>>);
    static_assert(std::ranges::input_range<std::string>);

    /*
     * ranges::output_range
     */
    static_assert(std::ranges::output_range<std::vector<int>, int>);
    static_assert(std::ranges::output_range<std::array<int, N>, int>);
    static_assert(std::ranges::output_range<std::deque<int>, int>);
    static_assert(std::ranges::output_range<std::list<int>, int>);
    static_assert(std::ranges::output_range<std::string, char>);

    /*
     * ranges::forward_range
     */
    static_assert(std::ranges::forward_range<std::vector<int>>);
    static_assert(std::ranges::forward_range<std::array<int, N>>);
    static_assert(std::ranges::forward_range<std::deque<int>>);
    static_assert(std::ranges::forward_range<std::list<int>>);

    /*
     * ranges::bidirectional_range
     */
    static_assert(std::ranges::bidirectional_range<std::vector<int>>);
    static_assert(std::ranges::bidirectional_range<std::array<int, N>>);
    static_assert(std::ranges::bidirectional_range<std::deque<int>>);
    static_assert(std::ranges::bidirectional_range<std::list<int>>);
    static_assert(!std::ranges::bidirectional_range<std::forward_list<int>>);

    /*
     * ranges::random_access_range
     */
    static_assert(std::ranges::random_access_range<std::vector<int>>);
    static_assert(std::ranges::random_access_range<std::array<int, N>>);
    static_assert(std::ranges::random_access_range<std::deque<int>>);
    static_assert(!std::ranges::random_access_range<std::list<int>>);
    static_assert(!std::ranges::random_access_range<std::forward_list<int>>);

    /*
     * ranges::contiguous_range
     */
    static_assert(std::ranges::contiguous_range<std::vector<int>>);
    static_assert(std::ranges::contiguous_range<std::array<int, N>>);
    static_assert(!std::ranges::contiguous_range<std::deque<int>>);
    static_assert(!std::ranges::contiguous_range<std::list<int>>);
    static_assert(!std::ranges::contiguous_range<std::forward_list<int>>);

    /*
     * std::common_range
     */
    static_assert(std::ranges::common_range<std::vector<int>>);
    static_assert(std::ranges::common_range<std::array<int, N>>);
    static_assert(std::ranges::common_range<std::deque<int>>);
    static_assert(std::ranges::common_range<std::list<int>>);
    static_assert(std::ranges::common_range<std::forward_list<int>>);

    /*
     * ranges::viewable_range
     */
    static_assert(std::ranges::viewable_range<std::vector<int>>);
    static_assert(std::ranges::viewable_range<std::array<int, N>>);
    static_assert(std::ranges::viewable_range<std::deque<int>>);
    static_assert(std::ranges::viewable_range<std::list<int>>);
    static_assert(std::ranges::viewable_range<std::string_view>);
    static_assert(std::ranges::viewable_range<std::forward_list<int>>);

    /*
     * ranges::constant_range
     */
#if 0 // NOLINT
    static_assert(std::ranges::constant_range<const std::vector<int>>);
    static_assert(std::ranges::constant_range<const std::array<int, N>>);
    static_assert(std::ranges::constant_range<const std::deque<int>>);
    static_assert(std::ranges::constant_range<const std::list<int>>);
    static_assert(std::ranges::constant_range<const std::forward_list<int>>);
#endif
}

TEST(
    ranges, Conversions
)
{
    // template< class C, ranges::input_range R, class... Args >
    //     requires(!ranges::view<C>)
    // constexpr C to(R && r, Args && ... args);
    std::vector<int> v1{1, 2, 3, 4, 5};            // NOLINT

    auto x = std::ranges::to<std::deque<int>>(v1); // NOLINT
    static_assert(std::is_same_v<decltype(x), std::deque<int>>);

    // ill-formed
    // auto y = std::ranges::to<std::array<int, 5>>(v1); // NOLINT
}

TEST(
    ranges, Factories
)
{
    auto re1 = std::ranges::empty_view<int>{};
    auto re2 = std::views::empty<int>;
    static_assert(std::is_same_v<decltype(re1), std::ranges::empty_view<int>>);
    static_assert(std::is_same_v<decltype(re1), decltype(re2)>);
    EXPECT_EQ(nullptr, re1.begin());
    EXPECT_EQ(nullptr, re1.end());
    EXPECT_EQ(nullptr, re1.data());
    EXPECT_EQ(0, re1.size());
    EXPECT_EQ(true, re1.empty());

    auto rs1 = std::ranges::single_view<int>{1};
    auto rs2 = std::views::single(1);
    static_assert(std::is_same_v<decltype(rs1), std::ranges::single_view<int>>);
    static_assert(std::is_same_v<decltype(rs1), decltype(rs2)>);

    static_assert(std::is_same_v<int*, decltype(rs1.begin())>);
    static_assert(std::is_same_v<int*, decltype(rs1.end())>);
    static_assert(std::is_same_v<int*, decltype(rs1.data())>);
    EXPECT_EQ(1, *rs1.begin());
    EXPECT_EQ(1, rs1.size());
    EXPECT_EQ(false, rs1.empty());

    auto ri1 = std::ranges::iota_view<int>{1};
    auto ri2 = std::views::iota(1);
    auto ri3 = std::views::iota(1, 10);    // NOLINT
    auto ri4 = std::views::iota('a', 'z'); // NOLINT
    static_assert(std::is_same_v<decltype(ri1), std::ranges::iota_view<int>>);
    static_assert(std::is_same_v<decltype(ri1), decltype(ri2)>);
    static_assert(std::is_same_v<decltype(ri3), std::ranges::iota_view<int, int>>);
    static_assert(std::is_same_v<decltype(ri4), std::ranges::iota_view<char, char>>);

    EXPECT_EQ(1, *ri3.begin());
    EXPECT_EQ(2, *++ri3.begin());
    EXPECT_EQ(9, *--ri3.end());

    EXPECT_EQ(25, ri4.size());

    auto rr1 = std::ranges::repeat_view<int>{1};
    auto rr2 = std::views::repeat(1);
    auto rr3 = std::views::repeat(1, 10);    // NOLINT
    auto rr4 = std::views::repeat('a', 'z'); // NOLINT
    static_assert(std::is_same_v<decltype(rr1), std::ranges::repeat_view<int>>);
    static_assert(std::is_same_v<decltype(rr1), decltype(rr2)>);
    static_assert(std::is_same_v<decltype(rr3), std::ranges::repeat_view<int, int>>);
    static_assert(std::is_same_v<decltype(rr4), std::ranges::repeat_view<char, char>>);

    EXPECT_EQ(1, *rr3.begin());
    EXPECT_EQ(1, *++rr3.begin());
    EXPECT_EQ(10, rr3.size());

    EXPECT_EQ('a', *rr4.begin());
    EXPECT_EQ('a', *++rr4.begin());
    EXPECT_EQ('a', *--rr4.end());
    EXPECT_EQ('z', rr4.size());

    auto ss1 = std::stringstream{"1 2 3 4 5"};
    auto ris1 = std::ranges::istream_view<std::string>{ss1};
    static_assert(std::is_same_v<decltype(ris1), std::ranges::basic_istream_view<std::string, char>>);

    EXPECT_EQ("1", *ris1.begin());
    EXPECT_EQ("2", *ris1.begin());
}

TEST(
    ranges, Adaptors_All
)
{
    const std::vector<int> vec1{1, 2, 3, 4, 5}; // NOLINT
    std::vector<int>       vec2{1, 2, 3, 4, 5}; // NOLINT

    auto a1 = std::views::all(vec1);            // NOLINT
    auto a2 = std::views::all(std::move(vec2)); // NOLINT

    static_assert(std::is_same_v<decltype(vec1), const std::vector<int>>);
    static_assert(std::is_same_v<decltype(a1), std::ranges::ref_view<decltype(vec1)>>);

    static_assert(std::is_same_v<decltype(vec2), std::vector<int>>);
    static_assert(std::is_same_v<decltype(a2), std::ranges::owning_view<decltype(vec2)>>);
}

TEST(
    ranges, Adaptors_AsRvalue
)
{
    const std::vector<int> vec1{1, 2, 3, 4, 5};  // NOLINT
    std::vector<int>       vec2{1, 2, 3, 4, 5};  // NOLINT

    auto a1 = std::views::all(vec1);             // NOLINT
    auto a2 = std::views::all(vec2);             // NOLINT
    auto a2x = std::views::all(std::move(vec2)); // NOLINT
    static_assert(std::is_same_v<decltype(a1), std::ranges::ref_view<decltype(vec1)>>);
    static_assert(std::is_same_v<decltype(a2), std::ranges::ref_view<decltype(vec2)>>);
    static_assert(std::is_same_v<decltype(a2x), std::ranges::owning_view<decltype(vec2)>>);

    auto v1 = vec1 | std::views::as_rvalue;
    auto v2 = vec2 | std::views::as_rvalue;
    auto v2x = std::move(vec2) | std::views::as_rvalue;
    static_assert(std::is_same_v<decltype(v1), std::ranges::as_rvalue_view<decltype(a1)>>);
    static_assert(std::is_same_v<decltype(v2), std::ranges::as_rvalue_view<decltype(a2)>>);
    static_assert(std::is_same_v<decltype(v2x), std::ranges::as_rvalue_view<decltype(a2x)>>);

    static_assert(std::is_same_v<const int&&, decltype(*v1.begin())>);
    static_assert(std::is_same_v<int&&, decltype(*v2.begin())>);
    static_assert(std::is_same_v<int&&, decltype(*v2x.begin())>);
}

TEST(
    ranges, Adaptors_Filter
)
{
    const std::vector<int> vec1{1, 2, 3, 4, 5}; // NOLINT
    std::vector<int>       vec2{1, 2, 3, 4, 5}; // NOLINT

    // filter
    // Predicate の引数は ranges::iterator_t<V>
    // => vec1 は const int&
    // => vec2 は int&
    auto v1 = vec1 | std::views::filter([](const int& i) { return i % 2 == 0; });
    auto v2 = vec2 | std::views::filter([](int& i) { return i % 2 == 0; });
    auto v2x = vec2 | std::views::as_rvalue | std::views::filter([](int i) { return i % 2 == 0; });

    static_assert(std::is_same_v<const int&, decltype(*v1.begin())>);
    static_assert(std::is_same_v<int&, decltype(*v2.begin())>);
    static_assert(std::is_same_v<int&&, decltype(*v2x.begin())>);

    auto it = v1.begin();
    EXPECT_EQ(2, *it++);
    EXPECT_EQ(4, *it++);
    EXPECT_EQ(v1.end(), it);
}

TEST(
    ranges, Adaptors_Transform
)
{
    const std::vector<int> vec1{1, 2, 3, 4, 5}; // NOLINT
    std::vector<int>       vec2{1, 2, 3, 4, 5}; // NOLINT

    // transform
    // Transform の引数は ranges::range_reference_t<V>
    // => vec1 は const int&
    // => vec2 は int&
    auto r1 = vec1 | std::views::transform([](const int& i) { return i * 2; });                     // NOLINT
    auto r1x = vec1 | std::views::transform([](const int& i) -> int&& { return i * 2; });           // NOLINT
    auto r1y = vec1 | std::views::transform([](const int& i) -> const int& { return i * 2; });      // NOLINT
    auto r2 = vec2 | std::views::transform([](const int& i) { return i * 2; });                     // NOLINT
    auto r2x = vec2 | std::views::as_rvalue | std::views::transform([](int&& i) { return i * 2; }); // NOLINT

    static_assert(std::is_same_v<int, decltype(*r1.begin())>);
    static_assert(std::is_same_v<int&&, decltype(*r1x.begin())>);
    static_assert(std::is_same_v<const int&, decltype(*r1y.begin())>);
    static_assert(std::is_same_v<int, decltype(*r2.begin())>);
    static_assert(std::is_same_v<int, decltype(*r2x.begin())>);

    EXPECT_EQ(5, r1.size());
    EXPECT_EQ(2, r1[0]);
    EXPECT_EQ(4, r1[1]);
    EXPECT_EQ(6, r1[2]);
    EXPECT_EQ(8, r1[3]);
    EXPECT_EQ(10, r1[4]);
}

TEST(
    ranges, Adaptors_Take
)
{
    const std::vector<int> vec1{1, 2, 3, 4, 5}; // NOLINT
    std::vector<int>       vec2{1, 2, 3, 4, 5}; // NOLINT

    // take
    auto r1 = vec1 | std::views::take(2);                                                              // NOLINT
    auto r1x = vec1 | std::views::transform([](const int& i) { return i * 2; }) | std::views::take(2); // NOLINT
    auto r1y = vec1 | std::views::take(100000);                                                        // NOLINT
    auto r2 = vec2 | std::views::take(2);                                                              // NOLINT

    static_assert(std::is_same_v<const int&, decltype(*r1.begin())>);
    static_assert(std::is_same_v<int, decltype(*r1x.begin())>);
    static_assert(std::is_same_v<int&, decltype(*r2.begin())>);
    EXPECT_EQ(2, r1.size());
    EXPECT_EQ(1, r1[0]);
    EXPECT_EQ(2, r1[1]);
    EXPECT_EQ(5, r1y.size());

    // take_while
    auto r3 = vec1 | std::views::take_while([](const int& i) { return i < 4; }); // NOLINT
    auto r4 = vec2 | std::views::take_while([](const int& i) { return i < 4; }); // NOLINT
    static_assert(std::is_same_v<const int&, decltype(*r3.begin())>);
    static_assert(std::is_same_v<int&, decltype(*r4.begin())>);

    EXPECT_EQ(1, r3[0]);
    EXPECT_EQ(2, r3[1]);
    EXPECT_EQ(3, r3[2]);
    EXPECT_EQ(3, std::ranges::distance(r3));
}

TEST(
    ranges, Adaptors_Drop
)
{
    const std::vector<int> vec1{1, 2, 3, 4, 5}; // NOLINT
    std::vector<int>       vec2{1, 2, 3, 4, 5}; // NOLINT

    auto r1 = vec1 | std::views::drop(2);
    auto r2 = vec2 | std::views::drop(2);
    auto r2x = vec2 | std::views::as_rvalue | std::views::drop(2);

    static_assert(std::is_same_v<const int&, decltype(*r1.begin())>);
    static_assert(std::is_same_v<int&, decltype(*r2.begin())>);
    static_assert(std::is_same_v<int&&, decltype(*r2x.begin())>);

    EXPECT_EQ(3, r1[0]);
    EXPECT_EQ(4, r1[1]);
    EXPECT_EQ(5, r1[2]);
    EXPECT_EQ(3, r1.size());

    // dtop_while
    auto r8 = vec1 | std::views::drop_while([](const int& i) { return i <= 3; }); // NOLINT
    EXPECT_EQ(4, r8[0]);
    EXPECT_EQ(5, r8[1]);
    EXPECT_EQ(2, std::ranges::distance(r8.begin(), r8.end()));

    // ソート必要
    auto v8x = std::vector<int>{1, 2, 5, 4, 3, 8, 1, -1, 999};                    // NOLINT
    auto r8x = v8x | std::views::drop_while([](const int& i) { return i <= 3; }); // NOLINT
    EXPECT_EQ(5, r8x[0]);
    EXPECT_EQ(4, r8x[1]);
    EXPECT_EQ(7, std::ranges::distance(r8x.begin(), r8x.end()));

    std::ranges::sort(v8x, std::ranges::less());                                   // NOLINT
    auto r8x2 = v8x | std::views::drop_while([](const int& i) { return i <= 3; }); // NOLINT
    EXPECT_EQ(4, r8x2[0]);
    EXPECT_EQ(5, r8x2[1]);
    EXPECT_EQ(4, std::ranges::distance(r8x2.begin(), r8x2.end()));
}

TEST(
    ranges, Adaptors_Join
)
{
    const auto vec1 = std::vector<std::vector<int>>{{1, 2}, {3, 4}, {5, 6}, {7}, {8, 9, 10}};
    const auto vec2 = std::vector<std::vector<std::vector<int>>>{{{1}, {2}}, {{3}}};

    auto r1 = vec1 | std::views::join; // NOLINT
    auto it1 = r1.begin();             // NOLINT
    static_assert(std::is_same_v<const int&, decltype(*it1)>);
    EXPECT_EQ(1, *it1++);
    EXPECT_EQ(2, *it1++);
    EXPECT_EQ(3, *it1++);
    EXPECT_EQ(4, *it1++);
    EXPECT_EQ(5, *it1++);
    EXPECT_EQ(6, *it1++);
    EXPECT_EQ(7, *it1++);
    EXPECT_EQ(8, *it1++);
    EXPECT_EQ(9, *it1++);
    EXPECT_EQ(10, *it1++);
    EXPECT_EQ(r1.end(), it1);

    auto r2 = vec2 | std::views::join; // NOLINT
    auto it2 = r2.begin();             // NOLINT
    static_assert(std::is_same_v<const std::vector<int>&, decltype(*it2)>);

    //
    //*ranges::iterator_t<ranges::range_reference_t<V>>
    // 1. ranges::range_reference_t<V> = std::string&
    // 2. ranges::iterator_t<std::string&> = char&
    auto r3 = std::vector<std::string>{"std", "::", "ranges", "::views::join"} | std::views::join; // NOLINT
    auto it3 = r3.begin();                                                                         // NOLINT
    static_assert(std::is_same_v<char&, decltype(*it3)>);
    EXPECT_EQ("std::ranges::views::join", std::accumulate(r3.begin(), r3.end(), std::string()));   // NOLINT
    //
    auto r4 =
        std::vector<std::vector<int>>{{1, 2}, {3, 4}, {5, 6}, {7}, {8, 9, 10}} | std::views::join_with(0); // NOLINT
    auto r4g = std::vector<int>{1, 2, 0, 3, 4, 0, 5, 6, 0, 7, 0, 8, 9, 10};                                // NOLINT

    auto it4 = r4.begin();                                                                                 // NOLINT
    static_assert(std::is_same_v<int&, decltype(*it4)>);
    EXPECT_EQ(1, *it4++);
    EXPECT_EQ(2, *it4++);
    EXPECT_EQ(0, *it4++);
    EXPECT_EQ(3, *it4++);
    EXPECT_EQ(4, *it4++);
    EXPECT_EQ(0, *it4++);
    EXPECT_EQ(5, *it4++);
    EXPECT_EQ(6, *it4++);
    EXPECT_EQ(0, *it4++);
    EXPECT_EQ(7, *it4++);
    EXPECT_EQ(0, *it4++);
    EXPECT_EQ(8, *it4++);
    EXPECT_EQ(9, *it4++);
    EXPECT_EQ(10, *it4++);
    EXPECT_EQ(r4.end(), it4);

    auto r5 = std::vector<std::vector<int>>{{1, 2}, {3}, {5, 6, 7}} | // NOLINT
              std::views::join_with(std::vector<int>{0, -1});         // NOLINT
    auto it5 = r5.begin();                                            // NOLINT
    static_assert(std::is_same_v<int&, decltype(*it5)>);
    EXPECT_EQ(1, *it5++);
    EXPECT_EQ(2, *it5++);
    EXPECT_EQ(0, *it5++);
    EXPECT_EQ(-1, *it5++);
    EXPECT_EQ(3, *it5++);
    EXPECT_EQ(0, *it5++);
    EXPECT_EQ(-1, *it5++);
    EXPECT_EQ(5, *it5++);
    EXPECT_EQ(6, *it5++);
    EXPECT_EQ(7, *it5++);
    EXPECT_EQ(r5.end(), it5);

    auto r6 =
        std::vector<std::string>{"std", "ranges", "views", "join"} | std::views::join_with(std::string{"::"}); // NOLINT
    auto it6 = r6.begin();                                                                                     // NOLINT
    static_assert(std::is_same_v<char&, decltype(*it6)>);
    EXPECT_EQ("std::ranges::views::join", std::accumulate(r6.begin(), r6.end(), std::string()));

    auto r7 = std::vector<std::vector<std::string>>{{"std", "ranges"}, {"views"}, {"join"}} |
              std::views::join_with(std::vector<std::string>{":", ":"}); // NOLINT
    auto it7 = r7.begin();                                               // NOLINT
    static_assert(std::is_same_v<std::string&, decltype(*it7)>);
    EXPECT_EQ("stdranges::views::join", std::accumulate(r7.begin(), r7.end(), std::string{}));
}

TEST(
    ranges, Adaptors_Split
)
{
    const std::string sss = "std::ranges::views::split"; // NOLINT

    auto r1 = std::views::split(sss, std::string("::")); // NOLINT
    auto it1 = r1.begin();
    auto sr1 = *it1;
    static_assert(std::is_same_v<std::string::const_iterator, std::ranges::iterator_t<decltype(sss)>>);
    static_assert(std::is_same_v<std::ranges::subrange<std::ranges::iterator_t<decltype(sss)>>, decltype(*it1)>);
    static_assert(std::is_same_v<std::string::const_iterator, decltype(sr1.begin())>);

    EXPECT_EQ("std", std::string(sr1.begin(), sr1.end()));
    it1++;
    sr1 = *it1;
    EXPECT_EQ("ranges", std::string(sr1.begin(), sr1.end()));
    it1++;
    sr1 = *it1;
    EXPECT_EQ("views", std::string(sr1.begin(), sr1.end()));
    it1++;
    sr1 = *it1;
    EXPECT_EQ("split", std::string(sr1.begin(), sr1.end()));
    it1++;
    EXPECT_EQ(r1.end(), it1);
}

TEST(
    ranges, Adaptors_LazySplit
)
{
    const std::string sss = "std::ranges::views::split";     // NOLINT

    auto r = std::views::lazy_split(sss, std::string("::")); // NOLINT
    auto it_o = r.begin();                                   // outer_iterator
    auto it_ov = *it_o;                                      // outer_iterator::value_type
    auto it_i = it_ov.begin();                               // inner_iterator (subrange)

    static_assert(std::is_same_v<std::string::const_iterator, std::ranges::iterator_t<decltype(sss)>>);
    static_assert(std::is_same_v<const char&, decltype(*it_i)>);

    EXPECT_EQ('s', *it_i++);
    EXPECT_EQ('t', *it_i++);
    EXPECT_EQ('d', *it_i++);
    EXPECT_EQ(it_ov.end(), it_i);
    it_o++;
    it_ov = *it_o;
    it_i = it_ov.begin();
    EXPECT_EQ('r', *it_i++);
    EXPECT_EQ('a', *it_i++);
    EXPECT_EQ('n', *it_i++);
    EXPECT_EQ('g', *it_i++);
    EXPECT_EQ('e', *it_i++);
    EXPECT_EQ('s', *it_i++);
    EXPECT_EQ(it_ov.end(), it_i);
    it_o++;
    it_ov = *it_o;
    it_i = it_ov.begin();
    EXPECT_EQ('v', *it_i++);
    EXPECT_EQ('i', *it_i++);
    EXPECT_EQ('e', *it_i++);
    EXPECT_EQ('w', *it_i++);
    EXPECT_EQ('s', *it_i++);
    EXPECT_EQ(it_ov.end(), it_i);
    it_o++;
    it_ov = *it_o;
    it_i = it_ov.begin();
    EXPECT_EQ('s', *it_i++);
    EXPECT_EQ('p', *it_i++);
    EXPECT_EQ('l', *it_i++);
    EXPECT_EQ('i', *it_i++);
    EXPECT_EQ('t', *it_i++);
    EXPECT_EQ(it_ov.end(), it_i);
    it_o++;
    EXPECT_EQ(r.end(), it_o);
}

TEST(
    ranges, Adaptors_Common
)
{
    std::vector<int> v1{1, 2, 3, 4, 5};                                                           // NOLINT
    auto             i1 = std::counted_iterator{v1.begin(), std::ranges::ssize(v1)};              // NOLINT
    auto             sr1 = std::ranges::subrange(i1, std::default_sentinel);                      // NOLINT
    auto             sr2 = std::ranges::subrange(i1, std::default_sentinel) | std::views::common; // NOLINT

    // accumulate は同じ型の iterator/sentinel を要求するため ill-formed
    // auto x = std::accumulate(sr1.begin(), sr1.end(), 0);                                          // NOLINT
    auto y = std::accumulate(sr2.begin(), sr2.end(), 0); // NOLINT

    // ill-formed
    // std::sentinel_for<decltype(v1.begin()> std::default_sentinel を満たさない
    //   __WeaklyEqualityComparableWith<decltype(v1.begin()), std::default_sentinel>
    // std::counted_iterator は operator を持つため比較可能
    // auto sr1x = std::ranges::subrange(v1.begin(), std::default_sentinel);                     // NOLINT
}

TEST(
    ranges, Adaptors_Reverse
)
{
    std::vector<int> v1{1, 2, 3, 4, 5};                 // NOLINT
    auto             r1 = v1 | std::views::reverse;     // NOLINT

    auto it = r1.begin();                               // NOLINT
    static_assert(std::is_same_v<decltype(*it), int&>); // NOLINT
    EXPECT_EQ(5, *it++);
    EXPECT_EQ(4, *it++);
    EXPECT_EQ(3, *it++);
    EXPECT_EQ(2, *it++);
    EXPECT_EQ(1, *it++);
    EXPECT_EQ(r1.end(), it);
}

TEST(
    ranges, Adaptors_Const
)
{
    std::vector<int> v1{1, 2, 3, 4, 5};                       // NOLINT
    auto             r1 = v1 | std::views::as_const;          // NOLINT

    auto it = r1.begin();                                     // NOLINT
    static_assert(std::is_same_v<decltype(*it), const int&>); // NOLINT
    EXPECT_EQ(1, *it++);
    EXPECT_EQ(2, *it++);
    EXPECT_EQ(3, *it++);
    EXPECT_EQ(4, *it++);
    EXPECT_EQ(5, *it++);
    EXPECT_EQ(r1.end(), it);
}

TEST(
    ranges, Adaptors_Elements
)
{
    const std::vector<std::pair<int, int>> v1{{1, 2}, {3, 4}, {5, 6}};                                 // NOLINT
    std::vector<std::pair<int, int>>       v2{{1, 2}, {3, 4}, {5, 6}};                                 // NOLINT
    auto                                   r1 = v1 | std::views::elements<0>;                          // NOLINT
    auto                                   r1x = std::move(v2) | std::views::elements<0>;              // NOLINT
    auto                                   r1y = v1 | std::views::as_rvalue | std::views::elements<0>; // NOLINT

    static_assert(std::is_same_v<const int&, decltype(*r1.begin())>);                                  // NOLINT
    static_assert(std::is_same_v<int&, decltype(*r1x.begin())>);                                       // NOLINT
    static_assert(std::is_same_v<const int&&, decltype(*r1y.begin())>);                                // NOLINT

    auto it = r1.begin();                                                                              // NOLINT
    static_assert(std::is_same_v<decltype(*it), const int&>);                                          // NOLINT
    EXPECT_EQ(1, *it++);
    EXPECT_EQ(3, *it++);
    EXPECT_EQ(5, *it++);
    EXPECT_EQ(r1.end(), it);

    auto r2 = v1 | std::views::elements<1>; // NOLINT
    auto it2 = r2.begin();                  // NOLINT
    EXPECT_EQ(2, *it2++);
    EXPECT_EQ(4, *it2++);
    EXPECT_EQ(6, *it2++);
    EXPECT_EQ(r2.end(), it2);
}

TEST(
    ranges, Adaptors_Keys
)
{
    const std::vector<std::pair<int, std::string>> v1{{1, "A"}, {3, "B"}, {5, "C"}};                    // NOLINT
    std::vector<std::pair<int, int>>               v2{{1, 2}, {3, 4}, {5, 6}};                          // NOLINT
    auto                                           r1 = v1 | std::views::keys;                          // NOLINT
    auto                                           r1x = std::move(v2) | std::views::keys;              // NOLINT
    auto                                           r1y = v1 | std::views::as_rvalue | std::views::keys; // NOLINT

    static_assert(std::is_same_v<const int&, decltype(*r1.begin())>);                                   // NOLINT
    static_assert(std::is_same_v<int&, decltype(*r1x.begin())>);                                        // NOLINT
    static_assert(std::is_same_v<const int&&, decltype(*r1y.begin())>);                                 // NOLINT

    auto it = r1.begin();                                                                               // NOLINT
    EXPECT_EQ(1, *it++);
    EXPECT_EQ(3, *it++);
    EXPECT_EQ(5, *it++);
    EXPECT_EQ(r1.end(), it);

    const std::unordered_map<std::string, int>                                     // NOLINT
               m1{{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}}; // NOLINT
    const auto r2 = m1 | std::views::keys;                                         // NOLINT
    auto       it2 = r2.begin();                                                   // NOLINT

    auto expected = std::ranges::to<std::unordered_set<std::string>>(m1 | std::views::keys);

    EXPECT_EQ(1, expected.erase(*it2++));
    EXPECT_EQ(1, expected.erase(*it2++));
    EXPECT_EQ(1, expected.erase(*it2++));
    EXPECT_EQ(1, expected.erase(*it2++));
    EXPECT_EQ(1, expected.erase(*it2++));
    EXPECT_EQ(r2.end(), it2);
    EXPECT_EQ(0, expected.size());
}

TEST(
    ranges, Adaptors_Values
)
{
    const std::vector<std::pair<int, std::string>> v1{{1, "A"}, {3, "B"}, {5, "C"}};                      // NOLINT
    std::vector<std::pair<int, std::string>>       v2{{1, "A"}, {3, "B"}, {5, "C"}};                      // NOLINT
    auto                                           r1 = v1 | std::views::values;                          // NOLINT
    auto                                           r1x = std::move(v2) | std::views::values;              // NOLINT
    auto                                           r1y = v1 | std::views::as_rvalue | std::views::values; // NOLINT

    static_assert(std::is_same_v<const std::string&, decltype(*r1.begin())>);                             // NOLINT
    static_assert(std::is_same_v<std::string&, decltype(*r1x.begin())>);                                  // NOLINT
    static_assert(std::is_same_v<const std::string&&, decltype(*r1y.begin())>);                           // NOLINT

    auto it = r1.begin();                                                                                 // NOLINT
    EXPECT_EQ("A", *it++);
    EXPECT_EQ("B", *it++);
    EXPECT_EQ("C", *it++);
    EXPECT_EQ(r1.end(), it);

    const std::unordered_map<std::string, int>                                     // NOLINT
               m1{{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}}; // NOLINT
    const auto r2 = m1 | std::views::values;                                       // NOLINT
    auto       it2 = r2.begin();                                                   // NOLINT

    auto expected = std::ranges::to<std::unordered_set<int>>(m1 | std::views::values);

    EXPECT_EQ(1, expected.erase(*it2++));
    EXPECT_EQ(1, expected.erase(*it2++));
    EXPECT_EQ(1, expected.erase(*it2++));
    EXPECT_EQ(1, expected.erase(*it2++));
    EXPECT_EQ(1, expected.erase(*it2++));
    EXPECT_EQ(r2.end(), it2);
    EXPECT_EQ(0, expected.size());
}

TEST(
    ranges, Adaptors_Enumerate
)
{
    {
        const std::vector<int> v1{};                                                          // NOLINT
        std::vector<int>       v2{};                                                          // NOLINT
        auto                   r1 = v1 | std::views::enumerate;                               // NOLINT
        auto                   r1x = std::move(v2) | std::views::enumerate;                   // NOLINT
        auto                   r1y = v1 | std::views::as_rvalue | std::views::enumerate;      // NOLINT

        static_assert(std::is_same_v<long, typename decltype(v1)::difference_type>);          // NOLINT

        static_assert(std::is_same_v<std::tuple<long, const int&>, decltype(*r1.begin())>);   // NOLINT
        static_assert(std::is_same_v<std::tuple<long, int&>, decltype(*r1x.begin())>);        // NOLINT
        static_assert(std::is_same_v<std::tuple<long, const int&&>, decltype(*r1y.begin())>); // NOLINT
    }

    auto v = std::vector<std::string>{"A", "B", "C", "D", "E"};                               // NOLINT
    auto r1 = v | std::views::enumerate;                                                      // NOLINT

    auto it = r1.begin();                                                                     // NOLINT

    const auto& [index, value] = *it++;
    EXPECT_EQ(0, index);
    EXPECT_EQ("A", value);
    const auto& [index2, value2] = *it++;
    EXPECT_EQ(1, index2);
    EXPECT_EQ("B", value2);
    const auto& [index3, value3] = *it++;
    EXPECT_EQ(2, index3);
    EXPECT_EQ("C", value3);
    const auto& [index4, value4] = *it++;
    EXPECT_EQ(3, index4);
    EXPECT_EQ("D", value4);
    const auto& [index5, value5] = *it++;
    EXPECT_EQ(4, index5);
    EXPECT_EQ("E", value5);
    EXPECT_EQ(r1.end(), it);
}

TEST(
    ranges, Adaptors_Zip
)
{
    {
        const std::vector<int>   v1{};                                                              // NOLINT
        std::vector<int>         v2{};                                                              // NOLINT
        std::vector<std::string> vs{};                                                              // NOLINT
        auto                     r1 = std::views::zip(v1, vs);
        auto                     r1x = std::views::zip(v2, vs);                                     // NOLINT
        auto                     r1y = std::views::zip(v2 | std::views::as_rvalue, vs);             // NOLINT

        static_assert(std::is_same_v<std::tuple<const int&, std::string&>, decltype(*r1.begin())>); // NOLINT
        static_assert(std::is_same_v<std::tuple<int&, std::string&>, decltype(*r1x.begin())>);      // NOLINT
        static_assert(std::is_same_v<std::tuple<int&&, std::string&>, decltype(*r1y.begin())>);     // NOLINT
    }

    const auto v = std::vector<std::string>{"A", "B", "C", "D", "E"};                               // NOLINT
    const auto v2 = std::vector<int>{1, 2, 3};                                                      // NOLINT

    auto r1 = std::views::zip(v, v2);                                                               // NOLINT
    auto it = r1.begin();                                                                           // NOLINT
    static_assert(std::is_same_v<decltype(*it), std::tuple<const std::string&, const int&>>);
    EXPECT_EQ("A", std::get<0>(*it));
    EXPECT_EQ(1, std::get<1>(*it));
    it++;
    EXPECT_EQ("B", std::get<0>(*it));
    EXPECT_EQ(2, std::get<1>(*it));
    it++;
    EXPECT_EQ("C", std::get<0>(*it));
    EXPECT_EQ(3, std::get<1>(*it));
    it++;
    EXPECT_EQ(r1.end(), it);

    auto v3 = std::vector<std::string>{"A", "B", "C", "D", "E"};       // NOLINT
    auto v4 = std::vector<int>{1, 2, 3};                               // NOLINT
    auto r34 = std::views::zip(v3, v4);                                // NOLINT
    auto it34 = r34.begin();                                           // NOLINT
    static_assert(std::is_same_v<decltype(*it34), std::tuple<std::string&, int&>>);

    const auto v5 = std::vector<std::string>{"A", "B", "C", "D", "E"}; // NOLINT
    auto       v6 = std::vector<int>{1, 2, 3};                         // NOLINT
    auto       r56 = std::views::zip(v5, v6);                          // NOLINT
    auto       it56 = r56.begin();                                     // NOLINT
    static_assert(std::is_same_v<decltype(*it56), std::tuple<const std::string&, int&>>);
}

TEST(
    ranges, Adaptors_ZipTransform
)
{
    {
        auto fn = [](const std::string& a, auto&& b) -> std::string { return a + "::" + std::to_string(b); }; // NOLINT
        auto fn2 = [](const std::string& a, auto&& b) -> const std::string&
        { return a + "::" + std::to_string(b); };                                                             // NOLINT

        const std::vector<int>   v1{};                                                                        // NOLINT
        std::vector<int>         v2{};                                                                        // NOLINT
        std::vector<std::string> vs{};                                                                        // NOLINT
        auto                     r1 = std::views::zip_transform(fn, vs, v1);
        auto                     r1x = std::views::zip_transform(fn, vs, v2);                                 // NOLINT
        auto                     r1y = std::views::zip_transform(fn, vs, v2 | std::views::as_rvalue);         // NOLINT
        auto                     r2 = std::views::zip_transform(fn2, vs, v1);

        static_assert(std::is_same_v<std::string, decltype(*r1.begin())>);                                    // NOLINT
        static_assert(std::is_same_v<std::string, decltype(*r1x.begin())>);                                   // NOLINT
        static_assert(std::is_same_v<std::string, decltype(*r1y.begin())>);                                   // NOLINT
        static_assert(std::is_same_v<const std::string&, decltype(*r2.begin())>);                             // NOLINT
    }

    const auto v = std::vector<std::string>{"A", "B", "C", "D", "E"};                                         // NOLINT
    const auto v2 = std::vector<int>{1, 2, 3};                                                                // NOLINT

    auto r1 = std::views::zip_transform(                                                                      // NOLINT
        [](const std::string& a, const int& b) -> std::string { return a + "::" + std::to_string(b); },       // NOLINT
        v,
        v2
    );                                                                                                        // NOLINT
    auto it = r1.cbegin();                                                                                    // NOLINT
    static_assert(std::is_same_v<decltype(*it), const std::string>);
    EXPECT_EQ("A::1", *it++);
    EXPECT_EQ("B::2", *it++);
    EXPECT_EQ("C::3", *it++);
    EXPECT_EQ(r1.end(), it);
}

TEST(
    ranges, Adaptors_Adjacent
)
{
    {
        const std::vector<int> v1{};                                                                 // NOLINT
        std::vector<int>       v2{};                                                                 // NOLINT
        auto                   r1 = v1 | std::views::adjacent<2>;                                    // NOLINT
        auto                   r1x = std::move(v2) | std::views::adjacent<2>;                        // NOLINT
        auto                   r1y = v1 | std::views::as_rvalue | std::views::adjacent<2>;           // NOLINT

        static_assert(std::is_same_v<std::tuple<const int&, const int&>, decltype(*r1.begin())>);    // NOLINT
        static_assert(std::is_same_v<std::tuple<int&, int&>, decltype(*r1x.begin())>);               // NOLINT
        static_assert(std::is_same_v<std::tuple<const int&&, const int&&>, decltype(*r1y.begin())>); // NOLINT
    }

    const auto r = std::views::iota(1);                                                              // NOLINT
    auto       a = r | std::views::take(10) | std::views::adjacent<3>;                               // NOLINT
    auto       it = a.begin();                                                                       // NOLINT
    static_assert(std::is_same_v<decltype(*it), std::tuple<int, int, int>>);

    EXPECT_EQ(std::make_tuple(1, 2, 3), *it++);
    EXPECT_EQ(std::make_tuple(2, 3, 4), *it++);
    EXPECT_EQ(std::make_tuple(3, 4, 5), *it++);
    EXPECT_EQ(std::make_tuple(4, 5, 6), *it++);
    EXPECT_EQ(std::make_tuple(5, 6, 7), *it++);
    EXPECT_EQ(std::make_tuple(6, 7, 8), *it++);
    EXPECT_EQ(std::make_tuple(7, 8, 9), *it++);
    EXPECT_EQ(std::make_tuple(8, 9, 10), *it++);
    EXPECT_EQ(a.end(), it);

    auto a2 = r | std::views::take(1) | std::views::adjacent<100>; // NOLINT
    auto it2 = a2.begin();                                         // NOLINT
    EXPECT_EQ(a2.end(), it2);

    auto a3 = r | std::views::take(4) | std::views::pairwise;      // NOLINT
    auto it3 = a3.begin();                                         // NOLINT
    EXPECT_EQ(std::make_tuple(1, 2), *it3++);
    EXPECT_EQ(std::make_tuple(2, 3), *it3++);
    EXPECT_EQ(std::make_tuple(3, 4), *it3++);
    EXPECT_EQ(a3.end(), it3);
}

TEST(
    ranges, Adaptors_AdjacentTransform
)
{
    {
        auto fn = [](auto&& a, auto&& b) -> std::string
        { return std::to_string(a) + "::" + std::to_string(b); };                                        // NOLINT
        auto fn2 = [](auto&& a, auto&& b) -> const std::string&
        { return std::to_string(a) + "::" + std::to_string(b); };                                        // NOLINT

        const std::vector<int> v1{};                                                                     // NOLINT
        std::vector<int>       v2{};                                                                     // NOLINT
        auto                   r1 = v1 | std::views::adjacent_transform<2>(fn);
        auto                   r1x = v1 | std::views::as_rvalue | std::views::adjacent_transform<2>(fn); // NOLINT
        auto                   r1y = v2 | std::views::adjacent_transform<2>(fn);                         // NOLINT
        auto                   r2 = v2 | std::views::adjacent_transform<2>(fn2);

        static_assert(std::is_same_v<std::string, decltype(*r1.begin())>);                               // NOLINT
        static_assert(std::is_same_v<std::string, decltype(*r1x.begin())>);                              // NOLINT
        static_assert(std::is_same_v<std::string, decltype(*r1y.begin())>);                              // NOLINT
        static_assert(std::is_same_v<const std::string&, decltype(*r2.begin())>);                        // NOLINT
    }

    const auto r = std::views::iota(1);                                                                  // NOLINT
    auto       a = r | std::views::take(5) |                                                             // NOLINT
             std::views::adjacent_transform<3>([](const auto... v) { return (v + ...); });               // NOLINT
    auto it = a.begin();                                                                                 // NOLINT
    static_assert(std::is_same_v<decltype(*it), int>);

    EXPECT_EQ(6, *it++);
    EXPECT_EQ(9, *it++);
    EXPECT_EQ(12, *it++);
    EXPECT_EQ(a.end(), it);

    auto a2 = r | std::views::take(5) |                                                   // NOLINT
              std::views::pairwise_transform([](const auto&... v) { return (v + ...); }); // NOLINT
    auto it2 = a2.begin();                                                                // NOLINT
    static_assert(std::is_same_v<decltype(*it2), int>);

    EXPECT_EQ(3, *it2++);
    EXPECT_EQ(5, *it2++);
    EXPECT_EQ(7, *it2++);
    EXPECT_EQ(9, *it2++);
    EXPECT_EQ(a2.end(), it2);

    const auto v = std::vector<int>{1, 2, 3, 4, 5};                                 // NOLINT
    auto       a3 = v |                                                             // NOLINT
              std::views::pairwise_transform([](auto&... v) { return (v + ...); }); // NOLINT
    auto it3 = a3.begin();                                                          // NOLINT
    static_assert(std::is_same_v<decltype(*it3), int>);

    EXPECT_EQ(3, *it3++);
    EXPECT_EQ(5, *it3++);
    EXPECT_EQ(7, *it3++);
    EXPECT_EQ(9, *it3++);
    EXPECT_EQ(a3.end(), it3);
}

TEST(
    ranges, Adaptors_Chunk
)
{
    {
        const std::vector<int> v1{};                                                    // NOLINT
        std::vector<int>       v2{};                                                    // NOLINT
        auto                   r1 = v1 | std::views::chunk(2);
        auto                   r1x = v1 | std::views::as_rvalue | std::views::chunk(2); // NOLINT
        auto                   r2 = v2 | std::views::chunk(2);

        // r1.begin() は iterator
        // *r1.begin() は return views::take(ranges::subrange(current_, end_), n_) に等しい
        //   current = ranges::iterator_t<Base> なので current = v1::iterator
        //   take の引数が subrange の特殊化なので、ranges::subrange<ranges::iterator_t<T>> に等しい
        static_assert(std::is_same_v<
                      std::ranges::subrange<decltype(v1)::const_iterator>,
                      decltype(*r1.begin())>);                     // NOLINT
        static_assert(std::is_same_v<
                      std::ranges::subrange<std::move_iterator<decltype(v1)::const_iterator>>,
                      decltype(*r1x.begin())>);                    // NOLINT
        static_assert(std::is_same_v<std::ranges::subrange<decltype(v1)::iterator>,
                                     decltype(*r2.begin())>);      // NOLINT
    }

    const auto r = std::views::iota(1);                            // NOLINT
    auto       a = r | std::views::take(5) | std::views::chunk(2); // NOLINT
    auto       it = a.begin();                                     // NOLINT

    // it => outer_iterator
    // *it => value_type
    // (*it).begin() => inner_iterator
    auto it_inner = (*it).begin();

    EXPECT_EQ(2, std::ranges::distance(*it));
    EXPECT_EQ(1, *it_inner++);
    EXPECT_EQ(2, *it_inner++);
    it++;
    it_inner = (*it).begin();
    EXPECT_EQ(2, std::ranges::distance(*it));
    EXPECT_EQ(3, *it_inner++);
    EXPECT_EQ(4, *it_inner++);
    it++;
    it_inner = (*it).begin();
    EXPECT_EQ(1, std::ranges::distance(*it));
    EXPECT_EQ(5, *it_inner++);
    it++;
    EXPECT_EQ(a.end(), it);
}

TEST(
    ranges, Adaptors_Slide
)
{
    {
        const std::vector<int> v1{};                                                    // NOLINT
        std::vector<int>       v2{};                                                    // NOLINT
        auto                   r1 = v1 | std::views::slide(2);
        auto                   r1x = v1 | std::views::as_rvalue | std::views::slide(2); // NOLINT
        auto                   r2 = v2 | std::views::slide(2);

        static_assert(std::is_same_v<std::span<const int>,
                                     decltype(*r1.begin())>);      // NOLINT
        static_assert(std::is_same_v<
                      std::ranges::subrange<std::move_iterator<decltype(v1)::const_iterator>>,
                      decltype(*r1x.begin())>);                    // NOLINT
        static_assert(std::is_same_v<std::span<int>,
                                     decltype(*r2.begin())>);      // NOLINT
    }

    const auto r = std::views::iota(1);                            // NOLINT
    auto       a = r | std::views::take(5) | std::views::slide(2); // NOLINT
    auto       it = a.begin();                                     // NOLINT

    // it => outer_iterator
    // *it => value_type
    // (*it).begin() => inner_iterator
    auto it_inner = (*it).begin();

    EXPECT_EQ(2, std::ranges::distance(*it));
    EXPECT_EQ(1, *it_inner++);
    EXPECT_EQ(2, *it_inner++);
    it++;
    it_inner = (*it).begin();
    EXPECT_EQ(2, std::ranges::distance(*it));
    EXPECT_EQ(2, *it_inner++);
    EXPECT_EQ(3, *it_inner++);
    it++;
    it_inner = (*it).begin();
    EXPECT_EQ(2, std::ranges::distance(*it));
    EXPECT_EQ(3, *it_inner++);
    EXPECT_EQ(4, *it_inner++);
    it++;
    it_inner = (*it).begin();
    EXPECT_EQ(2, std::ranges::distance(*it));
    EXPECT_EQ(4, *it_inner++);
    EXPECT_EQ(5, *it_inner++);
    it++;
    EXPECT_EQ(a.end(), it);
}

TEST(
    ranges, Adaptors_ChunkBy
)
{
    {
        const std::vector<int> v1{};                                                                         // NOLINT
        std::vector<int>       v2{};                                                                         // NOLINT
        auto                   r1 = v1 | std::views::chunk_by(std::ranges::less());                          // NOLINT
        auto                   r1x = v1 | std::views::as_rvalue | std::views::chunk_by(std::ranges::less()); // NOLINT
        auto                   r2 = v2 | std::views::chunk_by(std::ranges::less());

        static_assert(std::is_same_v<
                      std::ranges::subrange<decltype(v1)::const_iterator>,
                      decltype(*r1.begin())>);                // NOLINT
        static_assert(std::is_same_v<
                      std::ranges::subrange<std::move_iterator<decltype(v1)::const_iterator>>,
                      decltype(*r1x.begin())>);               // NOLINT
        static_assert(std::is_same_v<std::ranges::subrange<decltype(v2)::iterator>,
                                     decltype(*r2.begin())>); // NOLINT
    }

    // 隣り合う2つの要素が less を満たす限り chunk に追加する
    const auto v = std::vector<int>{1, 2, 3, 1, 2, 3, 3, 3, 1, 2, 3}; // NOLINT
    auto       r = v | std::views::chunk_by(std::ranges::less());     // NOLINT

    auto it = r.begin();                                              // NOLINT
    auto it_sr = (*it).begin();                                       // NOLINT
    static_assert(std::is_same_v<decltype(*it_sr), const int&>);

    EXPECT_EQ(1, *it_sr++);
    EXPECT_EQ(2, *it_sr++);
    EXPECT_EQ(3, *it_sr++);
    EXPECT_EQ((*it).end(), it_sr);

    it++;
    it_sr = (*it).begin(); // NOLINT
    EXPECT_EQ(1, *it_sr++);
    EXPECT_EQ(2, *it_sr++);
    EXPECT_EQ(3, *it_sr++);
    EXPECT_EQ((*it).end(), it_sr);

    it++;
    it_sr = (*it).begin(); // NOLINT
    EXPECT_EQ(3, *it_sr++);
    EXPECT_EQ((*it).end(), it_sr);

    it++;
    it_sr = (*it).begin(); // NOLINT
    EXPECT_EQ(3, *it_sr++);
    EXPECT_EQ((*it).end(), it_sr);

    it++;
    it_sr = (*it).begin(); // NOLINT
    EXPECT_EQ(1, *it_sr++);
    EXPECT_EQ(2, *it_sr++);
    EXPECT_EQ(3, *it_sr++);
    EXPECT_EQ((*it).end(), it_sr);

    it++;
    EXPECT_EQ(r.end(), it);
}

TEST(
    ranges, Adaptors_Stride
)
{
    {
        const std::vector<int> v1{};                                                     // NOLINT
        std::vector<int>       v2{};                                                     // NOLINT
        auto                   r1 = v1 | std::views::stride(2);                          // NOLINT
        auto                   r1x = v1 | std::views::as_rvalue | std::views::stride(2); // NOLINT
        auto                   r2 = v2 | std::views::stride(2);

        static_assert(std::is_same_v<const int&,
                                     decltype(*r1.begin())>);               // NOLINT
        static_assert(std::is_same_v<const int&&, decltype(*r1x.begin())>); // NOLINT
        static_assert(std::is_same_v<int&,
                                     decltype(*r2.begin())>);               // NOLINT
    }

    const auto v1 = std::views::iota(1) | std::views::take(10);             // NOLINT
    auto       r1 = v1 | std::views::stride(3);                             // NOLINT
    auto       it1 = r1.begin();                                            // NOLINT

    const auto v2 = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};        // NOLINT
    auto       r2 = v2 | std::views::stride(3);                             // NOLINT
    auto       it2 = r2.begin();                                            // NOLINT

    static_assert(std::is_same_v<decltype(*it1), int>);
    static_assert(std::is_same_v<decltype(*it2), const int&>);

    EXPECT_EQ(4, std::ranges::distance(r1));
    EXPECT_EQ(1, *it1++);
    EXPECT_EQ(4, *it1++);
    EXPECT_EQ(7, *it1++);
    EXPECT_EQ(10, *it1++);
    EXPECT_EQ(r1.end(), it1);
}

TEST(
    ranges, Adaptors_CartesianProduct
)
{
    {
        const std::vector<int>   v1{};                                                                // NOLINT
        std::vector<std::string> v2{};                                                                // NOLINT
        auto                     r1 = std::views::cartesian_product(v1, v2);                          // NOLINT
        auto                     r1x = std::views::cartesian_product(v1 | std::views::as_rvalue, v2); // NOLINT

        static_assert(std::is_same_v<std::tuple<const int&, std::string&>, decltype(*r1.begin())>);   // NOLINT
        static_assert(std::is_same_v<std::tuple<const int&&, std::string&>, decltype(*r1x.begin())>); // NOLINT
    }
    const auto v1 = std::vector<int>{1, 2, 3};                                                        // NOLINT
    const auto v2 = std::vector<std::string>{"A", "B"};                                               // NOLINT
    const auto v3 = std::vector<double>{-1.0, -2.0, -3.0};                                            // NOLINT

    const auto r12 = std::views::cartesian_product(v1, v2);                                           // NOLINT
    auto       it12 = r12.begin();                                                                    // NOLINT

    static_assert(std::is_same_v<decltype(*it12), std::tuple<const int&, const std::string&>>);
    EXPECT_EQ(6, r12.size());
    EXPECT_EQ(std::make_tuple(1, "A"), *it12++);
    EXPECT_EQ(std::make_tuple(1, "B"), *it12++);
    EXPECT_EQ(std::make_tuple(2, "A"), *it12++);
    EXPECT_EQ(std::make_tuple(2, "B"), *it12++);
    EXPECT_EQ(std::make_tuple(3, "A"), *it12++);
    EXPECT_EQ(std::make_tuple(3, "B"), *it12++);
    EXPECT_EQ(r12.end(), it12);

    const auto r123 = std::views::cartesian_product(v1, v2, v3); // NOLINT
    auto       it123 = r123.begin();                             // NOLINT

    static_assert(std::is_same_v<decltype(*it123), std::tuple<const int&, const std::string&, const double&>>);
    EXPECT_EQ(18, r123.size());
    EXPECT_EQ(std::make_tuple(1, "A", -1.0), *it123++);
    EXPECT_EQ(std::make_tuple(1, "A", -2.0), *it123++);
    EXPECT_EQ(std::make_tuple(1, "A", -3.0), *it123++);
    EXPECT_EQ(std::make_tuple(1, "B", -1.0), *it123++);
    EXPECT_EQ(std::make_tuple(1, "B", -2.0), *it123++);
    EXPECT_EQ(std::make_tuple(1, "B", -3.0), *it123++);
    EXPECT_EQ(std::make_tuple(2, "A", -1.0), *it123++);
    EXPECT_EQ(std::make_tuple(2, "A", -2.0), *it123++);
    EXPECT_EQ(std::make_tuple(2, "A", -3.0), *it123++);
    EXPECT_EQ(std::make_tuple(2, "B", -1.0), *it123++);
    EXPECT_EQ(std::make_tuple(2, "B", -2.0), *it123++);
    EXPECT_EQ(std::make_tuple(2, "B", -3.0), *it123++);
    EXPECT_EQ(std::make_tuple(3, "A", -1.0), *it123++);
    EXPECT_EQ(std::make_tuple(3, "A", -2.0), *it123++);
    EXPECT_EQ(std::make_tuple(3, "A", -3.0), *it123++);
    EXPECT_EQ(std::make_tuple(3, "B", -1.0), *it123++);
    EXPECT_EQ(std::make_tuple(3, "B", -2.0), *it123++);
    EXPECT_EQ(std::make_tuple(3, "B", -3.0), *it123++);
    EXPECT_EQ(r123.end(), it123);
}
} // namespace
