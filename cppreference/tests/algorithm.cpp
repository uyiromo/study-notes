#include "gtest/gtest.h"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <deque>
#include <execution>
#include <forward_list>
#include <initializer_list>
#include <iterator>
#include <list>
#include <random>
#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace
{
void dbl(
    auto& v
)
{
    v = v * 2; // NOLINT
}

TEST(
    algorithm, batch_foreach
)
{
    constexpr std::array<int, 6> expected = {2, 4, 6, 8, 10, 12}; // NOLINT

    std::array<int, 6> arr = {1, 2, 3, 4, 5, 6};                  // NOLINT
    std::vector<int>   vec = {1, 2, 3, 4, 5, 6};                  // NOLINT
    std::deque<int>    deq = {1, 2, 3, 4, 5, 6};                  // NOLINT
    std::list<int>     lst = {1, 2, 3, 4, 5, 6};                  // NOLINT
    // std::initializer_list<int> inl = {1, 2, 3, 4, 5, 6};              // NOLINT

    std::vector<int>                        rng = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::ranges::ref_view<std::vector<int>> view = rng | std::views::all;

    using std::begin, std::end;

    std::for_each(begin(arr), end(arr), [](auto& v) { v *= 2; }); // NOLINT
    std::for_each(begin(vec), end(vec), dbl<int>);                // NOLINT
    std::for_each(begin(deq), end(deq), dbl<int>);                // NOLINT
    std::for_each(begin(lst), end(lst), dbl<int>);                // NOLINT
    // std::for_each(begin(inl), end(inl), dbl<int>);                // NOLINT
    std::for_each(begin(view), end(view), dbl<int>);                                  // NOLINT

    EXPECT_TRUE(std::ranges::equal(arr, expected));                                   // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec, expected));                                   // NOLINT
    EXPECT_TRUE(std::ranges::equal(deq, expected));                                   // NOLINT
    EXPECT_TRUE(std::ranges::equal(lst, expected));                                   // NOLINT
    EXPECT_TRUE(std::ranges::equal(view, expected));                                  // NOLINT

    std::for_each(std::execution::par, begin(deq), end(deq), dbl<int>);               // NOLINT
    std::for_each(std::execution::parallel_policy(), begin(deq), end(deq), dbl<int>); // NOLINT
}

TEST(
    algorithm, batch_foreachN
)
{
    constexpr std::array<int, 6> expected = {2, 4, 6, 8, 5, 6}; // NOLINT

    std::array<int, 6> arr = {1, 2, 3, 4, 5, 6};                // NOLINT
    std::vector<int>   vec = {1, 2, 3, 4, 5, 6};                // NOLINT
    std::deque<int>    deq = {1, 2, 3, 4, 5, 6};                // NOLINT
    std::list<int>     lst = {1, 2, 3, 4, 5, 6};                // NOLINT
    // std::initializer_list<int> inl = {1, 2, 3, 4, 5, 6};              // NOLINT

    std::vector<int>                        rng = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::ranges::ref_view<std::vector<int>> view = rng | std::views::all;

    using std::begin, std::end;

    std::for_each_n(begin(arr), 4, [](auto& v) { v *= 2; }); // NOLINT
    std::for_each_n(begin(vec), 4, dbl<int>);                // NOLINT
    std::for_each_n(begin(deq), 4, dbl<int>);                // NOLINT
    std::for_each_n(begin(lst), 4, dbl<int>);                // NOLINT
    // std::for_each(begin(inl), end(inl), dbl<int>);                // NOLINT
    std::for_each_n(begin(view), 4, dbl<int>);                                   // NOLINT

    EXPECT_TRUE(std::ranges::equal(arr, expected));                              // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec, expected));                              // NOLINT
    EXPECT_TRUE(std::ranges::equal(deq, expected));                              // NOLINT
    EXPECT_TRUE(std::ranges::equal(lst, expected));                              // NOLINT
    EXPECT_TRUE(std::ranges::equal(view, expected));                             // NOLINT

    std::for_each_n(std::execution::par, begin(deq), 4, dbl<int>);               // NOLINT
    std::for_each_n(std::execution::parallel_policy(), begin(deq), 4, dbl<int>); // NOLINT
}

TEST(
    algorithm, Search_AllAnyNone
)
{
    std::array<int, 6>         arr = {1, 2, 3, 4, 5, 6};              // NOLINT
    std::vector<int>           vec = {1, 2, 3, 4, 5, 6};              // NOLINT
    std::deque<int>            deq = {1, 2, 3, 4, 5, 6};              // NOLINT
    std::list<int>             lst = {1, 2, 3, 4, 5, 6};              // NOLINT
    std::initializer_list<int> inl = {1, 2, 3, 4, 5, 6};              // NOLINT

    std::vector<int>                        rng = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::ranges::ref_view<std::vector<int>> view = rng | std::views::all;

    using std::begin, std::end;

    EXPECT_TRUE(std::all_of(begin(arr), end(arr), [](const auto& v) { return v > 0; }));    // NOLINT
    EXPECT_TRUE(std::all_of(begin(vec), end(vec), [](const auto& v) { return v > 0; }));    // NOLINT
    EXPECT_TRUE(std::all_of(begin(deq), end(deq), [](const auto& v) { return v > 0; }));    // NOLINT
    EXPECT_TRUE(std::all_of(begin(lst), end(lst), [](const auto& v) { return v > 0; }));    // NOLINT
    EXPECT_TRUE(std::all_of(begin(inl), end(inl), [](const auto& v) { return v > 0; }));    // NOLINT
    EXPECT_TRUE(std::all_of(begin(view), end(view), [](const auto& v) { return v > 0; }));  // NOLINT

    EXPECT_TRUE(std::any_of(begin(arr), end(arr), [](const auto& v) { return v == 3; }));   // NOLINT
    EXPECT_TRUE(std::any_of(begin(vec), end(vec), [](const auto& v) { return v == 3; }));   // NOLINT
    EXPECT_TRUE(std::any_of(begin(deq), end(deq), [](const auto& v) { return v == 3; }));   // NOLINT
    EXPECT_TRUE(std::any_of(begin(lst), end(lst), [](const auto& v) { return v == 3; }));   // NOLINT
    EXPECT_TRUE(std::any_of(begin(inl), end(inl), [](const auto& v) { return v == 3; }));   // NOLINT
    EXPECT_TRUE(std::any_of(begin(view), end(view), [](const auto& v) { return v == 3; })); // NOLINT

    EXPECT_TRUE(std::none_of(begin(arr), end(arr), [](const auto& v) { return v < 0; }));   // NOLINT
    EXPECT_TRUE(std::none_of(begin(vec), end(vec), [](const auto& v) { return v < 0; }));   // NOLINT
    EXPECT_TRUE(std::none_of(begin(deq), end(deq), [](const auto& v) { return v < 0; }));   // NOLINT
    EXPECT_TRUE(std::none_of(begin(lst), end(lst), [](const auto& v) { return v < 0; }));   // NOLINT
    EXPECT_TRUE(std::none_of(begin(inl), end(inl), [](const auto& v) { return v < 0; }));   // NOLINT
    EXPECT_TRUE(std::none_of(begin(view), end(view), [](const auto& v) { return v < 0; })); // NOLINT
}

TEST(
    algorithm, Search_FindEnd
)
{
    constexpr std::array<int, 2> test1 = {3, 4};         // NOLINT
    constexpr std::array<int, 2> test2 = {6, 7};         // NOLINT

    std::array<int, 6>         arr = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::vector<int>           vec = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::deque<int>            deq = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::list<int>             lst = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::initializer_list<int> inl = {1, 2, 3, 4, 5, 6}; // NOLINT
    // std::unordered_set<int>              uset = {1, 2, 3, 4, 5, 6};                   // NOLINT
    // std::unordered_map<std::string, int> umap =
    //     {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}}; // NOLINT

    std::vector<int>                        rng = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::ranges::ref_view<std::vector<int>> view = rng | std::views::all;

    using std::begin, std::end;

    EXPECT_NE(std::find_end(begin(arr), end(arr), begin(test1), end(test1)), end(arr));    // NOLINT
    EXPECT_NE(std::find_end(begin(vec), end(vec), begin(test1), end(test1)), end(vec));    // NOLINT
    EXPECT_NE(std::find_end(begin(deq), end(deq), begin(test1), end(test1)), end(deq));    // NOLINT
    EXPECT_NE(std::find_end(begin(lst), end(lst), begin(test1), end(test1)), end(lst));    // NOLINT
    EXPECT_NE(std::find_end(begin(inl), end(inl), begin(test1), end(test1)), end(inl));    // NOLINT
    EXPECT_NE(std::find_end(begin(view), end(view), begin(test1), end(test1)), end(view)); // NOLINT

    EXPECT_EQ(std::find_end(begin(arr), end(arr), begin(test2), end(test2)), end(arr));    // NOLINT
    EXPECT_EQ(std::find_end(begin(vec), end(vec), begin(test2), end(test2)), end(vec));    // NOLINT
    EXPECT_EQ(std::find_end(begin(deq), end(deq), begin(test2), end(test2)), end(deq));    // NOLINT
    EXPECT_EQ(std::find_end(begin(lst), end(lst), begin(test2), end(test2)), end(lst));    // NOLINT
    EXPECT_EQ(std::find_end(begin(inl), end(inl), begin(test2), end(test2)), end(inl));    // NOLINT
    EXPECT_EQ(std::find_end(begin(view), end(view), begin(test2), end(test2)), end(view)); // NOLINT

    // 要素を遇機で == するため end ではない
    EXPECT_NE(
        std::find_end( // NOLINT
            begin(arr),
            end(arr),
            begin(test2),
            end(test2),
            [](const auto& a, const auto& b) { return (a % 2) == (b % 2); }
        ),
        end(arr)
    ); // NOLINT
}

TEST(
    algorithm, Search_FindFirstOf
)
{
    constexpr std::array<int, 2> test1 = {6, 7};         // NOLINT
    constexpr std::array<int, 2> test2 = {7, 8};         // NOLINT

    std::array<int, 6>         arr = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::vector<int>           vec = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::deque<int>            deq = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::list<int>             lst = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::initializer_list<int> inl = {1, 2, 3, 4, 5, 6}; // NOLINT
    // std::unordered_set<int>              uset = {1, 2, 3, 4, 5, 6};                   // NOLINT
    // std::unordered_map<std::string, int> umap =
    //     {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}}; // NOLINT

    std::vector<int>                        rng = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::ranges::ref_view<std::vector<int>> view = rng | std::views::all;

    using std::begin, std::end;

    EXPECT_NE(std::find_first_of(begin(arr), end(arr), begin(test1), end(test1)), end(arr));    // NOLINT
    EXPECT_NE(std::find_first_of(begin(vec), end(vec), begin(test1), end(test1)), end(vec));    // NOLINT
    EXPECT_NE(std::find_first_of(begin(deq), end(deq), begin(test1), end(test1)), end(deq));    // NOLINT
    EXPECT_NE(std::find_first_of(begin(lst), end(lst), begin(test1), end(test1)), end(lst));    // NOLINT
    EXPECT_NE(std::find_first_of(begin(inl), end(inl), begin(test1), end(test1)), end(inl));    // NOLINT
    EXPECT_NE(std::find_first_of(begin(view), end(view), begin(test1), end(test1)), end(view)); // NOLINT

    EXPECT_EQ(std::find_first_of(begin(arr), end(arr), begin(test2), end(test2)), end(arr));    // NOLINT
    EXPECT_EQ(std::find_first_of(begin(vec), end(vec), begin(test2), end(test2)), end(vec));    // NOLINT
    EXPECT_EQ(std::find_first_of(begin(deq), end(deq), begin(test2), end(test2)), end(deq));    // NOLINT
    EXPECT_EQ(std::find_first_of(begin(lst), end(lst), begin(test2), end(test2)), end(lst));    // NOLINT
    EXPECT_EQ(std::find_first_of(begin(inl), end(inl), begin(test2), end(test2)), end(inl));    // NOLINT
    EXPECT_EQ(std::find_first_of(begin(view), end(view), begin(test2), end(test2)), end(view)); // NOLINT

    // 要素を odd/even で == するため end ではない
    EXPECT_NE(
        std::find_first_of( // NOLINT
            begin(arr),
            end(arr),
            begin(test2),
            end(test2),
            [](const auto& a, const auto& b) { return (a % 2) == (b % 2); }
        ),
        end(arr)
    ); // NOLINT
}

TEST(
    algorithm, Search_AdjacentFind
)
{
    std::array<int, 4>                   arr1 = {1, 2, 2, 3};                              // NOLINT
    std::array<int, 4>                   arr2 = {1, 3, 5, 7};                              // NOLINT
    std::unordered_map<std::string, int> umap1 = {{"A", 2}, {"B", 2}, {"C", 2}, {"D", 2}}; // NOLINT

    using std::begin, std::end;

    EXPECT_NE(std::adjacent_find(begin(arr1), end(arr1)), end(arr1)); // NOLINT
    EXPECT_EQ(std::adjacent_find(begin(arr2), end(arr2)), end(arr2)); // NOLINT
    EXPECT_NE(
        std::adjacent_find(                                           // NOLINT
            begin(arr2),
            end(arr2),
            [](const int& a, const int& b) { return (a % 2) == (b % 2); }
        ),
        end(arr2)
    );

    EXPECT_EQ(std::adjacent_find(begin(umap1), end(umap1)), end(umap1)); // NOLINT
    EXPECT_NE(
        std::adjacent_find(                                              // NOLINT
            begin(umap1),
            end(umap1),
            [](const auto& a, const auto& b) { return (a.second % 2) == (b.second % 2); }
        ),
        end(umap1)
    );
}

TEST(
    algorithm, Search_Count
)
{
    std::array<int, 5>                   arr = {1, 2, 2, 3, 5};                           // NOLINT
    std::unordered_map<std::string, int> umap = {{"A", 1}, {"B", 2}, {"C", 2}, {"D", 2}}; // NOLINT

    using std::begin, std::end;

    EXPECT_EQ(2, std::count(begin(arr), end(arr), 2));                                                      // NOLINT
    EXPECT_EQ(3, std::count_if(begin(arr), end(arr), [](const auto& v) { return (v % 2) == 1; }));          // NOLINT

    EXPECT_EQ(1, std::count(begin(umap), end(umap), std::make_pair(std::string("A"), 1)));                  // NOLINT
    EXPECT_EQ(3, std::count_if(begin(umap), end(umap), [](const auto& v) { return (v.second % 2) == 0; })); // NOLINT
}

TEST(
    algorithm, Search_Mismatch
)
{
    std::array<int, 5> arr1 = {1, 2, 3, 4, 5}; // NOLINT
    std::array<int, 2> arr2 = {1, 2};          // NOLINT
    std::array<int, 2> arr3 = {8, 9};          // NOLINT

    using std::begin, std::end;

    EXPECT_NE(std::make_pair(end(arr2), end(arr1)), std::mismatch(begin(arr2), end(arr2), begin(arr1)));     // NOLINT
    EXPECT_EQ(std::make_pair(begin(arr3), begin(arr1)), std::mismatch(begin(arr3), end(arr3), begin(arr1))); // NOLINT
    EXPECT_NE(
        std::make_pair(end(arr3), end(arr1)),
        std::mismatch(                                                                                       // NOLINT
            begin(arr3),
            end(arr3),
            begin(arr1),
            [](const auto& a, const auto& b) { return (a % 2) == (b % 2); }
        )
    ); // NOLINT
}

TEST(
    algorithm, Search_equal
)
{
    std::array<int, 5> arr1 = {1, 2, 3, 4, 5}; // NOLINT
    std::array<int, 3> arr2 = {1, 2, 9};       // NOLINT

    using std::begin, std::end;

    EXPECT_FALSE(std::equal(begin(arr2), end(arr2), begin(arr1)));    // NOLINT
    EXPECT_TRUE(std::equal(begin(arr2), end(arr2) - 1, begin(arr1))); // NOLINT

    EXPECT_TRUE(std::equal(                                           // NOLINT
        begin(arr2),
        end(arr2),
        begin(arr1),
        [](const auto& a, const auto& b) { return (a % 2) == (b % 2); }
    )); // NOLINT
}

TEST(
    algorithm, Search_search
)
{
    std::array<int, 5> arr1 = {1, 2, 3, 4, 5}; // NOLINT
    std::array<int, 3> arr2 = {1, 2, 9};       // NOLINT

    using std::begin, std::end;

    EXPECT_EQ(end(arr1), std::search(begin(arr1), end(arr1), begin(arr2), end(arr2)));       // NOLINT
    EXPECT_EQ(begin(arr1), std::search(begin(arr1), end(arr1), begin(arr2), end(arr2) - 1)); // NOLINT

    EXPECT_EQ(
        begin(arr1),
        std::search( // NOLINT
            begin(arr1),
            end(arr1),
            begin(arr2),
            end(arr2),
            [](const auto& a, const auto& b) { return (a % 2) == (b % 2); }
        )
    ); // NOLINT
}

TEST(
    algorithm, Search_searchN
)
{
    std::array<int, 6> arr1 = {1, 9, 9, 3, 4, 5}; // NOLINT

    using std::begin, std::end;

    EXPECT_EQ(end(arr1), std::search_n(begin(arr1), end(arr1), 5, 9));       // NOLINT
    EXPECT_EQ(begin(arr1) + 1, std::search_n(begin(arr1), end(arr1), 2, 9)); // NOLINT

    EXPECT_EQ(
        begin(arr1),
        std::search_n( // NOLINT
            begin(arr1),
            end(arr1),
            6,
            9,
            [](const auto& a, const auto& b) { return (a > 0) == (b > 0); }
        )
    ); // NOLINT
}

TEST(
    algorithm, Copy_copy
)
{
    constexpr std::array<int, 6> s_arr = {1, 2, 3, 4, 5, 6}; // NOLINT

    std::array<int, 6> d_arr = {0, 0, 0, 0, 0, 0};           // NOLINT
    std::vector<int>   d_vec = {};

    using std::begin, std::end;

    auto it1 = std::copy(begin(s_arr), end(s_arr), begin(d_arr));                               // NOLINT
    EXPECT_EQ(end(d_arr), it1);                                                                 // NOLINT
    EXPECT_TRUE(std::ranges::equal(d_arr, s_arr));                                              // NOLINT

    [[maybe_unused]] auto it2 = std::copy(begin(s_arr), end(s_arr), std::back_inserter(d_vec)); // NOLINT
    EXPECT_EQ(d_arr.size(), s_arr.size());                                                      // NOLINT
    EXPECT_TRUE(std::ranges::equal(d_vec, s_arr));                                              // NOLINT

    d_vec.resize(0);
    d_vec.shrink_to_fit();
    std::copy_if( // NOLINT
        begin(s_arr),
        end(s_arr),
        std::back_inserter(d_vec),
        [](const int& v) { return v % 2 == 0; }
    );
    EXPECT_EQ(s_arr.size() / 2, d_vec.size()); // NOLINT
    EXPECT_TRUE(std::ranges::equal(d_vec, s_arr | std::views::filter([](const int& v) { return v % 2 == 0; })));

    d_vec.resize(0);
    d_vec.shrink_to_fit();
    std::copy_n( // NOLINT
        begin(s_arr),
        4,
        std::back_inserter(d_vec)
    );
    EXPECT_EQ(4, d_vec.size()); // NOLINT
    EXPECT_TRUE(std::ranges::equal(d_vec, s_arr | std::views::take(4)));
}

TEST(
    algorithm, Copy_copyBackward
)
{
    //                      0  1  2  3  4  5  6  7  8
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 0, 0, 0}; // NOLINT

    using std::begin, std::end;

    std::copy_backward(begin(vec), begin(vec) + 5, end(vec)); // NOLINT
    EXPECT_EQ(1, vec[0]);                                     // NOLINT
    EXPECT_EQ(2, vec[1]);                                     // NOLINT
    EXPECT_EQ(3, vec[2]);                                     // NOLINT
    EXPECT_EQ(4, vec[3]);                                     // NOLINT
    EXPECT_EQ(1, vec[4]);                                     // NOLINT
    EXPECT_EQ(2, vec[5]);                                     // NOLINT
    EXPECT_EQ(3, vec[6]);                                     // NOLINT
    EXPECT_EQ(4, vec[7]);                                     // NOLINT
    EXPECT_EQ(5, vec[8]);                                     // NOLINT
}

