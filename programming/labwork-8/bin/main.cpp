#include <lib/buffer.h>
#include <iostream>


int main(int argc, char** argv) {

    CCircularBuffer<int> buff(5);
//    std::sort(buff.begin(), buff.end());
//    for (auto i : buff) std::cout << i << ' ';
//    CCircularBuffer<std::string> buff(5);
//    buff = {"123", "123345", "asdfgh", "sd", "qwer"};
//    for (auto s : buff) {
//        std::cout << s << ' ';
//    }
//    CCircularBuffer<int> buff(5);
//    buff.push_back(5);
//    buff.push_back(2);
//    buff.push_back(1);
//    buff.push_back(4);
//    buff.push_back(3);
//    CCircularBuffer<int>::Iterator it(buff);
//    std::sort(buff.begin(), buff.end());
//    for (auto i : buff) {
//        std::cout << i << ' ';
//    }
//    std::cout << *(buff.end() - 1);

//    CCircularBuffer<int> buff(3);
//    buff = {3, 2, 1};3
//    std::sort(buff.begin(), buff.end());
//    CCircularBuffer<int, std::allocator<int>> buff(5);
//    buff = {1, 2, 3, 4, 5};
//    v.push_back(1);
//    std::vector<int>::iterator i = v.begin();
//    std::vector<int>::iterator ii = v.end();
//    std::sort(i, ii);
//    CCircularBuffer<int, std::allocator<int>> test(5);
//    CCircularBuffer<int, std::allocator<int>>::Iterator it(test);
//    test.push_back(30);
//    test.push_back(40);
//    test.push_back(10);
//    test.push_back(20);
//    test.push_back(50);
//    test.push_back(60);
//    it = test.begin();
//    it -= 1;
//    std::cout << it[0];
//    CCircularBufferExt<int, std::allocator<int>> testEx(5);
//    CCircularBufferExt<int, std::allocator<int>>::Iterator it;
//    for (int i = 0; i < 10; i++) {
//        testEx.push_back(i);
//    }
//    std::cout << it[0];
//    testEx.insert(testEx.begin() + 6, 5);
//    testEx.push_front(10);
//    std::cout << testEx.size() << '\n';
//    std::cout << testEx.capacity() << '\n';
//    for (const auto& it: testEx) {
//        std::cout << it << '\n';
//    }
//    CCircularBufferExt<int, std::allocator<int>> testEx1(10);
//    std::cout << (testEx == testEx1) << '\n';
//    test.push_back(30);
//    test.push_back(40);
//    test.push_back(10);
//    test.push_back(20);
//    test.push_back(50);
//    test.push_back(60);
//    std::cout << *it << '\n';
//    for (const auto& iter : test) std::cout << iter << '\n';
//    CCircularBuffer<int, std::allocator<int>>::Iterator it1(test);
//    it1 = test.end() - 1;
//    std::cout << *it1 << '\n';
//    std::cout << *(test.end() - 1) << '\n';
//    it1 = test.end();
//    for (it = test.begin(); it != test.end(); it++) {
//        std::cout << *it << '\n';
//    }
//    it1 = test.begin() + 1;
//    std::cout << (it == it1);
//    std::cout << (it1 > it);
//    for (int j = 0; j < 10; j++) {
//        std::cout << *it << '\n';
//        it++;
//    }
//    CCircularBufferExt<int, std::allocator<int>>::Iterator itext(testEx);
//    testEx.push_back(1);
//    testEx.push_back(2);
//    itext = testEx.begin();
//    ++itext;
//    std::cout << itext[0];
//    it = test.begin();
//    it = test.begin() + 1;
//    std::cout << it[0];
//    for ( ; it != test.end(); it++) {
//    }
//    for (it : test) {
//        std::cout << it << '\n';
//    }
//    test.push_back(9);
//    test.push_back(11);
//    test.push_front(1);
//    test.insert(test.begin() + 1, 100);
//    test.insert(test.begin() + 3, 200);
//    test.insert(test.begin() + 1, 3, 50);
//    test.pop_back();
//    test.pop_front();
//    test.erase(test.begin());
//    test.erase(test.begin() + 1, test.begin() + 3);
//    std::sort(test.begin(), test.end());
//    for (it = test.begin(); it != test.end(); it++) {
//        std::cout << *it << '\n';
//    }
//    CCirtucalBuffer<int, std::allocator<int>> test1(10);
//    test.push_back(5);
//    test1.push_back(5);
//    std::cout << (test == test1) << '\n';
//    test.push_back(9);
//    test.push_back(11);
//    test.push_front(1);
//    test.pop_back();
//    test.pop_front();
//    std::cout << test[0] << '\n';
//    std::cout << test[1] << '\n';
//    std::cout << test[2] << '\n';
//    test.pop_back();
//    std::cout << test.size() << '\n';
//    std::cout << test.front() << '\n';
//    std::cout << test.back() << '\n';
//    test.clear();
//    std::cout << test.front();

}




