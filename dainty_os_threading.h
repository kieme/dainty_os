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

#ifndef _DAINTY_OS_THREADING_H_
#define _DAINTY_OS_THREADING_H_

// description
// os: operating system functionality used by dainty
//
//  not a complete API but only the things used by dainty.

#include "dainty_named.h"
#include "dainty_oops.h"
#include "dainty_os_call.h"
#include "dainty_os_clock.h"

namespace dainty
{
namespace os
{
namespace threading
{
  using clock::t_time;
  using named::p_cstr;
  using named::t_n;

///////////////////////////////////////////////////////////////////////////////

  class t_mutex_lock;

  class t_mutex_locked_scope {
  public:
    t_mutex_locked_scope(t_mutex_locked_scope&&) noexcept;
    ~t_mutex_locked_scope() noexcept; // explicit noexcept for clarity

    t_mutex_locked_scope(const t_mutex_locked_scope&) = delete;
    t_mutex_locked_scope& operator=(const t_mutex_locked_scope&) = delete;
    t_mutex_locked_scope& operator=(t_mutex_locked_scope&&) = delete;

    operator t_validity() const noexcept;

  private:
    friend class t_mutex_lock;
    t_mutex_locked_scope(t_mutex_lock*) noexcept;
    t_mutex_lock* swap_(t_mutex_lock*)  noexcept;
    t_mutex_lock* lock_;
  };

///////////////////////////////////////////////////////////////////////////////

  class t_monotonic_lock;

  class t_locked_scope {
  public:
    t_locked_scope(t_locked_scope&&) noexcept;
    ~t_locked_scope() noexcept; // explicit noexcept for clarity

    t_locked_scope(const t_locked_scope&) = delete;
    t_locked_scope& operator=(const t_locked_scope&) = delete;
    t_locked_scope& operator=(t_locked_scope&&) = delete;

    operator t_validity() const noexcept;

  private:
    friend class t_monotonic_lock;
    t_locked_scope(t_monotonic_lock*) noexcept;
    t_monotonic_lock* swap_(t_monotonic_lock*)  noexcept;
    t_monotonic_lock* lock_;
  };

///////////////////////////////////////////////////////////////////////////////

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

    operator t_validity() const noexcept;

    t_mutex_locked_scope make_locked_scope(t_err) noexcept;
    t_mutex_locked_scope make_locked_scope() noexcept;

    t_mutex_locked_scope make_locked_scope(t_err, t_time) noexcept;
    t_mutex_locked_scope make_locked_scope(t_time) noexcept;

    t_mutex_locked_scope trymake_locked_scope(t_err) noexcept;
    t_mutex_locked_scope trymake_locked_scope() noexcept;

  private:
    friend class t_mutex_locked_scope;
    friend class t_cond_var;
    named::t_void enter_scope_(t_mutex_locked_scope*) noexcept;
    named::t_void leave_scope_(t_mutex_locked_scope*) noexcept;

    ::pthread_mutex_t mutex_;
    t_validity        valid_;
  };

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

    t_mutex_locked_scope make_locked_scope(t_err, t_time) noexcept;
    t_mutex_locked_scope make_locked_scope(t_time) noexcept;

    t_mutex_locked_scope trymake_locked_scope(t_err) noexcept;
    t_mutex_locked_scope trymake_locked_scope() noexcept;

  private:
    friend class t_cond_var;
    friend class t_monotonic_cond_var;
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

    operator t_validity() const noexcept;

    t_int      signal() noexcept;
    t_validity signal(t_err) noexcept;

    t_int      broadcast() noexcept;
    t_validity broadcast(t_err) noexcept;

    t_int      wait(t_mutex_lock&) noexcept;
    t_validity wait(t_err, t_mutex_lock&) noexcept;

    t_int      wait_until(t_mutex_lock&, t_time) noexcept;
    t_validity wait_until(t_err, t_mutex_lock&, t_time) noexcept;