TEST(
    algorithm, Transformation_transform
)
{
    constexpr std::array<int, 6> arr1 = {1, 2, 3, 4, 5, 6};       // NOLINT
    constexpr std::array<int, 6> arr2 = {-1, -2, -3, -4, -5, -6}; // NOLINT

    std::vector<int> vec;

    using std::begin, std::end;

    std::transform(begin(arr1), end(arr1), std::back_inserter(vec), [](const auto& v) { return v * 2; });    // NOLINT
    EXPECT_EQ(arr1.size(), vec.size());                                                                      // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec, arr1 | std::views::transform([](const auto& v) { return v * 2; }))); // NOLINT

    vec.resize(0);
    vec.shrink_to_fit();
    std::transform( // NOLINT
        begin(arr1),
        end(arr1),
        begin(arr2),
        std::back_inserter(vec),
        [](const auto& v1, const auto& v2) { return v1 * v2; }
    );                                  // NOLINT
    EXPECT_EQ(arr1.size(), vec.size()); // NOLINT
    EXPECT_TRUE(std::ranges::equal(
        vec,
        std::views::zip_transform([](const auto& v1, const auto& v2) { return v1 * v2; }, arr1, arr2)
    )); // NOLINT
}

TEST(
    algorithm, Transformation_replace
)
{
    std::array<int, 7> arr1 = {1, 2, 3, 4, 3, 5, 6}; // NOLINT
    std::array<int, 6> arr2 = {1, 2, 3, 4, 5, 6};    // NOLINT

    using std::begin, std::end;

    std::replace(begin(arr1), end(arr1), 3, 9);                                           // NOLINT
    EXPECT_EQ(arr1.size(), arr1.size());                                                  // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 2, 9, 4, 9, 5, 6}, arr1));

    std::replace_if(begin(arr2), end(arr2), [](const int& v) { return v % 2 == 0; }, -1); // NOLINT
    EXPECT_EQ(arr2.size(), arr2.size());                                                  // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, -1, 3, -1, 5, -1}, arr2));
}

