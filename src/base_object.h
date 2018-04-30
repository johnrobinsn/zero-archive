// Copyright Joyent, Inc. and other Node contributors.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef SRC_BASE_OBJECT_H_
#define SRC_BASE_OBJECT_H_

#include "v8.h"

namespace ivan {

class Environment;

class BaseObject {
 public:
  inline BaseObject(v8::Isolate* isolate, v8::Local<v8::Object> handle);
  virtual ~BaseObject() = default;

  // Returns the wrapped object.  Returns an empty handle when
  // persistent.IsEmpty() is true.
  inline v8::Local<v8::Object> object() {
    return persistent_handle_.Get(isolate_);
  }

  inline v8::Persistent<v8::Object>& persistent() {
    return persistent_handle_;
  }

  inline v8::Isolate* isolate() {
    return isolate_;
  }

  // The handle_ must have an internal field count > 0, and the first
  // index is reserved for a pointer to this class. This is an
  // implicit requirement, but Node does not have a case where it's
  // required that MakeWeak() be called and the internal field not
  // be set.
  template <typename Type>
  inline void MakeWeak(Type* ptr);

  inline void ClearWeak();

 private:
  BaseObject();

  template <typename Type>
  static inline void WeakCallback(
      const v8::WeakCallbackInfo<Type>& data);

  v8::Persistent<v8::Object> persistent_handle_;
  v8::Isolate* isolate_;
};

}  // namespace ivan

#endif  // SRC_BASE_OBJECT_H_
