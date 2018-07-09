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

#include "dainty_os_fdbased.h"

namespace dainty
{
namespace os
{
namespace fdbased
{
  using named::t_void;

///////////////////////////////////////////////////////////////////////////////

  t_eventfd::t_eventfd(t_n cnt) noexcept : fd_{call_eventfd(cnt)} {
  }

  t_eventfd::t_eventfd(t_err err, t_n cnt) noexcept
      : fd_{call_eventfd(err, cnt)} {
  }

  t_eventfd::t_eventfd(t_eventfd&& event) noexcept : fd_(event.fd_) {
    event.fd_ = BAD_FD;
  }

  t_eventfd::~t_eventfd() {
    close();
  }

  t_validity t_eventfd::create(t_n cnt) noexcept {
    if (fd_ == BAD_FD) {
      fd_ =  call_eventfd(cnt);
      if (fd_ != BAD_FD)
        return VALID;
    }
    return INVALID;
  }

  t_validity t_eventfd::create(t_err err, t_n cnt) noexcept {
    T_ERR_GUARD(err) {
      if (fd_ == BAD_FD) {
        fd_ = call_eventfd(err, cnt);
        if (fd_ != BAD_FD)
          return VALID;
      } else
        err = E_XXX;
    }
    return INVALID;
  }

  t_validity t_eventfd::close() noexcept {
    if (fd_ != BAD_FD && call_close(fd_) == 0)
      return VALID;
    return INVALID;
  }

  t_validity t_eventfd::close(t_err err) noexcept {
    T_ERR_GUARD(err) {
      if (fd_ != BAD_FD)
        return call_close(err, fd_);
      err = E_XXX;
    }
    return INVALID;
  }

  t_validity t_eventfd::read(r_value value) noexcept {
    if (fd_ != BAD_FD) {
      auto cnt = call_read(fd_, &value, t_n{sizeof(t_value)});
      if (cnt == sizeof(value))
        return VALID;
    }
    return INVALID;
  }

  t_validity t_eventfd::read(t_err err, r_value value) noexcept {
    T_ERR_GUARD(err) {
      if (fd_ != BAD_FD) {
        auto cnt = call_read(err, fd_, &value, t_n{sizeof(t_value)});
        if (get(cnt) == sizeof(value))
          return VALID;
      } else
        err = E_XXX;
    }
    return INVALID;
  }

  t_validity t_eventfd::write(r_cvalue value) noexcept {
    if (fd_ != BAD_FD) {
      auto cnt = call_write(fd_, &value, t_n{sizeof(t_value)});
      if (cnt == sizeof(value))
        return VALID;
    }
    return INVALID;
  }

  t_validity t_eventfd::write(t_err err, r_cvalue value) noexcept {
    T_ERR_GUARD(err) {
      if (fd_ != BAD_FD) {
        auto cnt = call_write(err, fd_, &value, t_n{sizeof(t_value)});
        if (get(cnt) == sizeof(value))
          return VALID;
      } else
        err = E_XXX;
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

  t_epoll::t_epoll(t_n) noexcept {
  }

  t_epoll::t_epoll(t_err err, t_n n) noexcept {
    T_ERR_GUARD(err) {
    }
  }

  t_epoll::t_epoll(t_epoll&& epoll) noexcept {
  }

  t_epoll::~t_epoll() {
  }

  t_int t_epoll::create(t_n n) noexcept {
    return -1;
  }

  t_validity t_epoll::create(t_err err, t_n n) noexcept {
    T_ERR_GUARD(err) {
    }
    return INVALID;
  }

  t_int t_epoll::close() noexcept {
    return -1;
  }

  t_validity t_epoll::close(t_err err) noexcept {
    T_ERR_GUARD(err) {
    }
    return INVALID;
  }

  t_int t_epoll::add_watch_event(t_fd fd, r_event event) noexcept {
    return -1;
  }

  t_validity t_epoll::add_watch_event(t_err err, t_fd fd,
                                      r_event event) noexcept {
    T_ERR_GUARD(err) {
    }
    return INVALID;
  }

  t_int t_epoll::mod_watch_event(t_fd fd, r_event event) noexcept {
    return -1;
  }

  t_validity t_epoll::mod_watch_event(t_err err, t_fd fd,
                                      r_event event) noexcept {
    T_ERR_GUARD(err) {
    }
    return INVALID;
  }

  t_int t_epoll::del_watch_event(t_fd fd) noexcept {
    return -1;
  }

  t_validity t_epoll::del_watch_event(t_err err, t_fd fd) noexcept {
    T_ERR_GUARD(err) {
    }
    return INVALID;
  }

  t_int t_epoll::wait(t_n n, p_event event) noexcept {
    return -1;
  }

  t_n t_epoll::wait(t_err err, t_n n, p_event event) noexcept {
    T_ERR_GUARD(err) {
    }
    return t_n(-1);
  }

  t_int t_epoll::wait(t_n n, p_event event, r_ctime time) noexcept {
    return -1;
  }

  t_n t_epoll::wait(t_err err, t_n n, p_event event, r_ctime time) noexcept {
    T_ERR_GUARD(err) {
    }
    return t_n(-1);
  }

///////////////////////////////////////////////////////////////////////////////

  t_timerfd::t_timerfd(t_flags flags) noexcept {
  }

  t_timerfd::t_timerfd(t_err err, t_flags flags) noexcept {
    T_ERR_GUARD(err) {
    }
  }

  t_timerfd::t_timerfd(t_timerfd&&) noexcept {
  }

  t_timerfd::~t_timerfd() {
  }

  t_int t_timerfd::create(t_flags flags) noexcept {
    return -1;
  }

  t_validity t_timerfd::create(t_err err, t_flags flags) noexcept {
    T_ERR_GUARD(err) {
    }
    return INVALID;
  }

  t_int t_timerfd::close() noexcept {
    return -1;
  }

  t_validity t_timerfd::close(t_err err) noexcept {
    T_ERR_GUARD(err) {
    }
    return INVALID;
  }

  t_int t_timerfd::set_time(r_ctimerspec, t_flags flags) noexcept {
    return -1;
  }

  t_validity t_timerfd::set_time(t_err err, r_ctimerspec timer,
                                 t_flags flags) noexcept {
    T_ERR_GUARD(err) {
    }
    return INVALID;
  }

  t_int t_timerfd::set_time(r_ctimerspec, r_timerspec timer,
                            t_flags flags) noexcept {
    return -1;
  }

  t_validity t_timerfd::set_time(t_err err, r_ctimerspec ntimer,
                                 r_timerspec otimer, t_flags flags) noexcept {
    T_ERR_GUARD(err) {
    }
    return INVALID;
  }

  t_int t_timerfd::get_time(r_timerspec timer) noexcept {
    return -1;
  }

  t_validity t_timerfd::get_time(t_err err, r_timerspec timer) noexcept {
    T_ERR_GUARD(err) {
    }
    return INVALID;
  }

  t_int t_timerfd::read(r_data data) noexcept {
    return -1;
  }

  t_validity t_timerfd::read(t_err err, r_data data) noexcept {
    T_ERR_GUARD(err) {
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

}
}
}
