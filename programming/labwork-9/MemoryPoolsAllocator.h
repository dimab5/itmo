#pragma once

size_t default_size_of_pool;
size_t default_size_of_chunk = 1;

template<typename T>
class Pool {
public:
    using value_type = T;
    using pointer = T*;
    using interval = std::pair<size_t, size_t>;

    Pool(size_t size_of_pool = default_size_of_pool, size_t size_of_chunk = default_size_of_chunk) {
        size_of_intervals_ = size_of_pool;
        size_of_pool_ = size_of_pool;
        size_of_chunk_ = size_of_chunk;
        size_t number_bytes = size_of_pool * size_of_chunk_ * sizeof(value_type);
        begin_date_ = reinterpret_cast<pointer>(malloc(number_bytes));
        intervals_ = new interval[size_of_pool];
        deallocate(begin_date_, size_of_pool_);
    }

    ~Pool() {
        delete[] begin_date_;
        delete[] intervals_;
    }

    pointer allocate(size_t memory) {
        for (size_t i = 0; i < size_of_intervals_; i++) {
            size_t &l = intervals_[i].first;
            size_t &r = intervals_[i].second;

            if (r - l == memory) {
                erase(intervals_, i, size_of_intervals_);
                return (begin_date_ + l * size_of_chunk_);
            }

            if (r - l > memory) {
                size_t tmp = l;
                l += memory;
                return (begin_date_ + tmp * size_of_chunk_);
            }
        }

        return nullptr;
    }

    void deallocate(pointer ptr, size_t memory) {
        size_t deallocated_first = (ptr - begin_date_) / size_of_chunk_;
        size_t deallocated_last = deallocated_first + memory;

        for (int i = 0; i < size_of_intervals_; i++) {
            size_t &l = intervals_[i].first;
            size_t &r = intervals_[i].second;

            if (deallocated_last == l) {
                l = deallocated_first;
                return;
            }

            if (deallocated_first == r) {
                r = deallocated_last;
                i++;
                if (i < size_of_intervals_) {
                    if (intervals_[i].first == r) {
                        r = intervals_[i].second;
                        erase(intervals_, i, size_of_intervals_);
                    }
                }
                return;
            }

            if (deallocated_last < l) {
                insert(intervals_, std::make_pair(deallocated_first, deallocated_last), i, size_of_intervals_);
                return;
            }

            if (l == deallocated_last) {
                r = deallocated_last;
                return;
            }
        }

        insert(intervals_, std::make_pair(deallocated_first, deallocated_last), 0, size_of_intervals_);
    }

    pointer GetBeginDate() {
        return begin_date_;
    }

    void set_size_of_pool(size_t size_of_pool) {
        size_of_pool_ = size_of_pool;
    }

    void set_size_of_chunk(size_t size_of_chunk) {
        size_of_chunk_ = size_of_chunk;
    }

private:
    interval *intervals_ = nullptr;
    size_t size_of_intervals_;
    size_t size_of_pool_;
    size_t size_of_chunk_;
    pointer begin_date_;

    void erase(interval *arr, size_t pos, size_t &size) {
        if (pos > size) return;
        size--;
        for (size_t i = pos; i < size; i++) {
            arr[i] = arr[i + 1];
        }
    }

    void insert(interval *arr, interval value, size_t pos, size_t &size) {
        if (size >= size_of_pool_) {
            return;
        }
        for (size_t i = size - 1; i >= pos; i--) {
            arr[i + 1] = arr[i];
        }
        arr[pos] = value;
        size++;
    }
};

template<typename T,
        size_t number_of_pools_,
        size_t size_of_pool_,
        size_t size_of_chunk_
>
class MemoryPoolsAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using pool = Pool<value_type>;

    template<class U>
    struct rebind {
        using other = MemoryPoolsAllocator<U, number_of_pools_, size_of_pool_, size_of_chunk_>;
    };

    MemoryPoolsAllocator() {
        pools_ = new pool[number_of_pools_];
//        for (size_t i = 0; i < number_of_pools_; i++) {
//            Set_Pool(i, size_of_pool_, size_of_chunk_);
//        }
    }

    ~MemoryPoolsAllocator() {
        delete[] pools_;
    }

    void Set_Pool(size_t number, size_t size, size_t size_of_chunk) {
        pools_[number].set_size_of_pool(size);
        pools_[number].set_size_of_chunk(size_of_chunk);
    }

    pointer allocate(size_t n) {
        size_t memory = NeedBlocksFor(n);

        for (size_t i = 0; i < number_of_pools_; i++) {
            pointer returned_pointer = pools_[i].allocate(memory);

            if (returned_pointer) {
                return returned_pointer;
            }
        }

        throw std::bad_alloc();
    }

    void deallocate(pointer ptr, size_t n) noexcept {
        size_t memory = NeedBlocksFor(n);

        for (size_t i = 0; i < number_of_pools_; i++) {
            if (ptr > pools_[i].GetBeginDate()) {
                pools_[i].deallocate(ptr, memory);
            }
        }
    }

private:
    pool *pools_;

    size_t NeedBlocksFor(size_t n) {
        return (n + size_of_chunk_ - 1) / size_of_chunk_;
    }
};