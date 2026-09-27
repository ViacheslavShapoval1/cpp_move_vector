/*
Author: Viacheslav Shapoval
Title: Templated Vector
Description: implementation of a templated dynamic-array class
             named MoveVector<T>. The class will provide functionality
             similar to a limited version of std::vector.
Date Created: 9/12/2026
Date Last Modified: 9/14/2026
*/
#ifndef PROJECT3_MOVEVECTOR_H
#define PROJECT3_MOVEVECTOR_H

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <utility>
#include <iostream>
using namespace std;

// description: A templated dynamic-array class.
// precondition: T is a valid type, capable of being stored in a container.
// postcondition: Provides dynamic array functionality.
template <typename T>
class MoveVector {
public:
    using value_type = T;
    using size_type = std::size_t;
    using iterator = T*;
    using const_iterator = const T*;

    // Construction and destruction

    // description: Default constructor initializing an empty vector.
    // return: N/A
    // precondition: None.
    // postcondition: size is 0, capacity is 0, data is nullptr.
    MoveVector() noexcept;

    // description: Creates count value-initialized elements.
    // return: N/A
    // precondition: T can be value-initialized.
    // postcondition: Vector size and capacity equal to count, with elements
    //                initialized.
    explicit MoveVector(size_type count);

    // description: Creates count copies of value.
    // return: N/A
    // precondition: None.
    // postcondition: Vector size and capacity equal count,
    //                filled with copies of value.
    MoveVector(size_type count, const T& value);

    // description: Initializes vector from a given initializer list.
    // return: N/A
    // precondition: None.
    // postcondition: Elements match the initializer list order.
    MoveVector(std::initializer_list<T> values);

    // description: Copy constructor performing a deep copy.
    // return: N/A
    // precondition: None.
    // postcondition: A deep copy of the other vector is created
    //                without changing the original.
    MoveVector(const MoveVector& other);

    // description: Move constructor transferring ownership.
    // return: N/A
    // precondition: None.
    // postcondition: Ownership is transferred, leaving source empty and valid.
    MoveVector(MoveVector&& other) noexcept;

    // description: Destructor to clean up resources.
    // return: N/A
    // precondition: None.
    // postcondition: All constructed elements are destroyed exactly once
    //                and memory is deallocated.
    ~MoveVector();

    // Assignment

    // description: Copy assignment operator performing a deep copy.
    // return: MoveVector&
    // precondition: None.
    // postcondition: Deep copy is performed, previous resources released
    //                safely, returns *this.
    // This implementation relies on the copy constructor
    // which handles allocations and the swap function (which is
    // noexcept), eliminating the need for
    // manual destroy and deallocate logic here.
    MoveVector& operator=(const MoveVector& other);

    // description: Move assignment operator transferring ownership.
    // return: MoveVector&
    // precondition: None.
    // postcondition: Destination resources released, source allocation
    //                transferred, returns *this.
    MoveVector& operator=(MoveVector&& other) noexcept;

    // Element access

    // description: Access element without bounds checking.
    // return: T&
    // precondition: index < size().
    // postcondition: Returns reference to element at index.
    T& operator[](size_type index);

    // description: Access element without bounds checking (const).
    // return: const T&
    // precondition: index < size().
    // postcondition: Returns const reference to element at index.
    const T& operator[](size_type index) const;

    // description: Access element with bounds checking.
    // return: T&
    // precondition: index < size().
    // postcondition: Returns reference to element at index, throws if out
    //                of bounds.
    T& at(size_type index);

    // description: Access element with bounds checking (const).
    // return: const T&
    // precondition: index < size().
    // postcondition: Returns const reference to element at index,
    //                throws if out of bounds.
    const T& at(size_type index) const;

    // description: Returns the first element.
    // return: T&
    // precondition: Vector is not empty.
    // postcondition: Returns reference to the first element.
    T& front();

    // description: Returns the first element (const).
    // return: const T&
    // precondition: Vector is not empty.
    // postcondition: Returns const reference to the first element.
    const T& front() const;

    // description: Returns the final element.
    // return: T&
    // precondition: Vector is not empty.
    // postcondition: Returns reference to the last element.
    T& back();

    // description: Returns the final element (const).
    // return: const T&
    // precondition: Vector is not empty.
    // postcondition: Returns const reference to the last element.
    const T& back() const;

    // description: Returns pointer to start of memory block.
    // return: T*
    // precondition: None.
    // postcondition: Returns v_data pointer.
    T* data() noexcept;

