#include "gtest/gtest.h"
#include <algorithm>
#include <cstddef>
#include <forward_list>
#include <iterator>
#include <list>
#include <utility>

namespace
{

template <typename T>
class IndirectlyReadable
{
  public:
    using value_type = T;
    auto operator*() const -> T& {};
};

template <typename T>
class WeaklyIncrementable // NOLINT
{
  public:
    using value_type = T;
    auto operator*() const -> T& {};

    // movable
    WeaklyIncrementable(WeaklyIncrementable<T>&&) = default; // NOLINT
    auto operator=(
        WeaklyIncrementable<T>&& _                           // NOLINT
    ) noexcept -> WeaklyIncrementable<T>&
    {
    }

    using difference_type = std::ptrdiff_t;
    auto operator++() -> WeaklyIncrementable<T>& {} // ++I
    auto operator++(
        int
    ) -> void
    {
    }
};

template <typename T>
class Incrementable // NOLINT
{
  public:
    using value_type = T;
    auto operator*() const -> T& {};

    // movable
    Incrementable(Incrementable<T>&&) = default; // NOLINT
    auto operator=(
        Incrementable<T>&& _                     // NOLINT
    ) noexcept -> Incrementable<T>&
    {
    }

    using difference_type = std::ptrdiff_t;
    auto operator++() -> Incrementable<T>& {} // ++I
    auto operator++(
        int
    ) -> Incrementable<T>
    {
    }

    Incrementable() = default;                        // NOLINT
    Incrementable(const Incrementable<T>&) = default; // NOLINT

    auto operator=(
        const Incrementable<T>& _                     // NOLINT
    ) noexcept -> Incrementable<T>&
    {
    }

    auto operator==(
        const Incrementable<T>& _ // NOLINT
    ) const -> bool
    {
        return true;
    }
};

template <typename T>
class InputOrOutputIterator : WeaklyIncrementable<T> // NOLINT
{
  public:
    using typename WeaklyIncrementable<T>::value_type;

    auto operator*() const -> T& {};
};

template <typename T>
class SentinelFor //: InputOrOutputIterator<T> // NOLINT
{
  public:
    /* -- WeaklyIncrementable */
    using value_type = T;
    auto operator*() const -> T& {};

    // movable
    SentinelFor(SentinelFor<T>&&) = default; // NOLINT
    auto operator=(
        SentinelFor<T>&& _                   // NOLINT
    ) noexcept -> SentinelFor<T>&
    {
    }

    using difference_type = std::ptrdiff_t;
    auto operator++() -> SentinelFor<T>& {} // ++I
    auto operator++(
        int
    ) -> void
    {
    }
    /* -- SentinelFor */

    /* -- InputOrOutputIterator -- */
    // auto operator*() const -> T& {};

    // semiregular
    SentinelFor(const SentinelFor<T>&) = default; // NOLINT
    SentinelFor(SentinelFor<T>&) = default;       // NOLINT
    // SentinelFor(SentinelFor<T>&&) = default;      // NOLINT
    auto operator=(
        const SentinelFor<T>& _ // NOLINT
    ) noexcept -> SentinelFor<T>&
    {
    }
    SentinelFor() = default;    // NOLINT

    auto operator==(
        const SentinelFor<T>& _ // NOLINT
    ) const -> bool
    {
    }
};

template <typename T>
class SizedSentinelFor // NOLINT
{
  public:
    /* -- WeaklyIncrementable */
    using value_type = T;
    auto operator*() const -> T& {};

    // movable
    SizedSentinelFor(SizedSentinelFor<T>&&) = default; // NOLINT
    auto operator=(
        SizedSentinelFor<T>&& _                        // NOLINT
    ) noexcept -> SizedSentinelFor<T>&
    {
    }

    using difference_type = std::ptrdiff_t;
    auto operator++() -> SizedSentinelFor<T>& {} // ++I
    auto operator++(
        int
    ) -> void
    {
    }
    /* -- SizedSentinelFor */

