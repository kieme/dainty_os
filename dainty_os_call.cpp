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

  t_int call_pthread_init(r_pthread_mutexattr attr) noexcept {
    return {::pthread_mutexattr_init(&attr)};
  }

  t_validity call_pthread_init(t_err err, r_pthread_mutexattr attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_init(attr) == 0)
        return VALID;
      err = E_INIT_FAIL;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_destroy(r_pthread_mutexattr attr) noexcept {
    return {::pthread_mutexattr_destroy(&attr)};
  }

  t_validity call_pthread_destroy(t_err err,
                                  r_pthread_mutexattr attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_destroy(attr) == 0)
        return VALID;
      err = E_DESTROY_FAIL;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_set_recursive(r_pthread_mutexattr attr) noexcept {
    return {::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)};
  }

  t_validity call_pthread_set_recursive(t_err err,
                                        r_pthread_mutexattr attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_set_recursive(attr) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_bool call_pthread_is_recursive(R_pthread_mutexattr attr) noexcept {
    int type = 0;
    return ::pthread_mutexattr_gettype(&attr, &type) == 0 &&
           type == PTHREAD_MUTEX_RECURSIVE;
  }

  t_bool call_pthread_is_recursive(t_err err,
                                   R_pthread_mutexattr attr) noexcept {
    T_ERR_GUARD(err) {
      int type = 0;
      if (::pthread_mutexattr_gettype(&attr, &type) == 0)
        return type == PTHREAD_MUTEX_RECURSIVE;
      err = E_XXX;
    }
    return false;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_mutex_init(r_pthread_mutex mutex) noexcept {
     return {::pthread_mutex_init(&mutex, NULL)};
  }

  t_validity call_pthread_mutex_init(t_err err,
                                     r_pthread_mutex mutex) noexcept {
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

  t_int call_pthread_mutex_init(r_pthread_mutex mutex,
                                R_pthread_mutexattr attr) noexcept {
     return {::pthread_mutex_init(&mutex, &attr)};
  }

  t_validity call_pthread_mutex_init(t_err err, r_pthread_mutex mutex,
                                     R_pthread_mutexattr attr) noexcept {
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

  t_int call_pthread_mutex_destroy(r_pthread_mutex mutex) noexcept {
    return {::pthread_mutex_destroy(&mutex)};
  }

  t_validity call_pthread_mutex_destroy(t_err err,
                                        r_pthread_mutex mutex) noexcept {
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

  t_int call_pthread_mutex_lock(r_pthread_mutex mutex) noexcept {
    return {::pthread_mutex_lock(&mutex)};
  }

  t_validity call_pthread_mutex_lock(t_err err,
                                     r_pthread_mutex mutex) noexcept {
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

  t_int call_pthread_mutex_timedlock(r_pthread_mutex mutex,
                                     R_timespec spec) noexcept {
    return {::pthread_mutex_timedlock(&mutex, &spec)};
  }

  t_validity call_pthread_mutex_timedlock(t_err err,
                                          r_pthread_mutex mutex,
                                          R_timespec spec) noexcept {
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

  t_int call_pthread_mutex_trylock(r_pthread_mutex mutex) noexcept {
    return {::pthread_mutex_trylock(&mutex)};
  }

  t_validity call_pthread_mutex_trylock(t_err err,
                                        r_pthread_mutex mutex) noexcept {
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

  t_int call_pthread_mutex_unlock(r_pthread_mutex mutex) noexcept {
    return {::pthread_mutex_unlock(&mutex)};
  }

  t_validity call_pthread_mutex_unlock(t_err err,
                                       r_pthread_mutex mutex) noexcept {
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

  t_int call_pthread_init(r_pthread_condattr attr) noexcept {
    return {::pthread_condattr_init(&attr)};
  }

  t_validity call_pthread_init(t_err err, r_pthread_condattr attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_init(attr) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_set_monotonic(r_pthread_condattr attr) noexcept {
    return {::pthread_condattr_setclock(&attr, CLOCK_MONOTONIC)};
  }

  t_validity call_pthread_set_monotonic(t_err err,
                                        r_pthread_condattr attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_set_monotonic(attr) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_destroy(r_pthread_condattr attr) noexcept {
    return {::pthread_condattr_destroy(&attr)};
  }

  t_validity call_pthread_destroy(t_err err,
                                  r_pthread_condattr attr) noexcept {
    T_ERR_GUARD(err) {
      if (call_pthread_destroy(attr) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_bool call_pthread_is_monotonic(R_pthread_condattr attr) noexcept {
    t_clockid clk;
    return ::pthread_condattr_getclock(&attr, &clk) == 0 &&
           clk == CLOCK_MONOTONIC;
  }

  t_bool call_pthread_is_monotonic(t_err err,
                                   R_pthread_condattr attr) noexcept {
    T_ERR_GUARD(err) {
      t_clockid clk;
      t_int ret = ::pthread_condattr_getclock(&attr, &clk);
      if (ret == 0)
        return clk == CLOCK_MONOTONIC;
      err = E_XXX;
    }
    return false;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_cond_init(r_pthread_cond cond) noexcept {
    return {::pthread_cond_init(&cond, NULL)};
  }

  t_validity call_pthread_cond_init(t_err err, r_pthread_cond cond) noexcept {
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

  t_int call_pthread_cond_init(r_pthread_cond cond,
                               R_pthread_condattr attr) noexcept {
     return {::pthread_cond_init(&cond, &attr)};
  }

  t_validity call_pthread_cond_init(t_err err, r_pthread_cond cond,
                                    R_pthread_condattr attr) noexcept {
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

  t_int call_pthread_cond_destroy(r_pthread_cond cond) noexcept {
     return {::pthread_cond_destroy(&cond)};
  }

  t_validity call_pthread_cond_destroy(t_err err,
                                       r_pthread_cond cond) noexcept {
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

  t_int call_pthread_cond_signal(r_pthread_cond cond) noexcept {
     return {::pthread_cond_signal(&cond)};
  }

  t_validity call_pthread_cond_signal(t_err err,
                                      r_pthread_cond cond) noexcept {
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

  t_int call_pthread_cond_broadcast(r_pthread_cond cond) noexcept {
     return {::pthread_cond_broadcast(&cond)};
  }

  t_validity call_pthread_cond_broadcast(t_err err,
                                         r_pthread_cond cond) noexcept {
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

  t_int call_pthread_cond_wait(r_pthread_cond cond,
                               r_pthread_mutex mutex) noexcept {
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

  t_int call_pthread_cond_timedwait(r_pthread_cond cond,
                                    r_pthread_mutex mutex,
                                    R_timespec spec) noexcept {
     return {::pthread_cond_timedwait(&cond, &mutex, &spec)};
  }

  t_validity call_pthread_cond_timedwait(t_err err, r_pthread_cond cond,
                                         r_pthread_mutex mutex,
                                         R_timespec spec) noexcept {
    T_ERR_GUARD(err) {
      int j = call_pthread_cond_timedwait(cond, mutex, spec);
      switch (j) {
        case 0: return VALID;
        case ETIMEDOUT: err = E_TIMEOUT; break;
        default:        err = E_XXX;     break;
      }
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_set_detach(r_pthread_attr attr) noexcept {
    return {::pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)};
  }

  t_validity call_pthread_set_detach(t_err err,
                                     r_pthread_attr attr) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_set_detach(attr);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_bool call_pthread_is_detach(R_pthread_attr attr) noexcept {
    int state;
    if (::pthread_attr_getdetachstate(&attr, &state) == 0)
      return state == PTHREAD_CREATE_DETACHED;
    //assert();
    return false;
  }

  t_bool call_pthread_is_detach(t_err err, R_pthread_attr attr) noexcept {
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

  t_bool call_pthread_equal(R_pthread p1, R_pthread p2) noexcept {
    return ::pthread_equal(p1, p2);
  }

  t_int call_pthread_create(r_pthread thread, p_run run, p_void arg) noexcept {
    return {::pthread_create(&thread, NULL, run, arg)};
  }

  t_validity call_pthread_create(t_err err, r_pthread thread, p_run run,
                                 p_void arg) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_create(thread, run, arg);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_create(r_pthread thread, R_pthread_attr attr,
                            p_run run, p_void arg) noexcept {
    return {::pthread_create(&thread, &attr, run, arg)};
  }

  t_validity call_pthread_create(t_err err, r_pthread thread,
                                 R_pthread_attr attr, p_run run,
                                 p_void arg) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_create(thread, attr, run, arg);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_detach(r_pthread thread) noexcept {
    return {::pthread_detach(thread)};
  }

  t_validity call_pthread_detach(t_err err, r_pthread thread) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_detach(thread);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_join(r_pthread thread) noexcept {
    return {::pthread_join(thread, NULL)};
  }

  t_validity call_pthread_join(t_err err, r_pthread thread) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_join(thread);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_join(r_pthread thread, p_void& arg) noexcept {
    return {::pthread_join(thread, &arg)};
  }

  t_validity call_pthread_join(t_err err, r_pthread thread,
                               p_void& arg) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_join(thread, arg);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_cancel(r_pthread thread) noexcept {
    return {::pthread_cancel(thread)};
  }

  t_validity call_pthread_cancel(t_err err, r_pthread thread) noexcept {
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

  t_int call_pthread_setname_np(t_pthread thread, P_cstr name) noexcept {
    return {::pthread_setname_np(thread, get(name))};
  }

  t_validity call_pthread_setname_np(t_err err, t_pthread thread,
                                     P_cstr name) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_setname_np(thread, name);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_pthread_getname_np(t_pthread thread, p_cstr name,
                                t_n len) noexcept {
    return {::pthread_getname_np(thread, get(name), get(len))};
  }

  t_validity call_pthread_getname_np(t_err err, t_pthread thread,
                                     p_cstr name, t_n len) noexcept {
    T_ERR_GUARD(err) {
      t_int ret = call_pthread_getname_np(thread, name, len);
      if (ret == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_clock_gettime(t_clockid clk, r_timespec spec) noexcept {
    return {::clock_gettime(clk, &spec)};
  }

  t_validity call_clock_gettime(t_err err, t_clockid clk,
                                r_timespec spec) noexcept {
    T_ERR_GUARD(err) {
      if (call_clock_gettime(clk, spec) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_clock_gettime_monotonic(r_timespec spec) noexcept {
    return {::clock_gettime(CLOCK_MONOTONIC, &spec)};
  }

  t_validity call_clock_gettime_monotonic(t_err err,
                                          r_timespec spec) noexcept {
    T_ERR_GUARD(err) {
      if (call_clock_gettime_monotonic(spec) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_clock_gettime_realtime(r_timespec spec) noexcept {
    return {::clock_gettime(CLOCK_REALTIME, &spec)};
  }

  t_validity call_clock_gettime_realtime(t_err err, r_timespec spec) noexcept {
    T_ERR_GUARD(err) {
      if (call_clock_gettime_realtime(spec) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_fd call_epoll_create() noexcept {
    return t_fd{::epoll_create1(0)};
  }

  t_fd call_epoll_create(t_err err) noexcept {
    T_ERR_GUARD(err) {
      t_fd fd{call_epoll_create()};
      if (get(fd) >= 0)
        return fd;
      err = E_XXX;
    }
    return BAD_FD;
  }

  t_int call_epoll_ctl_add(t_fd efd, t_fd fd, r_epoll_event event) noexcept {
    return {::epoll_ctl(get(efd), EPOLL_CTL_ADD, get(fd), &event)};
  }

  t_validity call_epoll_ctl_add(t_err err, t_fd efd, t_fd fd,
                                ::epoll_event& event) noexcept {
    T_ERR_GUARD(err) {
      if (call_epoll_ctl_add(efd, fd, event) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_epoll_ctl_mod(t_fd efd, t_fd fd, r_epoll_event event) noexcept {
    return {::epoll_ctl(get(efd), EPOLL_CTL_MOD, get(fd), &event)};
  }

  t_validity call_epoll_ctl_mod(t_err err, t_fd efd, t_fd fd,
                                r_epoll_event event) noexcept {
    T_ERR_GUARD(err) {
      if (call_epoll_ctl_mod(efd, fd, event) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_epoll_ctl_del(t_fd efd, t_fd fd) noexcept {
    return {::epoll_ctl(get(efd), EPOLL_CTL_DEL, get(fd), NULL)};
  }

  t_validity call_epoll_ctl_del(t_err err, t_fd efd, t_fd fd) noexcept {
    T_ERR_GUARD(err) {
      if (call_epoll_ctl_del(efd, fd) == 0)
        return VALID;
      err = E_XXX;
    }
    return INVALID;
  }

  t_int call_epoll_wait(t_fd efd, p_epoll_event events, t_n max) noexcept {
    return {::epoll_wait(get(efd), events, get(max), -1)};
  }

  t_n call_epoll_wait(t_err err, t_fd efd, p_epoll_event events,
                      t_n max) noexcept {
    T_ERR_GUARD(err) {
      t_int n = call_epoll_wait(efd, events, max);
      if (n >= 0)
        return t_n(n);
      err = E_XXX;
    }
    return t_n{0};
  }

  t_int call_epoll_wait(t_fd efd, p_epoll_event events, t_n max,
                        t_uint microseconds) noexcept {
    return {::epoll_wait(get(efd), events, get(max), microseconds)};
  }

  t_n call_epoll_wait(t_err err, t_fd efd, p_epoll_event events,
                      t_n max, t_uint microseconds) noexcept {
    T_ERR_GUARD(err) {
      t_int n = call_epoll_wait(efd, events, max, microseconds);
      if (n >= 0)
        return t_n(n);
      err = E_XXX;
    }
    return t_n{0};
  }

///////////////////////////////////////////////////////////////////////////////

  t_fd call_eventfd(t_n cnt) noexcept {
    return t_fd{::eventfd(get(cnt), 0)};
  }

  t_fd call_eventfd(t_err err, t_n cnt) noexcept {
    T_ERR_GUARD(err) {
      t_fd fd{call_eventfd(cnt)};
      if (get(fd) >= 0)
        return fd;
      err = E_XXX;
    }
    return BAD_FD;
  }

///////////////////////////////////////////////////////////////////////////////

  t_int call_close(t_fd& fd) noexcept {
    if (fd != BAD_FD) {
      t_fd_ tmp = get(fd);
      fd = BAD_FD;
      return ::close(tmp);
    }
    return -1;
  }

  t_validity call_close(t_err err, t_fd& fd) noexcept {
    T_ERR_GUARD(err) {
      if (fd != BAD_FD) {
        ::close(get(fd));
        fd = BAD_FD;
        return VALID;
      }
      err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  ssize_t call_read(t_fd fd, p_void buf, t_n cnt) noexcept {
    return ::read(get(fd), buf, get(cnt));
  }

  t_n call_read(t_err err, t_fd fd, p_void buf, t_n cnt) noexcept {
    T_ERR_GUARD(err) {
      auto size = ::read(get(fd), buf, get(cnt));
      if (size > -1)
        return t_n(size);
      err = E_XXX; // assign err
    }
    return t_n{0};
  }

  ssize_t call_write(t_fd fd, P_void buf, t_n cnt) noexcept {
    return ::write(get(fd), buf, get(cnt));
  }

  t_n call_write(t_err err, t_fd fd, P_void buf, t_n cnt) noexcept {
    T_ERR_GUARD(err) {
      auto size = ::write(get(fd), buf, get(cnt));
      if (size > -1)
        return t_n(size);
      err = E_XXX; // assign err
    }
    return t_n{0};
  }

///////////////////////////////////////////////////////////////////////////////
}
}

