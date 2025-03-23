#ifndef HEADER
#define HEADER

#include <iostream>
#include <utility>
#include <cstddef>        
#include <initializer_list>
#include <algorithm>      
#include <exception>
#include <iterator>

namespace USER {
template <typename T> 
class Deque {
    public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using size_type = size_t;
    using const_pointer = const T*;
    using const_reference = const T&;

    class Iterator {
        public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator();
        Iterator(pointer ptr);

        reference operator*() ;
        pointer operator->() ;
        reference operator[](difference_type n);
        const reference operator[](difference_type n) const;
        Iterator& operator++();
        const Iterator operator++(int);
        Iterator& operator--();
        const Iterator operator--(int);
        Iterator& operator+=(difference_type n);
        Iterator& operator-=(difference_type n);
        Iterator operator+(difference_type n) const;
        Iterator operator-(difference_type n) const;
        difference_type operator-(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        bool operator<(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator<=(const Iterator& other) const;
        bool operator>=(const Iterator& other) const;

        private:
        pointer m_ptr = nullptr;
    };
    //ctors && dtor
    Deque();
    Deque(std::initializer_list<T> init);
    Deque(const Deque& other);
    Deque(Deque&& other);
    Deque& operator=(const Deque& other);
    Deque& operator=(Deque&& other);
    ~Deque();

    //methods;
    void push_front(const T& value); 
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    reference front(); 
    reference back();
    const_reference front() const; 
    const_reference back() const;
    bool isEmpty() const;
    int size() const;

    //operators
    reference operator[](int index);
    const_reference operator[](int index) const;

    //iterators methods
    Iterator begin();
    Iterator end();

    private:
    //data
    mutable pointer m_data_1 = nullptr;
    mutable pointer m_data_2 = nullptr;
    mutable size_type m_size_1 = 0;
    mutable size_type m_size_2 = 0;
    mutable size_type m_capacity_1 = 0;
    mutable size_type m_capacity_2 = 0;

    //helper methods
    void realloc_1();
    void realloc_2();
    void rearrange_1();
    void rearrange_2();
    void copy_(const Deque& other);
    void move_(Deque&& other);
};

}
#endif //HEADER