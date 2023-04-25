#include <vector>
#include <lib/stl_algorithms.h>
#include <gtest/gtest.h>


TEST(Stl, all_of) {
    std::vector<int> l = {2, 4, 6, 10, 54};
    ASSERT_TRUE(stl::all_of(l.begin(), l.end(), [](int i) { return i % 2 == 0; }));
}

TEST(Stl, any_of) {
    std::vector<int> l = {2, 4, 6, 10, 54};
    ASSERT_TRUE(stl::any_of(l.begin(), l.end(), [](int i) { return i == 54; }));
}

TEST(Stl, none_of) {
    std::vector<int> l = {2, 4, 6, 10, 54};
    ASSERT_TRUE(stl::none_of(l.begin(), l.end(), [](int i) { return i % 2 == 1; }));
}

TEST(Stl, one_of) {
    std::vector<int> l = {2, 4, 6, 10, 54, 67};
    ASSERT_TRUE(stl::one_of(l.begin(), l.end(), [](int i) { return i % 2 == 1; }));
}

TEST(Stl, is_sorted) {
    std::vector<int> l = {2, 4, 6, 10, 54, 67};
    ASSERT_TRUE(stl::is_sorted(l.begin(), l.end(), [](int i, int j) { return i < j; }));
}

TEST(Stl, is_partitioned) {
    std::vector<int> l = {2, 4, 6, 10, 54, 67, 53, 87, 89};
    ASSERT_TRUE(stl::is_partitioned(l.begin(), l.end(), [](int i) { return i % 2 == 0; }));
}

TEST(Stl, find_not) {
    std::vector<int> l = {2, 2, 2, 3, 54, 67, 53, 87, 89};
    ASSERT_EQ(*stl::find_not(l.begin(), l.end(), 2), 3);
}

TEST(Stl, find_backward) {
    std::vector<int> l = {2, 2, 2, 3, 54, 67, 53, 87, 89};
    ASSERT_EQ(*stl::find_backward(l.begin(), l.end(), 2), 2);
    ASSERT_EQ(l.end() - stl::find_backward(l.begin(), l.end(), 2), 7);
}

TEST(Stl, is_palindrome) {
    std::vector<int> l = {1, 2, 2, 1};
    ASSERT_TRUE(stl::is_palindrome(l.begin(), l.end(), [](int i, int j) { return i == j; }));
}

TEST(python, xrange) {
    auto x = stl::xrange(1, 6);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> test = {1, 2, 3, 4, 5};
    ASSERT_TRUE(v == test);
}

TEST(python, zip) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<char> b = {'a', 'b', 'c'};
    std::vector<std::pair<int, char>> v = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::vector<std::pair<int, char>> test;
    for (auto i : stl::zip(a, b)) {
        test.push_back({i.first, i.second});
    }
    ASSERT_TRUE(v == test);
}
