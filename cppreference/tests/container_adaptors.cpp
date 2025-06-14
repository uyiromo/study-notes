#include "gtest/gtest.h"
#include <deque>
#include <functional>
#include <queue>
#include <stack>
#include <vector>

namespace
{
TEST(
    container_adaptor, stack
)
{
    auto vec1 = std::vector<int>({1, 2, 3, 4, 5});                              // NOLINT

    auto stk1x = std::stack<int, std::vector<int>>();                           // NOLINT
    auto stk1y = std::stack<int, std::deque<int>>();                            // NOLINT
    auto stk2 = std::stack<int, std::vector<int>>(vec1);                        // NOLINT
    auto stk3 = std::stack<int, std::deque<int>>(++vec1.begin(), --vec1.end()); // NOLINT

    // top & pop
    // initializer_list は暗黙的に std::vector<int>&& に変換
    auto stk4 = std::stack<int, std::vector<int>>({1, 2, 3, 4, 5}); // NOLINT
    EXPECT_EQ(5, stk4.size());
    static_assert(std::is_same_v<decltype(stk4.top()), int&>);
    EXPECT_EQ(stk4.top(), 5);
    EXPECT_EQ(stk4.size(), 5);
    stk4.pop();
    EXPECT_EQ(stk4.size(), 4);

    stk4.push(6); // NOLINT
    EXPECT_EQ(stk4.top(), 6);
    EXPECT_EQ(stk4.size(), 5);

    stk4.emplace(7); // NOLINT
    EXPECT_EQ(stk4.top(), 7);
    EXPECT_EQ(stk4.size(), 6);

    // empty
    auto stk5 = std::stack<int, std::vector<int>>(); // NOLINT
    EXPECT_TRUE(stk5.empty());
}

TEST(
    container_adaptor, queue
)
{
    auto vec1 = std::vector<int>({1, 2, 3, 4, 5});                              // NOLINT

    auto que1x = std::queue<int, std::vector<int>>();                           // NOLINT
    auto que1y = std::queue<int, std::deque<int>>();                            // NOLINT
    auto que2 = std::queue<int, std::vector<int>>(vec1);                        // NOLINT
    auto que3 = std::queue<int, std::deque<int>>(++vec1.begin(), --vec1.end()); // NOLINT

    // front & back
    // initializer_list は暗黙的に std::vector<int>&& に変換
    auto que4 = std::queue<int, std::vector<int>>({0, 1, 2, 3, 4, 5}); // NOLINT
    EXPECT_EQ(5, que4.size());
    static_assert(std::is_same_v<decltype(que4.front()), int&>);
    static_assert(std::is_same_v<decltype(que4.back()), int&>);
    EXPECT_EQ(que4.front(), 0);
    EXPECT_EQ(que4.size(), 6);
    EXPECT_EQ(que4.back(), 5);
    EXPECT_EQ(que4.size(), 6);

    // push, emplace, pop
    que4.push(6); // NOLINT
    EXPECT_EQ(que4.front(), 0);
    EXPECT_EQ(que4.back(), 6);
    EXPECT_EQ(que4.size(), 7);

    que4.emplace(7); // NOLINT
    EXPECT_EQ(que4.front(), 0);
    EXPECT_EQ(que4.back(), 7);
    EXPECT_EQ(que4.size(), 8);
}

TEST(
    container_adaptor, priority_queue
)
{
    auto cmp = std::less<int>();                              // NOLINT

    auto vec1 = std::vector<int>({1, 2, 3, 4, 5});            // NOLINT

    auto pq1x = std::priority_queue<int, std::vector<int>>(); // NOLINT
    auto pq1y = std::priority_queue<int, std::deque<int>>();  // NOLINT

    // コンテナのみを引数には取れない
    // compare を指定するか、Iterator 範囲を指定する
    // => compare は左辺参照しか取れない
    // auto pq2 = std::priority_queue<int, std::vector<int>>(vec1);                        // NOLINT
    auto pq2x = std::priority_queue<int, std::vector<int>>(vec1.begin(), vec1.end()); // NOLINT
    auto pq2y = std::priority_queue<int, std::vector<int>>(cmp, vec1);

    // top, push, emplace, top
    // initializer_list は暗黙的に std::vector<int>&& に変換
    auto pq4 = std::priority_queue<int, std::vector<int>>(cmp, {5, 4, 3, 2, 1}); // NOLINT
    EXPECT_EQ(5, pq4.size());
    static_assert(std::is_same_v<decltype(pq4.top()), const int&>);

    EXPECT_EQ(pq4.top(), 5);
    EXPECT_EQ(pq4.size(), 5);
    pq4.pop();
    EXPECT_EQ(pq4.size(), 4);

    pq4.push(6); // NOLINT
    EXPECT_EQ(pq4.top(), 6);
    EXPECT_EQ(pq4.size(), 5);

    pq4.emplace(7); // NOLINT
    EXPECT_EQ(pq4.top(), 7);
    EXPECT_EQ(pq4.size(), 6);

    // empty
    auto pq5 = std::priority_queue<int, std::vector<int>>(); // NOLINT
    EXPECT_TRUE(pq5.empty());
}

TEST(
    container_adaptor, deque
)
{
    auto vec1 = std::vector<int>({1, 2, 3, 4, 5});             // NOLINT

    auto deq1x = std::deque<int>();                            // NOLINT
    auto deq1y = std::deque<int>(vec1);                        // NOLINT
    auto deq2 = std::deque<int>(++vec1.begin(), --vec1.end()); // NOLINT

    // front & back
    static_assert(std::is_same_v<decltype(deq1y.front()), int&>);
    static_assert(std::is_same_v<decltype(deq1y.back()), int&>);
    EXPECT_EQ(deq1y.front(), 1);
    EXPECT_EQ(deq1y.back(), 5);

    // push_front, push_back, pop_front, pop_back
    deq1y.push_front(0); // NOLINT
    EXPECT_EQ(deq1y.front(), 0);
    EXPECT_EQ(deq1y.back(), 5);
    deq1y.push_back(6);  // NOLINT
    EXPECT_EQ(deq1y.front(), 0);
    EXPECT_EQ(deq1y.back(), 6);

    deq1y.pop_front();
    EXPECT_EQ(deq1y.front(), 1);
    EXPECT_EQ(deq1y.back(), 6);
    deq1y.pop_back();
    EXPECT_EQ(deq1y.front(), 1);
    EXPECT_EQ(deq1y.back(), 5);

    // emplace_front, emplace_back
    deq1y.emplace_front(-2); // NOLINT
    EXPECT_EQ(deq1y.front(), -2);
    EXPECT_EQ(deq1y.back(), 5);
    deq1y.emplace_back(7);   // NOLINT
    EXPECT_EQ(deq1y.front(), -2);
    EXPECT_EQ(deq1y.back(), 7);

} // namespace
