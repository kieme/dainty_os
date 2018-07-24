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

#ifndef _DAINTY_OS_CALL_H_
#define _DAINTY_OS_CALL_H_

// description
// os: operating system functionality

#include <sys/eventfd.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "dainty_named.h"
#include "dainty_os_err.h"

namespace dainty
{
namespace os
{
  using named::p_void;
  using named::p_cvoid;
  using named::t_void;
  using named::t_bool;
  using named::t_int;

  using named::t_validity;
  using named::t_n;
  using named::p_str;
  using named::p_cstr;
  using named::VALID;
  using named::INVALID;

///////////////////////////////////////////////////////////////////////////////

  enum t_fd_tag_ {};
  using t_fd_ = named::t_int;
  using t_fd  = named::t_explicit<t_fd_, t_fd_tag_>;
  using p_run = p_void (*)(p_void);

  constexpr t_bool operator==(t_fd lh, t_fd rh) { return get(lh) == get(rh); }
  constexpr t_bool operator!=(t_fd lh, t_fd rh) { return !(lh == rh);        }

  constexpr t_fd  BAD_FD{-1};
  constexpr t_int OK_INT{0};

///////////////////////////////////////////////////////////////////////////////

  t_int      call_pthread_init(::pthread_mutexattr_t&) noexcept;
  t_validity call_pthread_init(t_err, ::pthread_mutexattr_t&) noexcept;

  t_int      call_pthread_destroy(::pthread_mutexattr_t&) noexcept;
  t_validity call_pthread_destroy(t_err, ::pthread_mutexattr_t&) noexcept;

  t_int      call_pthread_set_recursive(::pthread_mutexattr_t&) noexcept;
  t_validity call_pthread_set_recursive(t_err, ::pthread_mutexattr_t&) noexcept;

  t_bool     call_pthread_is_recursive(const ::pthread_mutexattr_t&) noexcept;
  t_bool     call_pthread_is_recursive(t_err,
                                       const ::pthread_mutexattr_t&) noexcept;

///////////////////////////////////////////////////////////////////////////////

  t_int      call_pthread_mutex_init(::pthread_mutex_t&) noexcept;
  t_validity call_pthread_mutex_init(t_err, ::pthread_mutex_t&) noexcept;

  t_int      call_pthread_mutex_init(::pthread_mutex_t&,
                                     const ::pthread_mutexattr_t&) noexcept;
  t_validity call_pthread_mutex_init(t_err, ::pthread_mutex_t&,
                                     const ::pthread_mutexattr_t&) noexcept;

  t_int      call_pthread_mutex_destroy(::pthread_mutex_t&) noexcept;
  t_validity call_pthread_mutex_destroy(t_err, ::pthread_mutex_t&) noexcept;

  t_int      call_pthread_mutex_lock(::pthread_mutex_t&) noexcept;
  t_validity call_pthread_mutex_lock(t_err, ::pthread_mutex_t&) noexcept;

  t_int      call_pthread_mutex_timedlock(::pthread_mutex_t&,
                                          const ::timespec&) noexcept;
  t_validity call_pthread_mutex_timedlock(t_err, ::pthread_mutex_t&,
                                          const ::timespec&) noexcept;

  t_int      call_pthread_mutex_trylock(::pthread_mutex_t&) noexcept;
  t_validity call_pthread_mutex_trylock(t_err, ::pthread_mutex_t&) noexcept;

  t_int      call_pthread_mutex_unlock(::pthread_mutex_t&) noexcept;
  t_validity call_pthread_mutex_unlock(t_err, ::pthread_mutex_t&) noexcept;

///////////////////////////////////////////////////////////////////////////////

  t_int      call_pthread_init(::pthread_condattr_t&) noexcept;
  t_validity call_pthread_init(t_err, ::pthread_condattr_t&) noexcept;

  t_int      call_pthread_destroy(::pthread_condattr_t&) noexcept;
  t_validity call_pthread_destroy(t_err, ::pthread_condattr_t&) noexcept;

  t_int      call_pthread_set_monotonic(::pthread_condattr_t&) noexcept;
  t_validity call_pthread_set_monotonic(t_err, ::pthread_condattr_t&) noexcept;

  t_bool     call_pthread_is_monotonic(const ::pthread_condattr_t&) noexcept;
  t_bool     call_pthread_is_monotonic(t_err,
                                       const ::pthread_condattr_t&) noexcept;

///////////////////////////////////////////////////////////////////////////////

  t_int      call_pthread_cond_init(::pthread_cond_t&) noexcept;
  t_validity call_pthread_cond_init(t_err, ::pthread_cond_t&) noexcept;

  t_int      call_pthread_cond_init(::pthread_cond_t&,
                                    const ::pthread_condattr_t&) noexcept;
  t_validity call_pthread_cond_init(t_err, ::pthread_cond_t&,
                                    const ::pthread_condattr_t&) noexcept;

  t_int      call_pthread_cond_destroy(::pthread_cond_t&) noexcept;
  t_validity call_pthread_cond_destroy(t_err, ::pthread_cond_t&) noexcept;

  t_int      call_pthread_cond_signal(::pthread_cond_t&) noexcept;
  t_validity call_pthread_cond_signal(t_err, ::pthread_cond_t&) noexcept;

  t_int      call_pthread_cond_broadcast(::pthread_cond_t&) noexcept;
  t_validity call_pthread_cond_broadcast(t_err, ::pthread_cond_t&) noexcept;

