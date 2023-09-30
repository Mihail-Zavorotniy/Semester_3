#include <iostream>

using namespace std;


template <typename T>
class Array {
    unsigned int size;
    T* head;
    
public:
    explicit Array(size_t size, const T& value): size(size) {
        head = static_cast<T*>(malloc(sizeof(T) * size));
        for (int i = 0; i != size; i++){
            *(head + i) = value;
        }
    }
    
    Array(const Array& other): size(size) {
        head = static_cast<T*>(malloc(sizeof(T) * size));
        for (int i = 0; i != size; i++){
            *(head + i) = *(other.head + i);
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
        if (other == this) { return *this; }
        
        free(head);
        size = other.size;
        head = static_cast<T*>(malloc(sizeof(T) * size));
        for (int i = 0; i != size; i++) {
            *(head + i) = *(other.head + i);
        }
        return *this;
    }
    
    Array& operator=(Array&& other) {
        if (other == this) { return *this; }
        
        free(head);
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