TEST(
    algorithm, Transformation_replaceCopy
)
{
    constexpr std::array<int, 7> arr1 = {1, 2, 3, 4, 3, 5, 6}; // NOLINT
    constexpr std::array<int, 6> arr2 = {1, 2, 3, 4, 5, 6};    // NOLINT

    std::vector<int> vec1;
    std::vector<int> vec2;

    using std::begin, std::end;

    std::replace_copy(begin(arr1), end(arr1), std::back_inserter(vec1), 3, 9); // NOLINT
    EXPECT_EQ(arr1.size(), vec1.size());                                       // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 2, 9, 4, 9, 5, 6}, vec1));

    std::replace_copy_if(
        begin(arr2),
        end(arr2),
        std::back_inserter(vec2),
        [](const int& v) { return v % 2 == 0; },
        -1
    );                                   // NOLINT
    EXPECT_EQ(arr2.size(), vec2.size()); // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, -1, 3, -1, 5, -1}, vec2));
}
TEST(
    algorithm, Generation_fill
)
{
    std::vector<int> vec1;
    std::vector<int> vec2;

    using std::begin, std::end;

    vec1.resize(6);                         // NOLINT
    std::fill(begin(vec1), end(vec1), 0xF); // NOLINT
    EXPECT_EQ(6, vec1.size());
    EXPECT_TRUE(std::ranges::equal(std::views::repeat(0xF) | std::views::take(6), vec1));

    std::fill_n(std::back_inserter(vec2), 9, 0xF); // NOLINT
    EXPECT_EQ(9, vec2.size());
    EXPECT_TRUE(std::ranges::equal(std::views::repeat(0xF) | std::views::take(9), vec2));
}