    // description: Returns pointer to start of memory block (const).
    // return: const T*
    // precondition: None.
    // postcondition: Returns const v_data pointer.
    const T* data() const noexcept;

    // Iterators

    // description: Iterator to beginning.
    // return: iterator
    // precondition: None.
    // postcondition: Returns pointer-based iterator to start.
    iterator begin() noexcept;

    // description: Iterator to beginning (const).
    // return: const_iterator
    // precondition: None.
    // postcondition: Returns const pointer-based iterator to start.
    const_iterator begin() const noexcept;

    // description: Iterator to end.
    // return: iterator
    // precondition: None.
    // postcondition: Returns pointer-based iterator to end.
    iterator end() noexcept;

    // description: Iterator to end (const).
    // return: const_iterator
    // precondition: None.
    // postcondition: Returns const pointer-based iterator to end.
    const_iterator end() const noexcept;

    // Capacity

    // description: Checks if vector is empty.
    // return: bool
    // precondition: None.
    // postcondition: Returns true if size is 0.
    bool empty() const noexcept;

    // description: Returns current size.
    // return: size_type
    // precondition: None.
    // postcondition: Returns v_size.
    size_type size() const noexcept;

    // description: Returns current capacity.
    // return: size_type
    // precondition: None.
    // postcondition: Returns v_capacity.
    size_type capacity() const noexcept;

    // description: Requests capacity to be at least newCapacity.
    // return: void
    // precondition: None.
    // postcondition: Capacity is >= newCapacity, existing elements
    //                transferred safely.
    void reserve(size_type newCapacity);

    // description: Reduces capacity to exactly the current size.
    // return: void
    // precondition: None.
    // postcondition: Capacity matches size.
    void shrink_to_fit();

    // Modifiers

    // description: Destroys all stored elements.
    // return: void
    // precondition: None.
    // postcondition: Size is 0, capacity and allocation preserved.
    void clear() noexcept;

    // description: Adds copied element to end of vector.
    // return: void
    // precondition: None.
    // postcondition: Element is copied to back, size is incremented.
    void push_back(const T& value);

    // description: Adds moved element to end of vector.
    // return: void
    // precondition: None.
    // postcondition: Element is moved to back, size is incremented.
    void push_back(T&& value);

    // description: This function utilizes a perfect forwarding method
    //              std::forward to pass in "raw ingredients" and construct
    //              directly in vector's memory
    // return: void
    // precondition: None.
    // postcondition: Element is constructed at back using perfect forwarding.
    template <typename... Args>
    void emplace_back(Args&&... args);

    // description: Destroys final element.
    // return: void
    // precondition: Vector is not empty.
    // postcondition: Size is decreased by one, capacity preserved.
    void pop_back();

    // description: Resizes the vector, value-initializing new elements
    //              if needed.
    // return: void
    // precondition: None.
    // postcondition: Vector size becomes newSize.
    void resize(size_type newSize);

    // description: Resizes the vector, copying value to new elements if
    //              needed.
    // return: void
    // precondition: None.
    // postcondition: Vector size becomes newSize.
    void resize(size_type newSize, const T& value);

