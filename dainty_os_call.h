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

#include <pthread.h>
#include <sys/eventfd.h>
#include <sys/epoll.h>
#include <time.h>
#include "dainty_named.h"
#include "dainty_os_err.h"

namespace dainty
{
namespace os
{
  using named::t_bool;
  using named::t_int;
  using named::t_validity;
  using named::VALID;
  using named::INVALID;

///////////////////////////////////////////////////////////////////////////////

  enum t_fd_tag_ {};
  using t_fd_ = named::t_int;
  using t_fd  = named::t_explicit<t_fd_, t_fd_tag_>;

  using t_err = oops::t_oops<>;

///////////////////////////////////////////////////////////////////////////////

  ::pthread_mutexattr_t&
    call_pthread_init(::pthread_mutexattr_t&) noexcept;
  ::pthread_mutexattr_t&
    call_pthread_init(t_err, ::pthread_mutexattr_t&) noexcept;

  ::pthread_mutexattr_t&
    call_pthread_set_recursive(::pthread_mutexattr_t&) noexcept;
  ::pthread_mutexattr_t&
    call_pthread_set_recursive(t_err, ::pthread_mutexattr_t&) noexcept;

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

  ::pthread_condattr_t&
    call_pthread_init(::pthread_condattr_t&) noexcept;
  ::pthread_condattr_t&
    call_pthread_init(t_err, ::pthread_condattr_t&) noexcept;

  ::pthread_condattr_t&
    call_pthread_set_monotonic(::pthread_condattr_t&) noexcept;
  ::pthread_condattr_t&
    call_pthread_set_monotonic(t_err, ::pthread_condattr_t&) noexcept;

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

  ::pthread_t call_pthread_self() noexcept;
  ::pthread_t call_pthread_self() noexcept;
  t_bool      call_pthread_equal(const ::pthread_t&,
                                 const ::pthread_t&) noexcept;

  // pthread create, delete, self, attr

///////////////////////////////////////////////////////////////////////////////

  t_int call_clock_gettime(::clockid_t, ::timespec&) noexcept;
  t_validity call_clock_gettime(t_err, ::clockid_t, ::timespec&) noexcept;

  t_int call_clock_gettime_monotonic(::timespec&) noexcept;
  t_validity call_clock_gettime_monotonic(t_err, ::timespec&) noexcept;

  t_int call_clock_gettime_realtime(::timespec&) noexcept;
  t_validity call_clock_gettime_realtime(t_err, ::timespec&) noexcept;

///////////////////////////////////////////////////////////////////////////////

  // epoll, wait, ctl,e cts

///////////////////////////////////////////////////////////////////////////////

  // select

///////////////////////////////////////////////////////////////////////////////

  // timerfd

///////////////////////////////////////////////////////////////////////////////

  // eventfd

///////////////////////////////////////////////////////////////////////////////

  // signal

///////////////////////////////////////////////////////////////////////////////

  // read, readn, write, writev

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
