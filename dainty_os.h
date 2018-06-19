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

#ifndef _DAINTY_OS_H_
#define _DAINTY_OS_H_

// description
// os: operating system functionality used by dainty

#include "dainty_named.h"
#include "dainty_oops.h"
#include "dainty_os_call.h"

namespace dainty
{
namespace os
{
  using named::t_validity;
  using named::VALID;
  using named::INVALID;

///////////////////////////////////////////////////////////////////////////////

  class t_mutex_lock;

  class t_mutex_locked_scope {
  public:
    t_mutex_locked_scope(t_mutex_locked_scope&&);
    ~t_mutex_locked_scope();

    t_mutex_locked_scope(const t_mutex_locked_scope&) = delete;
    t_mutex_locked_scope& operator=(const t_mutex_locked_scope&) = delete;
    t_mutex_locked_scope& operator=(t_mutex_locked_scope&&) = delete;

    operator t_validity() const { return lock_ ? VALID : INVALID; }

  private:
    friend class t_mutex_lock;
    inline t_mutex_locked_scope(t_mutex_lock* lock) : lock_(lock) {
    }
    inline t_mutex_lock* swap_(t_mutex_lock* lock) {
      t_mutex_lock* tmp = lock_; lock_ = lock; return tmp;
    }

    t_mutex_lock* lock_;
  };

  class t_mutex_lock {
  public:
    t_mutex_lock();
    t_mutex_lock(t_err err);
    t_mutex_lock(const pthread_mutexattr_t&);
    t_mutex_lock(t_err err, const pthread_mutexattr_t&);
    ~t_mutex_lock();

    t_mutex_lock(const t_mutex_lock&) = delete;
    t_mutex_lock(t_mutex_lock&&) = delete;
    t_mutex_lock& operator=(const t_mutex_lock&) = delete;
    t_mutex_lock& operator=(t_mutex_lock&&) = delete;

    operator t_validity() const { return valid_; }

    t_mutex_locked_scope make_locked_scope(t_err);
    t_mutex_locked_scope make_locked_scope();

    t_mutex_locked_scope trymake_locked_scope(t_err);
    t_mutex_locked_scope trymake_locked_scope();

  private:
    friend class t_mutex_locked_scope;
    named::t_void enter_scope_(t_mutex_locked_scope*);
    named::t_void leave_scope_(t_mutex_locked_scope*);

    ::pthread_mutex_t mutex_;
    t_validity        valid_;
  };

  inline
  t_mutex_locked_scope::t_mutex_locked_scope(t_mutex_locked_scope&& scope)
    : lock_(scope.swap_(nullptr)) {
    if (lock_)
      lock_->enter_scope_(this);
  }

  inline
  t_mutex_locked_scope::~t_mutex_locked_scope() {
    if (lock_)
      lock_->leave_scope_(this);
  }

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

  // thread
  // conditional_variable
}
}

#endif
