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

#include "dainty_os_threading.h"

namespace dainty
{
namespace os
{
namespace threading
{
///////////////////////////////////////////////////////////////////////////////

  t_mutex_lock::t_mutex_lock() noexcept
    : valid_{call_pthread_mutex_init(mutex_, NULL) == 0 ? VALID : INVALID} {
  }

  t_mutex_lock::t_mutex_lock(t_err err) noexcept
    : valid_{call_pthread_mutex_init(err, mutex_, NULL)} {
  }

  t_mutex_lock::t_mutex_lock(const pthread_mutexattr_t& attr) noexcept
    : valid_{call_pthread_mutex_init(mutex_, &attr) == 0 ? VALID : INVALID} {
  }

  t_mutex_lock::t_mutex_lock(t_err err, const pthread_mutexattr_t& attr) noexcept
    : valid_ {call_pthread_mutex_init(err, mutex_, &attr)} {
  }

  t_mutex_lock::~t_mutex_lock() noexcept {
    if (valid_ == VALID)
      call_pthread_mutex_destroy(mutex_);
  }

  t_mutex_locked_scope t_mutex_lock::make_locked_scope(t_err err) noexcept {
    if (!err) {
      if (valid_ == VALID) {
        if (call_pthread_mutex_lock(err, mutex_) == VALID)
          return {this};
      } else
        err = 5; // XXX
    }
    return {nullptr};
  }

  t_mutex_locked_scope t_mutex_lock::make_locked_scope() noexcept {
    if (valid_ == VALID && call_pthread_mutex_lock(mutex_) == 0)
      return {this};
    return {nullptr};
  }

  t_mutex_locked_scope t_mutex_lock::trymake_locked_scope(t_err err) noexcept {
    if (!err) {
      if (valid_ == VALID) {
        if (call_pthread_mutex_trylock(err, mutex_) == VALID)
          return {this};
      } else
        err = 5; //XXX
    }
    return {nullptr};
  }

  t_mutex_locked_scope t_mutex_lock::trymake_locked_scope() noexcept {
    if (valid_ == VALID && call_pthread_mutex_trylock(mutex_) == 0)
      return {this};
    return {nullptr};
  }

  named::t_void t_mutex_lock::enter_scope_(t_mutex_locked_scope*) noexcept {
    // can  use for debugging
  }

  named::t_void t_mutex_lock::leave_scope_(t_mutex_locked_scope* scope) noexcept {
    if (*scope == VALID)
      call_pthread_mutex_lock(mutex_);
    // can  use for debugging
  }

///////////////////////////////////////////////////////////////////////////////

  t_recursive_mutex_lock::t_recursive_mutex_lock() noexcept {
  }

  t_recursive_mutex_lock::t_recursive_mutex_lock(t_err err) noexcept {
  }

  t_recursive_mutex_lock::t_recursive_mutex_lock(const pthread_mutexattr_t&) noexcept {
  }

  t_recursive_mutex_lock::t_recursive_mutex_lock(t_err err,
                                                 const pthread_mutexattr_t&) noexcept {
  }

///////////////////////////////////////////////////////////////////////////////
  // thread
}
}
}