    /* -- InputOrOutputIterator -- */
    // auto operator*() const -> T& {};

    // semiregular
    SizedSentinelFor(const SizedSentinelFor<T>&) = default; // NOLINT
    SizedSentinelFor(SizedSentinelFor<T>&) = default;       // NOLINT
    // SizedSentinelFor(SizedSentinelFor<T>&&) = default;      // NOLINT
    auto operator=(
        const SizedSentinelFor<T>& _ // NOLINT
    ) noexcept -> SizedSentinelFor<T>&
    {
    }
    SizedSentinelFor() = default;    // NOLINT

    auto operator==(
        const SizedSentinelFor<T>& _ // NOLINT
    ) const -> bool
    {
    }

    auto operator-(
        const SizedSentinelFor<T>& _ // NOLINT
    ) const -> std::ptrdiff_t
    {
        return 0;                    // Dummy implementation
    }
};

TEST(
    IteratorConcepts, concepts
)
{
    using T = int;

    static_assert(std::indirectly_readable<IndirectlyReadable<T>>);
    static_assert(std::indirectly_writable<IndirectlyReadable<T>, T>);

    static_assert(std::weakly_incrementable<WeaklyIncrementable<T>>);
    static_assert(std::incrementable<Incrementable<T>>);

    static_assert(std::input_or_output_iterator<WeaklyIncrementable<T>>);
    static_assert(std::sentinel_for<SentinelFor<T>, SentinelFor<T>>);
    static_assert(std::sized_sentinel_for<SizedSentinelFor<T>, SizedSentinelFor<T>>);
}

TEST(
    Iterator, IteratorAssociatedTypes
)
{
    using vi = std::vector<int>::iterator;

    // static_assert(std::is_same_v<std::incrementable_traits<int>::difference_type, std::ptrdiff_t>);
    static_assert(std::is_same_v<std::incrementable_traits<int*>::difference_type, std::ptrdiff_t>);
    static_assert(std::is_same_v<std::incrementable_traits<vi>::difference_type, std::ptrdiff_t>);

    // static_assert(std::is_same_v<std::indirectly_readable_traits<int>::value_type, int>);
    static_assert(std::is_same_v<std::indirectly_readable_traits<int*>::value_type, int>);
    static_assert(std::is_same_v<std::indirectly_readable_traits<vi>::value_type, int>);

    static_assert(std::is_same_v<std::iter_value_t<int*>, int>);
    static_assert(std::is_same_v<std::iter_reference_t<int*>, int&>);
    static_assert(std::is_same_v<std::iter_difference_t<int*>, std::ptrdiff_t>);
    // std::move(*(int*))
    static_assert(std::is_same_v<std::iter_rvalue_reference_t<int*>, int&&>);

    static_assert(std::is_same_v<std::iter_value_t<vi>, int>);
    static_assert(std::is_same_v<std::iter_reference_t<vi>, int&>);
    static_assert(std::is_same_v<std::iter_difference_t<vi>, std::ptrdiff_t>);
    static_assert(std::is_same_v<std::iter_rvalue_reference_t<vi>, int&&>);
}

TEST(
    Iterator, IteratorPrimitives
)
{
    static_assert(std::is_same_v<
                  std::iterator_traits<std::vector<int>::iterator>::iterator_category,
                  std::random_access_iterator_tag>);
    static_assert(std::is_same_v<
                  std::iterator_traits<std::array<int, 4>::iterator>::iterator_category,
                  std::random_access_iterator_tag>);
    static_assert(std::is_same_v<
                  std::iterator_traits<std::forward_list<int>::iterator>::iterator_category,
                  std::forward_iterator_tag>);
    static_assert(std::is_same_v<
                  std::iterator_traits<std::list<int>::iterator>::iterator_category,
                  std::bidirectional_iterator_tag>);
    static_assert(std::is_same_v<std::iterator_traits<int*>::iterator_category, std::random_access_iterator_tag>);
}

TEST(
    Iterator, ReverseIterator
)
{
    std::vector<int> v{1, 2, 3, 4, 5}; // NOLINT
    auto             it = v.begin();   // NOLINT

    auto rev1 = std::reverse_iterator(it);
    auto rev2 = std::make_reverse_iterator(v.end());
    static_assert(std::is_same_v<decltype(rev1), std::reverse_iterator<decltype(it)>>);
    static_assert(std::is_same_v<decltype(rev2), decltype(rev1)>);
    static_assert(std::is_same_v<decltype(rev1.base()), decltype(it)>);

    EXPECT_EQ(*(rev1.base()), 1);
    *(rev1 - 1) = -1;
    *rev2 = 10;      // NOLINT
    *(rev2 + 1) = 9; // NOLINT
    EXPECT_EQ(*(v.end() - 1), 10);
    EXPECT_EQ(*(v.end() - 2), 9);
    EXPECT_EQ(*(it + 0), -1);
    EXPECT_EQ(*(it + 1), 2);
    EXPECT_EQ(*(it + 2), 3);
    EXPECT_EQ(*(it + 3), 9);
    EXPECT_EQ(*(it + 4), 10);
}

TEST(
    Iterator, BackInserter
)
{
    auto vec = std::vector<int>{1, 2, 3, 4, 5};      // NOLINT
    auto fl = std::forward_list<int>{1, 2, 3, 4, 5}; // NOLINT

    auto back1 = std::back_insert_iterator<decltype(vec)>(vec);
    auto back2 = std::back_inserter(vec);
    static_assert(std::is_same_v<decltype(back1), std::back_insert_iterator<decltype(vec)>>);

    *back1 = 100; // NOLINT
    *back1 = 200; // NOLINT
    back1 = 300;  // NOLINT
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
    EXPECT_EQ(vec[5], 100);
    EXPECT_EQ(vec[6], 200);
    EXPECT_EQ(vec[7], 300);

    // 宣言は可能だが ill-formed (push_back を持たない)
    auto back3 = std::back_insert_iterator<decltype(fl)>(fl);
    auto back4 = std::back_inserter(fl);
    //*back3 = 300; // NOLINT
}

TEST(
    Iterator, FrontInserter
)
{
    auto vec = std::vector<int>{1, 2, 3, 4, 5};      // NOLINT
    auto fl = std::forward_list<int>{1, 2, 3, 4, 5}; // NOLINT

    // vector は push_front を持たない
    auto back1 = std::front_insert_iterator<decltype(vec)>(vec);
    auto back2 = std::front_inserter(vec);
    static_assert(std::is_same_v<decltype(back1), std::front_insert_iterator<decltype(vec)>>);
    //*back1 = 100;     // NOLINT

    auto back3 = std::front_insert_iterator<decltype(fl)>(fl);
    auto back4 = std::front_inserter(fl);
    static_assert(std::is_same_v<decltype(back3), std::front_insert_iterator<decltype(fl)>>);

    *back3 = 100;         // NOLINT
    *back3 = 200;         // NOLINT
    back3 = 300;          // NOLINT

    auto it = fl.begin(); // NOLINT
    EXPECT_EQ(*it++, 300);
    EXPECT_EQ(*it++, 200);
    EXPECT_EQ(*it++, 100);
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 4);
    EXPECT_EQ(*it++, 5);
}

