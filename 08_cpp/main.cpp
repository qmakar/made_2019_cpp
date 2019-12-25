//
//  main.cpp
//  08_cpp
//
//  Created by qmakar on 10.12.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//


#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>


template <class T, class Alloc = std::allocator<T>>
class Vector;

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
    friend class Vector<T>;
    T* current_;
    
public:
    Iterator(const Iterator &it): current_(it.current_) {};
    
    Iterator(T* p)  : current_(p) {};
    
    bool operator!=(Iterator const& other) const{
        return current_ != other.current_;
    }
    
    bool operator==(Iterator const& other) const{
        return current_ == other.current_;
    }
    
    bool operator<(Iterator const& other) const{
        return current_ < other.current_;
    }
    
    bool operator>(Iterator const& other) const{
        return current_ > other.current_;
    }
    
    bool operator<=(Iterator const& other) const{
        return !(*this > other);
    }
    
    bool operator>=(Iterator const& other) const{
        return !(*this < other);
    }
    
    T operator*() const{
        return *current_;
    }
    
    T& operator [](int idx) {
        return *(current_ + idx);
    }
    
    Iterator operator+(T const n) {
        return Iterator(current_ + n);
    }
    
    Iterator operator-(T const n) {
        return Iterator(current_ - n);
    }
    
    size_t operator-(Iterator const it) {
        return abs(current_ - it.current_);
    }
    
    Iterator& operator+=(const int& n) {
        current_ += n;
        return *this;
    }
    
    Iterator& operator-=(const int& n) {
        current_ -= n;
        return *this;
    }
    
    Iterator& operator++(){
        ++current_;
        return *this;
    }
    
    Iterator& operator--(){
        --current_;
        return *this;
    }
    
    friend const Iterator operator+(const int& n, const Iterator& it){
        return Iterator(it.current_ + n);
    }

};


template <class T, class Alloc>
class Vector{
    size_t size_ = 0;
    size_t true_size_ = 0;
    T* data_ = nullptr;
    Alloc alloc_;
    
public:
    using iterator = Iterator<T>;
    
    Vector(){};
    
    Vector(std::initializer_list<T> values){
        // size is min degree of 2
        int degree = std::log(values.size())/std::log(2);
        size_ = 1 << (degree + 1);
        true_size_ = values.size();
        data_ = alloc_.allocate(size_);
        
        typename std::initializer_list<T>::iterator it;
        size_t i = 0;
        for (it = values.begin(); it != values.end(); ++it){
            alloc_.construct(data_ + i, *it);
            i++;
        }
    };
    
    ~Vector(){
        if (data_){
            alloc_.destroy(data_);
            alloc_.deallocate(data_, size_);
            data_ = nullptr;
        }
        size_ = 0;
        true_size_ = 0;
    }
    
    size_t size(){
        return true_size_;
    }
    
    bool empty(){
        if (true_size_ == 0){
            return true;
        }
        return false;
    }
    
    void realloc(size_t new_size, size_t elem_count){
        T* tmp = alloc_.allocate(new_size);
        for (size_t i = 0; i < elem_count; i++){
            alloc_.construct(tmp + i, data_[i]);
        }
        alloc_.destroy(data_);
        alloc_.deallocate(data_, size_);
        data_ = tmp;
        size_ = new_size;
    }
    
    void clear(){
        if (data_){
            alloc_.destroy(data_);
            alloc_.deallocate(data_, size_);
            data_ = nullptr;
        }
        size_ = true_size_ = 0;
    }
    
    T* get(size_t ind){
        return data_ + ind;
    }
    
    iterator begin(){
        return iterator(data_);
    }
    iterator end(){
        return iterator(data_ + true_size_);
    }
    
    iterator rbegin(){
        return iterator(data_ + size_ - 1);
    }
    iterator rend(){
        return iterator(data_ - 1);
    }
    
    void push_back( T&& value ){
        size_t new_index = true_size_;
        if (size_ == 0){
            size_ = 2;
            true_size_ = 1;
            data_ = alloc_.allocate(size_);
            alloc_.construct(data_, value);
        }
        else if (new_index < size_){
            alloc_.construct(data_ + new_index, value);
            true_size_++;
        }
        else{
            size_t new_size = size_ * 2;
            realloc(new_size, true_size_);
            alloc_.construct(data_ + new_index, value);
            
            true_size_++;
        }
    }
    
    void pop_back(){
        if (true_size_ == 0){
            return;
        }
        
        true_size_--;
        if (true_size_ <= size_ / 4){
            size_ /= 2;
            
            realloc(size_, true_size_);
        }
    }
    
    void resize(size_t count, const T& value = 0){
        if (count == 0){
            if (data_){
                alloc_.destroy(data_);
                alloc_.deallocate(data_, size_);
            }
            size_ = count;
            true_size_ = count;
        }
        else if (count > true_size_){
            T* tmp = alloc_.allocate(count);
            for (size_t i = 0; i < true_size_; i++){
                alloc_.construct(tmp + i, data_[i]);
            }
            for (size_t i = true_size_; i < count; i++){
                alloc_.construct(tmp + i, value);
            }
            alloc_.destroy(data_);
            alloc_.deallocate(data_, size_);
            data_ = tmp;
            size_ = count;
            true_size_ = count;
        }
        else if (count < true_size_){
            realloc(count, count);
            true_size_ = count;
        }
    }
    
    
    
    void reserve(size_t size ){
        if (size > size_){
            // size is min degree of 2
            int degree = std::log(size)/std::log(2);
            size_t new_size = 1 << (degree + 1);
            
            realloc(new_size, true_size_);
        }
    }
    
    void print(){
        for (size_t i = 0; i < true_size_; i++){
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
    }
    
    T& operator [](size_t idx) {
        return data_[idx];
    }
    
    const T& operator [](size_t idx) const {
        return data_[idx];
    }

};

int main()
{
    Vector<int> vec = {1,2,3};
    
    // test operator[]
    assert(vec[0] == 1);
    std::cout << "Elements of vector are:" << std::endl;
    vec.print();
    std::cout << std::endl;
    
    // test size()
    assert(vec.size() == 3);
    std::cout << "Size of vector is: " << vec.size() << std::endl;
    std::cout << std::endl;
    
    // test push_back()
    vec.push_back(5);
    vec.push_back(5);
    vec.push_back(5);
    vec.push_back(6);
    vec.push_back(700);
    assert(vec.size() == 8 && vec[vec.size() - 1] == 700);
    std::cout << "After 5 push_back elements of vector are:" << std::endl;
    vec.print();
    std::cout << std::endl;
    
    // test pop_back()
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    assert(vec.size() == 3 && vec[vec.size() - 1] == 3);
    std::cout << "After 5 pop_back elements of vector are:" << std::endl;
    vec.print();
    std::cout << std::endl;
    
    // test empty
    assert(vec.empty() == 0);
    std::cout << "vec.empty() == 0" << std::endl;
    std::cout << std::endl;
    
    // test pop clear vector
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    assert(vec.empty() == 1);
    std::cout << "pop empty vector, but vec.empty() == 1" << std::endl;
    std::cout << std::endl;
    
    // test resize
    vec.resize(10, 0);
    assert(vec.size() == 10);
    std::cout << "vec.resize(10, 0) & elements of vector are:" << std::endl;
    vec.print();
    std::cout << "Size of vector is: " << vec.size() << std::endl;
    std::cout << std::endl;
    
    // test resize
    vec.resize(1, 123);
    assert(vec.size() == 1);
    std::cout << "vec.resize(123, 0) & elements of vector are:" << std::endl;
    vec.print();
    std::cout << "Size of vector is: " << vec.size() << std::endl;
    std::cout << std::endl;
    
    //test clear
    vec.clear();
    assert(vec.size() == 0);
    std::cout << "vec.clear() & elements of vector are:" << std::endl;
    vec.print();
    std::cout << "Size of vector is: " << vec.size() << std::endl;
    std::cout << std::endl;
    
    
    vec.push_back(7);
    vec.push_back(6);
    std::cout << "Elements of vector are:" << std::endl;
    vec.print();
    
    
    //test iterator
    Iterator<int> iter = vec.begin();
    assert(*iter == 7);
    std::cout << "*iter == " << *iter << std::endl;
    
    ++iter;
    assert(*iter == 6);
    std::cout << "++iter, *iter == " << *iter << std::endl;
    ++iter;
    assert(iter == vec.end());
    std::cout << "++iter, iter == vec.end()" << std::endl;
    ++iter;
//    assert(iter == vec.end());
//    std::cout << "++iter, iter == vec.end()" << std::endl;
    
    --iter;
    --iter;
    assert(*iter == 6);
    std::cout << "--iter, *iter == " << *iter << std::endl;
    --iter;
    assert(*iter == 7);
    std::cout << "--iter, *iter == " << *iter << std::endl;
    --iter;
//    assert(iter == vec.begin());
//    std::cout << "--iter, iter == vec.begin() "<< std::endl;
    
    
//    assert(iter == vec.end());
//    std::cout << "iter += 10, iter == vec.end() "<< std::endl;
    
    iter+= 10;
    assert(iter >= vec.begin());
    std::cout << "iter >= vec.begin()"<< std::endl;
    
//    iter += -20;
    iter = vec.begin();
    assert(*(1 + iter) == 6);
    std::cout << "iter = vec.begin(), *(1 + iter) == 6"<< std::endl;
    
    Iterator<int> iter2 = vec.begin();
    iter2 += 100;
    assert(iter2 - iter == 100);
    std::cout << "iter2 += 100, iter2 - iter == 100"<< std::endl;
    
    // test UNSTOPPABLE CLEAR!!!
    vec.clear();
    vec.clear();
    std::cout << "vec.clear(); vec.clear(); NO SEGMENTAION FAULT"<< std::endl;
    
    std::cout << "\n\nAll tests passed! We are awesome!=)\n"<< std::endl;
    
    vec.resize(0);
    vec.pop_back();
    vec.pop_back();
    vec.clear();
    vec.clear();
    vec.resize(0);
    vec.resize(0);
    
    return 0;
}
