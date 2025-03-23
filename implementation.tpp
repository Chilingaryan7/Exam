#ifndef IMPLEMENTATION
#define IMPLEMENTATION

#include "header.hpp" // delate in end
using namespace USER;

template<typename T>
Deque<T>::Deque() : m_data_1{nullptr}, m_data_2{nullptr}, m_size_1{0}, m_size_2{0}, m_capacity_1{0}, m_capacity_2{0} {}

template<typename T>
Deque<T>::Deque(std::initializer_list<T> init) {
    size1 = init.size() / 2;
    size2 = init.size() - size1;
    m_capacity_1 = size1;
    m_capacity_2 = size2; 
    m_data_1 = new T[size1];
    m_data_2 = new T[size2];
    for (size_t i = 0; i < size1; ++i) {
        m_data_2[i] = init[m_size_1 - i - 1];
    }
    for (size_t i = 0; i < size2; ++i) {
        m_data_2[i] = init[m_size_1 + i - 1];
    }
}

template<typename T>
Deque<T>::Deque(const Deque& other) {
    copy_(other);
}

template<typename T>
Deque<T>::Deque(Deque&& other) {
   move_(std::move(other))
}

template<typename T>
Deque<T>& Deque<T>::operator=(const Deque& other) {
    if (this != &other) {
        delete[] m_data_1;
        delete[] m_data_2;
        copy_(other);
    }
    return  *this;
}

template<typename T>
Deque<T>& Deque<T>::operator=(Deque&& other) {
    if (this != &other) {
        delete[] m_data_1;
        delete[] m_data_2;
        copy_(other);
    }
    return  *this;
}


template<typename T>
Deque<T>::~Deque() {
    delete[] m_data_1;
    delete[]m_data_2;
    m_capacity_1 = m_capacity_2 = m_size_1 = m_size_2 = 0;

}

template<typename T>
void Deque<T>::push_front(const T& value) {
    if (m_capacity_2 == m_size_2) {
        realloc_2();
    }
    m_data_2[m_size_2++] = value;
    void();
}


template<typename T>
void Deque<T>::push_back(const T& value) {
    if (m_capacity_1 == m_size_1) {
        realloc_1();
    }
    m_data_1[m_size_1++] = value;
    void();
}

template<typename T>
void Deque<T>::pop_front() {
    if (!m_size_2) {
        if (m_size_1) {
            rearrange_2();
        } else {
            throw std::run_time_error(": Empty deque");
        }
    }
    --m_size_2;
    return;
}

template<typename T>
void Deque<T>::pop_back() {
    if (m_size_1) {
        if (m_size_2) {
            rearrange_1();
        } else {
            throw std::run_time_error(": Empty deque");
        }
    }
    --m_size_1;
    return;
}

template<typename T>
Deque<T>::reference Deque<T>::front() {
    if (!m_size_2) {
         if (m_size_1) {
            rearrange_2();
        } else {
            throw std::run_time_error(": Empty deque");
        }
    }
    return m_data_2[m_size_2 - 1];
}

template<typename T>
Deque<T>::const_reference Deque<T>::front() const {
    if (!m_size_2) {
         if (m_size_1) {
            rearrange_2();
        } else {
            throw std::run_time_error(": Empty deque");
        }
    }
    return m_data_2[m_size_2 - 1];
}

template<typename T>
Deque<T>::reference Deque<T>::back() {
    if (m_size_1) {
        if (m_size_2) {
            rearrange_1();
        } else {
            throw std::run_time_error(": Empty deque");
        }
    }
    return m_data_1[m_size_1 - 1];
}

template<typename T>
Deque<T>::const_reference Deque<T>::back() const {
    if (m_size_1) {
        if (m_size_2) {
            rearrange_1();
        } else {
            throw std::run_time_error(": Empty deque");
        }
    }
    return m_data_1[m_size_1 - 1];
}

template<typename T>
bool Deque<T>::isEmpty() const {
    return (m_size_1 == 0) &&  (m_size_2 == 0);
}

template<typename T>
int Deque<T>::size() const {
    return m_size_1 + m_size_2;
}