    // description: Exchanges elements between two vectors.
    // return: void
    // precondition: None.
    // postcondition: Vector contents and capacities are swapped.
    void swap(MoveVector& other) noexcept;

private:
    size_type v_size;     //vector size
    size_type v_capacity; //vector capacity
    value_type* v_data;   //vector data
    allocator <value_type> v_alloc;//vector allocator for raw memory management
    using v_alloc_traits = allocator_traits<allocator<value_type>>;
};
    // description: Default constructor initializing an empty vector.
    // return: N/A
    // precondition: None.
    // postcondition: size is 0, capacity is 0, data is nullptr.
    template <typename T>
    MoveVector<T>::MoveVector() noexcept :
        //v_alloc purely for advance memory management for the v_data member
        v_size(0), v_capacity(0), v_data(nullptr), v_alloc()
    {}

    // description: Creates count value-initialized elements.
    // return: N/A
    // precondition: T can be value-initialized.
    // postcondition: Vector size and capacity equal to count, with elements
    //                initialized.
    template <typename T>
    MoveVector<T>::MoveVector(size_type count) : v_size(count), v_capacity
                                (count), v_data(nullptr), v_alloc()
    {
        if (v_size > 0) {
            // allocate memory without construction
            v_data = v_alloc.allocate(v_capacity);
            // tracks all constructed objects
            size_type successes = 0;
            try {
                //attempt to construct
                for (size_t i = 0; i < v_size; ++i) {
                    v_alloc_traits::construct(v_alloc, &v_data[i]);
                    ++successes;
                }
            }
            catch (...) {
                // in case of failure destroy and deallocate
                for (size_t i = 0; i < successes; ++i) {
                    v_alloc_traits::destroy(v_alloc, &v_data[i]);
                }
                v_alloc.deallocate(v_data, v_capacity);
                throw;
            }
        }
    }

    // description: Creates count copies of value.
    // return: N/A
    // precondition: None.
    // postcondition: Vector size and capacity equal count,
    //                filled with copies of value.
    template <typename T>
    MoveVector<T>::MoveVector(size_type count, const T& value) :
            v_size(count), v_capacity(count), v_data(nullptr), v_alloc()
    {
        if (v_size > 0) {
            // allocate memory without construction
            v_data = v_alloc.allocate(v_capacity);
            size_type successes = 0; //to track all constructed objects
            try {
                // attempt to construct
                for (size_t i = 0; i < v_size; ++i) {
                    v_alloc_traits::construct(v_alloc, &v_data[i], value);
                    ++successes;
                }
            }
            catch (...) {
                // in case of failure destroy and deallocate
                for (size_t i = 0; i < successes; ++i) {
                    v_alloc_traits::destroy(v_alloc, &v_data[i]);
                }
                v_alloc.deallocate(v_data, v_capacity);
                throw;
            }
        }
    }

    // description: Initializes vector from a given initializer list.
    // return: N/A
    // precondition: None.
    // postcondition: Elements match the initializer list order.
    template <typename T>
    MoveVector<T>::MoveVector(std::initializer_list<T> values) :
        v_size(values.size()), v_capacity(values.size()), v_data(nullptr),
        v_alloc()
    {
        if (values.size() > 0) {
            // allocate memory without construction
            v_data = v_alloc.allocate(v_capacity);
            // tracks constructed objects
            size_type successes = 0;
            try {
                // attempt to construct
                for (size_t i = 0; i < v_size; ++i) {
                    v_alloc_traits::construct(v_alloc, &v_data[i],
                        *(values.begin() + i));
                    ++successes;
                }
            }
            catch (...) {
                // in case of failure destroy and deallocate
                for (size_t i = 0; i < successes; ++i) {
                    v_alloc_traits::destroy(v_alloc, &v_data[i]);
                }
                v_alloc.deallocate(v_data, v_capacity);
                throw;
            }
        }
    }

    // description: Copy constructor performing a deep copy.
    // return: N/A
    // precondition: None.
    // postcondition: A deep copy of the other vector is created
    //                without changing the original.
    template <typename T>
    MoveVector<T>::MoveVector(const MoveVector& other) : v_size(other.v_size),
        v_capacity(other.v_capacity), v_data(nullptr), v_alloc()
    {
        if (v_capacity > 0) {
            // Allocate
            v_data = v_alloc.allocate(v_capacity);
            size_type successes = 0;
            try {
                // Construct
                for (size_t i = 0; i < v_size; ++i) {
                    v_alloc_traits::construct(v_alloc, &v_data[i],
                                                other.v_data[i]);
                    ++successes;
                }
            } catch (...) {
                // construction fails - destroy and deallocate
                for (size_t i = 0; i < successes; ++i) {
                    v_alloc_traits::destroy(v_alloc, &v_data[i]);
                }
                v_alloc.deallocate(v_data, v_capacity);
                throw;
            }
        }
    }

    // description: Move constructor transferring ownership.
    // return: N/A
    // precondition: None.
    // postcondition: Ownership is transferred, leaving source empty and valid.
    template <typename T>
    MoveVector<T>::MoveVector(MoveVector&& other) noexcept : v_size(other
        .v_size),
        v_capacity(other.v_capacity), v_data(other.v_data),
        v_alloc(std::move(other.v_alloc))
    {
        other.v_data = nullptr;
        other.v_size = 0;
        other.v_capacity = 0;
    }

    // description: Destructor to clean up resources.
    // return: N/A
    // precondition: None.
    // postcondition: All constructed elements are destroyed exactly once
    //                and memory is deallocated.
    template <typename T>
    MoveVector<T>::~MoveVector() {
        clear();
        if (v_data != nullptr) {
            v_alloc.deallocate(v_data,v_capacity);
            v_data = nullptr;
        }
        v_capacity = 0;
    }

    // Assignment

    // description: Copy assignment operator performing a deep copy.
    // return: MoveVector&
    // precondition: None.
    // postcondition: Deep copy is performed, previous resources released
    //                safely, returns *this.
    // This implementation relies on the copy constructor
    // which handles allocations and the swap function (which is
    // noexcept), eliminating the need for
    // manual destroy and deallocate logic here.
    template <typename T>
    MoveVector<T>& MoveVector<T>::operator=(const MoveVector& other) {
        if (this != &other) {
            //Construct safely from the given vector and swap
            MoveVector temp(other);
            this->swap(temp);
        }
        return *this;
    }

    // description: Move assignment operator transferring ownership.
    // return: MoveVector&
    // precondition: None.
    // postcondition: Destination resources released, source allocation
    //                transferred, returns *this.
    template <typename T>
    MoveVector<T>& MoveVector<T>::operator=(MoveVector&& other) noexcept {
        if (this != &other) {
            // Releases the memory by destroying the objects (if not empty)
            if (v_data != nullptr) {
                clear();
                v_alloc.deallocate(v_data,v_capacity);
                v_data = nullptr;
            }
            // Transfers (steals) the ownership
            v_capacity = other.v_capacity;
            v_size = other.v_size;
            v_data = other.v_data;
            v_alloc = std::move(other.v_alloc);
            // Return to a default state
            other.v_data = nullptr;
            other.v_size = 0;
            other.v_capacity = 0;
        }
        return *this;
    }

    // Element access

    // description: Access element without bounds checking.
    // return: T&
    // precondition: index < size().
    // postcondition: Returns reference to element at index.
    template <typename T>
    T& MoveVector<T>::operator[](size_type index) {
        return v_data[index];
    }

    // description: Access element without bounds checking (const).
    // return: const T&
    // precondition: index < size().
    // postcondition: Returns const reference to element at index.
    template <typename T>
    const T& MoveVector<T>::operator[](size_type index) const {
        return v_data[index];
    }

    // description: Access element with bounds checking.
    // return: T&
    // precondition: index < size().
    // postcondition: Returns reference to element at index, throws if out
    //                of bounds.
    template <typename T>
    T& MoveVector<T>::at(size_type index) {
        if (index >= v_size) {
            throw std::out_of_range("Out of bounds");
        }
        return v_data[index];
    }

    // description: Access element with bounds checking (const).
    // return: const T&
    // precondition: index < size().
    // postcondition: Returns const reference to element at index,
    //                throws if out of bounds.
    template <typename T>
    const T& MoveVector<T>::at(size_type index) const {
        if (index >= v_size) {
            throw std::out_of_range("Out of bounds");
        }
        return v_data[index];
    }

    // description: Returns the first element.
    // return: T&
    // precondition: Vector is not empty.
    // postcondition: Returns reference to the first element.
    template <typename T>
    T& MoveVector<T>::front() {
        if (empty()) {
            throw std::out_of_range("Out of bounds");
        }
        return v_data[0];
    }

    // description: Returns the first element (const).
    // return: const T&
    // precondition: Vector is not empty.
    // postcondition: Returns const reference to the first element.
    template <typename T>
    const T& MoveVector<T>::front() const {
        if (empty()) {
            throw std::out_of_range("Out of bounds");
        }
        return v_data[0];
    }

    // description: Returns the final element.
    // return: T&
    // precondition: Vector is not empty.
    // postcondition: Returns reference to the last element.
    template <typename T>
    T& MoveVector<T>::back() {
        if (empty()) {
            throw std::out_of_range("Out of bounds");
        }
        return v_data[v_size - 1];
    }

    // description: Returns the final element (const).
    // return: const T&
    // precondition: Vector is not empty.
    // postcondition: Returns const reference to the last element.
    template <typename T>
    const T& MoveVector<T>::back() const {
        if (empty()) {
            throw std::out_of_range("Out of bounds");
        }
        return v_data[v_size - 1];
    }

    // description: Returns pointer to start of memory block.
    // return: T*
    // precondition: None.
    // postcondition: Returns v_data pointer.
    template <typename T>
    T* MoveVector<T>::data() noexcept {
        return v_data;
    }

    // description: Returns pointer to start of memory block (const).
    // return: const T*
    // precondition: None.
    // postcondition: Returns const v_data pointer.
    template <typename T>
    const T* MoveVector<T>::data() const noexcept {
        return v_data;
    }

    // Iterators

    // description: Iterator to beginning.
    // return: iterator
    // precondition: None.
    // postcondition: Returns pointer-based iterator to start.
    template <typename T>
    T* MoveVector<T>::begin() noexcept {
        return v_data;
    }

    // description: Iterator to beginning (const).
    // return: const_iterator
    // precondition: None.
    // postcondition: Returns const pointer-based iterator to start.
    template <typename T>
    const T* MoveVector<T>::begin() const noexcept {
        return v_data;
    }

    // description: Iterator to end.
    // return: iterator
    // precondition: None.
    // postcondition: Returns pointer-based iterator to end.
