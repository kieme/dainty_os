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
  using named::t_n_;
  using named::t_n;
  using t_fd = os::t_fd;

///////////////////////////////////////////////////////////////////////////////

  class t_eventfd final {
  public:
    using t_fd     = fdbased::t_fd;
    using t_value  = named::t_uint64;
    using r_value  = t_value&;
    using r_cvalue = const t_value&;

     t_eventfd(t_n)         noexcept;
     t_eventfd(t_err, t_n)  noexcept;
     t_eventfd(t_eventfd&&) noexcept;
    ~t_eventfd();

    t_eventfd(const t_eventfd&)            = delete;
    t_eventfd& operator=(const t_eventfd&) = delete;
    t_eventfd& operator=(t_eventfd&&)      = delete;

    t_fd     get_fd()     const noexcept;
    operator t_validity() const noexcept;

    t_validity create(       t_n cnt) noexcept;
    t_validity create(t_err, t_n cnt) noexcept;

    t_validity close() noexcept;
    t_validity close(t_err) noexcept;

    t_validity read(       r_value) noexcept;
    t_validity read(t_err, r_value) noexcept;

    t_validity write(       r_cvalue) noexcept;
    t_validity write(t_err, r_cvalue) noexcept;

  private:
    t_fd fd_ = t_fd(-1);
  };

///////////////////////////////////////////////////////////////////////////////

  class t_epoll final {
  public:
    using t_time  = clock::t_time;
    using t_n     = named::t_n;
    using r_ctime = const t_time&;
    using t_fd    = fdbased::t_fd;
    using t_event = ::epoll_event;
    using r_event = t_event&;
    using p_event = t_event*;

     t_epoll(       t_n)  noexcept;
     t_epoll(t_err, t_n)  noexcept;
     t_epoll(t_epoll&&)   noexcept;
    ~t_epoll();

    t_epoll(const t_epoll&)            = delete;
    t_epoll& operator=(const t_epoll&) = delete;
    t_epoll& operator=(t_epoll&&)      = delete;

    operator t_validity() const noexcept;
    t_fd     get_fd()     const noexcept;

    t_int      create(       t_n) noexcept;
    t_validity create(t_err, t_n) noexcept;

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
    t_int wait(t_event (&event)[N]) noexcept {
      return wait(t_n{N}, event);
    }

    template<t_n_ N>
    inline
    t_n wait(t_err err, t_event (&event)[N]) noexcept {
      return wait(err, t_n{N}, event);
    }

    template<t_n_ N>
    inline
    t_int  wait(t_event (&event)[N], r_ctime time) noexcept {
      return wait(t_n{N}, event, time);
    }

    template<t_n_ N>
    inline
    t_n wait(t_err err, t_event (&event)[N], r_ctime time) noexcept {
      return wait(err, t_n{N}, event, time);
    }

  private:
    t_fd fd_ = t_fd(-1);
  };

///////////////////////////////////////////////////////////////////////////////

  class t_timerfd final {
  public:
    using t_flags      = named::t_int;
    using t_time       = clock::t_time;
    using t_fd         = fdbased::t_fd;
    using t_timerspec  = ::itimerspec;
    using r_timerspec  = t_timerspec&;
    using r_ctimerspec = const t_timerspec&;
    using t_data       = named::t_uint64;
    using r_data       = t_data&;

     t_timerfd(       t_flags) noexcept;
     t_timerfd(t_err, t_flags) noexcept;
     t_timerfd(t_timerfd&&)    noexcept;
    ~t_timerfd();

    t_timerfd(const t_timerfd&)            = delete;
    t_timerfd& operator=(const t_timerfd&) = delete;
    t_timerfd& operator=(t_timerfd&&)      = delete;

    operator t_validity() const noexcept;
    t_fd     get_fd()     const noexcept;

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

    t_int      read(       r_data) noexcept;
    t_validity read(t_err, r_data) noexcept;

  private:
    t_fd fd_ = t_fd(-1);
  };

///////////////////////////////////////////////////////////////////////////////

}
}
}

#endif