TEST(
    Iterator, Inserter
)
{
    auto vec = std::vector<int>{1, 2, 3, 4, 5};      // NOLINT
    auto fl = std::forward_list<int>{1, 2, 3, 4, 5}; // NOLINT

    auto ins1 = std::insert_iterator<decltype(vec)>(vec, vec.begin());
    auto ins2 = std::inserter(vec, vec.begin());
    static_assert(std::is_same_v<decltype(ins1), std::insert_iterator<decltype(vec)>>);
    static_assert(std::is_same_v<decltype(ins2), std::insert_iterator<decltype(vec)>>);

    *ins1 = 100; // NOLINT
    *ins1 = 200; // NOLINT
    ins1 = 300;  // NOLINT
    EXPECT_EQ(vec[0], 100);
    EXPECT_EQ(vec[1], 200);
    EXPECT_EQ(vec[2], 300);
    EXPECT_EQ(vec[3], 1);
    EXPECT_EQ(vec[4], 2);
    EXPECT_EQ(vec[5], 3);
    EXPECT_EQ(vec[6], 4);
    EXPECT_EQ(vec[7], 5);

    // forward_list は insert を持たない
    auto ins3 = std::insert_iterator<decltype(fl)>(fl, fl.before_begin());
    auto ins4 = std::inserter(fl, fl.before_begin());
    static_assert(std::is_same_v<decltype(ins3), std::insert_iterator<decltype(fl)>>);
    static_assert(std::is_same_v<decltype(ins4), std::insert_iterator<decltype(fl)>>);
}

