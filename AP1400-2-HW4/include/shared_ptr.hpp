#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>
#include <utility>
template<typename T>
class SharedPtr {
private:
  T* _p = nullptr;
  size_t* count_p = nullptr;

public:
  // some functions that operator the count
  void increment() {
    ++(*count_p);
  }
  void decrement() {
    --(*count_p);
    if (this->zero()) { // delete them when count is decreased to 0?
      delete this->_p;
      delete this->count_p;
      this->_p = nullptr;
      this->count_p = nullptr;
    }
  }
  bool zero() {
    return *count_p == 0;
  }

  // constructor
  SharedPtr() : _p(nullptr), count_p(nullptr) {}
  SharedPtr(std:: nullptr_t) : _p(nullptr), count_p(nullptr) {}
  SharedPtr(T* p) : _p(p), count_p(nullptr) {
    if (_p) {
      count_p = new size_t(1);  // initialize the count with 1
    }
  }
  // destructor
  ~SharedPtr() {
    if (this->count_p) {
      // decrease the count, if it reaches 0, then delete automatically
      this->decrement();
      this->_p = nullptr;
    }
  }
  // copy constructor and copy assignment operator
  SharedPtr(const SharedPtr& other) :
    _p(other._p),
    count_p(other.count_p) {
    this->increment();
  }

  // avoid being attacked by `ptr1 = ptr1`
  SharedPtr& operator=(const SharedPtr& other) {
    if (this == &other) {
      return *this;
    }
    this->decrement();  // this will point to another object, so the count--

    this->_p = other._p;
    this->count_p = other.count_p;
    this->increment();
    return *this;
  }

  size_t use_count() {
    if (!count_p) {
      return 0;
    }
    return *this->count_p;
  }

  T* get() {
    return this->_p;
  }

  T operator*() {
    return *this->_p;
  }

  const T operator*() const {
    return *this->_p;
  }

  T* operator->() {
    return this->_p;
  }

  const T* operator->() const {
    return this->_p;
  }

  void reset() {
    this->decrement();

    _p = nullptr;
    count_p = nullptr;
  }

  void reset(T* ptr) {
    this->decrement();

    _p = ptr;
    count_p = new size_t(1);
  }

  explicit operator bool() {
    return _p != nullptr;
  }
};

template<typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}


#endif
