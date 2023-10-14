#include <iostream>

using namespace std;


struct S {
    S() = delete;
    
    S(const S&) = default;
    
    S& operator=(const S&) = delete;
    
    S(int i) {}
};


template <typename T>
class Array {
    unsigned int size;
    T* head;
    
public:
    explicit Array(size_t size, const T& value): size(size) {
        head = static_cast<T*>(malloc(sizeof(T) * size));
        T* tmpPtr = head;
        for (int i = 0; i != size; i++) {
            tmpPtr = new (tmpPtr) T(value);
            tmpPtr += 1;
        }
    }
    
    Array(const Array& other): size(other.size) {
        head = static_cast<T*>(malloc(sizeof(T) * size));
        T* tmpPtr = head;
        for (int i = 0; i != size; i++) {
            tmpPtr = new (tmpPtr) T(*(other.head + i));
            tmpPtr += 1;
        }
    }
    
    Array(Array&& other) {
        swap(size, other.size);
        swap(head, other.head);
    }
    
    ~Array() {
        free(head);
    }
    
    Array& operator=(const Array& other) {
        if (&other == this) { return *this; }
        
        free(head);
        size = other.size;
        head = static_cast<T*>(malloc(sizeof(T) * size));
        T* tmpPtr = head;
        for (int i = 0; i != size; i++) {
            tmpPtr = new (tmpPtr) T(*(other.head + i));
            tmpPtr += 1;
        }
        return *this;
    }
    
    Array& operator=(Array&& other) {
        swap(size, other.size);
        swap(head, other.head);
        return *this;
    }
    
    unsigned int getSize() const {
        return size;
    }
    
    T& operator[](size_t idx) {
        return *(head + idx);
    }
    
    const T& operator[](size_t idx) const {
        return *(head + idx);
    }

};