TEST(
    Iterator, ConstIterator
)
{
    std::vector<int> v{1, 2, 3, 4, 5}; // NOLINT
    auto             it = v.begin();   // NOLINT

#if 0
    auto ci1 = std::basic_const_iterator(it);
    auto ci2 = std::make_const_iterator(it);
    static_assert(std::is_same_v<decltype(ci1), std::basic_const_iterator<decltype(it)>>);
    static_assert(std::is_same_v<decltype(ci2), std::basic_const_iterator<decltype(it)>>);
    static_assert(std::is_same_v<decltype(ci1), std::const_iterator<decltype(it)>>);
    static_assert(std::is_same_v<decltype(ci1.base()), decltype(std::as_const(it))>);

    // iterator_category は std::iterator_traits<Iter>::iterator_category
    // ::iterator_category は contiguous_iterator_tag にはならない
    //   see: https://en.cppreference.com/w/cpp/iterator/iterator_traits.html
    static_assert(std::is_same_v<typename decltype(ci1)::iterator_category, std::random_access_iterator_tag>);
    static_assert(std::is_same_v<typename decltype(ci1)::iterator_concept, std::contiguous_iterator_tag>);

    // iter_value_t は std::iter_value_t<Iter> に移譲されるので元の型になる
    static_assert(std::is_same_v<std::iter_value_t<decltype(ci1)>, int>);

    static_assert(std::is_same_v<decltype(*ci1), const int&>);
#endif
}

TEST(
    Iterator, MoveIterator
)
{
    std::vector<int> v{1, 2, 3, 4, 5}; // NOLINT
    auto             it = v.begin();   // NOLINT

    auto mv1 = std::move_iterator(it);
    auto mv2 = std::make_move_iterator(it);
    static_assert(std::is_same_v<decltype(mv1), std::move_iterator<decltype(it)>>);
    static_assert(std::is_same_v<decltype(mv2), std::move_iterator<decltype(it)>>);
    static_assert(std::is_same_v<decltype(mv1.base()), decltype(std::as_const(it))>);

    static_assert(std::is_same_v<decltype(mv1)::iterator_category, std::random_access_iterator_tag>);
    static_assert(std::is_same_v<decltype(mv1)::iterator_concept, std::random_access_iterator_tag>);

    // iter_value_t は std::iter_value_t<Iter> に移譲されるので元の型になる
    static_assert(std::is_same_v<std::iter_value_t<decltype(mv1)>, int>);

    static_assert(std::is_same_v<decltype(*mv1), int&&>);
}

template <class ForwardIter>
void fire(
    ForwardIter first, ForwardIter last
)
{
    std::copy(first, last, std::ostream_iterator<std::string>{std::cout, " "});
}

