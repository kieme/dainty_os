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
    t_mutex_locked_scope(t_mutex_locked_scope&&) noexcept;
    ~t_mutex_locked_scope() noexcept; // explicit noexcept for clarity

    t_mutex_locked_scope(const t_mutex_locked_scope&) = delete;
    t_mutex_locked_scope& operator=(const t_mutex_locked_scope&) = delete;
    t_mutex_locked_scope& operator=(t_mutex_locked_scope&&) = delete;

    operator t_validity() const noexcept { return lock_ ? VALID : INVALID; }

  private:
    friend class t_mutex_lock;
    inline t_mutex_locked_scope(t_mutex_lock* lock) noexcept : lock_(lock) {
    }
    inline t_mutex_lock* swap_(t_mutex_lock* lock)  noexcept {
      t_mutex_lock* tmp = lock_; lock_ = lock; return tmp;
    }
    t_mutex_lock* lock_;
  };

  class t_mutex_lock {
  public:
    t_mutex_lock() noexcept;
    t_mutex_lock(t_err err) noexcept;
    t_mutex_lock(const pthread_mutexattr_t&) noexcept;
    t_mutex_lock(t_err err, const pthread_mutexattr_t&) noexcept;
    ~t_mutex_lock() noexcept; // explicit noexcept for clarity

    t_mutex_lock(const t_mutex_lock&) = delete;
    t_mutex_lock(t_mutex_lock&&) = delete;
    t_mutex_lock& operator=(const t_mutex_lock&) = delete;
    t_mutex_lock& operator=(t_mutex_lock&&) = delete;

    operator t_validity() const noexcept { return valid_; }

    t_mutex_locked_scope make_locked_scope(t_err) noexcept;
    t_mutex_locked_scope make_locked_scope() noexcept;

    t_mutex_locked_scope trymake_locked_scope(t_err) noexcept;
    t_mutex_locked_scope trymake_locked_scope() noexcept;

  private:
    friend class t_mutex_locked_scope;
    friend class t_cond_var;
    named::t_void enter_scope_(t_mutex_locked_scope*) noexcept;
    named::t_void leave_scope_(t_mutex_locked_scope*) noexcept;

    ::pthread_mutex_t     mutex_;
    t_validity            valid_;
  };

  inline
  t_mutex_locked_scope::t_mutex_locked_scope(t_mutex_locked_scope&& scope) noexcept
    : lock_(scope.swap_(nullptr)) {
    if (lock_)
      lock_->enter_scope_(this);
  }

  inline
  t_mutex_locked_scope::~t_mutex_locked_scope() noexcept {
    if (lock_)
      lock_->leave_scope_(this);
  }

///////////////////////////////////////////////////////////////////////////////

  class t_recursive_mutex_lock {
  public:
    t_recursive_mutex_lock() noexcept;
    t_recursive_mutex_lock(t_err err) noexcept;
    t_recursive_mutex_lock(pthread_mutexattr_t&) noexcept;
    t_recursive_mutex_lock(t_err err, pthread_mutexattr_t&) noexcept;

    operator t_validity() const noexcept;

    t_mutex_locked_scope make_locked_scope(t_err) noexcept;
    t_mutex_locked_scope make_locked_scope() noexcept;

    t_mutex_locked_scope trymake_locked_scope(t_err) noexcept;
    t_mutex_locked_scope trymake_locked_scope() noexcept;

  private:
    ::pthread_mutexattr_t attr_;
    t_mutex_lock          mutex_;
  };

///////////////////////////////////////////////////////////////////////////////

  class t_cond_var {
  public:
    t_cond_var() noexcept;
    t_cond_var(t_err err) noexcept;
    t_cond_var(const pthread_condattr_t&) noexcept;
    t_cond_var(t_err err, const pthread_condattr_t&) noexcept;
    ~t_cond_var() noexcept; // explicit noexcept for clarity

    t_cond_var(const t_cond_var&) = delete;
    t_cond_var(t_cond_var&&) = delete;
    t_cond_var& operator=(const t_cond_var&) = delete;
    t_cond_var& operator=(t_cond_var&&) = delete;

    operator t_validity() const noexcept { return valid_; }

    t_validity signal() noexcept;
    t_validity signal(t_err) noexcept;

    t_validity broadcast() noexcept;
    t_validity broadcast(t_err) noexcept;

    t_validity wait(t_mutex_lock&) noexcept;
    t_validity wait(t_err, t_mutex_lock&) noexcept;

    t_validity wait_until(t_mutex_lock&, const timespec&) noexcept;
    t_validity wait_until(t_err, t_mutex_lock&, const timespec&) noexcept;

  private:
    ::pthread_cond_t cond_;
    t_validity       valid_;
  };

///////////////////////////////////////////////////////////////////////////////

  class t_monotonic_cond_var {
  public:
    t_monotonic_cond_var() noexcept;
    t_monotonic_cond_var(t_err err) noexcept;
    t_monotonic_cond_var(pthread_condattr_t&) noexcept;
    t_monotonic_cond_var(t_err err, pthread_condattr_t&) noexcept;

    operator t_validity() const noexcept;

    t_validity signal() noexcept;
    t_validity signal(t_err) noexcept;

    t_validity broadcast() noexcept;
    t_validity broadcast(t_err) noexcept;

    t_validity wait(t_mutex_lock&) noexcept;
    t_validity wait(t_err, t_mutex_lock&) noexcept;

    t_validity wait_for(t_mutex_lock&, const timespec&) noexcept;
    t_validity wait_for(t_err, t_mutex_lock&, const timespec&) noexcept;

  private:
    ::pthread_condattr_t attr_;
    t_cond_var           cond_;
  };

///////////////////////////////////////////////////////////////////////////////

  // thread
  // conditional_variable
  /*
  class thread {
  public:
    thread();
    thread(t_err);
    thread(const pthread_attr_t);
    thread(t_err);
  private:
    ::pthread_t thread_;
  };
  */
}
}

#endif
