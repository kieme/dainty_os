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

#include "dainty_os_clock.h"
#include "dainty_os_threading.h"

namespace dainty
{
namespace os
{
namespace threading
{
  using clock::to_;

///////////////////////////////////////////////////////////////////////////////

  t_mutex_lock::t_mutex_lock() noexcept {
    if (call_pthread_mutex_init(mutex_) == 0)
      valid_ = VALID;
  }

  t_mutex_lock::t_mutex_lock(t_err err) noexcept {
    T_ERR_GUARD(err) {
      valid_ = call_pthread_mutex_init(err, mutex_);
    }
  }

  t_mutex_lock::t_mutex_lock(const ::pthread_mutexattr_t& attr) noexcept {
    if (call_pthread_mutex_init(mutex_, attr) == 0)
      valid_ = VALID;
  }

  t_mutex_lock::t_mutex_lock(t_err err,
                             const ::pthread_mutexattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      valid_ = call_pthread_mutex_init(err, mutex_, attr);
    }
  }

  t_mutex_lock::~t_mutex_lock() {
    if (valid_ == VALID)
      call_pthread_mutex_destroy(mutex_);
  }

  t_mutex_lock::t_locked_scope t_mutex_lock::make_locked_scope() noexcept {
    if (valid_ == VALID && call_pthread_mutex_lock(mutex_) == 0)
      return {this};
    return {nullptr};
  }

  t_mutex_lock::t_locked_scope
      t_mutex_lock::make_locked_scope(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID) {
        if (call_pthread_mutex_lock(err, mutex_) == VALID)
          return {this};
      } else
        err = E_INVALID_INST;
    }
    return {nullptr};
  }

  t_mutex_lock::t_locked_scope
      t_mutex_lock::make_locked_scope(t_err err, t_time time) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID) {
        if (call_pthread_mutex_timedlock(err, mutex_, to_(time)) == VALID)
          return {this};
      } else
        err = E_INVALID_INST;
    }
    return {nullptr};
  }

  t_mutex_lock::t_locked_scope
      t_mutex_lock::make_locked_scope(t_time time) noexcept {
    if (valid_ == VALID &&
        call_pthread_mutex_timedlock(mutex_, to_(time)) == 0)
      return {this};
    return {nullptr};
  }

  t_mutex_lock::t_locked_scope
      t_mutex_lock::trymake_locked_scope(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID) {
        if (call_pthread_mutex_trylock(err, mutex_) == VALID)
          return {this};
      } else
        err = E_INVALID_INST;
    }
    return {nullptr};
  }

  t_mutex_lock::t_locked_scope t_mutex_lock::trymake_locked_scope() noexcept {
    if (valid_ == VALID && call_pthread_mutex_trylock(mutex_) == 0)
      return {this};
    return {nullptr};
  }

  t_void t_mutex_lock::enter_scope_(t_locked_scope*) noexcept {
    // can  use for debugging
  }

  t_void t_mutex_lock::leave_scope_(t_locked_scope* scope) noexcept {
    if (*scope == VALID)
      call_pthread_mutex_lock(mutex_);
    // can  use for debugging
  }