TEST(
    Iterator, CountedIterator
)
{
    std::list<std::string> stars{"Pollux", "Arcturus", "Mira", "Aldebaran", "Sun"};

    // counted iterator
    using IT = std::common_iterator<std::counted_iterator<std::list<std::string>::iterator>, std::default_sentinel_t>;

    // stars.begin() から stars.size() - 1 個の要素を表現する counted_iterator
    fire(IT(std::counted_iterator(stars.begin(), stars.size() - 1)), IT(std::default_sentinel)); // NOLINT
}

template <std::ranges::random_access_range R>
constexpr auto trivial_strlen(
    R&& r // NOLINT
) -> std::size_t
{
    auto iter = r.begin();
    while (*iter != std::ranges::range_value_t<R>{})
    {
        ++iter;
    }
    return iter - r.begin();
}

template <std::ranges::random_access_range R>
constexpr auto my_strlen(
    R&& r // NOLINT
) -> std::size_t
{
    if constexpr (std::same_as<std::ranges::sentinel_t<R>, std::unreachable_sentinel_t>)
    {
        return trivial_strlen(std::forward<R>(r));
    }
    else
    {
        return std::ranges::find(std::forward<R>(r), std::ranges::range_value_t<R>{}) - std::ranges::begin(r);
    }
}

TEST(
    Iterator, UnreachableSentinel
)
{
    constexpr static char str[] = "The quick brown fox jumps over a lazy dog.";        // NOLINT
    static_assert(my_strlen(str) == 42);                                               // NOLINT

    constexpr auto unsafe_str = std::ranges::subrange{str, std::unreachable_sentinel}; // NOLINT
    static_assert(my_strlen(unsafe_str) == 42);                                        // NOLINT
}

TEST(
    Iterator, StreamIterators
)
{
    /*
     * istream_iterator
     */
    auto str = std::istringstream("0.1 0.2 0.3 0.4");
    auto ii = std::istream_iterator<double>(str); // NOLINT

    EXPECT_EQ(*(ii++), 0.1);
    EXPECT_EQ(*(ii++), 0.2);
    EXPECT_EQ(*(ii++), 0.3);
    EXPECT_EQ(*(ii++), 0.4);
    EXPECT_EQ(std::istream_iterator<double>(), ii);

    /*
     * ostream_iterator
     */
    std::ostringstream oss;
    auto               oi = std::ostream_iterator<int>(oss, ", ");          // NOLINT
    std::fill_n(oi, 5, 42);                                                 // NOLINT
    EXPECT_EQ(oss.str(), "42, 42, 42, 42, 42, ");

    ::testing::internal::CaptureStdout();                                   // NOLINT
    auto oi2 = std::ostream_iterator<int>(std::cout, "|");                  // NOLINT
    std::fill_n(oi2, 5, 42);                                                // NOLINT
    EXPECT_EQ(::testing::internal::GetCapturedStdout(), "42|42|42|42|42|"); // NOLINT

    //

    /*
     * istreambuf_iterator
     */
    str = std::istringstream("0.1 0.2 0.3 0.4");
    auto ibi = std::istreambuf_iterator(str); // NOLINT

    EXPECT_EQ(*(ibi++), '0');
    EXPECT_EQ(*(ibi++), '.');
    EXPECT_EQ(*(ibi++), '1');
    EXPECT_EQ(*(ibi++), ' ');
    EXPECT_EQ(*(ibi++), '0');
    EXPECT_EQ(*(ibi++), '.');
    EXPECT_EQ(*(ibi++), '2');
    EXPECT_EQ(*(ibi++), ' ');
    EXPECT_EQ(*(ibi++), '0');
    EXPECT_EQ(*(ibi++), '.');
    EXPECT_EQ(*(ibi++), '3');
    EXPECT_EQ(*(ibi++), ' ');
    EXPECT_EQ(*(ibi++), '0');
    EXPECT_EQ(*(ibi++), '.');
    EXPECT_EQ(*(ibi++), '4');
    EXPECT_EQ(std::istreambuf_iterator<char>(), ibi);

    /*
     * ostreambuf_iterator
     */
    oss.str("");
    oss.flush();

    auto obi = std::ostreambuf_iterator<char>(oss);               // NOLINT
    std::fill_n(obi, 5, '5');                                     // NOLINT
    EXPECT_EQ(oss.str(), "55555");

    ::testing::internal::CaptureStdout();                         // NOLINT
    auto obi2 = std::ostreambuf_iterator<char>(std::cout);        // NOLINT
    std::fill_n(obi2, 5, 'X');                                    // NOLINT
    EXPECT_EQ(::testing::internal::GetCapturedStdout(), "XXXXX"); // NOLINT
}