template <typename T>
    T* MoveVector<T>::end() noexcept {
        return v_data + v_size;
    }

    // description: Iterator to end (const).
    // return: const_iterator
    // precondition: None.
    // postcondition: Returns const pointer-based iterator to end.
template <typename T>
    const T* MoveVector<T>::end() const noexcept {
        return v_data + v_size;
    }

    // Capacity

    // description: Checks if vector is empty.
    // return: bool
    // precondition: None.
    // postcondition: Returns true if size is 0.
template <typename T>
    bool MoveVector<T>::empty() const noexcept {
        return (v_size == 0);
    }

    // description: Returns current size.
    // return: size_type
    // precondition: None.
    // postcondition: Returns v_size.
template <typename T>
    size_t MoveVector<T>::size() const noexcept {
        return v_size;
    }

    // description: Returns current capacity.
    // return: size_type
    // precondition: None.
    // postcondition: Returns v_capacity.
template <typename T>
    size_t MoveVector<T>::capacity() const noexcept {
        return v_capacity;
    }

    // description: Requests capacity to be at least newCapacity.
    // return: void
    // precondition: None.
    // postcondition: Capacity is >= newCapacity, existing elements
    //                transferred safely.
    template <typename T>
    void MoveVector<T>::reserve(size_type newCapacity) {
        if (newCapacity > v_capacity) {
            //allocate new memory
            value_type* new_data = v_alloc.allocate(newCapacity);
            size_type successes = 0;
            try {
                if (v_data != nullptr) {
                    //fill out that memory
                    for (size_type i = 0; i < v_size; ++i) {
                        v_alloc_traits::construct(v_alloc, &new_data[i],
                            move_if_noexcept(v_data[i]));
                        ++successes;
                    }
                    //clear out old memory
                    for (size_type i = 0; i < v_size; ++i) {
                        v_alloc_traits::destroy(v_alloc, &v_data[i]);
                    }
                    v_alloc.deallocate(v_data,v_capacity);
                }
                //steal pointer
                v_data = new_data;
                v_capacity = newCapacity;
            } catch (...) {
                // if construction fails - destroy and deallocate
                for (size_t i = 0; i < successes; ++i) {
                    v_alloc_traits::destroy(v_alloc, &new_data[i]);
                }
                v_alloc.deallocate(new_data, newCapacity);
                throw;
            }
        }
    }

    // description: Reduces capacity to exactly the current size.
    // return: void
    // precondition: None.
    // postcondition: Capacity matches size.
    template <typename T>
    void MoveVector<T>::shrink_to_fit() {
        if (v_capacity > v_size) {
            //allocate new memory
            size_type newCapacity = v_size;
            // If size is > 0 allocate, otherwise assign with nullptr.
            value_type* new_data = (newCapacity > 0) ?
                v_alloc.allocate(newCapacity) : nullptr;
            size_type successes = 0;
            try {
                if (v_data != nullptr) {
                    //fill out that memory
                    for (size_type i = 0; i < v_size; ++i) {
                        v_alloc_traits::construct(v_alloc, &new_data[i],
                            move_if_noexcept(v_data[i]));
                        ++successes;
                    }
                    //clear out old memory
                    for (size_type i = 0; i < v_size; ++i) {
                        v_alloc_traits::destroy(v_alloc, &v_data[i]);
                    }
                    v_alloc.deallocate(v_data,v_capacity);
                }
                //steal pointer
                v_data = new_data;
                v_capacity = newCapacity;
            } catch (...) {
                // if failure - destroy and deallocate
                for (size_t i = 0; i < successes; ++i) {
                    v_alloc_traits::destroy(v_alloc, &new_data[i]);
                }
                if (new_data != nullptr) {
                    v_alloc.deallocate(new_data, newCapacity);
                }
                throw;
            }
        }
    }

    // Modifiers

    // description: Destroys all stored elements.
    // return: void
    // precondition: None.
    // postcondition: Size is 0, capacity and allocation preserved.
    template <typename T>
    void MoveVector<T>::clear() noexcept {
        for (size_t i = 0; i < v_size; ++i) {
            v_alloc_traits::destroy(v_alloc, &v_data[i]);
        }
        v_size = 0;
    }

    // description: Adds copied element to end of vector.
    // return: void
    // precondition: None.
    // postcondition: Element is copied to back, size is incremented.
    template <typename T>
    void MoveVector<T>::push_back(const T& value) {
        // in case more memory needed
        if (v_size == v_capacity) {
            T temp = value;
            size_type newCapacity = (v_capacity > 0) ? (2*v_capacity) : 1;
            // utilizes build-in safety of reserve() function
            reserve(newCapacity);
            v_alloc_traits::construct(v_alloc,&v_data[v_size],move(temp));
        } else {
            v_alloc_traits::construct(v_alloc,&v_data[v_size], value);
        }
        ++v_size;
    }

    // description: Adds moved element to end of vector.
    // return: void
    // precondition: None.
    // postcondition: Element is moved to back, size is incremented.
    template <typename T>
    void MoveVector<T>::push_back(T&& value) {
        // in case more memory needed
        if (v_size == v_capacity) {
            size_type newCapacity = (v_capacity > 0) ? (2*v_capacity) : 1;
            // utilizes build-in safety of reserve() function
            reserve(newCapacity);
        }
        v_alloc_traits::construct(v_alloc,&v_data[v_size],
            std::move(value));
        ++v_size;
    }

    // description: This function utilizes a perfect forwarding method
    //              std::forward to pass in "raw ingredients" and construct
    //              directly in vector's memory
    // return: void
    // precondition: None.
    // postcondition: Element is constructed at back using perfect forwarding.
    template <typename T>
    template <typename... Args>
    void MoveVector<T>::emplace_back(Args&&... args) {
        if (v_size == v_capacity) {
            size_type newCapacity = (v_capacity > 0) ? (2*v_capacity) : 1;
            reserve(newCapacity);
        }
        v_alloc_traits::construct(v_alloc,&v_data[v_size],
            std::forward<Args>(args)...);
        ++v_size;
    }

    // description: Destroys final element.
    // return: void
    // precondition: Vector is not empty.
    // postcondition: Size is decreased by one, capacity preserved.
    template <typename T>
    void MoveVector<T>::pop_back() {
        if (!empty()) {
            --v_size;
            v_alloc_traits::destroy(v_alloc,&v_data[v_size]);
        }
    }

    // description: Resizes the vector, value-initializing new elements
    //              if needed.
    // return: void
    // precondition: None.
    // postcondition: Vector size becomes newSize.
    template <typename T>
    void MoveVector<T>::resize(size_type newSize) {
        if (newSize > v_size) {
            if (newSize > v_capacity) {
                // Utilizes reserve() safely relocating existing elements to
                // the newly allocated memory
                reserve(newSize);
            }
            // Construct new objects
            while (v_size < newSize) {
                v_alloc_traits::construct(v_alloc, &v_data[v_size]);
                ++v_size;
            }
        }
        // Or destroy excess objects
        else if (newSize < v_size) {
            while (v_size > newSize) {
                --v_size;
                v_alloc_traits::destroy(v_alloc, &v_data[v_size]);
            }
        }
    }

    // description: Resizes the vector, copying value to new elements if
    //              needed.
    // return: void
    // precondition: None.
    // postcondition: Vector size becomes newSize.
    template <typename T>
    void MoveVector<T>::resize(size_type newSize, const T& value) {
        if (newSize > v_size) {
            // Allocate more memory if needed
            if (newSize > v_capacity) {
                // Utilizes reserve() safely relocating existing elements to
                // the newly allocated memory
                reserve(newSize);
            }
            // Construct new objects
            while (v_size < newSize) {
                v_alloc_traits::construct(v_alloc, &v_data[v_size],value);
                ++v_size;
            }
        }
        // Or destroy excess objects
        else if (newSize < v_size) {
            while (v_size > newSize) {
                --v_size;
                v_alloc_traits::destroy(v_alloc, &v_data[v_size]);
            }
        }
    }

    // description: Exchanges elements between two vectors.
    // return: void
    // precondition: None.
    // postcondition: Vector contents and capacities are swapped.
    template <typename T>
    void MoveVector<T>::swap(MoveVector& other) noexcept {
        std::swap(v_data, other.v_data);
        std::swap(v_size, other.v_size);
        std::swap(v_capacity, other.v_capacity);
        std::swap(v_alloc, other.v_alloc);
    }
#endif