TEST(
    algorithm, Generation_generate
)
{
    std::vector<int> vec1;
    std::vector<int> vec2;

    using std::begin, std::end;
    auto v1 = std::views::iota(0);                                                        // NOLINT
    auto v2 = std::views::iota(0xF);                                                      // NOLINT

    vec1.resize(6);                                                                       // NOLINT
    std::generate(begin(vec1), end(vec1), [it = v1.begin()]() mutable { return *it++; }); // NOLINT
    EXPECT_EQ(6, vec1.size());
    EXPECT_TRUE(std::ranges::equal(std::views::iota(0) | std::views::take(6), vec1));

    std::generate_n(std::back_inserter(vec2), 9, [it = v2.begin()]() mutable { return *it++; }); // NOLINT
    EXPECT_EQ(9, vec2.size());
    EXPECT_TRUE(std::ranges::equal(std::views::iota(0xF) | std::views::take(9), vec2));
}

TEST(
    algorithm, Removing_remove
)
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::vector<int> vec2 = {1, 2, 3, 4, 5, 6}; // NOLINT

    using std::begin, std::end;

    auto it1 = std::remove(begin(vec1), end(vec1), 3);                                            // NOLINT
    EXPECT_EQ(6, vec1.size());                                                                    // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 2, 4, 5, 6}, std::span(begin(vec1), it1)));

    auto it2 = std::remove_if(begin(vec2), end(vec2), [](const int& v) { return v % 2 == 0; });   // NOLINT
    EXPECT_EQ(6, vec2.size());                                                                    // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 3, 5}, std::span(begin(vec2), it2))); // NOLINT
}

TEST(
    algorithm, Removing_removeCopy
)
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::vector<int> vec2 = {1, 2, 3, 4, 5, 6}; // NOLINT

    std::vector<int> vec1x;
    std::vector<int> vec2x;

    using std::begin, std::end;

    std::remove_copy(begin(vec1), end(vec1), std::back_inserter(vec1x), 3); // NOLINT
    EXPECT_EQ(6, vec1.size());                                              // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 2, 3, 4, 5, 6}, vec1));
    EXPECT_EQ(5, vec1x.size());                                             // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 2, 4, 5, 6}, vec1x));

    std::remove_copy_if(                                                    // NOLINT
        begin(vec2),
        end(vec2),
        std::back_inserter(vec2x),
        [](const int& v) { return v % 2 == 0; }
    );                                                                      // NOLINT
    EXPECT_EQ(6, vec2.size());                                              // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 2, 3, 4, 5, 6}, vec2));
    EXPECT_EQ(3, vec2x.size());                                             // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 3, 5}, vec2x)); // NOLINT
}

TEST(
    algorithm, Removing_unique
)
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 3, 3, 6}; // NOLINT
    std::vector<int> vec2 = vec1;

    std::vector<int> vec2x;

    using std::begin, std::end;

    auto it1 = std::unique(begin(vec1), end(vec1));                                                           // NOLINT
    EXPECT_EQ(8, vec1.size());                                                                                // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 2, 3, 4, 5, 3, 6}, std::span(begin(vec1), it1))); // NOLINT

    std::unique_copy(begin(vec2), end(vec2), std::back_inserter(vec2x));                                      // NOLINT
    EXPECT_EQ(8, vec2.size());                                                                                // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 2, 3, 4, 5, 3, 3, 6}, vec2));
    EXPECT_EQ(7, vec2x.size());                                                                               // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 2, 3, 4, 5, 3, 6}, vec2x));                       // NOLINT
}

TEST(
    algorithm, Order_reverse
)
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6};       // NOLINT

    const std::vector<int> vec2 = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::vector<int>       vec2x;

    using std::begin, std::end;

    std::reverse(begin(vec1), end(vec1));                                 // NOLINT
    EXPECT_EQ(6, vec1.size());                                            // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec2 | std::views::reverse, vec1));    // NOLINT

    std::reverse_copy(begin(vec2), end(vec2), std::back_inserter(vec2x)); // NOLINT
    EXPECT_EQ(6, vec2x.size());                                           // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec2 | std::views::reverse, vec2x));
}

TEST(
    algorithm, Order_rotate
)
{
    const std::vector<int> GOLDEN = {4, 5, 6, 1, 2, 3}; // NOLINT

    std::vector<int>       vec1 = {1, 2, 3, 4, 5, 6};   // NOLINT
    const std::vector<int> vec2 = {1, 2, 3, 4, 5, 6};   // NOLINT
    std::vector<int>       vec2x;

    using std::begin, std::end;

    std::rotate(begin(vec1), begin(vec1) + 3, end(vec1));                                 // NOLINT
    EXPECT_EQ(6, vec1.size());                                                            // NOLINT
    EXPECT_TRUE(std::ranges::equal(GOLDEN, vec1));

    std::rotate_copy(begin(vec2), begin(vec2) + 3, end(vec2), std::back_inserter(vec2x)); // NOLINT
    EXPECT_EQ(6, vec2x.size());                                                           // NOLINT
    EXPECT_TRUE(std::ranges::equal(GOLDEN, vec2x));
}

TEST(
    algorithm, Order_shift
)
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::vector<int> vec2 = {1, 2, 3, 4, 5, 6}; // NOLINT

    using std::begin, std::end;

    std::shift_left(begin(vec1), end(vec1), 3);  // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{4, 5, 6, 4, 5, 6}, vec1));

    std::shift_right(begin(vec2), end(vec2), 3); // NOLINT
    EXPECT_EQ(6, vec2.size());                   // NOLINT
    EXPECT_EQ(1, vec2[0]);                       // NOLINT
    EXPECT_EQ(2, vec2[1]);                       // NOLINT
    EXPECT_EQ(3, vec2[2]);                       // NOLINT
    EXPECT_EQ(1, vec2[3]);                       // NOLINT
    EXPECT_EQ(2, vec2[4]);                       // NOLINT
    EXPECT_EQ(3, vec2[5]);                       // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 2, 3, 1, 2, 3}, vec2));
}

TEST(
    algorithm, Order_shuffle
)
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6}; // NOLINT

    using std::begin, std::end;

    std::shuffle(begin(vec1), end(vec1), std::mt19937{std::random_device{}()}); // NOLINT

    EXPECT_EQ(6, vec1.size());                                                  // NOLINT
    EXPECT_EQ(1, std::count(begin(vec1), end(vec1), 1));                        // NOLINT
    EXPECT_EQ(1, std::count(begin(vec1), end(vec1), 2));                        // NOLINT
    EXPECT_EQ(1, std::count(begin(vec1), end(vec1), 3));                        // NOLINT
    EXPECT_EQ(1, std::count(begin(vec1), end(vec1), 4));                        // NOLINT
    EXPECT_EQ(1, std::count(begin(vec1), end(vec1), 5));                        // NOLINT
    EXPECT_EQ(1, std::count(begin(vec1), end(vec1), 6));                        // NOLINT
}