  t_int      call_pthread_cond_wait(::pthread_cond_t&,
                                    ::pthread_mutex_t&) noexcept;
  t_validity call_pthread_cond_wait(t_err, ::pthread_cond_t&,
                                    ::pthread_mutex_t&) noexcept;

  t_int      call_pthread_cond_timedwait(::pthread_cond_t&, ::pthread_mutex_t&,
                                         const ::timespec&) noexcept;
  t_validity call_pthread_cond_timedwait(t_err, ::pthread_cond_t&,
                                         ::pthread_mutex_t&,
                                         const ::timespec&) noexcept;

///////////////////////////////////////////////////////////////////////////////

  t_int      call_pthread_set_detach(       ::pthread_attr_t&) noexcept;
  t_validity call_pthread_set_detach(t_err, ::pthread_attr_t&) noexcept;

  t_bool     call_pthread_is_detach(       const ::pthread_attr_t&) noexcept;
  t_bool     call_pthread_is_detach(t_err, const ::pthread_attr_t&) noexcept;

  ::pthread_t call_pthread_self() noexcept;
  ::pthread_t call_pthread_self() noexcept;
  t_bool      call_pthread_equal(const ::pthread_t&,
                                 const ::pthread_t&) noexcept;

  t_int      call_pthread_create(       ::pthread_t&, p_run, p_void) noexcept;
  t_validity call_pthread_create(t_err, ::pthread_t&, p_run, p_void) noexcept;

  t_int      call_pthread_create(       ::pthread_t&, const ::pthread_attr_t&,
                                 p_run, p_void) noexcept;
  t_validity call_pthread_create(t_err, ::pthread_t&, const ::pthread_attr_t&,
                                 p_run, p_void) noexcept;

  t_int      call_pthread_detach(       ::pthread_t&)      noexcept;
  t_validity call_pthread_detach(t_err, ::pthread_t&) noexcept;

  t_int      call_pthread_join(       ::pthread_t&) noexcept;
  t_validity call_pthread_join(t_err, ::pthread_t&) noexcept;

  t_int      call_pthread_join(       ::pthread_t&, p_void&) noexcept;
  t_validity call_pthread_join(t_err, ::pthread_t&, p_void&) noexcept;

  t_int      call_pthread_cancel(       ::pthread_t&) noexcept;
  t_validity call_pthread_cancel(t_err, ::pthread_t&) noexcept;

  t_void     call_pthread_exit(       p_void) noexcept;
  t_void     call_pthread_exit(t_err, p_void) noexcept;

  t_int      call_pthread_setname_np(       ::pthread_t, p_cstr) noexcept;
  t_validity call_pthread_setname_np(t_err, ::pthread_t, p_cstr) noexcept;

  t_int      call_pthread_getname_np(       ::pthread_t, p_str, t_n) noexcept;
  t_validity call_pthread_getname_np(t_err, ::pthread_t, p_str, t_n) noexcept;

///////////////////////////////////////////////////////////////////////////////

  t_int      call_clock_gettime(       ::clockid_t, ::timespec&) noexcept;
  t_validity call_clock_gettime(t_err, ::clockid_t, ::timespec&) noexcept;

  t_int      call_clock_gettime_monotonic(       ::timespec&) noexcept;
  t_validity call_clock_gettime_monotonic(t_err, ::timespec&) noexcept;

  t_int      call_clock_gettime_realtime(       ::timespec&) noexcept;
  t_validity call_clock_gettime_realtime(t_err, ::timespec&) noexcept;

///////////////////////////////////////////////////////////////////////////////

  t_fd call_epoll_create(     ) noexcept;
  t_fd call_epoll_create(t_err) noexcept;

  t_int      call_epoll_ctl_add(       t_fd, t_fd, ::epoll_event&) noexcept;
  t_validity call_epoll_ctl_add(t_err, t_fd, t_fd, ::epoll_event&) noexcept;

  t_int      call_epoll_ctl_mod(       t_fd, t_fd, ::epoll_event&) noexcept;
  t_validity call_epoll_ctl_mod(t_err, t_fd, t_fd, ::epoll_event&) noexcept;

  t_int      call_epoll_ctl_del(       t_fd, t_fd) noexcept;
  t_validity call_epoll_ctl_del(t_err, t_fd, t_fd) noexcept;

  t_int      call_epoll_wait(       t_fd, ::epoll_event*, t_int max) noexcept;
  t_n        call_epoll_wait(t_err, t_fd, ::epoll_event*, t_int max) noexcept;

///////////////////////////////////////////////////////////////////////////////

  // timerfd

///////////////////////////////////////////////////////////////////////////////

  t_fd call_eventfd(       t_n) noexcept;
  t_fd call_eventfd(t_err, t_n) noexcept;

///////////////////////////////////////////////////////////////////////////////

  t_int      call_close(       t_fd&) noexcept;
  t_validity call_close(t_err, t_fd&) noexcept;

///////////////////////////////////////////////////////////////////////////////

  ssize_t    call_read(        t_fd, p_void, t_n count) noexcept;
  t_n        call_read(t_err,  t_fd, p_void, t_n count) noexcept;

  ssize_t    call_write(       t_fd, p_cvoid, t_n count) noexcept;
  t_n        call_write(t_err, t_fd, p_cvoid, t_n count) noexcept;

  // readv, writev

///////////////////////////////////////////////////////////////////////////////

  // signal

///////////////////////////////////////////////////////////////////////////////

  // socket api

///////////////////////////////////////////////////////////////////////////////

  // pipe

///////////////////////////////////////////////////////////////////////////////

  // time

///////////////////////////////////////////////////////////////////////////////
}
}

#endif
