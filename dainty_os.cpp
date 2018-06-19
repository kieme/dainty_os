/******************************************************************************

 MIT License

 Copyright (c) 2018 kieme, frits.germs@gmx.net

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

******************************************************************************/

#include "dainty_os.h"

namespace dainty
{
namespace os
{
///////////////////////////////////////////////////////////////////////////////

  t_mutex_lock::t_mutex_lock()
    : valid_{call_pthread_mutex_init(mutex_, NULL) == 0 ? VALID : INVALID} {
  }

  t_mutex_lock::t_mutex_lock(t_err err)
    : valid_{INVALID} {
    if (!err) {
      valid_ = call_pthread_mutex_init(mutex_, NULL) == 0 ? VALID : INVALID;
      if (valid_ == INVALID)
        err = 10;
    }
  }

  t_mutex_lock::t_mutex_lock(const pthread_mutexattr_t& attr)
    : valid_{call_pthread_mutex_init(mutex_, &attr) == 0 ? VALID : INVALID} {
  }

  t_mutex_lock::t_mutex_lock(t_err err, const pthread_mutexattr_t& attr)
    : valid_{INVALID} {
    if (!err) {
      valid_ = call_pthread_mutex_init(mutex_, &attr) == 0 ? VALID : INVALID;
      if (valid_ == INVALID)
        err = 10;
    }
  }

  t_mutex_lock::~t_mutex_lock() {
    if (valid_ == VALID)
      call_pthread_mutex_destroy(mutex_);
  }

  t_mutex_locked_scope t_mutex_lock::make_locked_scope(t_err err) {
    if (!err) {
      if (valid_ == VALID) {
        if (call_pthread_mutex_lock(err, mutex_))
          return {this};
      } else
        err = 5;
    }
    return {nullptr};
  }

  t_mutex_locked_scope t_mutex_lock::make_locked_scope() {
    if (valid_ == VALID && call_pthread_mutex_lock(mutex_) == 0)
      return {this};
    return {nullptr};
  }

  t_mutex_locked_scope t_mutex_lock::trymake_locked_scope(t_err err) {
    if (!err) {
      if (valid_ == VALID) {
        if (call_pthread_mutex_trylock(err, mutex_))
          return {this};
      } else
        err = 5;
    }
    return {nullptr};
  }

  t_mutex_locked_scope t_mutex_lock::trymake_locked_scope() {
    if (valid_ == VALID && call_pthread_mutex_trylock(mutex_) == 0)
      return {this};
    return {nullptr};
  }

  named::t_void t_mutex_lock::enter_scope_(t_mutex_locked_scope*) {
    // can  use for debugging
  }

  named::t_void t_mutex_lock::leave_scope_(t_mutex_locked_scope*) {
    // can  use for debugging
  }

///////////////////////////////////////////////////////////////////////////////
  // thread
  // conditional_variable
}
}
