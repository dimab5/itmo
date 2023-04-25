#include <iostream>


template<typename Type, class Allocator = std::allocator<Type>>
class CCircularBuffer {
public:
    using iterator = Type*;
    using const_iterator = const Type*;
    using reference = Type&;
    using const_reference = const Type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using allocator_type = Allocator;

    class Iterator : public CCircularBuffer<Type, std::allocator<Type>> {
    public:
        explicit Iterator(const CCircularBuffer<Type, std::allocator<Type>>& Object)
                : CCircularBuffer<Type, std::allocator<Type>>(Object) {
            this->size_ = 0;
            this->capacity_ = Object.capacity_;
            this->buffer = this->b_allocator.allocate(Object.capacity_);
            this->first = Object.buffer;
            this->last = Object.last;
            this->current = Object.buffer;
            for (size_t i = 0; i < Object.capacity_; i++) {
                this->push_back(*(Object.buffer + i));
            }
        };

        Iterator() : CCircularBuffer<Type, std::allocator<Type>>() {};

        Iterator(iterator it) : CCircularBuffer<Type, std::allocator<Type>>() {
            this->iter_ = it;
        }

        iterator Get() const {
            return this->iter_;
        }

        void operator++() {
            if (this->iter_ == this->end() - 1) {
                this->iter_ = this->begin();
            }
            else {
                this->iter_++;
            }
        }

        void operator++(Type) {
            CCircularBuffer copy {*this};
            ++(*this);
        }

        void operator--() {
            if (this->iter_ == this->begin()) {
                this->iter_ = this->end() - 1;
            }
            else {
                this->iter_--;
            }
        }

        void operator--(Type) {
            CCircularBuffer copy {*this};
            --(*this);
        }

        void operator+(int n) {
            this->iter_ += n;
            while (this->iter_ > this->end() - 1) {
                this->iter_ -= this->capacity_;
            }
        }

        void operator+=(int n) {
            this->iter_ += n;
            while (this->iter_ > this->end() - 1) {
                this->iter_ -= this->capacity_;
            }
        }

        void operator-(int n) {
            this->iter_ -= n;
            while (this->iter_ < this->begin()) {
                this->iter_ += this->capacity_;
            }
        }

        void operator-=(int n) {
            this->iter_ -= n;
            while (this->iter_ < this->begin()) {
                this->iter_ += this->capacity_;
            }
        }

        Iterator operator+(const CCircularBuffer<Type, Allocator>::Iterator& it) {
            return Iterator(this->iter_ + it.iter_);
        }

        Iterator operator-(CCircularBuffer<Type, Allocator>::Iterator& it) {
            return Iterator(this->iter_ - it.iter_);
        }

        reference operator*() {
            return *(this->iter_);
        }

        virtual reference operator[](size_t num) {
            return *(this->iter_ + num);
        }

        virtual Iterator& operator=(iterator Other_Iterator) {
            this->iter_ = Other_Iterator;
            return *this;
        }

        virtual Iterator& operator=(CCircularBuffer<Type, Allocator>::Iterator& it) {
            this->iter_ = it.iter_;
            return *this;
        }

        bool operator==(typename CCircularBuffer<Type, std::allocator<Type>>::Iterator left) {
            return left.iter_ == this->iter_;
        }

        bool operator!=(typename CCircularBuffer<Type, std::allocator<Type>>::Iterator left) {
            return left.iter_ != this->iter_;
        }

        bool operator==(iterator left) {
            return left == this->iter_;
        }

        bool operator!=(iterator left) {
            return left != *this;
        }

        bool operator>(typename CCircularBuffer<Type, std::allocator<Type>>::Iterator left) {
            return left.iter_ > this->iter_;
        }

        bool operator<=(typename CCircularBuffer<Type, std::allocator<Type>>::Iterator left) {
            return !(left > *this);
        }

        bool operator<(typename CCircularBuffer<Type, std::allocator<Type>>::Iterator left) {
            return left.iter_ < this->iter_;
        }

        bool operator>=(typename CCircularBuffer<Type, std::allocator<Type>>::Iterator left) {
            return !(left < *this);
        }