TEST(
    algorithm, Sampling_sample
)
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::vector<int> vec2;

    using std::begin, std::end;

    std::sample(begin(vec1), end(vec1), std::back_inserter(vec2), 3, std::mt19937{std::random_device{}()}); // NOLINT
    EXPECT_EQ(3, vec2.size());                                                                              // NOLINT
    EXPECT_LE(std::count(begin(vec2), end(vec2), 1), 1);                                                    // NOLINT
    EXPECT_LE(std::count(begin(vec2), end(vec2), 2), 1);                                                    // NOLINT
    EXPECT_LE(std::count(begin(vec2), end(vec2), 3), 1);                                                    // NOLINT
    EXPECT_LE(std::count(begin(vec2), end(vec2), 4), 1);                                                    // NOLINT
    EXPECT_LE(std::count(begin(vec2), end(vec2), 5), 1);                                                    // NOLINT
    EXPECT_LE(std::count(begin(vec2), end(vec2), 6), 1);                                                    // NOLINT
}

TEST(
    algorithm, Partitioning_partition
)
{
    std::vector<int>       vec1 = {1, 2, 3, 4, 5, 6}; // NOLINT
    const std::vector<int> vec2 = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::vector<int>       vec3x;
    std::vector<int>       vec3y;
    std::vector<int>       vec4 = vec1;

    auto is_even = [](const int& v) { return v % 2 == 0; };

    using std::begin, std::end;

    EXPECT_FALSE(std::is_partitioned(begin(vec1), end(vec1), is_even)); // NOLINT
    auto it1 = std::partition(begin(vec1), end(vec1), is_even);         // NOLINT
    EXPECT_TRUE(std::is_partitioned(begin(vec1), end(vec1), is_even));  // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{6, 2, 4, 3, 5, 1}, vec1));
    EXPECT_TRUE(begin(vec1) + 3 == it1);                                // NOLINT

    std::partition_copy(                                                // NOLINT
        begin(vec2),
        end(vec2),
        std::back_inserter(vec3x),
        std::back_inserter(vec3y),
        is_even
    );                                                                      // NOLINT
    EXPECT_EQ(3, vec3x.size());                                             // NOLINT
    EXPECT_EQ(3, vec3y.size());                                             // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{2, 4, 6}, vec3x)); // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{1, 3, 5}, vec3y)); // NOLINT

    auto it4 = std::stable_partition(begin(vec4), end(vec4), is_even);      // NOLINT
    EXPECT_TRUE(std::is_partitioned(begin(vec4), end(vec4), is_even));      // NOLINT
    EXPECT_TRUE(std::ranges::equal(std::initializer_list{2, 4, 6, 1, 3, 5}, vec4));
    EXPECT_TRUE(begin(vec4) + 3 == it4);                                    // NOLINT

    // partitioned ではないので UB
    // auto it5x = std::partition_point(begin(vec2), end(vec2), is_even);      // NOLINT
    // EXPECT_EQ(begin(vec2) + 1, it5x);                                       // NOL
    auto it5y = std::partition_point(begin(vec4), end(vec4), is_even); // NOLINT
    EXPECT_EQ(begin(vec4) + 3, it5y);                                  // NOLINT
}

TEST(
    algorithm, Sorting_sort
)
{
    std::vector<int>       vec1 = {1, 2, 3, 4, 5, 6}; // NOLINT
    const std::vector<int> vec2 = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::vector<int>       vec3x;
    std::vector<int>       vec3y;
    std::vector<int>       vec4 = vec1;

    using std::begin, std::end;

    std::shuffle(begin(vec1), end(vec1), std::mt19937{std::random_device{}()});
    EXPECT_FALSE(std::is_sorted(begin(vec1), end(vec1)));                // NOLINT
    std::sort(begin(vec1), end(vec1));                                   // NOLINT
    EXPECT_TRUE(std::is_sorted(begin(vec1), end(vec1)));                 // NOLINT
    std::sort(begin(vec1), end(vec1), std::greater{});                   // NOLINT
    EXPECT_TRUE(std::is_sorted(begin(vec1), end(vec1), std::greater{})); // NOLINT
}

TEST(
    algorithm, Sorting_partialSort
)
{
    std::vector<int>       vec1 = {1, 9, 4, 6, 3, 2, 7, 8, 5}; // NOLINT
    const std::vector<int> vec2 = {1, 2, 3, 4, 5, 6};          // NOLINT
    std::vector<int>       vec3x;
    std::vector<int>       vec3y;
    std::vector<int>       vec4 = vec1;

    using std::begin, std::end;

    std::partial_sort(begin(vec1), begin(vec1) + 3, end(vec1)); // NOLINT
    EXPECT_FALSE(std::is_sorted(begin(vec1), end(vec1)));       // NOLINT
    EXPECT_TRUE(std::is_sorted(begin(vec1), begin(vec1) + 3));  // NOLINT

    vec3x.resize(9);                                            // NOLINT
    std::partial_sort_copy(                                     // NOLINT
        begin(vec2),
        end(vec2),
        begin(vec3x),
        begin(vec3x) + 3
    );
    EXPECT_EQ(1, vec3x[0]); // NOLINT
    EXPECT_EQ(2, vec3x[1]); // NOLINT
    EXPECT_EQ(3, vec3x[2]); // NOLINT
    EXPECT_EQ(0, vec3x[3]); // NOLINT
    EXPECT_EQ(0, vec3x[4]); // NOLINT
    EXPECT_EQ(0, vec3x[5]); // NOLINT
    EXPECT_EQ(0, vec3x[6]); // NOLINT
    EXPECT_EQ(0, vec3x[7]); // NOLINT
    EXPECT_EQ(0, vec3x[8]); // NOLINT
}

TEST(
    algorithm, Sorting_IsSortedUntil
)
{
    //                     ここまでソート済み ->|
    const std::vector<int> vec1 = {1, 2, 3, 6, 9, 4, 7, 8, 5}; // NOLINT

    using std::begin, std::end;

    auto it1 = std::is_sorted_until(begin(vec1), end(vec1)); // NOLINT
    EXPECT_EQ(begin(vec1) + 5, it1);
    EXPECT_EQ(4, *it1);
}

TEST(
    algorithm, Sorting_NthElement
)
{
    std::vector<int> vec1;

    using std::begin, std::end;

    std::generate_n(std::back_inserter(vec1), 9, [n = 0]() mutable { return n++; }); // NOLINT
    std::shuffle(begin(vec1), end(vec1), std::mt19937{std::random_device{}()});      // NOLINT

    std::nth_element(begin(vec1), begin(vec1) + 4, end(vec1));                       // NOLINT
    for (const auto& v : vec1)
    {
        std::cerr << v << " ";                                                       // NOLINT
    }
}

TEST(
    algorithm, BinarySearch_Bound
)
{
    const std::vector<int> vec1 = {1, 2, 3, 4, 4, 5, 6, 7, 8, 4, 9}; // NOLINT

    using std::begin, std::end;

    auto it1 = std::lower_bound(begin(vec1), end(vec1), 4);          // NOLINT
    EXPECT_EQ(4, *it1);                                              // NOLINT
    EXPECT_EQ(begin(vec1) + 3, it1);                                 // NOLINT

    auto it2 = std::upper_bound(begin(vec1), end(vec1), 4);          // NOLINT
    EXPECT_EQ(5, *it2);                                              // NOLINT
    EXPECT_EQ(begin(vec1) + 5, it2);                                 // NOLINT

    auto [it3x, it3y] = std::equal_range(begin(vec1), end(vec1), 4); // NOLINT
    EXPECT_EQ(4, *it3x);                                             // NOLINT
    EXPECT_EQ(5, *it3y);                                             // NOLINT
    EXPECT_EQ(begin(vec1) + 3, it3x);                                // NOLINT
    EXPECT_EQ(begin(vec1) + 5, it3y);                                // NOLINT

    EXPECT_TRUE(std::binary_search(begin(vec1), end(vec1), 4));      // NOLINT
    EXPECT_FALSE(std::binary_search(begin(vec1), end(vec1), 10));    // NOLINT
}