///////////////////////////////////////////////////////////////////////////////

  t_recursive_mutex_lock::t_recursive_mutex_lock() noexcept {
    ::pthread_mutexattr_t attr;
    if (call_pthread_init(attr) == 0) {
      if (call_pthread_set_recursive(attr) == 0 &&
          call_pthread_mutex_init(mutex_, attr) == 0)
        valid_ = VALID;
      call_pthread_destroy(attr);
    }
  }

  t_recursive_mutex_lock::t_recursive_mutex_lock(t_err err) noexcept {
    T_ERR_GUARD(err) {
      ::pthread_mutexattr_t attr;
      call_pthread_init(err, attr);
      call_pthread_set_recursive(err.tag(1), attr);
      valid_ = call_pthread_mutex_init(err, mutex_, attr);
      if (err.tag() == 1)
        call_pthread_destroy(attr);
    }
  }

  t_recursive_mutex_lock::
      t_recursive_mutex_lock(const ::pthread_mutexattr_t& attr) noexcept {
    if (call_pthread_is_recursive(attr) &&
        call_pthread_mutex_init(mutex_, attr) == 0)
      valid_ = VALID;
  }

  t_recursive_mutex_lock::
      t_recursive_mutex_lock(t_err err,
                             const ::pthread_mutexattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_is_recursive(attr))
        valid_ = call_pthread_mutex_init(err, mutex_, attr);
      else
        err = E_ATTR_NOT_RECURSIVE;
    }
  }

  t_recursive_mutex_lock::~t_recursive_mutex_lock() {
    if (valid_ == VALID)
      call_pthread_mutex_destroy(mutex_);
  }

  t_recursive_mutex_lock::t_locked_scope
      t_recursive_mutex_lock::make_locked_scope(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID) {
        if (call_pthread_mutex_lock(err, mutex_) == VALID)
          return {this};
      } else
        err = E_INVALID_INST;
    }
    return {nullptr};
  }

  t_recursive_mutex_lock::t_locked_scope
      t_recursive_mutex_lock::make_locked_scope() noexcept {
    if (valid_ == VALID && call_pthread_mutex_lock(mutex_) == 0)
      return {this};
    return {nullptr};
  }

  t_recursive_mutex_lock::t_locked_scope
      t_recursive_mutex_lock::make_locked_scope(t_err err,
                                                t_time time) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID) {
        if (call_pthread_mutex_timedlock(err, mutex_, to_(time)) == VALID)
          return {this};
      } else
        err = E_INVALID_INST;
    }
    return {nullptr};
  }

  t_recursive_mutex_lock::t_locked_scope
      t_recursive_mutex_lock::make_locked_scope(t_time time) noexcept {
    if (valid_ == VALID &&
        call_pthread_mutex_timedlock(mutex_, to_(time)) == 0)
      return {this};
    return {nullptr};
  }

  t_recursive_mutex_lock::t_locked_scope
      t_recursive_mutex_lock::trymake_locked_scope(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID) {
        if (call_pthread_mutex_trylock(err, mutex_) == VALID)
          return {this};
      } else
        err = E_INVALID_INST;
    }
    return {nullptr};
  }

  t_recursive_mutex_lock::t_locked_scope
      t_recursive_mutex_lock::trymake_locked_scope() noexcept {
    if (valid_ == VALID && call_pthread_mutex_trylock(mutex_) == 0)
      return {this};
    return {nullptr};
  }

  t_void t_recursive_mutex_lock::enter_scope_(t_locked_scope*) noexcept {
    // can  use for debugging
  }

  t_void t_recursive_mutex_lock::leave_scope_(t_locked_scope* scope) noexcept {
    if (*scope == VALID)
      call_pthread_mutex_lock(mutex_);
    // can  use for debugging
  }