TEST(
    Iterator, IteratorOperations
)
{
    using std::advance;
    using std::distance;
    using std::next;
    using std::prev;

    const std::vector<int> v{1, 2, 3, 4, 5}; // NOLINT
    auto                   it = v.begin();   // NOLINT

    // advance
    advance(it, 2);
    EXPECT_EQ(*it, 3);                                  // NOLINT

    it = v.begin();                                     // NOLINT
    std::ranges::advance(it, 2);
    EXPECT_EQ(*it, 3);                                  // NOLINT

    it = v.begin();                                     // NOLINT
    std::ranges::advance(it, v.end());
    EXPECT_EQ(it, v.end());                             // NOLINT

    it = v.begin();
    std::ranges::advance(it, 100, std::ranges::end(v)); // NOLINT
    EXPECT_EQ(it, v.end());                             // NOLINT

    //
    // distance
    EXPECT_EQ(5, distance(v.begin(), v.end()));              // NOLINT
    EXPECT_EQ(5, std::ranges::distance(v.begin(), v.end())); // NOLINT

    //
    // next
    it = v.begin();
    EXPECT_EQ(*next(it), 2);                                 // NOLINT
    EXPECT_EQ(*next(it, 2), 3);                              // NOLINT
    EXPECT_EQ(*std::ranges::next(it), 2);                    // NOLINT
    EXPECT_EQ(*std::ranges::next(it, 2), 3);                 // NOLINT
    EXPECT_EQ(std::ranges::next(it, 100, v.end()), v.end()); // NOLINT

    //
    // next
    auto it2 = v.end();
    EXPECT_EQ(*prev(it2), 5);                                     // NOLINT
    EXPECT_EQ(*prev(it2, 2), 4);                                  // NOLINT
    EXPECT_EQ(*std::ranges::prev(it2), 5);                        // NOLINT
    EXPECT_EQ(*std::ranges::prev(it2, 2), 4);                     // NOLINT
    EXPECT_EQ(std::ranges::prev(it2, 100, v.begin()), v.begin()); // NOLINT
}

TEST(
    Iterator, RangeAccess
)
{
    using std::begin, std::cbegin;
    using std::data;
    using std::empty;
    using std::end, std::cend;
    using std::rbegin, std::crbegin;
    using std::rend, std::crend;
    using std::size, std::ssize;

    auto v = std::vector<int>{};           // NOLINT
    auto a = std::array<int, 5>{};         // NOLINT
    int  x[5];                             // NOLINT
    auto i = std::initializer_list<int>{}; // NOLINT

    // begin
    static_assert(std::is_same_v<decltype(begin(v)), std::vector<int>::iterator>);           // NOLINT
    static_assert(std::is_same_v<decltype(begin(a)), std::array<int, 5>::iterator>);         // NOLINT
    static_assert(std::is_same_v<decltype(begin(x)), int*>);                                 // NOLINT
    static_assert(std::is_same_v<decltype(begin(i)), std::initializer_list<int>::iterator>); // NOLINT

    // cbegin
    static_assert(std::is_same_v<decltype(cbegin(v)), std::vector<int>::const_iterator>);           // NOLINT
    static_assert(std::is_same_v<decltype(cbegin(a)), std::array<int, 5>::const_iterator>);         // NOLINT
    static_assert(std::is_same_v<decltype(cbegin(x)), const int*>);                                 // NOLINT
    static_assert(std::is_same_v<decltype(cbegin(i)), std::initializer_list<int>::const_iterator>); // NOLINT

    // end
    static_assert(std::is_same_v<decltype(end(v)), std::vector<int>::iterator>);           // NOLINT
    static_assert(std::is_same_v<decltype(end(a)), std::array<int, 5>::iterator>);         // NOLINT
    static_assert(std::is_same_v<decltype(end(x)), int*>);                                 // NOLINT
    static_assert(std::is_same_v<decltype(end(i)), std::initializer_list<int>::iterator>); // NOLINT

    // cend
    static_assert(std::is_same_v<decltype(cend(v)), std::vector<int>::const_iterator>);           // NOLINT
    static_assert(std::is_same_v<decltype(cend(a)), std::array<int, 5>::const_iterator>);         // NOLINT
    static_assert(std::is_same_v<decltype(cend(x)), const int*>);                                 // NOLINT
    static_assert(std::is_same_v<decltype(cend(i)), std::initializer_list<int>::const_iterator>); // NOLINT

    // rbegin
    static_assert(std::is_same_v<decltype(rbegin(v)), std::vector<int>::reverse_iterator>);   // NOLINT
    static_assert(std::is_same_v<decltype(rbegin(a)), std::array<int, 5>::reverse_iterator>); // NOLINT
    static_assert(std::is_same_v<decltype(rbegin(x)), std::reverse_iterator<int*>>);          // NOLINT
    static_assert(std::is_same_v<decltype(rbegin(i)), std::reverse_iterator<const int*>>);    // NOLINT

    // crbegin
    static_assert(std::is_same_v<decltype(crbegin(v)), std::vector<int>::const_reverse_iterator>);   // NOLINT
    static_assert(std::is_same_v<decltype(crbegin(a)), std::array<int, 5>::const_reverse_iterator>); // NOLINT
    static_assert(std::is_same_v<decltype(crbegin(x)), std::reverse_iterator<const int*>>);          // NOLINT
    static_assert(std::is_same_v<decltype(crbegin(i)),
                                 std::reverse_iterator<const int*>>);                                // NOLINT

    // size
    static_assert(std::is_same_v<decltype(size(v)), std::size_t>); // NOLINT
    static_assert(std::is_same_v<decltype(size(a)), std::size_t>); // NOLINT
    static_assert(std::is_same_v<decltype(size(x)), std::size_t>); // NOLINT
    static_assert(std::is_same_v<decltype(size(i)), std::size_t>); // NOLINT

    // ssize
    static_assert(std::is_same_v<decltype(ssize(v)), std::ptrdiff_t>); // NOLINT
    static_assert(std::is_same_v<decltype(ssize(a)), std::ptrdiff_t>); // NOLINT
    static_assert(std::is_same_v<decltype(ssize(x)), std::ptrdiff_t>); // NOLINT
    static_assert(std::is_same_v<decltype(ssize(i)), std::ptrdiff_t>); // NOLINT

    // data
    static_assert(std::is_same_v<decltype(data(v)), int*>);                      // NOLINT
    static_assert(std::is_same_v<decltype(data(a)), int*>);                      // NOLINT
    static_assert(std::is_same_v<decltype(data(x)), int*>);                      // NOLINT
    static_assert(std::is_same_v<decltype(data(i)), const int*>);                // NOLINT
    static_assert(std::is_same_v<decltype(data(std::as_const(v))), const int*>); // NOLINT
    static_assert(std::is_same_v<decltype(data(std::as_const(a))), const int*>); // NOLINT
    static_assert(std::is_same_v<decltype(data(std::as_const(x))), const int*>); // NOLINT
    static_assert(std::is_same_v<decltype(data(std::as_const(i))), const int*>); // NOLINT
}
} // namespace