TEST(
    algorithm, Set_includes
)
{
    const std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // NOLINT
    const std::vector<int> vec2 = {3, 4, 5, 7};                // NOLINT
    const std::vector<int> vec3 = {1, 2, 11};                  // NOLINT

    using std::begin, std::end;

    EXPECT_TRUE(std::includes(begin(vec1), end(vec1), begin(vec2), end(vec2)));  // NOLINT
    EXPECT_FALSE(std::includes(begin(vec1), end(vec1), begin(vec3), end(vec3))); // NOLINT
    EXPECT_TRUE(std::includes(                                                   // NOLINT
        begin(vec1),
        end(vec1),
        begin(vec3),
        end(vec3) - 1
    ));                                      // NOLINT

    auto vec1r = vec1 | std::views::reverse; // NOLINT
    auto vec2r = vec2 | std::views::reverse; // NOLINT

    EXPECT_TRUE(std::includes(               // NOLINT
        begin(vec1r),
        end(vec1r),
        begin(vec2r),
        end(vec2r),
        std::greater{} // NOLINT
    ));
}
TEST(
    algorithm, Set_Set
)
{
    const std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // NOLINT
    const std::vector<int> vec2 = {1, 2, 3, 4, 9, 10};         // NOLINT

    using std::begin, std::end;

    {
        std::vector<int> v;
        std::set_union(begin(vec1), end(vec1), begin(vec2), end(vec2), std::back_inserter(v));         // NOLINT
        EXPECT_EQ(10, v.size());                                                                       // NOLINT
        EXPECT_TRUE(std::ranges::equal(v, std::initializer_list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10})); // NOLINT
    }

    {
        std::vector<int> v;
        std::set_intersection(begin(vec1), end(vec1), begin(vec2), end(vec2), std::back_inserter(v)); // NOLINT
        EXPECT_EQ(5, v.size());                                                                       // NOLINT
        EXPECT_TRUE(std::ranges::equal(v, std::initializer_list<int>{1, 2, 3, 4, 9}));                // NOLINT
    }

    {
        std::vector<int> v;
        std::set_difference(begin(vec1), end(vec1), begin(vec2), end(vec2), std::back_inserter(v)); // NOLINT
        EXPECT_EQ(4, v.size());                                                                     // NOLINT
        EXPECT_TRUE(std::ranges::equal(v, std::initializer_list<int>{5, 6, 7, 8}));                 // NOLINT
    }

    {
        std::vector<int> v;
        std::set_symmetric_difference(begin(vec1), end(vec1), begin(vec2), end(vec2), std::back_inserter(v)); // NOLINT
        EXPECT_EQ(5, v.size());                                                                               // NOLINT
        EXPECT_TRUE(std::ranges::equal(v, std::initializer_list<int>{5, 6, 7, 8, 10}));                       // NOLINT
    }
}

TEST(
    algorithm, Merge_Merge
)
{

    using std::begin, std::end;

    {
        auto odd = std::views::iota(1) | std::views::stride(2) | std::views::take(5) | std::views::common;  // NOLINT
        auto even = std::views::iota(2) | std::views::stride(2) | std::views::take(5) | std::views::common; // NOLINT

        std::vector<int> v;
        std::merge(begin(odd), end(odd), begin(even), end(even), std::back_inserter(v));                    // NOLINT
        EXPECT_EQ(10, v.size());                                                                            // NOLINT
        EXPECT_TRUE(std::ranges::equal(v, std::views::iota(1) | std::views::take(10)));                     // NOLINT
    }

    {
        std::vector<int> v = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};                           // NOLINT
        std::inplace_merge(begin(v), begin(v) + v.size() / 2, end(v));                  // NOLINT
        EXPECT_EQ(10, v.size());                                                        // NOLINT
        EXPECT_TRUE(std::ranges::equal(v, std::views::iota(1) | std::views::take(10))); // NOLINT
    }
}

TEST(
    algorithm, Heap_Heap
)
{
    using std::begin, std::end;

    std::vector<int> v = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};        // NOLINT
    EXPECT_FALSE(std::ranges::is_heap(v));                       // NOLINT

    std::make_heap(begin(v), end(v));                            // NOLINT
    EXPECT_TRUE(std::ranges::is_heap(v));                        // NOLINT

    v.emplace_back(11);                                          // NOLINT
    EXPECT_EQ(10, v.front());
    EXPECT_FALSE(std::ranges::is_heap(v));                       // NOLINT
    std::push_heap(begin(v), end(v));                            // NOLINT
    EXPECT_TRUE(std::ranges::is_heap(v));                        // NOLINT
    EXPECT_EQ(11, v.front());
    EXPECT_EQ(11, v.size());                                     // NOLINT

    std::pop_heap(begin(v), end(v));                             // NOLINT
    EXPECT_EQ(end(v) - 1, std::is_heap_until(begin(v), end(v))); // NOLINT
    EXPECT_FALSE(std::ranges::is_heap(v));                       // NOLINT
    EXPECT_EQ(11, v.size());                                     // NOLINT
    EXPECT_EQ(10, v.front());

    // この時点では、*front が *last-1 に移動しただけなので、vector 全体を見ると heap ではない
    v.pop_back();
    EXPECT_EQ(end(v), std::is_heap_until(begin(v), end(v))); // NOLINT
    EXPECT_TRUE(std::ranges::is_heap(v));                    // NOLINT
    EXPECT_EQ(10, v.size());                                 // NOLINT
    EXPECT_EQ(10, v.front());

    EXPECT_FALSE(std::is_sorted(begin(v), end(v)));          // NOLINT
    std::sort_heap(begin(v), end(v));                        // NOLINT
    EXPECT_TRUE(std::is_sorted(begin(v), end(v)));           // NOLINT
    EXPECT_EQ(1, v.front());
}

TEST(
    algorithm, MinMax_MinMax
)
{
    using std::begin, std::end;
    const std::initializer_list<int> ilist = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10}; // NOLINT
    const std::vector<int>           vec = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};   // NOLINT

    static_assert(std::is_same_v<const int&, decltype(std::max(1, 2))>);
    static_assert(std::is_same_v<int, decltype(std::max(ilist))>);
    EXPECT_EQ(2, std::max(1, 2));
    EXPECT_EQ(10, std::max(ilist));

    static_assert(std::is_same_v<
                  decltype(vec)::const_iterator,
                  decltype(std::max_element(begin(vec), end(vec)))>);                               // NOLINT
    EXPECT_EQ(10, *std::max_element(begin(vec), end(vec)));                                         // NOLINT

    static_assert(std::is_same_v<std::pair<const int&, const int&>, decltype(std::minmax(10, 1))>); // NOLINT
    EXPECT_EQ(std::make_pair(1, 10), std::minmax(10, 1));                                           // NOLINT

    static_assert(std::is_same_v<
                  std::pair<decltype(vec)::const_iterator, decltype(vec)::const_iterator>,
                  decltype(std::minmax_element(begin(vec), end(vec)))>); // NOLINT
    auto [it_min, it_max] = std::minmax_element(begin(vec), end(vec));   // NOLINT
    EXPECT_EQ(1, *it_min);                                               // NOLINT
    EXPECT_EQ(10, *it_max);                                              // NOLINT
}