///////////////////////////////////////////////////////////////////////////////

  t_cond_var::t_cond_var() noexcept {
    if (call_pthread_cond_init(cond_) == 0)
      valid_ = VALID;
  }

  t_cond_var::t_cond_var(t_err err) noexcept {
    T_ERR_GUARD(err) {
      valid_ = call_pthread_cond_init(err, cond_);
    }
  }

  t_cond_var::t_cond_var(const pthread_condattr_t& attr) noexcept {
    if (call_pthread_cond_init(cond_, attr) == 0)
      valid_ = VALID;
  }

  t_cond_var::t_cond_var(t_err err, const pthread_condattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      valid_ = call_pthread_cond_init(err, cond_, attr);
    }
  }

  t_cond_var::~t_cond_var() {
    if (valid_ == VALID)
      call_pthread_cond_destroy(cond_);
  }

  t_int t_cond_var::signal() noexcept {
    if (valid_ == VALID)
      return call_pthread_cond_signal(cond_);
    return -1;
  }

  t_validity t_cond_var::signal(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID)
        return call_pthread_cond_signal(err, cond_);
      err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_cond_var::broadcast() noexcept {
    if (valid_ == VALID)
      return call_pthread_cond_broadcast(cond_);
    return -1;
  }

  t_validity t_cond_var::broadcast(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID)
        return call_pthread_cond_broadcast(err, cond_);
      err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_cond_var::wait_(::pthread_mutex_t& mutex) noexcept {
    if (valid_ == VALID)
      return call_pthread_cond_wait(cond_, mutex);
    return -1;
  }

  t_validity t_cond_var::wait_(t_err err, ::pthread_mutex_t& mutex) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID)
        return call_pthread_cond_wait(err, cond_, mutex);
      err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_cond_var::wait_until_(::pthread_mutex_t& mutex,
                                t_time time) noexcept {
    if (valid_ == VALID)
      return call_pthread_cond_timedwait(cond_, mutex, to_(time));
    return -1;
  }

  t_validity t_cond_var::wait_until_(t_err err, ::pthread_mutex_t& mutex,
                                     t_time time) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID)
        return call_pthread_cond_timedwait(err, cond_, mutex, to_(time));
      err = E_INVALID_INST;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_monotonic_cond_var::t_monotonic_cond_var() noexcept {
    ::pthread_condattr_t attr;
    if (call_pthread_init(attr) == 0) {
      if (call_pthread_set_monotonic(attr) == 0 &&
          call_pthread_cond_init(cond_) == 0)
        valid_ = VALID;
      call_pthread_destroy(attr);
    }
  }

  t_monotonic_cond_var::t_monotonic_cond_var(t_err err) noexcept {
    T_ERR_GUARD(err) {
      ::pthread_condattr_t attr;
      call_pthread_init(err, attr);
      call_pthread_set_monotonic(err.tag(1), attr);
      valid_ = call_pthread_cond_init(err, cond_, attr);
      if (err.tag() == 1)
        call_pthread_destroy(attr);
    }
  }

  t_monotonic_cond_var::
      t_monotonic_cond_var(const ::pthread_condattr_t& attr) noexcept {
    if (call_pthread_is_monotonic(attr) &&
        call_pthread_cond_init(cond_, attr) == 0)
      valid_ = VALID;
  }

  t_monotonic_cond_var::
      t_monotonic_cond_var(t_err err,
                           const ::pthread_condattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_is_monotonic(err, attr))
        valid_ = call_pthread_cond_init(err, cond_, attr);
      else
        err = E_ATTR_NOT_MONOTONIC;
    }
  }

  t_monotonic_cond_var::~t_monotonic_cond_var() {
    if (valid_ == VALID)
      call_pthread_cond_destroy(cond_);
  }

  t_int t_monotonic_cond_var::signal() noexcept {
    if (valid_ == VALID)
      return call_pthread_cond_signal(cond_);
    return -1;
  }

  t_validity t_monotonic_cond_var::signal(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID)
        return call_pthread_cond_signal(err, cond_);
      err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_monotonic_cond_var::broadcast() noexcept {
    if (valid_ == VALID)
      return call_pthread_cond_broadcast(cond_);
    return -1;
  }

  t_validity t_monotonic_cond_var::broadcast(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID)
        return call_pthread_cond_broadcast(err, cond_);
      err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_monotonic_cond_var::wait_(::pthread_mutex_t& mutex) noexcept {
    if (valid_ == VALID)
      return call_pthread_cond_wait(cond_, mutex);
    return -1;
  }

  t_validity t_monotonic_cond_var::wait_(t_err err,
                                         ::pthread_mutex_t& mutex) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID)
        return call_pthread_cond_wait(err, cond_, mutex);
      err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_monotonic_cond_var::wait_for_(::pthread_mutex_t& mutex,
                                        t_time time) noexcept {
    if (valid_ == VALID) {
      time += clock::monotonic_now();
      return call_pthread_cond_timedwait(cond_, mutex, to_(time));
    }
    return -1;
  }

  t_validity t_monotonic_cond_var::wait_for_(t_err err,
                                             ::pthread_mutex_t& mutex,
                                             t_time time) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID) {
        time += clock::monotonic_now(err);
        return call_pthread_cond_timedwait(err, cond_, mutex, to_(time));
      }
      err = E_INVALID_INST;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_monotonic_lock::t_monotonic_lock() noexcept : cnt_{0}, mutex_{}, cond_{} {
  }

  t_monotonic_lock::t_monotonic_lock(t_err err) noexcept
    : cnt_{0}, mutex_{err}, cond_{err} {
  }

  t_monotonic_lock::~t_monotonic_lock() {
    //knows all locked_scope instances - can be used for debugging
  }

  t_monotonic_lock::t_locked_scope
      t_monotonic_lock::make_locked_scope(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (*this == VALID) {
        ::pthread_t th = call_pthread_self();
        <% auto scope = mutex_.make_locked_scope(err);
          if (scope == VALID) {
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
        err = E_INVALID_INST;
    }
    return {nullptr};
  }

  t_monotonic_lock::t_locked_scope
      t_monotonic_lock::make_locked_scope() noexcept {
    if (*this == VALID) {
      ::pthread_t th = call_pthread_self();
      <% auto scope = mutex_.make_locked_scope();
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

  t_monotonic_lock::t_locked_scope
      t_monotonic_lock::trymake_locked_scope(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (*this == VALID) {
        ::pthread_t th = call_pthread_self();
        <% auto scope = mutex_.make_locked_scope(err);
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
      } else
        err = E_INVALID_INST;
    }
    return {nullptr};
  }

  t_monotonic_lock::t_locked_scope
      t_monotonic_lock::trymake_locked_scope() noexcept {
    if (*this == VALID) {
      ::pthread_t th = call_pthread_self();
      <% auto scope = mutex_.make_locked_scope();
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

  t_monotonic_lock::t_locked_scope
    t_monotonic_lock::make_locked_scope(t_err err, t_time time) noexcept {
    T_ERR_GUARD(err) {
      if (*this == VALID) {
        ::pthread_t th = call_pthread_self();
        <% auto scope = mutex_.make_locked_scope(err);
          if (scope == VALID) {
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
        err = E_INVALID_INST;
    }
    return {nullptr};
  }

  t_monotonic_lock::t_locked_scope
    t_monotonic_lock::make_locked_scope(t_time time) noexcept {
    if (*this == VALID) {
      ::pthread_t th = call_pthread_self();
      <% auto scope = mutex_.make_locked_scope();
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
      <% auto scope = mutex_.make_locked_scope();
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

  t_pthread::t_pthread() noexcept {
  }

  t_pthread::t_pthread(p_run run, p_void arg) noexcept {
    create(run, arg);
  }

  t_pthread::t_pthread(t_err err, p_run run, p_void arg) noexcept {
    create(err, run, arg);
  }

  t_pthread::t_pthread(p_run run, p_void arg,
                       const ::pthread_attr_t& attr) noexcept {
    create(run, arg, attr);
  }

  t_pthread::t_pthread(t_err err, p_run run, p_void arg,
                       const ::pthread_attr_t& attr) noexcept {
    create(err, run, arg, attr);
  }

  t_pthread::~t_pthread() {
    if (valid_ == VALID && join_)
      join();
  }

  t_int t_pthread::create(p_run run, p_void arg) noexcept {
    if (valid_ == INVALID) {
      join_ = true;
      t_int ret = call_pthread_create(thread_, run, arg);
      if (ret == 0)
        valid_ = VALID;
      return ret;
    }
    return -1;
  }

  t_validity t_pthread::create(t_err err, p_run run, p_void arg) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == INVALID) {
        join_ = true;
        return (valid_ = call_pthread_create(err, thread_, run, arg));
      }
      err = E_VALID_INST;
    }
    return INVALID;
  }

  t_int t_pthread::create(p_run run, p_void arg,
                          const ::pthread_attr_t& attr) noexcept {
    if (valid_ == INVALID) {
      join_ = !call_pthread_is_detach(attr);
      t_int ret = call_pthread_create(thread_, attr, run, arg);
      if (ret == 0)
        valid_ = VALID;
      return ret;
    }
    return -1;
  }

  t_validity t_pthread::create(t_err err, p_run run, p_void arg,
                               const ::pthread_attr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == INVALID) {
        join_ = !call_pthread_is_detach(attr);
        return (valid_ = call_pthread_create(err, thread_, attr, run, arg));
      } else
        err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_pthread::detach() noexcept {
    if (valid_ == VALID && join_) {
      t_int ret = call_pthread_detach(thread_);
      if (ret == 0)
        join_ = false;
      return ret;
    }
    return -1;
  }

  t_validity t_pthread::detach(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID && join_) {
        if (call_pthread_detach(err, thread_) == VALID) {
          join_ = false;
          return VALID;
        }
      } else
        err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_pthread::join() noexcept {
    if (valid_ == VALID && join_) {
      t_int ret = call_pthread_join(thread_);
      if (ret == 0)
        valid_ = INVALID;
      return ret;
    }
    return -1;
  }

  t_validity t_pthread::join(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID && join_) {
        if (call_pthread_join(err, thread_) == VALID)
          return (valid_ = INVALID);
      } else
        err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_pthread::join(p_void& arg) noexcept {
    if (valid_ == VALID && join_) {
      t_int ret = call_pthread_join(thread_, arg);
      if (ret == 0)
        valid_ = INVALID;
      return ret;
    }
    return -1;
  }

  t_validity t_pthread::join(t_err err, p_void& arg) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID && join_) {
        if (call_pthread_join(err, thread_, arg) == VALID)
          return (valid_ = INVALID);
      } else
        err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_pthread::cancel() noexcept {
    if (valid_ == VALID) {
      t_int ret = call_pthread_cancel(thread_);
      if (ret == 0)
        valid_ = INVALID;
      return ret;
    }
    return -1;
  }

  t_validity t_pthread::cancel(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID) {
        if (call_pthread_cancel(err, thread_) == VALID)
          return (valid_ = INVALID);
      } else
        err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_pthread::set_name(p_cstr name) noexcept {
    if (valid_ == VALID) {
      return set_name(thread_, name);
    }
    return -1;
  }

  t_validity t_pthread::set_name(t_err err, p_cstr name) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID)
        return set_name(err, thread_, name);
      err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_int t_pthread::get_name(p_str name, t_n len) noexcept {
    if (valid_ == VALID) {
      return get_name(thread_, name, len);
    }
    return -1;
  }

  t_validity t_pthread::get_name(t_err err, p_str name, t_n len) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID)
        return get_name(err, thread_, name, len);
      err = E_INVALID_INST;
    }
    return INVALID;
  }

  t_bool t_pthread::is_equal(const ::pthread_t& pthread) noexcept {
    if (valid_ == VALID)
      return call_pthread_equal(thread_, pthread);
    return false;
  }

  t_bool t_pthread::is_equal(t_err err, const ::pthread_t& pthread) noexcept {
    T_ERR_GUARD(err) {
      if (valid_ == VALID)
        return call_pthread_equal(thread_, pthread);
      err = E_INVALID_INST;
    }
    return false;
  }

  t_bool t_pthread::is_equal(const t_pthread& pthread) noexcept {
    return is_equal(pthread.thread_);
  }

  t_bool t_pthread::is_equal(t_err err, const t_pthread& pthread) noexcept {
    return is_equal(err, pthread.thread_);
  }

  ::pthread_t t_pthread::get_self() noexcept {
    return call_pthread_self();
  }

  ::pthread_t t_pthread::get_self(t_err err) noexcept {
    T_ERR_GUARD(err) {
      return call_pthread_self();
    }
    return {};
  }

  t_void t_pthread::exit(p_void arg) noexcept {
    call_pthread_exit(arg);
  }

  t_void t_pthread::exit(t_err err, p_void arg) noexcept {
    call_pthread_exit(err, arg);
  }

  t_int t_pthread::set_name(::pthread_t thread, p_cstr name) noexcept {
    return call_pthread_setname_np(thread, name);
  }

  t_validity t_pthread::set_name(t_err err, ::pthread_t thread,
                                 p_cstr name) noexcept {
    return call_pthread_setname_np(err, thread, name);
  }

  t_int t_pthread::get_name(::pthread_t thread, p_str name,
                            t_n len) noexcept {
    return call_pthread_getname_np(thread, name, len);
  }

  t_validity t_pthread::get_name(t_err err, ::pthread_t thread, p_str name,
                                 t_n len) noexcept {
    return call_pthread_getname_np(err, thread, name, len);
  }

///////////////////////////////////////////////////////////////////////////////
}
}
}
