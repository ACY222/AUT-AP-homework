#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>
#include <utility>
template<typename T>
class SharedPtr {
private:
  T* _p = nullptr;
  size_t* count_p = nullptr;

  // some functions that operator the count
  void increment() {
    ++(*count_p);
  }
  void decrement() {
    --(*count_p);
    if (this->zero()) { // delete them when count is decreased to 0
      delete this->_p;
      delete this->count_p;
      this->_p = nullptr; // because count == 0, now there's no other pointers
      this->count_p = nullptr;
    }
  }
  bool zero() {
    if (count_p)
      return *count_p == 0;
    return false;
  }

public:
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
    }
  }
  // copy constructor and copy assignment operator
  SharedPtr(const SharedPtr& other) :
    _p(other._p),
    count_p(other.count_p) {
    this->increment();
  }

  SharedPtr& operator=(const SharedPtr& other) {
    // avoid being attacked by `ptr1 = ptr1`
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
    return count_p ? *count_p : 0;
  }

  T* get() const {
    return this->_p;
  }

  T& operator*() {
    return *this->_p;
  }

  const T& operator*() const {
    return *this->_p;
  }

  T* operator->() {
    return this->_p;
  }

  const T* operator->() const {
    return this->_p;
  }

  void reset() {
    if (!_p) return;    // if _p == nullptr, do nothing
    this->decrement();

    _p = nullptr;
    count_p = nullptr;
  }

  void reset(T* ptr) {
    if (this->_p == ptr) return;
    SharedPtr temp(ptr);
    std::swap(*this, temp);
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
