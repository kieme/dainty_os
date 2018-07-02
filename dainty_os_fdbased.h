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

#ifndef _DAINTY_OS_FDBASED_H_
#define _DAINTY_OS_FDBASED_H_

// description
// os: operating system functionality used by dainty
//
//  not a complete API but only the things used by dainty.
//
// DAINTY_OS_CLOCK_OVERFLOW_ASSERT

#include "dainty_named.h"
#include "dainty_oops.h"
#include "dainty_os_call.h"
#include "dainty_os_clock.h"

namespace dainty
{
namespace os
{
namespace fdbased
{
  using named::t_void;

///////////////////////////////////////////////////////////////////////////////

  class t_eventfd final {
  public:
    using t_fd    = fdbased::t_fd;
    using t_value = named::t_uint64;

     t_eventfd() noexcept;
     t_eventfd(t_err) noexcept;
     t_eventfd(t_fd) noexcept;
     t_eventfd(t_err, t_fd) noexcept;
     t_eventfd(t_eventfd&&) noexcept;
    ~t_eventfd();

    t_eventfd(const t_eventfd&)           = delete;
    t_eventfd& operator(const t_eventfd&) = delete;
    t_eventfd& operator(t_eventfd&&)      = delete;

    t_fd     get_fd()     const noexcept;
    operator t_validity() const noexcept;

    t_fd release() noexcept;

    t_bool     assign_fd(       t_fd) noexcept;
    t_validity assign_fd(t_err, t_fd) noexcept;

    t_int      create() noexcept;
    t_validity create(t_err) noexcept;

    t_int      close() noexcept;
    validity   close(t_err) noexcept;

    t_int      read(       t_value&) noexcept;
    t_validity read(t_err, t_value&) noexcept;

    t_int      write(       const t_value&) noexcept;
    t_validity write(t_err, const t_value&) noexcept;

  private:
    t_fd fd_;
  };

///////////////////////////////////////////////////////////////////////////////

  class t_epoll final {
  public:
    using clock::t_time;
    using named::t_n;
    using r_ctime = const t_time&;
    using t_fd    = fdbased::t_fd;
    using t_event = ::t_epoll_event;
    using r_event = t_event&;
    using p_event = t_event*;

     t_epoll(       t_n)    noexcept;
     t_epoll(t_err, t_n)    noexcept;
     t_epoll(       t_fd)   noexcept;
     t_epoll(t_err, t_fd)   noexcept;
     t_eventfd(t_eventfd&&) noexcept;
    ~t_epoll();

    t_epoll(const t_epoll&)           = delete;
    t_epoll& operator(const t_epoll&) = delete;
    t_epoll& operator(t_epoll&&)      = delete;

    operator t_validity() const noexcept;
    t_fd     get_fd()     const noexcept;

    t_fd release() noexcept;

    t_bool     assign_fd(       t_fd) noexcept;
    t_validity assign_fd(t_err, t_fd) noexcept;

    t_int      create(       t_n) noexcept;
    t_validty  create(t_err, t_n) noexcept;

    t_int      close() noexcept;
    t_validity close(t_err) noexcept;

    t_int      add_watch_event(       t_fd, r_event) noexcept;
    t_validity add_watch_event(t_err, t_fd, r_event) noexcept;
    t_int      mod_watch_event(       t_fd, r_event) noexcept;
    t_validity mod_watch_event(t_err, t_fd, r_event) noexcept;
    t_int      del_watch_event(       t_fd) noexcept;
    t_validity del_watch_event(t_err, t_fd) noexcept;

    t_int wait(       t_n, p_event) noexcept;
    t_n   wait(t_err, t_n, p_event) noexcept;

    t_int wait(       t_n, p_event, r_ctime) noexcept;
    t_n   wait(t_err, t_n, p_event, r_ctime) noexcept;

    template<t_n_ N>
    inline
    t_int wait(t_event (event&)[N]) noexcept {
      return wait(t_n{N}, event);
    }

    template<t_n_ N>
    inline
    t_n wait(t_err err, t_event (event&)[N]) noexcept {
      return wait(err, t_n{N}, event);
    }

    template<t_n_ N>
    inline
    t_int  wait(t_event (event&)[N], r_ctime time) noexcept {
      return wait(t_n{N}, event, time);
    }

    template<t_n_ N>
    inline
    t_n wait(t_err err, t_event (event&)[N], r_ctime time) noexcept {
      return wait(err, t_n{N}, event, time);
    }

  private:
    t_fd fd_;
  };

///////////////////////////////////////////////////////////////////////////////

  class t_timerfd final {
  public:
    using clock::t_time;
    using t_fd         = fdbased::t_fd;
    using t_timerspec  = ::itimerspec;
    using r_timerspec  = t_imterspace&;
    using r_ctimerspec = const t_imterspace&;
    using t_readdata   = named::t_uint64;
    using r_readdata   = t_readdata&;
    using t_flags      = named::t_int;

     t_timerfd(       t_flags) noexcept;
     t_timerfd(t_err, t_flags) noexcept;
     t_timerfd(       t_fd)    noexcept;
     t_timerfd(t_err, t_fd)    noexcept;
    ~t_timerfd();

    t_timerfd(const t_timerfd&)           = delete;
    t_timerfd& operator(const t_timerfd&) = delete;
    t_timerfd& operator(t_timerfd&&)      = delete;

    operator t_validity() const noexcept;
    t_fd     get_fd()     const noexcept;

    t_fd release() noexcept;

    t_bool     assign_fd(       t_fd) noexcept;
    t_validity assign_fd(t_err, t_fd) noexcept;

    t_int      create(       t_flags) noexcept;
    t_validity create(t_err, t_flags) noexcept;

    t_int      close()      noexcept;
    t_validity close(t_err) noexcept;

    t_int      set_time(       r_ctimerspec, t_flags) noexcept;
    t_validity set_time(t_err, r_ctimerspec, t_flags) noexcept;
    t_int      set_time(       r_ctimerspec, r_timerspec, t_flags) noexcept;
    t_validity set_time(t_err, r_ctimerspec, r_timerspec, t_flags) noexcept;

    t_int      get_time(       r_timerspec) noexcept;
    t_validity get_time(t_err, r_timerspec) noexcept;

    t_int      read(       r_readdata) noexcept;
    t_validity read(t_err, r_readdata) noexcept;

  private:
    t_fd fd_;
  };

///////////////////////////////////////////////////////////////////////////////

}
}
}

#endif