        friend bool operator==(Type* left, typename CCircularBuffer<Type, std::allocator<Type>>::Iterator right) {
            return left == right.Get();
        }

        friend bool operator!=(Type* left, typename CCircularBuffer<Type, std::allocator<Type>>::Iterator right) {
            return !(left == right);
        }

    protected:
        iterator iter_;
    };

    explicit CCircularBuffer(size_t capacity)
            : size_(0),
              capacity_(capacity),
              buffer(b_allocator.allocate(capacity)),
              first(buffer),
              last(buffer + capacity),
              current(buffer)
              {}

    CCircularBuffer(size_t capacity, Type value)
            : size_(0),
              capacity_(capacity),
              buffer(b_allocator.allocate(capacity)),
              first(buffer),
              last(buffer + capacity),
              current(buffer)
              {
                for (size_t i = 0; i < capacity; i++) {
                    push_back(value);
                }
              }

    explicit CCircularBuffer(const CCircularBuffer<Type, std::allocator<Type>>& Object)
            : size_(0),
              capacity_(Object.capacity_),
              buffer(b_allocator.allocate(Object.capacity_)),
              first(buffer),
              last(buffer + Object.capacity_),
              current(buffer)
              {
                for (size_t i = 0; i < Object.capacity_; i++) {
                    push_back(*(Object.buffer + i));
                }
              }

    CCircularBuffer() = default;

    ~CCircularBuffer() {
        clear();
        b_allocator.deallocate(buffer, capacity_);
    }

    void push_back(const_reference element) {
        if (current == last) {
            current = first;
        }
        b_allocator.construct(current, element);
        current++;
        if (!full()) {
            size_++;
        }
    }

    void push_front(const_reference element) {
        if (full()) {
            throw std::overflow_error("CCircularBuffer overflow");
        }
        iterator curr = current;
        while (curr != first - 1) {
            *(curr + 1) = *curr;
            curr--;
        }
        b_allocator.construct(first, element);
        current++;
        size_++;
    }

    bool empty() const {
        return size_ == 0;
    }

    bool full() const {
        return size_ == capacity_;
    }

    void pop_back() {
        if (empty()) {
            throw std::underflow_error("CCircularBuffer underflow");
        }
        current--;
        b_allocator.destroy(current);
        size_--;
    }

    void pop_front() {
        if (empty()) {
            throw std::underflow_error("CCircularBuffer underflow");
        }
        iterator curr = begin();
        while (curr != end()) {
            *curr = *(curr + 1);
            curr++;
        }
        b_allocator.destroy(current);
        current--;
        size_--;
    }

    reference front() const {
        return *first;
    }

    iterator begin() const {
        return first;
    }
//    Iterator begin() const {
//        CCircularBuffer<Type, Allocator>::Iterator it(*this);
//        it = this->first;
//        return it;
//    }

    iterator rbegin() const {
        if (!full()) return current;
        return last;
    }

    const_iterator cbegin() const {
        return first;
    }

    reference back() const {
        return *(last - 1);
    }

    iterator end() const {
        if (!full()) return current;
        return last;
    }
//    Iterator end() const {
//        CCircularBuffer<Type, Allocator>::Iterator it(*this);
//        it = this->last;
//        return it;
//    }

    iterator rend() const {
        return first;
    }

