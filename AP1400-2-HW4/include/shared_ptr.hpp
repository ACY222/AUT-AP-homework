#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <utility>
template <typename T>
class SharedPtr {
private:
  T* _p = nullptr;
  int* count_p = nullptr;

  bool zero() {
    return (*count_p) == 0;
  }
  void increment() {
    (*count_p)++;
  }

  void decrement() {
    (*count_p)--;
    if (zero()) {
      delete _p;
      delete count_p;
      _p = nullptr;
      count_p = nullptr;
    }
  }

public:
  // constructor
  SharedPtr() : _p(nullptr), count_p(nullptr) {}
  SharedPtr(T* p) : _p(p) {
    if (_p) {
      count_p = new int(1);
    }
  }
  // destructor
  ~SharedPtr() {
    if (count_p)
      decrement();  // delete if necessary
    _p = nullptr;
    count_p = nullptr;
  }
  // copy constructor
  SharedPtr(const SharedPtr& other) :
    _p(other._p),
    count_p(other.count_p) {
    increment();
  }

  SharedPtr& operator=(const SharedPtr& other) {
    if (this == &other) {
      return *this;
    }

    if (this->count_p)
      this->decrement();  // derease the original count

    _p = other._p;
    count_p = other.count_p;
    this->increment();  // increase the new count
    return *this;
  }

  int use_count() {
    return count_p ? *count_p : 0;
  }

  T* get() {
    return _p;
  }

  T operator*() {
    return *_p;
  }

  T* operator->() {
    return _p;
  }

  void reset() {
    if (_p)
      delete _p;
    if (count_p)
      delete count_p;
    _p = nullptr;
    count_p = nullptr;
  }

  void reset(T* p) {
    if (_p)
      delete _p;
    _p = p;
    *count_p = 1;
  }

  explicit operator bool() {
    return _p != nullptr;
  }
};

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif
