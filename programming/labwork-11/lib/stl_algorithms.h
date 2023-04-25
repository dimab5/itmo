#pragma once
#include <iostream>

namespace stl {

    template<typename Iterator, typename Predicate>
    bool all_of(Iterator begin, Iterator end, Predicate condition) {
        for (auto it = begin; it != end; it++) {
            if (!condition(*it)) {
                return false;
            }
        }
        return true;
    }

    template<typename Iterator, typename Predicate>
    bool any_of(Iterator begin, Iterator end, Predicate condition) {
        for (auto it = begin; it != end; it++) {
            if (condition(*it)) {
                return true;
            }
        }
        return false;
    }

    template<typename Iterator, typename Predicate>
    bool none_of(Iterator begin, Iterator end, Predicate condition) {
        for (auto it = begin; it != end; it++) {
            if (condition(*it)) {
                return false;
            }
        }
        return true;
    }

    template<typename Iterator, typename Predicate>
    bool one_of(Iterator begin, Iterator end, Predicate condition) {
        size_t cnt = 0;
        for (auto it = begin; it != end; it++) {
            if (condition(*it)) {
                cnt++;
            }
        }
        return cnt == 1;
    }

    template<typename Iterator, typename Compare>
    bool is_sorted(Iterator begin, Iterator end, Compare comp) {
        if (begin == end) {
            return true;
        }

        Iterator prev = begin;
        ++begin;
        for (; begin != end; ++prev, ++begin) {
            if (!comp(*prev, *begin)) {
                return false;
            }
        }
        return true;
    }

    template<typename Iterator, typename Predicate>
    bool is_partitioned(Iterator begin, Iterator end, Predicate condition) {
        while (begin != end && condition(*begin++));
        while (begin != end) {
            if (condition(*begin++)) {
                return false;
            }
        }
        return true;
    }

    template<typename Iterator, typename Type>
    Iterator find_not(Iterator begin, Iterator end, const Type &value) {
        while (begin != end && *begin++ == value);
        return --begin;
    }

    template<typename Iterator, typename Type>
    Iterator find_backward(Iterator begin, Iterator end, const Type &value) {
        while (begin != end && *end-- != value);
        return ++end;
    }

    template<typename Iterator, typename Predicate>
    bool is_palindrome(Iterator begin, Iterator end, Predicate condition) {
        size_t size = end - begin;
        for (size_t i = 0; i < size / 2; i++) {
            if (!condition(*(begin + i), *(end - 1 - i))) {
                return false;
            }
        }
        return true;
    }


    template<typename Type>
    class Xrange {
    public:
        Xrange() = default;

        ~Xrange() = default;

        class iterator : public std::iterator<std::input_iterator_tag, Type> {
        public:
            iterator(Type value, Type begin, Type end, Type step) : value_(value), begin_(begin), end_(end), step_(step) {}

            iterator(const iterator &other)
                    :
                    value_(other.value_),
                    end_(other.end_),
                    step_(other.step_) {}

            ~iterator() = default;

            iterator &operator++() {
                if (step_ > 0) {
                    if (value_ + step_ < end_) {
                        value_ += step_;
                    } else {
                        value_ = end_;
                    }
                } else {
                    if (value_ + step_ > end_) {
                        value_ += step_;
                    } else {
                        value_ = end_;
                    }
                }
                return *this;
            }

            iterator operator++(int) {
                iterator copy(*this);
                ++(*this);
                return copy;
            }

            bool operator==(const iterator &other) const {
                return value_ == other.value_;
            }

            bool operator!=(const iterator &other) const {
                return value_ != other.value_;
            }

            Type operator*() const {
                return value_;
            }

        private:
            Type value_;
            Type begin_;
            Type end_;
            Type step_;
        };

        Xrange(Type begin, Type end, Type step) : begin_(begin), end_(end), step_(step) {}

        explicit Xrange(Type end) : end_(end) {}

        Xrange(Type begin, Type end) : begin_(begin), end_(end) {}

        iterator begin() const {
            return iterator(begin_, begin_, end_, step_);
        }

        iterator end() const {
            return iterator(end_, begin_, end_, step_);
        }

    private:
        Type begin_ = 0;
        Type end_;
        Type step_ = 1;
    };

    template<typename Type>
    Xrange<Type> xrange(Type end) {
        return Xrange<Type>(0, end, 1);
    }

    template<typename Type>
    Xrange<Type> xrange(Type begin, Type end, Type step) {
        return Xrange<Type>(begin, end, step);
    }

    template<typename Type>
    Xrange<Type> xrange(Type begin, Type end) {
        return Xrange<Type>(begin, end, 1);
    }


    template<typename Container1, typename Container2>
    class Zip {
    public:
        template<typename It1, typename It2>
        class iterator {
        public:
            iterator(It1 iterator1, It2 iterator2) : it1(iterator1), it2(iterator2) {}

            iterator &operator++() {
                ++it1;
                ++it2;
                return *this;
            }

            bool operator!=(const iterator &other) const {
                return it1 != other.it1 && it2 != other.it2;
            }

            bool operator==(const iterator &other) const {
                return !(*this != other);
            }

            std::pair<typename std::iterator_traits<It1>::value_type,
                    typename std::iterator_traits<It2>::value_type> operator*() const {
                return {*it1, *it2};
            }

        private:
            It1 it1;
            It2 it2;
        };

        Zip(Container1 &C1, Container2 &C2) : Cont1(C1), Cont2(C2) {}

        auto begin() const {
            return iterator<typename Container1::iterator, typename Container2::iterator>(std::begin(Cont1),
                                                                                          std::begin(Cont2));
        }

        auto end() const {
            return iterator<typename Container1::iterator, typename Container2::iterator>(std::end(Cont1),
                                                                                          std::end(Cont2));
        }

    private:
        Container1 &Cont1;
        Container2 &Cont2;
    };

    template<typename Container1, typename Container2>
    Zip<Container1, Container2> zip(Container1 &C1, Container2 &C2) {
        return Zip<Container1, Container2>(C1, C2);
    }

};