    const_iterator cend() const {
        if (!full()) return current;
        return last;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void clear() {
        while (!empty()) {
            pop_back();
        }
    }

    friend void swap(CCircularBuffer<Type, Allocator>& l, CCircularBuffer<Type, Allocator> r) {
        CCircularBuffer<Type, Allocator> tmp;
        tmp = r;
        r = l;
        l = tmp;
    }

    void swap(CCircularBuffer<Type, Allocator>& l) {
        CCircularBuffer<Type, Allocator> tmp;
        tmp = *this;
        *this = l;
        l = tmp;
    }

    allocator_type get_allocator() const {
        return b_allocator;
    }

    reference operator[](size_t index) const {
        if (index < size_) {
            return *(first + index);
        }
    }

    iterator insert(iterator index, const_reference value) {
        iterator curr = end();
        while (curr != index - 1) {
            *(curr + 1) = *curr;
            curr--;
        }
        b_allocator.construct(index, value);
        current++;
        size_++;
        return begin();
    }

    iterator insert(iterator index, size_t count, const_reference value) {
        for (size_t i = 0; i < count; i++) {
            insert(index + i, value);
        }
        return begin();
    }

    iterator erase(iterator position) {
        iterator curr = position;
        if (curr > end() - 1) {
            return begin();;
        }
        b_allocator.destroy(position);
        while (curr != end()) {
            *curr = *(curr + 1);
            curr++;
        }
        b_allocator.destroy(current);
        current--;
        size_--;
        return begin();
    }

    iterator erase(iterator beg, iterator end) {
        size_t count = end - beg;
        iterator curr = beg;
        while (curr != end) {
            *curr = *(curr + count);
            curr++;
        }
        for (size_t i = 0; i < count; i++) {
            b_allocator.destroy(current);
            current--;
            size_--;
        }
        return begin();
    }


    friend bool operator==(CCircularBuffer<Type, Allocator>& left, CCircularBuffer<Type, Allocator>& right) {
        if (left.size_ != right.size_ || left.capacity_ != right.capacity_) {
            return false;
        }
        for (size_t i = 0; i < left.size_; i++) {
            if (left[i] != right[i]) {
                return false;
            }
        }
        return true;
    }

    friend bool operator!=(CCircularBuffer<Type, Allocator>& left, CCircularBuffer<Type, Allocator>& right) {
        return !(left == right);
}

    CCircularBuffer<Type, Allocator>& operator=(std::initializer_list<Type> list) {
        for (const auto& it : list) {
            this->push_back(it);
        }
    }

protected:
    pointer buffer;
    allocator_type b_allocator;
    iterator first;
    iterator last;
    iterator current;
    size_t size_;
    size_t capacity_;
};


template<typename Type, class Allocator = std::allocator<Type>>
class CCircularBufferExt : public CCircularBuffer<Type, Allocator> {
public:
    using iterator = Type*;
    using const_iterator = const Type*;
    using reference = Type&;
    using const_reference = const Type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using allocator_type = Allocator;

    class Iterator : public CCircularBufferExt<Type, std::allocator<Type>>,
                     public CCircularBuffer<Type, std::allocator<Type>>::Iterator {
    public:
        explicit Iterator(const CCircularBuffer<Type, std::allocator<Type>>& Object)
                    : CCircularBufferExt<Type, std::allocator<Type>>(Object),
                      CCircularBuffer<Type, std::allocator<Type>>::Iterator(Object) {}

        Iterator& operator=(iterator Other_Iterator) override {
            this->iter_ = Other_Iterator;
            return *this;
        }

        virtual reference operator[](size_t num) override {
            return *(this->iter_ + num);
        }
    };

    explicit CCircularBufferExt(size_t capacity)
            : CCircularBuffer<Type, std::allocator<Type>>(capacity) {}

    CCircularBufferExt(size_t capacity, Type value)
            : CCircularBuffer<Type, std::allocator<Type>>(capacity, value) {}

    explicit CCircularBufferExt(const CCircularBuffer<Type, std::allocator<Type>>& Object)
            : CCircularBuffer<Type, std::allocator<Type>>(Object) {}

    void push_back(const_reference element) {
        if (this->full()) {
            this->capacity_ *= 2;
            pointer temp = this->b_allocator.allocate(this->capacity_);
            this->first = temp;
            this->last = temp + this->capacity_;
            this->current = temp;
            for (int i = 0; i < this->size_; i++) {
                this->b_allocator.construct(this->current, *(this->buffer + i));
                this->current++;
            }
            this->buffer = temp;
        }
        this->b_allocator.construct(this->current, element);
        this->current++;
        this->size_++;
    }

    void push_front(const_reference element) {
        if (this->full()) {
            this->capacity_ *= 2;
            pointer temp = this->b_allocator.allocate(this->capacity_);
            this->first = temp;
            this->last = temp + this->capacity_;
            this->current = temp;
            for (int i = 0; i < this->size_; i++) {
                this->b_allocator.construct(this->current, *(this->buffer + i));
                this->current++;
            }
            this->buffer = temp;
        }
        iterator curr = this->current;
        while (curr != this->first - 1) {
            *(curr + 1) = *curr;
            curr--;
        }
        this->b_allocator.construct(this->first, element);
        this->current++;
        this->size_++;
    }

