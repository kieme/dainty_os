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
#include "dainty_named.h"
#include "dainty_oops.h"

namespace dainty
{
namespace os
{
  using named::t_int;
  using named::t_bool;

  using t_err = oops::t_oops<>;

///////////////////////////////////////////////////////////////////////////////

  t_bool call_pthread_mutex_init(t_err, pthread_mutex_t&,
                                 const pthread_mutexattr_t* = nullptr) noexcept;
  t_int  call_pthread_mutex_init(pthread_mutex_t&,
                                 const pthread_mutexattr_t* = nullptr) noexcept;

  t_bool call_pthread_mutex_lock(t_err, pthread_mutex_t&) noexcept;
  t_int  call_pthread_mutex_lock(pthread_mutex_t&) noexcept;

  t_bool call_pthread_mutex_trylock(t_err, pthread_mutex_t&) noexcept;
  t_int  call_pthread_mutex_trylock(pthread_mutex_t&) noexcept;

  t_bool call_pthread_mutex_destroy(t_err, pthread_mutex_t&) noexcept;
  t_int  call_pthread_mutex_destroy(pthread_mutex_t&) noexcept;

///////////////////////////////////////////////////////////////////////////////

  // conditional variable

///////////////////////////////////////////////////////////////////////////////

  // pthread create, delete, self, attr

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