template<typename T>
Deque<T>::reference Deque<T>::operator[](int index) {
    if (index >= m_size_1 + m_size_2) {
        throw std::out_of_range("Invalid index");
    }
    if (index < m_size_2) {
        return m_ data_2[m_size_2 - 1 - index];
    }
    return m_data_1[m_size_1 - (index - m_size_2) - 1];
    
}

template<typename T>
Deque<T>::const_reference Deque<T>::operator[](int index) const {
    if (index >= m_size_1 + m_size_2) {
        throw std::out_of_range("Invalid index");
    }
    if (index < m_size_2) {
        return m_ data_2[m_size_2 - 1 - index];
    }
    return m_data_1[m_size_1 - (index - m_size_2) - 1];
    
}


template<typename T>
void Deque<T>::copy_(const Deque& other){
    m_size_1 = other.m_size_1;
    m_size_2 = other.m_size_2;
    m_capacity_1 = other.m_capacity_1;
    m_capacity_2 = other.m_capacity_2;
    m_data_1 = new T[m_size_1];
    m_data_2 = new T[m_size_2];
    for (int i = 0; i < m_size_1; ++i) {
        m_data_1[i] = other.m_data_1[i];
    } 
    for (int i = 0; i < m_size_2; ++i) {
        m_data_2[i] = other.m_data_2[i];
    } 
    return;
}

template<typename T>
void Deque<T>::move_(Deque&& other){
    m_size_1 = std::exchange(other.m_size_1, 0);
    m_size_2 = std::exchange(other.m_size_2, 0);
    m_capacity_1 = std::exchange(other.m_capacity_1, 0);
    m_capacity_2 = std::exchange(other.m_capacity_2, 0);
    m_data_1 = std::exchange(other.m_data_1, nullptr);
    m_data_2 = std::exchange(other.m_data_2, nullptr);
}


template<typename T>
void Deque<T>::realloc_1(){
    pointer ptr = new T[m_capacity_1 * 2];
    for (int i = 0; i < m_size_1; ++i) {
        ptr[i] = m_data_1[i];
    }
    m_capacity_1 *= 2;
    delete m_data_1;
    m_data_1 = ptr;
    return;
}

template<typename T>
void Deque<T>::realloc_2(){
    pointer ptr = new T[m_capacity_2 * 2];
    for (int i = 0; i < m_size_2; ++i) {
        ptr[i] = m_data_2[i];
    }
    m_capacity_2 *= 2;
    delete m_data_2;
    m_data_2 = ptr;
    return;
}

template<typename T>
void Deque<T>::rearrange_1(){
    while (m_capacity_1 < m_size_2) {
        realloc_1();
    }
    for (int i = 0; i < m_size_2; ++i) {
        m_data_1[m_size_2 - i] = m_data_2[i];
    }
    m_size_1 = m_size_2;
    m_size_2 = 0;
}

template<typename T>
void Deque<T>::rearrange_2(){
    while (m_capacity_2 < m_size_1) {
        realloc_2();
    }
    for (int i = 0; i < m_size_1; ++i) {
        m_data_2[m_size_1 - i] = m_data_1[i];
    }
    m_size_2 = m_size_1;
    m_size_1 = 0;
}

template<typename T>
Deque<T>::Iterator Deque<T>::begin() {
    if (m_size_2) {
        return Iterator(m_data_2[m_size_2 - 1]);
    }
    if (m_size_1) {
        return Iterator(m_data_2[0]);
    }
    return Iterator(nullptr);
}

template<typename T>
Deque<T>::Iterator Deque<T>::end() {
    return Iterator(m_data_1[m_size_1]);
}


template<typename T>
Deque<T>::Iterator::Iterator() : m_ptr{nullptr};

template<typename T>
Deque<T>::Iterator::Iterator(Deque<T>::Iterator::pointer ptr) : m_ptr{ptr} {}

template<typename T>
Deque<T>::Iterator::reference Deque<T>::Iterator::operator*() {
    return *m_ptr;
} 

template<typename T>
Deque<T>::Iterator::pointer Deque<T>::Iterator::operator->() {
    return m_ptr;
} 

template<typename T>
Deque<T>::Iterator& Deque<T>::Iterator::operator++(){
    if(m_ptr == &m_data[m_size_2 - 1]) {
        m_ptr = m_data_1;
    } else {
        ++m_ptr;
    }
    return *m_ptr;
}

#endif //IMPLEMENTATION