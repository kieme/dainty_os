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
  using clock::to_;

///////////////////////////////////////////////////////////////////////////////

  t_mutex_lock::t_mutex_lock() noexcept
    : valid_{call_pthread_mutex_init(mutex_) == 0 ? VALID : INVALID} {
  }

  t_mutex_lock::t_mutex_lock(t_err err) noexcept
    : valid_{call_pthread_mutex_init(err, mutex_)} {
  }

  t_mutex_lock::t_mutex_lock(const pthread_mutexattr_t& attr) noexcept
    : valid_{call_pthread_mutex_init(mutex_, attr) == 0 ? VALID : INVALID} {
  }

  t_mutex_lock::t_mutex_lock(t_err err, const pthread_mutexattr_t& attr) noexcept
    : valid_ {call_pthread_mutex_init(err, mutex_, attr)} {
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

  t_mutex_locked_scope t_mutex_lock::make_locked_scope(t_err err,
                                                       t_time time) noexcept {
    if (!err) {
      if (valid_ == VALID) {
        if (call_pthread_mutex_timedlock(err, mutex_, to_(time)) == VALID)
          return {this};
      } else
        err = 5; // XXX
    }
    return {nullptr};
  }

  t_mutex_locked_scope t_mutex_lock::make_locked_scope(t_time time) noexcept {
    if (valid_ == VALID &&
        call_pthread_mutex_timedlock(mutex_, to_(time)) == 0)
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

  t_recursive_mutex_lock::t_recursive_mutex_lock() noexcept
    : mutex_(call_pthread_set_recursive(call_pthread_init(attr_))) {
  }

  t_recursive_mutex_lock::t_recursive_mutex_lock(t_err err) noexcept
    : mutex_(err, call_pthread_set_recursive(err,
                                             call_pthread_init(err, attr_))) {
  }

  t_recursive_mutex_lock::
    t_recursive_mutex_lock(pthread_mutexattr_t& attr) noexcept
    : mutex_(call_pthread_set_recursive(attr)) {
  }

  t_recursive_mutex_lock::
    t_recursive_mutex_lock(t_err err, pthread_mutexattr_t& attr) noexcept
    : mutex_(err, call_pthread_set_recursive(err, attr)) {
  }

///////////////////////////////////////////////////////////////////////////////

  t_cond_var::t_cond_var() noexcept
    : valid_{call_pthread_cond_init(cond_) == 0 ? VALID : INVALID} {
  }

  t_cond_var::t_cond_var(t_err err) noexcept
    : valid_{call_pthread_cond_init(err, cond_)} {
  }

  t_cond_var::t_cond_var(const pthread_condattr_t& attr) noexcept
    : valid_{call_pthread_cond_init(cond_, attr) == 0 ? VALID : INVALID} {
  }

  t_cond_var::t_cond_var(t_err err, const pthread_condattr_t& attr) noexcept
    : valid_{call_pthread_cond_init(err, cond_, attr)} {
  }

  t_cond_var::~t_cond_var() noexcept {
    if (valid_ == VALID)
      call_pthread_cond_destroy(cond_);
  }

  t_int t_cond_var::signal() noexcept {
    if (valid_ == VALID)
      return call_pthread_cond_signal(cond_);
    return -1;
  }

  t_validity t_cond_var::signal(t_err err) noexcept {
    if (!err) {
      if (valid_ == VALID)
        return call_pthread_cond_signal(err, cond_);
      err = 10; // XXX
    }
    return INVALID;
  }

  t_int t_cond_var::broadcast() noexcept {
    if (valid_ == VALID)
      return call_pthread_cond_broadcast(cond_);
    return -1;
  }

  t_validity t_cond_var::broadcast(t_err err) noexcept {
    if (!err) {
      if (valid_ == VALID)
        return call_pthread_cond_broadcast(err, cond_);
      err = 10; // XXX
    }
    return INVALID;
  }

  t_int t_cond_var::wait(t_mutex_lock& lock) noexcept {
    if (valid_ == VALID)
      return call_pthread_cond_wait(cond_, lock.mutex_);
    return -1;
  }

  t_validity t_cond_var::wait(t_err err, t_mutex_lock& lock) noexcept {
    if (!err) {
      if (valid_ == VALID)
        return call_pthread_cond_wait(err, cond_, lock.mutex_);
      err = 10; // XXX
    }
    return INVALID;
  }

  t_int t_cond_var::wait_until(t_mutex_lock& lock, t_time time) noexcept {
    if (valid_ == VALID)
      return call_pthread_cond_timedwait(cond_, lock.mutex_, to_(time));
    return -1;
  }

  t_validity t_cond_var::wait_until(t_err err, t_mutex_lock& lock,
                                    t_time time) noexcept {
    if (!err) {
      if (valid_ == VALID)
        return call_pthread_cond_timedwait(err, cond_, lock.mutex_, to_(time));
      err = 10; // XXX
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_monotonic_cond_var::t_monotonic_cond_var() noexcept
    : cond_(call_pthread_set_monotonic(call_pthread_init(attr_))) {
  }

  t_monotonic_cond_var::t_monotonic_cond_var(t_err err) noexcept
    : cond_(err, call_pthread_set_monotonic(err,
                                            call_pthread_init(err, attr_))) {
  }

  t_monotonic_cond_var::t_monotonic_cond_var(pthread_condattr_t& attr) noexcept
    : cond_(call_pthread_set_monotonic(attr)) {
  }

  t_monotonic_cond_var::t_monotonic_cond_var(t_err err,
                                             pthread_condattr_t& attr) noexcept
    : cond_(err, call_pthread_set_monotonic(err, attr)) {
  }

///////////////////////////////////////////////////////////////////////////////

  t_monotonic_lock::t_monotonic_lock() noexcept : cnt_{0}, mutex_{}, cond_{} {
  }

  t_monotonic_lock::t_monotonic_lock(t_err err) noexcept
    : cnt_{0}, mutex_{err}, cond_{err} {
  }

  t_locked_scope t_monotonic_lock::make_locked_scope(t_err err) noexcept {
    if (!err) {
      if (*this == VALID) {
        ::pthread_t th = call_pthread_self();
        <% t_mutex_locked_scope scope{mutex_.make_locked_scope(err)};
          if (!err) {
            if (!cnt_) {
              owner_ = th;
              cnt_   = 1;
            } else if (owner_ == th)
              ++cnt_;
            else {
              do {
                cond_.wait(err,  mutex_);
              } while (!err && cnt_);
              if (!err) {
                owner_ = th;
                cnt_ = 1;
              }
            }
            if (!err)
              return {this};
          }
        %>
      } else
        err = 10; // XXX
    }
    return {nullptr};
  }

  t_locked_scope t_monotonic_lock::make_locked_scope() noexcept {
    if (*this == VALID) {
      ::pthread_t th = call_pthread_self();
      <% t_mutex_locked_scope scope{mutex_.make_locked_scope()};
        if (scope == VALID) {
          named::t_int j = 0;
          if (!cnt_) {
            owner_ = th;
            cnt_   = 1;
          } else if (owner_ == th)
            ++cnt_;
          else {
            do {
              j = cond_.wait(mutex_);
            } while (!j && cnt_);
            if (!j) {
              owner_ = th;
              cnt_ = 1;
            }
          }
          if (!j)
            return {this};
        }
      %>
    }
    return {nullptr};
  }

  t_locked_scope t_monotonic_lock::trymake_locked_scope(t_err err) noexcept {
    if (!err) {
      if (*this == VALID) {
        ::pthread_t th = call_pthread_self();
        <% t_mutex_locked_scope scope{mutex_.make_locked_scope(err)};
          if (!err) {
            if (!cnt_) {
              owner_ = th;
              cnt_   = 1;
            } else if (owner_ == th)
              ++cnt_;
            else
              return {nullptr};
            return {this};
          }
        %>
      } else
        err = 10; // XXX
    }
    return {nullptr};
  }

  t_locked_scope t_monotonic_lock::trymake_locked_scope() noexcept {
    if (*this == VALID) {
      ::pthread_t th = call_pthread_self();
      <% t_mutex_locked_scope scope{mutex_.make_locked_scope()};
        if (scope == VALID) {
          if (!cnt_) {
            owner_ = th;
            cnt_   = 1;
          } else if (owner_ == th)
            ++cnt_;
          else
            return {nullptr};
          return {this};
        }
      %>
    }
    return {nullptr};
  }

  t_locked_scope
    t_monotonic_lock::make_locked_scope(t_err err, t_time time) noexcept {
    if (!err) {
      if (*this == VALID) {
        ::pthread_t th = call_pthread_self();
        <% t_mutex_locked_scope scope{mutex_.make_locked_scope(err)};
          if (!err) {
            if (!cnt_) {
              owner_ = th;
              cnt_   = 1;
            } else if (owner_ == th)
              ++cnt_;
            else {
              do {
                cond_.wait_for(err, mutex_, time);
              } while (!err && cnt_);
              if (!err) {
                owner_ = th;
                cnt_ = 1;
              }
            }
            if (!err)
              return {this};
          }
        %>
      } else
        err = 10; // XXX
    }
    return {nullptr};
  }

  t_locked_scope
    t_monotonic_lock::make_locked_scope(t_time time) noexcept {
    if (*this == VALID) {
      ::pthread_t th = call_pthread_self();
      <% t_mutex_locked_scope scope{mutex_.make_locked_scope()};
        if (scope == VALID) {
          named::t_int j = 0;
          if (!cnt_) {
            owner_ = th;
            cnt_   = 1;
          } else if (owner_ == th)
            ++cnt_;
          else {
            do {
              j = cond_.wait_for(mutex_, time);
            } while (!j && cnt_);
            if (!j) {
              owner_ = th;
              cnt_ = 1;
            }
          }
          if (!j)
            return {this};
        }
      %>
    }
    return {nullptr};
  }

  named::t_void t_monotonic_lock::enter_scope_(t_locked_scope* lock) noexcept {
     // debugging
  }

  named::t_void t_monotonic_lock::leave_scope_(t_locked_scope* lock) noexcept {
    if (*this == VALID) {
      ::pthread_t th = call_pthread_self();
      <% t_mutex_locked_scope scope{mutex_.make_locked_scope()};
        if (scope == VALID) {
          if (cnt_ && call_pthread_equal(th, owner_)) {
            --cnt_;
            if (!cnt_)
              cond_.signal();
          }
        }
      %>
    }
  }

///////////////////////////////////////////////////////////////////////////////

  t_pthread::t_pthread() noexcept : valid_{INVALID}, joinable_(true)  {
  }

  t_pthread::t_pthread(p_run run, p_arg arg) noexcept
   : valid_{create(run, arg) == 0 ? VALID : INVALID}, joinable_(true) {
  }

  t_pthread::t_pthread(t_err err, p_run run, p_arg arg) noexcept
    : valid_{create(err, run, arg)}, joinable_(true) {
  }

  t_pthread::t_pthread(::pthread_attr_t& attr, p_run run, p_arg arg) noexcept
    : valid_{create(attr, run, arg) == 0 ? VALID : INVALID}, joinable_(true) {
  }

  t_pthread::t_pthread(t_err err, ::pthread_attr_t& attr, p_run run,
                       p_arg arg) noexcept
    : valid_{create(err, attr, run, arg)}, joinable_(true) {
  }

  t_pthread::~t_pthread() noexcept {
    if (valid_ == VALID && joinable_)
      join();
  }

  t_int t_pthread::create(p_run run, p_arg arg) noexcept {
    if (valid_ == INVALID)
      return call_pthread_create(run, arg);
    return -1;
  }

  t_validity t_pthread::create(t_err err, p_run run, p_arg arg) noexcept {
    if (!err) {
      if (valid_ == INVALID)
        valid_ = call_pthread_create(err, run, arg);
      else
        err = 19;
    }
    return valid_;
  }

  t_int t_pthread::create(::pthread_attr_t& attr, p_run run,
                          p_arg arg) noexcept {
    if (valid_ == INVALID) {
      // check if deteched - XXX
      return call_pthread_create(attr, run, arg);
    }
    return -1;
  }

  t_validity t_pthread::create(t_err err, ::pthread_attr_t& attr, p_run run,
                               p_arg arg) noexcept {
    if (!err) {
      if (valid_ == INVALID) {
       // check if deteched - XXX
        valid_ = call_pthread_create(err, attr, run, arg);
      } else
        err = 19;
    }
    return valid_;
  }

  t_int t_pthread::detach() noexcept {
    t_int tmp = -1;
    if (valid_ == VALID && joinable_) {
      tmp = call_pthread_detach(thread_);
      if (tmp == 0)
        joinable_ == false;
    }
    return tmp;
  }

  t_validity t_pthread::detach(t_err err) noexcept {
    t_validity valid = INVALID;
    if (!err) {
      if (valid_ == VALID && joinable_) {
        valid = call_pthread_detach(err, thread_);
        if (valid == VALID)
          joinable_ == false;
      } else
        err = 19; // XXX
    }
    return valid;
  }

  t_int t_pthread::join() noexcept {
    t_int tmp = -1;
    if (valid_ == VALID && joinable_) {
      tmp = call_pthread_join(thread_);
      if (tmp == 0)
        valid_ = INVALID;
    }
    return tmp;
  }

  t_validity t_pthread::join(t_err err) noexcept {
    return INVALID;
  }

  t_int t_pthread::join(t_int& status) noexcept {
    return -1;
  }

  t_validity t_pthread::join(t_err err, t_int& status) noexcept {
    return INVALID;
  }

  t_int t_pthread::cancel() noexcept {
    return -1;
  }

  t_validity t_pthread::cancel(t_err err) noexcept {
    return INVALID;
  }

  t_int t_pthread::exit(t_int status) noexcept {
    return -1;
  }

  t_validity t_pthread::exit(t_err err, t_int status) noexcept {
    return INVALID;
  }

  t_int t_pthread::set_name(p_cstr name) noexcept {
    return -1;
  }

  t_validity t_pthread::set_name(t_err err, p_cstr name) noexcept {
    return INVALID;
  }

  t_int t_pthread::get_name(p_cstr name, t_n len) noexcept {
    return -1;
  }

  t_validity t_pthread::get_name(t_err err, p_cstr name, t_n len) noexcept {
    return INVALID;
  }

  t_bool t_pthread::is_equal(const ::pthread_t& pthread) noexcept {
    if (valid_ == VALID)
      return call_pthread_equal(thread_, pthread);
    return false;
  }

  t_bool t_pthread::is_equal(t_err err, const ::pthread_t& pthread) noexcept {
    if (!err) {
      if (valid_ == VALID)
        return call_pthread_equal(thread_, pthread);
      err = 10; //XXX
    }
    return false;
  }

  ::pthread_t t_pthread::get_self() noexcept {
    return call_pthread_self();
  }

  ::pthread_t t_pthread::get_self(t_err err) noexcept {
    if (!err)
      return call_pthread_self();
    return {};
  }

  t_int t_pthread::set_name(t_pthread& pthread, p_cstr name) noexcept {
    return -1;
  }

  t_validity t_pthread::set_name(t_err err, t_pthread& pthread,
                                 p_cstr name) noexcept {
    return INVALID;
  }

  t_int t_pthread::get_name(t_pthread& pthread, p_cstr name,
                            t_n len) noexcept {
    return -1;
  }

  t_validity t_pthread::get_name(t_err err, t_pthread& pthread, p_cstr name,
                                 t_n len) noexcept {
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////
}
}
}