    void insert(iterator index, const_reference value) {
        if (this->full()) {
            this->capacity_ *= 2;
            pointer temp = this->b_allocator.allocate(this->capacity_);
            this->first = temp;
            this->last = temp + this->capacity_;
            this->current = temp;
            for (int i = 0; i < this->size_; i++) {
                this->b_allocator.construct(this->current, *(this->buffer + i));
                this->current++;
            }
            this->buffer = temp;
        }
        iterator curr = this->end();
        while (curr != index - 1) {
            *(curr + 1) = *curr;
            curr--;
        }
        this->b_allocator.construct(index, value);
        this->current++;
        this->size_++;
        return this->begin();
    }

    void insert(iterator index, size_t count, const_reference value) {
        for (size_t i = 0; i < count; i++) {
            insert(index + i, value);
        }
        return this->begin();
    }

    CCircularBufferExt<Type, Allocator>& operator=(std::initializer_list<Type> list) {
        for (const auto& it : list) {
            this->push_back(it);
        }
    }
};


template<typename Type, class Allocator = std::allocator<Type>>
class BinaryTree : public CCircularBuffer<Type, Allocator> {
public:
    BinaryTree(size_t capacity) : CCircularBuffer<Type, Allocator>(capacity) {
        this->size_ = 0;
        this->capacity_ = capacity;
        this->buffer = this->b_allocator.allocate(capacity);
        this->first = this->buffer;
        this->last = this->buffer + capacity;
        this->current = this->buffer;
    }

    BinaryTree(size_t capacity, Type value) : CCircularBuffer<Type, Allocator>(capacity, value) {
        this->size_ = 0;
        this->capacity_ = capacity;
        this->buffer = this->b_allocator.allocate(capacity);
        this->first = this->buffer;
        this->last = this->buffer + capacity;
        this->current = this->buffer;
        for (size_t i = 0; i < capacity; i++) {
            this->push_back(value);
        }
    }

    struct Node {
        Type data;
        Node* left = nullptr;
        Node* right = nullptr;
        size_t time;
    };

    Node* newNode(Type x) {
        Node* node = new Node;
        node->data = x;
        node->left = node->right = nullptr;
        return node;
    }

    Node* insert(Node* node, Type x, size_t num) {
        if (node == nullptr) {
            node = newNode(x);
        }
        if (x < node->data)
            node->left = insert(node->left, x, num);
        if (x > node->data)
            node->right = insert(node->right, x, num);
        node->time = num;
        return node;
    }

    Node* min(Node *node) {
        if (node->left == nullptr) {
            return node;
        }
        return min(node->left);
    }

    Node* del(Node* node, Type x) {
        if (node == nullptr)
            return node;
        if (x < node->data)
            node->left = del(node->left, x);
        else if (x > node->data)
            node->right = del(node->right, x);
        else if (node->left != nullptr and node->right != nullptr) {
            node->data = min(node->right)->data;
            node->right = del(node->right, node->data);
        }
        else {
            if (node->left != nullptr)
                node = node->left;
            else if (node->right != nullptr)
                node = node->right;
            else
                node = nullptr;
        }
        return node;
    }

    void fill(Node* node) {
        if (node->left != nullptr)
            fill(node->left);
        *(this->first + (node->time % this->capacity_)) = node->data;
        if (node->right != nullptr)
            fill(node->right);
    }

    void push_back(Type value) {
        root = insert(root, value, this->current - this->first);
        if (this->size_ < this->capacity_) {
            this->size_++;
        }
        fill(root);
        if (this->current == this->last) {
            this->current = this->first;
        }
        else {
            this->current++;
        }
    }

    void pop_back() {
        root = del(root, *(this->current));
        this->current--;
        this->b_allocator.destroy(this->current);
        this->size_--;
    }

    Node* Get_Root() const {
        return root;
    }

    Type& operator[](size_t num) {
        return *(this->first + num);
    }

private:
    Node* root = nullptr;
};
