#include <lib/buffer.h>
#include <gtest/gtest.h>


TEST(Buffer, push_back) {
    CCircularBuffer<int> buff(3);
    buff.push_back(1);
    ASSERT_TRUE(*(buff.end() - 1) == 1);
    buff.push_back(2);
    ASSERT_TRUE(*(buff.end() - 1) == 2);
    buff.push_back(3);
    ASSERT_TRUE(*(buff.end() - 1) == 3);
    buff.push_back(4);
    ASSERT_TRUE(*buff.begin() == 4);
    CCircularBuffer<int> buff1(3);
    buff1 = {4, 2, 3};
    ASSERT_TRUE(buff == buff1);
}

TEST(Buffer, push_front) {
    CCircularBuffer<int> buff(3);
    buff.push_front(1);
    ASSERT_TRUE(*buff.begin() == 1);
    buff.push_front(2);
    ASSERT_TRUE(*buff.begin() == 2);
    buff.push_front(3);
    ASSERT_TRUE(*buff.begin() == 3);
}

TEST(Buffer, empty) {
    CCircularBuffer<int> buff(5);
    ASSERT_TRUE(buff.empty() == true);
}

TEST(Buffer, full) {
    CCircularBuffer<int> buff(5);
    buff.insert(buff.begin(), 5, 1);
    ASSERT_TRUE(buff.full() == true);
}

TEST(Buffer, pop_back) {
    CCircularBuffer<int> buff(2, 1);
    buff.pop_back();
    ASSERT_TRUE(buff.size() == 1);
    buff.pop_back();
    ASSERT_TRUE(buff.empty() == true);
}

TEST(Buffer, pop_front) {
    CCircularBuffer<int> buff(2, 1);
    buff.pop_front();
    ASSERT_TRUE(buff.size() == 1);
    buff.pop_front();
    ASSERT_TRUE(buff.empty() == true);
}

TEST(Buffer, BeginEnd) {
    CCircularBuffer<int> buff(3);
    buff = {1, 2, 3};
    ASSERT_TRUE(buff.front() == 1);
    ASSERT_TRUE(buff.back() == 3);
}

TEST(Buffer, size) {
    CCircularBuffer<int> buff(3);
    ASSERT_TRUE(buff.size() == 0);
    buff.push_back(1);
    ASSERT_TRUE(buff.size() == 1);
    buff.push_front(2);
    ASSERT_TRUE(buff.size() == 2);
}

TEST(Buffer, capacity) {
    CCircularBuffer<int> buff(3);
    ASSERT_TRUE(buff.capacity() == 3);
}

TEST(Buffer, clear) {
    CCircularBuffer<int> buff(5);
    buff = {1, 2, 3, 4, 5};
    ASSERT_FALSE(buff.empty());
    buff.clear();
    ASSERT_TRUE(buff.empty());
}

TEST(Buffer, access_operator) {
    CCircularBuffer<int> buff(5);
    buff = {1, 2, 3, 4, 5};
    ASSERT_TRUE(buff[3] == 4);
    ASSERT_TRUE(buff[1] == 2);
}

TEST(Buffer, insert) {
    CCircularBuffer<int> buff(5);
    buff = {1, 2};
    buff.insert(buff.begin() + 2, 5);
    ASSERT_TRUE(buff[2] == 5);
    buff.insert(buff.begin(), 2, 7);
    ASSERT_TRUE(buff[0] == 7 && buff[1] == 7);
    ASSERT_TRUE(buff.full());
}

TEST(Buffer, erase) {
    CCircularBuffer<int> buff(5);
    buff = {1, 2, 3, 4, 5};
    buff.erase(buff.begin() + 3);
    ASSERT_TRUE(buff[3] == 5);
    buff.erase(buff.begin(), buff.end() - 1);
    ASSERT_TRUE(buff[0] == 5);
    buff.erase(buff.begin(), buff.end());
    ASSERT_TRUE(buff.empty());
}

