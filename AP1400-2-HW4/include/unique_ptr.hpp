#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <utility>
template<typename T>
class UniquePtr {
private:
  T* _p = nullptr;    // the ptr
  //
public:
  // default constructor
  UniquePtr() : _p(nullptr) {}
  // constructor
  UniquePtr(T* p) : _p(p) {}
  // destructor
  ~UniquePtr() {
    if (_p) {   // avoid delete twice
      delete _p;
      _p = nullptr;
    }
  }
  // delete copy constructor and copy assignment operator
  UniquePtr(const UniquePtr& other) = delete;
  UniquePtr& operator=(const UniquePtr& other) = delete;
  // get, return the raw pointer stored in the class
  T* get() const {
    return _p;
  }
  // operator*, dereference
  T& operator*() {
    return *_p;
  }
  const T& operator*() const {
    return *_p;
  }
  // operator->, arrow operator like normal pointers
  T* operator->() {
    return _p;
  }
  const T* operator->() const {
    return _p;
  }
  // reset, delete the pointer and assign `nullptr` to it
  void reset() {
    delete _p;
    _p = nullptr;
  }
  // reset, have an input, make a new pointer with it after deleting the old
  void reset(T* p) {
    delete _p;
    _p = p;
  }
  // release, returns the stored pointer in the class(like get), with 2
  // differences: 1. the UniquePtr class won't store the pointer anymore, 2.
  //    deleting the pointer should not be done by UniquePtr class after calling
  //    release()
  T* release() {
    T* temp = _p; // now they point to the same space
    _p = nullptr;
    return temp;
  }

  explicit operator bool() {
    return _p != nullptr;
  }
};

template<typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) { // learn about this function
  return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif
