#include <iostream>

template <typename T>
class DynamicArray
{
private:
    T *arr_ = nullptr;
    int len_ = 0;        // length user thinks array is
    int capacity_ = 0;   // actual array size

    void inspectIndexOutOfRange(int index) const;

public:
    DynamicArray() {};
    DynamicArray(const int len);
    ~DynamicArray() { delete[] arr_; }

    int len() const { return len_; }
    int capacity() const { return capacity_; }

    int isEmpty() const { return len_ == 0; }

    T get(int index) const;
    void set(int index, T element);

    void clear();
    void resize(int len);
    void append(T element);

    T& operator[](int index);
    void operator+=(T element) { append(element); }

};

// private

template <typename T>
void DynamicArray<T>::inspectIndexOutOfRange(int index) const 
{
    if (index < 0 || index > len_-1) {
        if (isEmpty()) {
            throw std::out_of_range("Index out of range. Dynamic array is empty.");
        }
        else {
            throw std::out_of_range("Index out of range. Valid range is [0, " + std::to_string(len_ - 1) + "]");
        }
    }
}

// end private


// public

template <typename T>
DynamicArray<T>::DynamicArray(const int len) 
    : len_(len), capacity_(len)
{
    if (len_ < 0) {
        throw std::out_of_range("Invalid array length. Length must be non-negative.");
    }    
    arr_ = new T[len];
}

template <typename T>
T DynamicArray<T>::get(int index) const 
{
    inspectIndexOutOfRange(index);
    return arr_[index];
}

template <typename T>
void DynamicArray<T>::set(int index, T element)
{
    inspectIndexOutOfRange(index);
    arr_[index] = element;
}

template <typename T>
void DynamicArray<T>::clear()
{
    delete[] arr_;
    arr_ = new T[capacity_];
    len_ = 0;
}

template <typename T>
void DynamicArray<T>::resize(int len) 
{
    capacity_ = len;
    len_ = len;
    delete[] arr_;
    arr_ = new T[capacity];
}

template <typename T>
void DynamicArray<T>::append(T element)
{
    if (len_+1 > capacity_) {
        capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
        T *new_arr = new T [capacity_];
        for (int i = 0; i < len_; i++) {
            new_arr[i] = arr_[i];
        }
        new_arr[len_++] = element;
        delete[] arr_;
        arr_ = new_arr; 
    }
    else {
        arr_[len_++] = element;
    }
}

template <typename T>
T& DynamicArray<T>::operator[](int index)
{
    inspectIndexOutOfRange(index);
    return arr_[index];
}

// end public