TEST(
    algorithm, MinMax_Clamp
)
{
    static_assert(std::is_same_v<const int&, decltype(std::clamp(1, 2, 3))>); // NOLINT

    EXPECT_EQ(5, std::clamp(5, 0, 10));                                       // NOLINT
    EXPECT_EQ(0, std::clamp(-1, 0, 10));                                      // NOLINT
    EXPECT_EQ(10, std::clamp(11, 0, 10));                                     // NOLINT
}

TEST(
    algorithm, Lexicographical
)
{
    using std::begin, std::end;

    const std::vector<int> vec1 = {2, 3, 4, 5, 7};                                             // NOLINT
    const std::vector<int> vec2 = {1, 2, 3, 4, 5};                                             // NOLINT
    const std::vector<int> vec3 = {1};                                                         // NOLINT

    EXPECT_TRUE(std::lexicographical_compare(begin(vec2), end(vec2), begin(vec1), end(vec1))); // NOLINT
    EXPECT_TRUE(std::lexicographical_compare(begin(vec3), end(vec3), begin(vec1), end(vec1))); // NOLINT
}

TEST(
    algorithm, Permutation
)
{
    using std::begin, std::end;

    std::vector<int> vec1 = {1, 2, 3};                                          // NOLINT

    EXPECT_TRUE(std::next_permutation(begin(vec1), end(vec1)));                 // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec1, std::initializer_list<int>{1, 3, 2})); // NOLINT
    EXPECT_TRUE(std::next_permutation(begin(vec1), end(vec1)));                 // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec1, std::initializer_list<int>{2, 1, 3})); // NOLINT
    EXPECT_TRUE(std::next_permutation(begin(vec1), end(vec1)));                 // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec1, std::initializer_list<int>{2, 3, 1})); // NOLINT
    EXPECT_TRUE(std::next_permutation(begin(vec1), end(vec1)));                 // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec1, std::initializer_list<int>{3, 1, 2})); // NOLINT
    EXPECT_TRUE(std::next_permutation(begin(vec1), end(vec1)));                 // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec1, std::initializer_list<int>{3, 2, 1})); // NOLINT
    EXPECT_FALSE(std::next_permutation(begin(vec1), end(vec1)));                // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec1, std::initializer_list<int>{1, 2, 3})); // NOLINT

    EXPECT_FALSE(std::prev_permutation(begin(vec1), end(vec1)));                // NOLINT
    EXPECT_TRUE(std::ranges::equal(vec1, std::initializer_list<int>{3, 2, 1})); // NOLINT
}

