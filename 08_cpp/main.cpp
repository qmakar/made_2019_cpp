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
    T* begin_;
    T* end_;
    
public:
    Iterator(const Iterator &it): current_(it.current_) {};
    
    Iterator(T* p)  : current_(p) {};
    
    template <typename D>
    Iterator(Vector<D> & arr){
        current_ = arr.get(0);
        begin_ = arr.get(0);
        end_ = arr.get(arr.size());
    }
    
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
        if (current_ + n <= end_)
            return Iterator(current_ + n);
        return Iterator(end_);
    }
    
    Iterator operator-(T const n) {
        if (current_ - n >= begin_)
            return Iterator(current_ - n);
        return Iterator(begin_);
    }
    
    size_t operator-(Iterator const it) {
        return abs(current_ - it.current_);
    }
    
    Iterator& operator+=(const int& n) {
        if (n > 0){
            if (current_ + n <= end_)
                current_ += n;
            else
                current_ = end_;
        }
        else{
            int k = abs(n);
            if (current_ - k >= begin_)
                current_ -= k;
            else
                current_ = begin_;
        }
        return *this;
    }
    
    Iterator& operator-=(const int& n) {
        if (n > 0){
            if (current_ - n >= begin_)
                current_ -= n;
            else
                current_ = begin_;
        }
        else{
            int k = abs(n);
            if (current_ + k <= end_)
                current_ += k;
            else
                current_ = end_;
        }
        return *this;
    }
    
    Iterator& operator++(){
        if (current_ + 1 <= end_)
            ++current_;
        return *this;
    }
    
    Iterator& operator--(){
        if (current_ - 1 >= begin_)
            --current_;
        return *this;
    }
    
    friend const Iterator operator+(const int& n, const Iterator& it){
        if (it.current_ + n < it.end_)
            return Iterator(it.current_ + n);
        return Iterator(it.end_);
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
        
        std::copy(values.begin(), values.end(), data_);
    };
    
    ~Vector(){
        if (data_){
            alloc_.deallocate(data_, size_);
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
    
    void clear(){
        alloc_.deallocate(data_, size_);
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
            data_[0] = value;
        }
        else if (new_index < size_ - 1){
            data_[new_index] = value;
            true_size_++;
        }
        else{
            size_t new_size = size_ * 2;
            T* tmp = alloc_.allocate(new_size);
            
            for (int i = 0; i < true_size_; i++){
                tmp[i] = data_[i];
            }
            tmp[new_index] = value;
            
            alloc_.deallocate(data_, size_);
            data_ = tmp;
            size_ = new_size;
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
            
            T* tmp = alloc_.allocate(size_);
            for (int i = 0; i < true_size_; i++){
                tmp[i] = data_[i];
            }
            alloc_.deallocate(data_, size_);
            data_ = tmp;
        }
    }
    
    void resize(size_t count, const T& value = 0){
        if (count == 0){
            alloc_.deallocate(data_, size_);
            size_ = count;
            true_size_ = count;
        }
        else if (count > true_size_){
            T* tmp = alloc_.allocate(count);
            
            for (size_t i = 0; i < true_size_; i++){
                tmp[i] = data_[i];
            }
            for (size_t i = true_size_; i < count; i++){
                tmp[i] = value;
            }
            
            alloc_.deallocate(data_, size_);
            data_ = tmp;
            size_ = count;
            true_size_ = count;
        }
        else if (count < true_size_){
            T* tmp = alloc_.allocate(count);
            for (int i = 0; i < count; i++){
                tmp[i] = data_[i];
            }
            alloc_.deallocate(data_, size_);
            data_ = tmp;
            true_size_ = count;
            size_ = count;
        }
    }
    
    void reserve(size_t size ){
        if (size > size_){
            // size is min degree of 2
            int degree = std::log(size)/std::log(2);
            size_ = 1 << (degree + 1);
            T* tmp =alloc_.allocate(true_size_);
            for (size_t i = 0; i < true_size_; i++){
                tmp[i] = data_[i];
            }
            alloc_.deallocate(data_, size_);
            data_ = tmp;
        }
    }
    
    void print(){
        for (size_t i = 0; i < true_size_; i++){
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
    }
    
    T& operator [](int idx) {
        return data_[idx];
    }
    
    T operator [](int idx) const {
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
    Iterator<int> iter(vec);
    assert(*iter == 7);
    std::cout << "*iter == " << *iter << std::endl;
    
    ++iter;
    assert(*iter == 6);
    std::cout << "++iter, *iter == " << *iter << std::endl;
    ++iter;
    assert(iter == vec.end());
    std::cout << "++iter, iter == vec.end()" << std::endl;
    ++iter;
    assert(iter == vec.end());
    std::cout << "++iter, iter == vec.end()" << std::endl;
    
    --iter;
    assert(*iter == 6);
    std::cout << "--iter, *iter == " << *iter << std::endl;
    --iter;
    assert(*iter == 7);
    std::cout << "--iter, *iter == " << *iter << std::endl;
    --iter;
    assert(iter == vec.begin());
    std::cout << "--iter, iter == vec.begin() "<< std::endl;
    
    iter+= 10;
    assert(iter == vec.end());
    std::cout << "iter += 10, iter == vec.end() "<< std::endl;
    
    
    assert(iter >= vec.begin());
    std::cout << "iter >= vec.begin()"<< std::endl;
    
    iter += -20;
    assert(*(1 + iter) == 6);
    std::cout << "iter += -20, *(1 + iter) == 6"<< std::endl;
    
    Iterator<int> iter2(vec);
    iter2 += 100;
    assert(iter2 - iter == 2);
    std::cout << "iter2 += 100, iter2 - iter == 2"<< std::endl;
    
    std::cout << "\n\nAll tests passed! We are awesome!=)\n"<< std::endl;
    
    return 0;
}
