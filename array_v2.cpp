#include <iostream>

using namespace std;


void memSwap(void* a, void* b, unsigned int len) {
    char* byteA = static_cast<char*>(a);
    char* byteB = static_cast<char*>(b);
    for (int i = 0; i != len; i++) {
        swap(*(byteA + i), *(byteB + i));
    }
}


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
        for (int i = 0; i != size; i++) {
            T* tmp = new T(value);
            memSwap(head + i, tmp, sizeof(T));
            delete tmp;
        }
    }
    
    Array(const Array& other): size(size) {
        head = static_cast<T*>(malloc(sizeof(T) * size));
        for (int i = 0; i != size; i++) {
            T* tmp = new T(*(other.head + i));
            memSwap(head + i, tmp, sizeof(T));
            delete tmp;
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
        for (int i = 0; i != size; i++) {
            T* tmp = new T(*(other.head + i));
            memSwap(head + i, tmp, sizeof(T));
            delete tmp;
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
