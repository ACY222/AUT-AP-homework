#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <cstddef>
#include <utility>
template <typename T>
class UniquePtr {
private:
  T* _p = nullptr;

public:
  // constructor
  UniquePtr() : _p(nullptr) {}
  UniquePtr(std::nullptr_t) : _p(nullptr) {}
  UniquePtr(T* p) : _p(p) {}
  // destructor
  ~UniquePtr() {
    delete _p;
    _p = nullptr;
  }
  // copy constructor, copy assignment operator
  UniquePtr(const UniquePtr& other) = delete;
  UniquePtr& operator=(const UniquePtr& other) = delete;

  T* get() {
    return _p;
  }

  T operator*() {
    return *_p;
  }

  T* operator->() {
    return _p;
  }

  void reset(T* p) {
    delete _p;
    _p = p;
  }

  void reset() {
    delete _p;
    _p = nullptr;
  }

  T* release() {
    auto temp = _p;
    _p = nullptr;
    return temp;
  }

  explicit operator bool() {
    return _p != nullptr;
  }
};

template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
  return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif
