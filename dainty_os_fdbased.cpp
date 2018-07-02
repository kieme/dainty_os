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
// os: operating system functionality used by dainty
//
//  not a complete API but only the things used by dainty.
//

#include "dainty_os_fdbased.h"

namespace dainty
{
namespace os
{
namespace fdbased
{
  using named::t_void;

///////////////////////////////////////////////////////////////////////////////

  t_eventfd::t_eventfd() noexcept {
  }

  t_eventfd::t_eventfd(t_err err) noexcept {
  }

  t_eventfd::t_eventfd(t_fd fd) noexcept {
  }

  t_eventfd::t_eventfd(t_err err, t_fd fd) noexcept {
  }

  t_eventfd::t_eventfd(t_eventfd&& event) noexcept {
  }

  t_eventfd::~t_eventfd() {
  }

  t_fd t_eventfd::release() noexcept {
  }

  t_bool t_eventfd::assign_fd(t_fd fd) noexcept {
  }

  t_validity t_eventfd::assign_fd(t_err err, t_fd fd) noexcept {
  }

  t_int t_eventfd::create() noexcept {
  }

  t_validity t_eventfd::create(t_err err) noexcept {
  }

  t_int t_eventfd::close() noexcept {
  }

  t_validity t_eventfd::close(t_err err) noexcept {
  }

  t_int t_eventfd::read(r_value value) noexcept {
  }

  t_validity t_eventfd::read(t_err err, r_value value) noexcept {
  }

  t_int t_eventfd::write(r_cvalue value) noexcept {
  }

  t_validity t_eventfd::write(t_err err, r_cvalue value) noexcept {
  }

///////////////////////////////////////////////////////////////////////////////

  t_epoll::t_epoll(t_n) noexcept {
  }

  t_epoll::t_epoll(t_err err, t_n n) noexcept {
  }

  t_epoll::t_epoll(t_fd fd) noexcept {
  }

  t_epoll::t_epoll(t_err err, t_fd fd) noexcept {
  }

  t_epoll::t_epoll(t_epollfd&& epoll) noexcept {
  }

  t_epoll::~t_epoll() {
  }

  t_fd t_epoll::release() noexcept {
  }

  t_bool t_epoll::assign_fd(t_fd fd) noexcept {
  }

  t_validity t_epoll::assign_fd(t_err err, t_fd fd) noexcept {
  }

  t_int t_epoll::create(t_n n) noexcept {
  }

  t_validty t_epoll::create(t_err err, t_n n) noexcept {
  }

  t_int t_epoll::close() noexcept {
  }

  t_validity t_epoll::close(t_err err) noexcept {
  }

  t_int t_epoll::add_watch_event(t_fd fd, r_event event) noexcept {
  }

  t_validity t_epoll::add_watch_event(t_err err, t_fd fd,
                                      r_event event) noexcept {
  }

  t_int t_epoll::mod_watch_event(t_fd fd, r_event event) noexcept {
  }

  t_validity t_epoll::mod_watch_event(t_err err, t_fd fd,
                                      r_event event) noexcept {
  }

  t_int t_epoll::del_watch_event(t_fd fd) noexcept {
  }

  t_validity t_epoll::del_watch_event(t_err err, t_fd fd) noexcept {

  t_int t_epoll::wait(t_n n, p_event event) noexcept {
  }

  t_n t_epoll::wait(t_err err, t_n n, p_event event) noexcept {
  }

  t_int t_epoll::wait(t_n n, p_event event, r_ctime time) noexcept {
  }

  t_n t_epoll::wait(t_err err, t_n n, p_event event, r_ctime time) noexcept {
  }

///////////////////////////////////////////////////////////////////////////////

  t_timerfd::t_timerfd(t_flags flags) noexcept {
  }

  t_timerfd::t_timerfd(t_err err, t_flags flags) noexcept {
  }

  t_timerfd::t_timerfd(t_fd fd) noexcept {
  }

  t_timerfd::t_timerfd(t_err err, t_fd fd) noexcept {
  }

  t_timerfd::t_timerfd(t_timerfd&& timer) {
  }

  t_timerfd::~t_timerfd() {
  }

  t_fd t_timerfd::release() noexcept {
  }

  t_bool t_timerfd::assign_fd(t_fd fd) noexcept {
  }

  t_validity t_timerfd::assign_fd(t_err err, t_fd fd) noexcept {
  }

  t_int t_timerfd::create(t_flags flags) noexcept {
  }

  t_validity t_timerfd::create(t_err err, t_flags flags) noexcept {
  }

  t_int t_timerfd::close() noexcept {
  }

  t_validity t_timerfd::close(t_err err) noexcept {
  }

  t_int t_timerfd::set_time(r_ctimerspec, t_flags flags) noexcept {
  }

  t_validity t_timerfd::set_time(t_err err, r_ctimerspec timer,
                                 t_flags flags) noexcept {
  }

  t_int t_timerfd::set_time(r_ctimerspec, r_timerspec timer,
                            t_flags flags) noexcept {
  }

  t_validity t_timerfd::set_time(t_err err, r_ctimerspec ntimer,
                                 r_timerspec otimer, t_flags flags) noexcept {
  }

  t_int t_timerfd::get_time(r_timerspec timer) noexcept {
  }

  t_validity t_timerfd::get_time(t_err err, r_timerspec timer) noexcept {
  }

  t_int t_timerfd::read(r_data data) noexcept {
  }

  t_validity t_timerfd::read(t_err err, r_data data) noexcept {
  }

///////////////////////////////////////////////////////////////////////////////

}
}
}
