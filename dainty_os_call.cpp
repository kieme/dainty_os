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

  ::pthread_mutexattr_t&
    call_pthread_init(::pthread_mutexattr_t& attr) noexcept {
    if (::pthread_mutexattr_init(&attr)) {
      // assert - XXX
    }
    return attr;
  }

  ::pthread_mutexattr_t&
    call_pthread_init(t_err err, ::pthread_mutexattr_t& attr) noexcept {
    if (!err)
      call_pthread_init(attr);
    return attr;
  }

  ::pthread_mutexattr_t&
    call_pthread_set_recursive(::pthread_mutexattr_t& attr) noexcept {
    if (::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) {
      // assert - XXX
    }
    return attr;
  }

  ::pthread_mutexattr_t&
    call_pthread_set_recursive(t_err err,
                               ::pthread_mutexattr_t& attr) noexcept {
    if (!err)
      call_pthread_set_recursive(attr);
    return attr;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_mutex_init(::pthread_mutex_t& mutex) noexcept {
     return {::pthread_mutex_init(&mutex, NULL)};
  }

  t_validity call_pthread_mutex_init(t_err err,
                                     ::pthread_mutex_t& mutex) noexcept {
    if (!err) {
      int j = call_pthread_mutex_init(mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_mutex_init(mutex, attr);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_mutex_destroy(mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_mutex_lock(mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_mutex_timedlock(mutex, spec);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_mutex_trylock(mutex);
      switch (j) {
        case 0: return VALID;
        case EBUSY: {
          err = 8; //XXX
        } break;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_mutex_unlock(mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
        } break;
      }
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  ::pthread_condattr_t&
    call_pthread_init(::pthread_condattr_t& attr) noexcept {
    if (::pthread_condattr_init(&attr)) {
      // assert - XXX
    }
    return attr;
  }

  ::pthread_condattr_t&
    call_pthread_init(t_err err, ::pthread_condattr_t& attr) noexcept {
    if (!err)
      call_pthread_init(attr);
    return attr;
  }

  ::pthread_condattr_t&
    call_pthread_set_monotonic(::pthread_condattr_t& attr) noexcept {
    if (::pthread_condattr_setclock(&attr, CLOCK_MONOTONIC)) {
      // assert - XXX
    }
    return attr;
  }

  ::pthread_condattr_t&
    call_pthread_set_monotonic(t_err err, ::pthread_condattr_t& attr) noexcept {
    if (!err)
      call_pthread_set_monotonic(err, attr);
    return attr;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_cond_init(::pthread_cond_t& cond) noexcept {
     return {::pthread_cond_init(&cond, NULL)};
  }

  t_validity call_pthread_cond_init(t_err err,
                                    ::pthread_cond_t& cond) noexcept {
    if (!err) {
      int j = call_pthread_cond_init(cond);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_cond_init(cond, attr);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_cond_destroy(cond);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_cond_signal(cond);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_cond_broadcast(cond);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_cond_wait(cond, mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
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
    if (!err) {
      int j = call_pthread_cond_timedwait(cond, mutex, spec);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
        } break;
      }
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  ::pthread_t call_pthread_self() noexcept {
     return ::pthread_self();
  }

  t_bool call_pthread_equal(const ::pthread_t& p1,
                            const ::pthread_t& p2) noexcept {
    return ::pthread_equal(p1, p2);
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_clock_gettime(::clockid_t clk, ::timespec& spec) noexcept {
    return {::clock_gettime(clk, &spec)};
  }

  t_validity call_clock_gettime(t_err err, ::clockid_t clk,
                                ::timespec& spec) noexcept {
    if (!err)
      if (call_clock_gettime(clk, spec) == 0)
        return VALID;
    return INVALID;
  }

  t_int call_clock_gettime_monotonic(::timespec& spec) noexcept {
    return {::clock_gettime(CLOCK_MONOTONIC, &spec)};
  }

  t_validity call_clock_gettime_monotonic(t_err err,
                                          ::timespec& spec) noexcept {
    if (!err)
      if (call_clock_gettime_monotonic(spec) == 0)
        return VALID;
    return INVALID;
  }

  t_int call_clock_gettime_realtime(::timespec& spec) noexcept {
    return {::clock_gettime(CLOCK_REALTIME, &spec)};
  }

  t_validity call_clock_gettime_realtime(t_err err,
                                          ::timespec& spec) noexcept {
    if (!err)
      if (call_clock_gettime_realtime(spec) == 0)
        return VALID;
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////
}
}

