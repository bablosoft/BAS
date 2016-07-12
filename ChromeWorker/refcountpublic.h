#ifndef REFCOUNTPUBLIC_H
#define REFCOUNTPUBLIC_H

///
// Class that implements atomic reference counting.
///
class CefRefCountPublic {
 public:
  CefRefCountPublic() : ref_count_(0) {}

  ///
  // Increment the reference count.
  ///
  void AddRef() const {
    base::AtomicRefCountInc(&ref_count_);
  }

  ///
  // Decrement the reference count. Returns true if the reference count is 0.
  ///
  bool Release() const {
    return !base::AtomicRefCountDec(&ref_count_);
  }

  ///
  // Returns true if the reference count is 1.
  ///
  bool HasOneRef() const {
    return base::AtomicRefCountIsOne(&ref_count_);
  }

 public:
  mutable base::AtomicRefCount ref_count_;
 private:
  DISALLOW_COPY_AND_ASSIGN(CefRefCountPublic);
};

///
// Macro that provides a reference counting implementation for classes extending
// CefBase.
///
#define IMPLEMENT_REFCOUNTING_PUBLIC(ClassName)            \
  public:                                           \
    void AddRef() const OVERRIDE {                  \
      ref_count_.AddRef();                          \
    }                                               \
    bool Release() const OVERRIDE {                 \
      if (ref_count_.Release()) {                   \
        delete static_cast<const ClassName*>(this); \
        return true;                                \
      }                                             \
      return false;                                 \
    }                                               \
    bool HasOneRef() const OVERRIDE {               \
      return ref_count_.HasOneRef();                \
    }                                               \
  private:                                          \
    CefRefCountPublic ref_count_;


#define IMPLEMENT_REFCOUNTING_NONE()                \
  public:                                           \
    void AddRef() const OVERRIDE {                  \
      ref_count_.AddRef();                          \
    }                                               \
    bool Release() const OVERRIDE {                 \
      if (ref_count_.Release()) {                   \
        return true;                                \
      }                                             \
      return false;                                 \
    }                                               \
    bool HasOneRef() const OVERRIDE {               \
      return ref_count_.HasOneRef();                \
    }                                               \
    CefRefCountPublic ref_count_;



#endif // REFCOUNTPUBLIC_H