TEST(
    algorithm, Numeric_iota
)
{
    using std::begin, std::end;

    std::vector<int> v;
    v.resize(10);                   // NOLINT

    std::iota(begin(v), end(v), 1); // NOLINT
    EXPECT_EQ(10, v.size());        // NOLINT
    EXPECT_TRUE(std::ranges::equal(v, std::initializer_list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}

TEST(
    algorithm, Numeric_accumulate
)
{
    using std::begin, std::end;

    auto v = std::views::iota(1, 11) | std::views::common;                         // NOLINT

    EXPECT_EQ(55, std::accumulate(begin(v), end(v), 0));                           // NOLINT
    EXPECT_EQ(3'628'800, std::accumulate(begin(v), end(v), 1, std::multiplies{})); // NOLINT
}

TEST(
    algorithm, Numeric_innerProduct
)
{
    using std::begin, std::end;

    const auto v1 = std::vector<int>{1, 2, 3, 4, 5};                      // NOLINT
    const auto v2 = std::vector<int>{6, 7, 8, 9, 10, 100000000};          // NOLINT

    EXPECT_EQ(130, std::inner_product(begin(v1), end(v1), begin(v2), 0)); // NOLINT

    // (1+6) * (2+7) * (3+8) * (4+9) * (5+10) = 7 * 9 * 11 * 13 * 15 = 135135
    EXPECT_EQ(135135, std::inner_product(begin(v1), end(v1), begin(v2), 1, std::multiplies{}, std::plus{})); // NOLINT
}

TEST(
    algorithm, Numeric_adjacentDifference
)
{
    using std::begin, std::end;

    const auto v1 = std::vector<int>{1, 2, 5, 3, 100};                                              // NOLINT
    auto       v = std::vector<int>{};

    [[maybe_unused]] auto it = std::adjacent_difference(begin(v1), end(v1), std::back_inserter(v)); // NOLINT
    EXPECT_EQ(5, v.size());                                                                         // NOLINT
    EXPECT_TRUE(std::ranges::equal(v, std::initializer_list<int>{1, 1, 3, -2, 97}));                // NOLINT
}

TEST(
    algorithm, Numeric_partialSum
)
{
    using std::begin, std::end;

    const auto v1 = std::vector<int>{1, 2, 5, 3, 100};                                      // NOLINT
    auto       v = std::vector<int>{};

    [[maybe_unused]] auto it = std::partial_sum(begin(v1), end(v1), std::back_inserter(v)); // NOLINT
    EXPECT_EQ(5, v.size());                                                                 // NOLINT
    EXPECT_TRUE(std::ranges::equal(v, std::initializer_list<int>{1, 3, 8, 11, 111}));       // NOLINT
}

TEST(
    algorithm, Numeric_reduce
)
{
    using std::begin, std::end;

    auto v = std::views::iota(1, 11) | std::views::common;                     // NOLINT

    EXPECT_EQ(55, std::reduce(begin(v), end(v)));                              // NOLINT
    EXPECT_EQ(155, std::reduce(begin(v), end(v), 100));                        // NOLINT
    EXPECT_EQ(3'628'800, std::reduce(begin(v), end(v), 1, std::multiplies{})); // NOLINT
}

TEST(
    algorithm, Numeric_scan
)
{
    using std::begin, std::end;

    const auto v1 = std::vector<int>{1, 2, 5, 3, 100}; // NOLINT
    auto       vx = std::vector<int>{};
    auto       vy = std::vector<int>{};
    auto       vz = std::vector<int>{};

    [[maybe_unused]] auto it = std::partial_sum(begin(v1), end(v1), std::back_inserter(vx)); // NOLINT
    EXPECT_EQ(5, vx.size());                                                                 // NOLINT
    // 1
    // 1 + 2 = 3
    // 1 + 2 + 5 = 8
    // 1 + 2 + 5 + 3 = 11
    // 1 + 2 + 5 + 3 + 100 = 111
    EXPECT_TRUE(std::ranges::equal(vx, std::initializer_list<int>{1, 3, 8, 11, 111}));         // NOLINT

    std::exclusive_scan(begin(v1), end(v1), std::back_inserter(vy), -100);                     // NOLINT
    EXPECT_EQ(5, vy.size());                                                                   // NOLINT
    EXPECT_TRUE(std::ranges::equal(vy, std::initializer_list<int>{-100, -99, -97, -92, -89})); // NOLINT

    std::inclusive_scan(begin(v1), end(v1), std::back_inserter(vz));                           // NOLINT
    EXPECT_EQ(5, vz.size());                                                                   // NOLINT
    EXPECT_TRUE(std::ranges::equal(vz, std::initializer_list<int>{1, 3, 8, 11, 111}));         // NOLINT
}

TEST(
    algorithm, Numeric_transformReduce
)
{
    using std::begin, std::end;

    const auto v1 = std::vector<int>{1, 2, 3, 4, 5}; // NOLINT

    // 0 + (1*1) + (2*2) + (3*3) + (4*4) + (5*5) = 55
    EXPECT_EQ(55, std::transform_reduce(begin(v1), end(v1), begin(v1), 0, std::plus{}, std::multiplies{})); // NOLINT
}

TEST(
    algorithm, Numeric_transformScan
)
{
    using std::begin, std::end;

    const auto v1 = std::vector<int>{1, 2, 5, 3, 100}; // NOLINT
    auto       vi = std::vector<int>{};
    auto       ve = std::vector<int>{};

    std::transform_exclusive_scan(
        begin(v1),
        end(v1),
        std::back_inserter(vi),
        -100,                // NOLINT
        std::plus{},
        [](const auto& x) { return x * 2; }
    );                       // NOLINT
    EXPECT_EQ(5, vi.size()); // NOLINT

    // -100
    // -100 + 1 * 2 = -98
    // -100 + 1 * 2 + 2 * 2 = -94
    // -100 + 1 * 2 + 2 * 2 + 5 * 2 = -84
    // -100 + 1 * 2 + 2 * 2 + 5 * 2 + 3 * 2 = -78
    // -100 + 1 * 2 + 2 * 2 + 5 * 2 + 3 * 2 + 100 * 2 = -78
    EXPECT_TRUE(std::ranges::equal(vi, std::initializer_list<int>{-100, -98, -94, -84, -78})); // NOLINT

    std::transform_inclusive_scan(
        begin(v1),
        end(v1),
        std::back_inserter(ve),
        std::plus{},
        [](const auto& x) { return x * 2; }
    );                       // NOLINT
    EXPECT_EQ(5, ve.size()); // NOLINT
    // 1 * 2 = 2
    // 1 * 2 + 2 * 2 = 6
    // 1 * 2 + 2 * 2 + 5 * 2 = 16
    // 1 * 2 + 2 * 2 + 5 * 2 + 3 * 2 = 22
    // 1 * 2 + 2 * 2 + 5 * 2 + 3 * 2 + 100 * 2 = 122
    EXPECT_TRUE(std::ranges::equal(ve, std::initializer_list<int>{2, 6, 16, 22, 222})); // NOLINT
}

TEST(
    algorithm, Uninitialized_Copy
)
{
    constexpr std::array<int, 8> GOLDEN = {1, 2, 3, 4, 5, 6, 7, 8}; // NOLINT

    int* p = static_cast<int*>(aligned_alloc(64, sizeof(int) * 8)); // NOLINT
    std::uninitialized_copy(GOLDEN.begin(), GOLDEN.end(), p);       // NOLINT
    EXPECT_EQ(1, p[0]);                                             // NOLINT
    EXPECT_EQ(2, p[1]);                                             // NOLINT
    EXPECT_EQ(3, p[2]);                                             // NOLINT
    EXPECT_EQ(4, p[3]);                                             // NOLINT
    EXPECT_EQ(5, p[4]);                                             // NOLINT
    EXPECT_EQ(6, p[5]);                                             // NOLINT
    EXPECT_EQ(7, p[6]);                                             // NOLINT
    EXPECT_EQ(8, p[7]);                                             // NOLINT

    int* q = static_cast<int*>(aligned_alloc(64, sizeof(int) * 8)); // NOLINT
    std::uninitialized_copy_n(GOLDEN.begin(), 4, q);                // NOLINT
    EXPECT_EQ(1, q[0]);                                             // NOLINT
    EXPECT_EQ(2, q[1]);                                             // NOLINT
    EXPECT_EQ(3, q[2]);                                             // NOLINT
    EXPECT_EQ(4, q[3]);                                             // NOLINT
}

TEST(
    algorithm, Uninitialized_Fill
)
{
    int* p = static_cast<int*>(aligned_alloc(64, sizeof(int) * 8)); // NOLINT
    std::uninitialized_fill(p, p + 8, 0xFF);                        // NOLINT
    EXPECT_EQ(0xFF, p[0]);                                          // NOLINT
    EXPECT_EQ(0xFF, p[1]);                                          // NOLINT
    EXPECT_EQ(0xFF, p[2]);                                          // NOLINT
    EXPECT_EQ(0xFF, p[3]);                                          // NOLINT
    EXPECT_EQ(0xFF, p[4]);                                          // NOLINT
    EXPECT_EQ(0xFF, p[5]);                                          // NOLINT
    EXPECT_EQ(0xFF, p[6]);                                          // NOLINT
    EXPECT_EQ(0xFF, p[7]);                                          // NOLINT

    int* q = static_cast<int*>(aligned_alloc(64, sizeof(int) * 8)); // NOLINT
    std::uninitialized_fill_n(q, 4, 0xAA);                          // NOLINT
    EXPECT_EQ(0xAA, q[0]);                                          // NOLINT
    EXPECT_EQ(0xAA, q[1]);                                          // NOLINT
    EXPECT_EQ(0xAA, q[2]);                                          // NOLINT
    EXPECT_EQ(0xAA, q[3]);                                          // NOLINT
}

TEST(
    algorithm, Destroy
)
{
    struct S                                                  // NOLINT
    {
        int x;                                                // NOLINT

        S() : x(0) {}                                         // NOLINT
        S(int v) : x(v) {};

        ~S() { x = -1; }                                      // NOLINT
    };

    S* p = static_cast<S*>(aligned_alloc(64, sizeof(S) * 8)); // NOLINT
    for (int i = 0; i < 8; ++i)                               // NOLINT
    {
        std::construct_at(&p[i], i + 1);                      // NOLINT
    }
    EXPECT_EQ(1, p[0].x);                                     // NOLINT
    EXPECT_EQ(2, p[1].x);                                     // NOLINT
    EXPECT_EQ(3, p[2].x);                                     // NOLINT
    EXPECT_EQ(4, p[3].x);                                     // NOLINT
    EXPECT_EQ(5, p[4].x);                                     // NOLINT
    EXPECT_EQ(6, p[5].x);                                     // NOLINT
    EXPECT_EQ(7, p[6].x);                                     // NOLINT
    EXPECT_EQ(8, p[7].x);                                     // NOLINT

    std::destroy_at(&p[0]);                                   // NOLINT
    EXPECT_EQ(-1, p[0].x);                                    // NOLINT
    EXPECT_EQ(2, p[1].x);                                     // NOLINT
    EXPECT_EQ(3, p[2].x);                                     // NOLINT
    EXPECT_EQ(4, p[3].x);                                     // NOLINT
    EXPECT_EQ(5, p[4].x);                                     // NOLINT
    EXPECT_EQ(6, p[5].x);                                     // NOLINT
    EXPECT_EQ(7, p[6].x);                                     // NOLINT
    EXPECT_EQ(8, p[7].x);                                     // NOLINT

    std::destroy_n(p + 1, 3);                                 // NOLINT
    EXPECT_EQ(-1, p[0].x);                                    // NOLINT
    EXPECT_EQ(-1, p[1].x);                                    // NOLINT
    EXPECT_EQ(-1, p[2].x);                                    // NOLINT
    EXPECT_EQ(-1, p[3].x);                                    // NOLINT
    EXPECT_EQ(5, p[4].x);                                     // NOLINT
    EXPECT_EQ(6, p[5].x);                                     // NOLINT
    EXPECT_EQ(7, p[6].x);                                     // NOLINT
    EXPECT_EQ(8, p[7].x);                                     // NOLINT

    std::destroy(p + 4, p + 8);                               // NOLINT
    EXPECT_EQ(-1, p[0].x);                                    // NOLINT
    EXPECT_EQ(-1, p[1].x);                                    // NOLINT
    EXPECT_EQ(-1, p[2].x);                                    // NOLINT
    EXPECT_EQ(-1, p[3].x);                                    // NOLINT
    EXPECT_EQ(-1, p[4].x);                                    // NOLINT
    EXPECT_EQ(-1, p[5].x);                                    // NOLINT
    EXPECT_EQ(-1, p[6].x);                                    // NOLINT
    EXPECT_EQ(-1, p[7].x);                                    // NOLINT
}

} // namespace