TEST(Buffer, equal) {
    CCircularBuffer<int> buff1(4);
    CCircularBuffer<int> buff2(4);
    ASSERT_TRUE(buff1 == buff2);
    buff1 = {1, 2, 3, 4};
    buff2 = {1, 2, 3, 4};
    ASSERT_TRUE(buff1 == buff2);
    buff1.push_back(5);
    ASSERT_FALSE(buff1 == buff2);
}

TEST(Buffer, not_equal) {
    CCircularBuffer<int> buff1(4);
    CCircularBuffer<int> buff2(4);
    ASSERT_FALSE(buff1 != buff2);
    buff1 = {1, 2, 3, 4};
    buff2 = {1, 2, 3, 4};
    ASSERT_FALSE(buff1 != buff2);
    buff1.push_back(5);
    ASSERT_TRUE(buff1 != buff2);
}

TEST(Iterator, increment) {
    CCircularBuffer<int> buff(5);
    buff = {1, 2, 3, 4, 5};
    CCircularBuffer<int>::Iterator it(buff);
    it = buff.begin();
    ASSERT_TRUE(*it == 1);
    it++;
    ASSERT_TRUE(*it == 2);
}

TEST(Iterator, decrement) {
    CCircularBuffer<int> buff(5);
    buff = {1, 2, 3, 4, 5};
    CCircularBuffer<int>::Iterator it(buff);
    it = buff.end() - 1;
    ASSERT_TRUE(*it == 5);
    it--;
    ASSERT_TRUE(*it == 4);
}

TEST(Iterator, plus) {
    CCircularBuffer<int> buff(5);
    buff = {1, 2, 3, 4, 5};
    CCircularBuffer<int>::Iterator it(buff);
    it = buff.begin();
    ASSERT_TRUE(*it == 1);
    it += 3;
    ASSERT_TRUE(*it == 4);
}

TEST(Iterator, minus) {
    CCircularBuffer<int> buff(5);
    buff = {1, 2, 3, 4, 5};
    CCircularBuffer<int>::Iterator it(buff);
    it = buff.end() - 1;
    ASSERT_TRUE(*it == 5);
    it -= 2;
    ASSERT_TRUE(*it == 3);
}

TEST(Iterator, access_operator) {
    CCircularBuffer<int> buff(5);
    buff = {1, 2, 3, 4, 5};
    CCircularBuffer<int>::Iterator it(buff);
    it = buff.begin();
    ASSERT_TRUE(it[0] == 1);
    ASSERT_TRUE(it[3] == 4);
    it++;
    ASSERT_TRUE(it[3] = 5);
}

TEST(Iterator, equal) {
    CCircularBuffer<int> buff(5);
    buff = {1, 2, 3, 4, 5};
    CCircularBuffer<int>::Iterator it1(buff);
    it1 = buff.begin();
    CCircularBuffer<int>::Iterator it2(buff);
    it2 = buff.begin();
    ASSERT_TRUE(it1 == it2);
    it1 += 2;
    it2 += 2;
    ASSERT_TRUE(it1 == it2);
    it1++;
    ASSERT_TRUE(it1 != it2);
}

TEST(Iterator, compare) {
    CCircularBuffer<int> buff(5);
    buff = {1, 2, 3, 4, 5};
    CCircularBuffer<int>::Iterator it1(buff);
    it1 = buff.begin();
    CCircularBuffer<int>::Iterator it2(buff);
    it2 = buff.begin() + 1;
    ASSERT_LE(*it1, *it2);
    it1 += 2;
    ASSERT_GT(*it1, *it2);
}

TEST(BufferExt, expansion) {
    CCircularBufferExt<int> buff(3);
    buff = {1, 2, 3};
    ASSERT_EQ(buff.size(), 3);
    ASSERT_EQ(buff.capacity(), 3);
    buff.push_back(4);
    ASSERT_EQ(buff.size(), 4);
    ASSERT_EQ(buff.capacity(), 6);
}