    t_int      wait(t_recursive_mutex_lock&) noexcept;
    t_validity wait(t_err, t_recursive_mutex_lock&) noexcept;

    t_int      wait_until(t_recursive_mutex_lock&, t_time) noexcept;
    t_validity wait_until(t_err, t_recursive_mutex_lock&, t_time) noexcept;

  private:
    ::pthread_cond_t cond_;
    t_validity       valid_;
  };

///////////////////////////////////////////////////////////////////////////////

  class t_monotonic_cond_var {
  public:
    t_monotonic_cond_var() noexcept;
    t_monotonic_cond_var(t_err) noexcept;
    t_monotonic_cond_var(pthread_condattr_t&) noexcept;
    t_monotonic_cond_var(t_err, pthread_condattr_t&) noexcept;

    operator t_validity() const noexcept;

    t_int      signal() noexcept;
    t_validity signal(t_err) noexcept;

    t_int      broadcast() noexcept;
    t_validity broadcast(t_err) noexcept;

    t_int      wait(t_mutex_lock&) noexcept;
    t_validity wait(t_err, t_mutex_lock&) noexcept;

    t_int      wait_for(t_mutex_lock&, t_time) noexcept;
    t_validity wait_for(t_err, t_mutex_lock&, t_time) noexcept;

    t_int      wait(t_recursive_mutex_lock&) noexcept;
    t_validity wait(t_err, t_recursive_mutex_lock&) noexcept;

    t_int      wait_for(t_recursive_mutex_lock&, t_time) noexcept;
    t_validity wait_for(t_err, t_recursive_mutex_lock&, t_time) noexcept;

  private:
    ::pthread_condattr_t attr_;
    t_cond_var           cond_;
  };

///////////////////////////////////////////////////////////////////////////////

  class t_monotonic_lock {
  public:
    t_monotonic_lock() noexcept;
    t_monotonic_lock(t_err err) noexcept;

    operator t_validity() const noexcept;

    t_locked_scope make_locked_scope(t_err) noexcept;
    t_locked_scope make_locked_scope() noexcept;

    t_locked_scope trymake_locked_scope(t_err) noexcept;
    t_locked_scope trymake_locked_scope() noexcept;

    t_locked_scope make_locked_scope(t_err, t_time) noexcept;
    t_locked_scope make_locked_scope(t_time) noexcept;

  private:
    friend class t_locked_scope;
    named::t_void enter_scope_(t_locked_scope*) noexcept;
    named::t_void leave_scope_(t_locked_scope*) noexcept;

    ::pthread_t          owner_;
    named::t_uint        cnt_;
    t_mutex_lock         mutex_;
    t_monotonic_cond_var cond_;
  };

///////////////////////////////////////////////////////////////////////////////

  class t_pthread {
  public:
    enum  p_arg_tag_ {};
    using p_arg_ = named::p_void;
    using p_arg  = named::t_explicit<p_arg_, p_arg_tag_>;
    using p_run  = p_arg (*)(p_arg arg);

    t_pthread() noexcept;
    t_pthread(p_run, p_arg) noexcept;
    t_pthread(t_err, p_run, p_arg) noexcept;
    t_pthread(::pthread_attr_t&, p_run, p_arg) noexcept;
    t_pthread(t_err, ::pthread_attr_t&, p_run, p_arg) noexcept;
    ~t_pthread() noexcept;

    t_pthread(const t_pthread&) = delete;
    t_pthread(t_pthread&&) = delete;
    t_pthread& operator=(const t_pthread&) = delete;
    t_pthread& operator=(t_pthread&&) = delete;

    operator t_validity() const noexcept;

    t_bool   is_joinable() const noexcept;

    t_int      create(p_run, p_arg) noexcept;
    t_validity create(t_err, p_run, p_arg) noexcept;

    t_int      create(::pthread_attr_t&, p_run, p_arg) noexcept;
    t_validity create(t_err, ::pthread_attr_t&, p_run, p_arg) noexcept;

    t_int      detach() noexcept;
    t_validity detach(t_err) noexcept;

    t_int      join() noexcept;
    t_validity join(t_err) noexcept;

    t_int      join(       t_int& status) noexcept;
    t_validity join(t_err, t_int& status) noexcept;

    t_int      cancel() noexcept;
    t_validity cancel(t_err) noexcept;

    t_int      exit(       t_int status) noexcept;
    t_validity exit(t_err, t_int status) noexcept;

    t_int      set_name(       p_cstr name) noexcept;
    t_validity set_name(t_err, p_cstr name) noexcept;
    t_int      get_name(       p_cstr name, t_n) noexcept;
    t_validity get_name(t_err, p_cstr name, t_n) noexcept;

    t_bool is_equal(       const ::pthread_t&) noexcept;
    t_bool is_equal(t_err, const ::pthread_t&) noexcept;

    static ::pthread_t get_self()      noexcept;
    static ::pthread_t get_self(t_err) noexcept;

    static t_int      set_name(       t_pthread&, p_cstr name) noexcept;
    static t_validity set_name(t_err, t_pthread&, p_cstr name) noexcept;
    static t_int      get_name(       t_pthread&, p_cstr name, t_n len) noexcept;
    static t_validity get_name(t_err, t_pthread&, p_cstr name, t_n len) noexcept;

    //bool sigqueue(        const sig_id, const sig_val) noexcept;
    //bool sigqueue(t_err, const sig_id, const sig_val) noexcept;

    // static bool   procsigmask(       const how_type, const sig_set*, sig_set* = 0);
    // static bool   procsigmask(t_err, const how_type, const sig_set*, sig_set* = 0);

  private:
    ::pthread_t thread_;
    t_validity  valid_;
    t_bool      joinable_;
  };

///////////////////////////////////////////////////////////////////////////////

  inline t_mutex_locked_scope::operator t_validity() const noexcept {
    return lock_ ? VALID : INVALID;
  }

  inline
  t_mutex_locked_scope::t_mutex_locked_scope(t_mutex_lock* lock) noexcept
    : lock_(lock) {
  }

  inline
  t_mutex_lock* t_mutex_locked_scope::swap_(t_mutex_lock* lock) noexcept {
    t_mutex_lock* tmp = lock_; lock_ = lock; return tmp;
  }

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

  inline t_locked_scope::operator t_validity() const noexcept {
    return lock_ ? VALID : INVALID;
  }

  inline
  t_locked_scope::t_locked_scope(t_monotonic_lock* lock) noexcept
    : lock_(lock) {
  }

  inline
  t_monotonic_lock* t_locked_scope::swap_(t_monotonic_lock* lock) noexcept {
    t_monotonic_lock* tmp = lock_; lock_ = lock; return tmp;
  }

  inline
  t_locked_scope::t_locked_scope(t_locked_scope&& scope) noexcept
    : lock_(scope.swap_(nullptr)) {
    if (lock_)
      lock_->enter_scope_(this);
  }

  inline
  t_locked_scope::~t_locked_scope() noexcept {
    if (lock_)
      lock_->leave_scope_(this);
  }

///////////////////////////////////////////////////////////////////////////////

  inline
  t_mutex_lock::operator t_validity() const noexcept {
    return valid_;
  }

///////////////////////////////////////////////////////////////////////////////

  inline
  t_recursive_mutex_lock::operator t_validity() const noexcept {
    return mutex_;
  }

  inline
  t_mutex_locked_scope
    t_recursive_mutex_lock::make_locked_scope(t_err err) noexcept {
    return mutex_.make_locked_scope(err);
  }

  inline
  t_mutex_locked_scope
    t_recursive_mutex_lock::make_locked_scope() noexcept {
    return mutex_.make_locked_scope();
  }

  inline
  t_mutex_locked_scope
    t_recursive_mutex_lock::make_locked_scope(t_err err,
                                              t_time time) noexcept {
    return mutex_.make_locked_scope(err, time);
  }

  inline
  t_mutex_locked_scope
    t_recursive_mutex_lock::make_locked_scope(t_time time) noexcept {
    return mutex_.make_locked_scope(time);
  }

  inline
  t_mutex_locked_scope
    t_recursive_mutex_lock::trymake_locked_scope(t_err err) noexcept {
    return mutex_.trymake_locked_scope(err);
  }

  inline
  t_mutex_locked_scope
    t_recursive_mutex_lock::trymake_locked_scope() noexcept {
    return mutex_.trymake_locked_scope();
  }

///////////////////////////////////////////////////////////////////////////////

  inline
  t_cond_var::operator t_validity() const noexcept {
    return valid_;
  }

  inline
  t_int t_cond_var::wait(t_recursive_mutex_lock& lock) noexcept {
    return wait(lock.mutex_);
  }

  inline
  t_validity t_cond_var::wait(t_err err,
                              t_recursive_mutex_lock& lock) noexcept {
    return wait(err, lock.mutex_);
  }

  inline
  t_int t_cond_var::wait_until(t_recursive_mutex_lock& lock,
                               t_time time) noexcept {
    return wait_until(lock.mutex_, time);
  }

  inline
  t_validity t_cond_var::wait_until(t_err err, t_recursive_mutex_lock& lock,
                                    t_time time) noexcept {
    return wait_until(err, lock.mutex_, time);
  }

///////////////////////////////////////////////////////////////////////////////

  inline
  t_monotonic_cond_var::operator t_validity() const noexcept {
    return cond_;
  }

  inline
  t_int t_monotonic_cond_var::signal() noexcept {
    return cond_.signal();
  }

  inline
  t_validity t_monotonic_cond_var::signal(t_err err) noexcept {
    return cond_.signal(err);
  }

  inline
  t_int t_monotonic_cond_var::broadcast() noexcept {
    return cond_.broadcast();
  }

  inline
  t_validity t_monotonic_cond_var::broadcast(t_err err) noexcept {
    return cond_.broadcast(err);
  }

  inline
  t_int t_monotonic_cond_var::wait(t_mutex_lock& lock) noexcept {
    return cond_.wait(lock);
  }

  inline
  t_validity t_monotonic_cond_var::wait(t_err err,
                                        t_mutex_lock& lock) noexcept {
    return cond_.wait(err, lock);
  }

  inline
  t_int t_monotonic_cond_var::wait_for(t_mutex_lock& lock,
                                       t_time time) noexcept {
    return cond_.wait_until(lock, time);
  }

  inline
  t_validity t_monotonic_cond_var::wait_for(t_err err, t_mutex_lock& lock,
                                            t_time time) noexcept {
    return cond_.wait_until(err, lock, time);
  }

  inline
  t_int t_monotonic_cond_var::wait(t_recursive_mutex_lock& lock) noexcept {
    return wait(lock.mutex_);
  }

  inline
  t_validity t_monotonic_cond_var::wait(t_err err,
                                        t_recursive_mutex_lock& lock) noexcept {
    return wait(err, lock.mutex_);
  }

  inline
  t_int t_monotonic_cond_var::wait_for(t_recursive_mutex_lock& lock,
                                       t_time time) noexcept {
    return wait_for(lock.mutex_, time);
  }

  inline
  t_validity t_monotonic_cond_var::wait_for(t_err err,
                                            t_recursive_mutex_lock& lock,
                                            t_time time) noexcept {
    return wait_for(err, lock.mutex_, time);
  }

///////////////////////////////////////////////////////////////////////////////

  inline
  t_monotonic_lock::operator t_validity() const noexcept {
    return (mutex_ == VALID && cond_ == VALID) ?  VALID : INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  inline
  t_pthread::operator t_validity() const noexcept {
    return valid_;
  }

  inline
  t_bool t_pthread::is_joinable() const noexcept {
    return joinable_;
  }

///////////////////////////////////////////////////////////////////////////////
}
}
}

#endif
