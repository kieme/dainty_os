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

// description
// os: operating system functionality

#include <errno.h>
#include "dainty_os_call.h"

namespace dainty
{
namespace os
{
///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_init(::pthread_mutexattr_t& attr) noexcept {
    return {::pthread_mutexattr_init(&attr)};
  }

  t_validity call_pthread_init(t_err err,
                               ::pthread_mutexattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_init(attr) == 0)
        return VALID;
      err = E_INIT_FAIL;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_destroy(::pthread_mutexattr_t& attr) noexcept {
    return {::pthread_mutexattr_destroy(&attr)};
  }

  t_validity call_pthread_destroy(t_err err,
                                  ::pthread_mutexattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_destroy(attr) == 0)
        return VALID;
      err = E_DESTROY_FAIL;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_set_recursive(::pthread_mutexattr_t& attr) noexcept {
    return {::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)};
  }

  t_validity call_pthread_set_recursive(t_err err,
                                        ::pthread_mutexattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_set_recursive(attr) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_bool
      call_pthread_is_recursive(const ::pthread_mutexattr_t& attr) noexcept {
    int type = 0;
    return ::pthread_mutexattr_gettype(&attr, &type) == 0 &&
           type == PTHREAD_MUTEX_RECURSIVE;
  }

  t_bool
      call_pthread_is_recursive(t_err err,
                                const ::pthread_mutexattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      int type = 0;
      if (::pthread_mutexattr_gettype(&attr, &type) == 0)
        return type == PTHREAD_MUTEX_RECURSIVE;
      err = E_XXX;
    }
    return false;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_mutex_init(::pthread_mutex_t& mutex) noexcept {
     return {::pthread_mutex_init(&mutex, NULL)};
  }

  t_validity call_pthread_mutex_init(t_err err,
                                     ::pthread_mutex_t& mutex) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_mutex_init(mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_mutex_init(::pthread_mutex_t& mutex,
                                const ::pthread_mutexattr_t& attr) noexcept {
     return {::pthread_mutex_init(&mutex, &attr)};
  }

  t_validity
    call_pthread_mutex_init(t_err err, ::pthread_mutex_t& mutex,
                            const ::pthread_mutexattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_mutex_init(mutex, attr);
      switch (j) {
        case 0: return VALID;
        default: {
          err =  E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_mutex_destroy(::pthread_mutex_t& mutex) noexcept {
    return {::pthread_mutex_destroy(&mutex)};
  }

  t_validity call_pthread_mutex_destroy(t_err err,
                                        ::pthread_mutex_t& mutex) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_mutex_destroy(mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_mutex_lock(::pthread_mutex_t& mutex) noexcept {
    return {::pthread_mutex_lock(&mutex)};
  }

  t_validity call_pthread_mutex_lock(t_err err,
                                     ::pthread_mutex_t& mutex) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_mutex_lock(mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_mutex_timedlock(::pthread_mutex_t& mutex,
                                     const ::timespec& spec) noexcept {
    return {::pthread_mutex_timedlock(&mutex, &spec)};
  }

  t_validity call_pthread_mutex_timedlock(t_err err,
                                          ::pthread_mutex_t& mutex,
                                          const ::timespec& spec) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_mutex_timedlock(mutex, spec);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_mutex_trylock(::pthread_mutex_t& mutex) noexcept {
    return {::pthread_mutex_trylock(&mutex)};
  }

  t_validity call_pthread_mutex_trylock(t_err err,
                                        ::pthread_mutex_t& mutex) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_mutex_trylock(mutex);
      switch (j) {
        case 0: return VALID;
        case EBUSY: {
          err = E_XXX;
        } break;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_mutex_unlock(::pthread_mutex_t& mutex) noexcept {
    return {::pthread_mutex_unlock(&mutex)};
  }

  t_validity call_pthread_mutex_unlock(t_err err,
                                       ::pthread_mutex_t& mutex) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_mutex_unlock(mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_init(::pthread_condattr_t& attr) noexcept {
    return {::pthread_condattr_init(&attr)};
  }

  t_validity call_pthread_init(t_err err,
                               ::pthread_condattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_init(attr) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_set_monotonic(::pthread_condattr_t& attr) noexcept {
    return {::pthread_condattr_setclock(&attr, CLOCK_MONOTONIC)};
  }

  t_validity call_pthread_set_monotonic(t_err err,
                                        ::pthread_condattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_set_monotonic(attr) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_destroy(::pthread_condattr_t& attr) noexcept {
    return {::pthread_condattr_destroy(&attr)};
  }

  t_validity call_pthread_destroy(t_err err,
                                  ::pthread_condattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_destroy(attr) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_bool call_pthread_is_monotonic(const ::pthread_condattr_t& attr) noexcept {
    ::clockid_t clk;
    return ::pthread_condattr_getclock(&attr, &clk) == 0 &&
           clk == CLOCK_MONOTONIC;
  }

  t_bool call_pthread_is_monotonic(t_err err,
                                   const ::pthread_condattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      ::clockid_t clk;
      t_int ret = ::pthread_condattr_getclock(&attr, &clk);
      if (ret == 0)
        return clk == CLOCK_MONOTONIC;
      err = E_XXX;
    }
    return false;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_cond_init(::pthread_cond_t& cond) noexcept {
     return {::pthread_cond_init(&cond, NULL)};
  }

  t_validity call_pthread_cond_init(t_err err,
                                    ::pthread_cond_t& cond) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_cond_init(cond);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_cond_init(::pthread_cond_t& cond,
                               const ::pthread_condattr_t& attr) noexcept {
     return {::pthread_cond_init(&cond, &attr)};
  }

  t_validity call_pthread_cond_init(t_err err, ::pthread_cond_t& cond,
                                    const ::pthread_condattr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_cond_init(cond, attr);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_cond_destroy(::pthread_cond_t& cond) noexcept {
     return {::pthread_cond_destroy(&cond)};
  }

  t_validity call_pthread_cond_destroy(t_err err,
                                       ::pthread_cond_t& cond) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_cond_destroy(cond);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_cond_signal(::pthread_cond_t& cond) noexcept {
     return {::pthread_cond_signal(&cond)};
  }

  t_validity call_pthread_cond_signal(t_err err,
                                      ::pthread_cond_t& cond) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_cond_signal(cond);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_cond_broadcast(::pthread_cond_t& cond) noexcept {
     return {::pthread_cond_broadcast(&cond)};
  }

  t_validity call_pthread_cond_broadcast(t_err err,
                                         ::pthread_cond_t& cond) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_cond_broadcast(cond);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_cond_wait(::pthread_cond_t& cond,
                               ::pthread_mutex_t& mutex) noexcept {
     return {::pthread_cond_wait(&cond, &mutex)};
  }

  t_validity call_pthread_cond_wait(t_err err, ::pthread_cond_t& cond,
                                    ::pthread_mutex_t& mutex) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_cond_wait(cond, mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_cond_timedwait(::pthread_cond_t& cond,
                                    ::pthread_mutex_t& mutex,
                                    const ::timespec& spec) noexcept {
     return {::pthread_cond_timedwait(&cond, &mutex, &spec)};
  }

  t_validity call_pthread_cond_timedwait(t_err err, ::pthread_cond_t& cond,
                                         ::pthread_mutex_t& mutex,
                                         const ::timespec& spec) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_cond_timedwait(cond, mutex, spec);
      switch (j) {
        case 0: return VALID;
        default: {
          err = E_XXX;
        } break;
      }
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_set_detach(::pthread_attr_t& attr) noexcept {
    return {::pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)};
  }

  t_validity call_pthread_set_detach(t_err err,
                                     ::pthread_attr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_set_detach(attr);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_bool call_pthread_is_detach(const ::pthread_attr_t& attr) noexcept {
    int state;
    if (::pthread_attr_getdetachstate(&attr, &state) == 0)
      return state == PTHREAD_CREATE_DETACHED;
    //assert();
    return false;
  }

  t_bool call_pthread_is_detach(t_err err,
                                const ::pthread_attr_t& attr) noexcept {
    T_ERR_GUARD(err) {
      int state = 0;
      if (::pthread_attr_getdetachstate(&attr, &state) == 0)
        return state == PTHREAD_CREATE_DETACHED;
      err = E_XXX;
    }
    return false;
  }

  ::pthread_t call_pthread_self() noexcept {
     return ::pthread_self();
  }

  t_bool call_pthread_equal(const ::pthread_t& p1,
                            const ::pthread_t& p2) noexcept {
    return ::pthread_equal(p1, p2);
  }

  t_int call_pthread_create(::pthread_t& thread, p_run run,
                            p_void arg) noexcept {
    return {::pthread_create(&thread, NULL, run, arg)};
  }

  t_validity call_pthread_create(t_err err, ::pthread_t& thread, p_run run,
                                 p_void arg) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_create(thread, run, arg);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_create(::pthread_t& thread, const ::pthread_attr_t& attr,
                            p_run run, p_void arg) noexcept {
    return {::pthread_create(&thread, &attr, run, arg)};
  }

  t_validity call_pthread_create(t_err err, ::pthread_t& thread,
                                 const ::pthread_attr_t& attr, p_run run,
                                 p_void arg) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_create(thread, attr, run, arg);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_detach(::pthread_t& thread) noexcept {
    return {::pthread_detach(thread)};
  }

  t_validity call_pthread_detach(t_err err, ::pthread_t& thread) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_detach(thread);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_join(::pthread_t& thread) noexcept {
    return {::pthread_join(thread, NULL)};
  }

  t_validity call_pthread_join(t_err err, ::pthread_t& thread) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_join(thread);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_join(::pthread_t& thread, p_void& arg) noexcept {
    return {::pthread_join(thread, &arg)};
  }

  t_validity call_pthread_join(t_err err,
                               ::pthread_t& thread, p_void& arg) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_join(thread, arg);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_cancel(::pthread_t& thread) noexcept {
    return {::pthread_cancel(thread)};
  }

  t_validity call_pthread_cancel(t_err err,
                                 ::pthread_t& thread) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_cancel(thread);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_void call_pthread_exit(p_void arg) noexcept {
    ::pthread_exit(arg);
  }

  t_void call_pthread_exit(t_err err, p_void arg) noexcept {
    T_ERR_GUARD(err) {
      call_pthread_exit(arg);
    }
  }

  t_int call_pthread_setname_np(::pthread_t thread, p_cstr name) noexcept {
    return {::pthread_setname_np(thread, get(name))};
  }

  t_validity call_pthread_setname_np(t_err err, ::pthread_t thread,
                                     p_cstr name) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_setname_np(thread, name);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_getname_np(::pthread_t thread, p_str name,
                                t_n len) noexcept {
    return {::pthread_getname_np(thread, get(name), get(len))};
  }

  t_validity call_pthread_getname_np(t_err err, ::pthread_t thread,
                                     p_str name, t_n len) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_getname_np(thread, name, len);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_clock_gettime(::clockid_t clk, ::timespec& spec) noexcept {
    return {::clock_gettime(clk, &spec)};
  }

  t_validity call_clock_gettime(t_err err, ::clockid_t clk,
                                ::timespec& spec) noexcept {
    T_ERR_GUARD(err) {
      if (call_clock_gettime(clk, spec) == 0)
        return VALID;
    }
    return INVALID;
  }

  t_int call_clock_gettime_monotonic(::timespec& spec) noexcept {
    return {::clock_gettime(CLOCK_MONOTONIC, &spec)};
  }

  t_validity call_clock_gettime_monotonic(t_err err,
                                          ::timespec& spec) noexcept {
    T_ERR_GUARD(err) {
      if (call_clock_gettime_monotonic(spec) == 0)
        return VALID;
    }
    return INVALID;
  }

  t_int call_clock_gettime_realtime(::timespec& spec) noexcept {
    return {::clock_gettime(CLOCK_REALTIME, &spec)};
  }

  t_validity call_clock_gettime_realtime(t_err err,
                                          ::timespec& spec) noexcept {
    T_ERR_GUARD(err) {
      if (call_clock_gettime_realtime(spec) == 0)
        return VALID;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////
}
}

