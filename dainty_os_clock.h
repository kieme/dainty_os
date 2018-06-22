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

#ifndef _DAINTY_OS_CLOCK_H_
#define _DAINTY_OS_CLOCK_H_

// description
// os: operating system functionality used by dainty
//
//  not a complete API but only the things used by dainty.

#include "dainty_named.h"
#include "dainty_oops.h"
#include "dainty_os_call.h"

namespace dainty
{
namespace os
{
namespace clock
{
  enum t_nsec_tag_ {};
  using t_nsec_ = named::t_ullong;
  using t_nsec  = named::t_explicit<t_nsec_, t_nsec_tag_>;

  enum t_usec_tag_ {};
  using t_usec_ = named::t_ulong;
  using t_usec  = named::t_explicit<t_usec_, t_usec_tag_>;

  enum t_msec_tag_ {};
  using t_msec_ = named::t_uint;
  using t_msec  = named::t_explicit<t_msec_, t_msec_tag_>;

  enum t_sec_tag_ {};
  using t_sec_ = named::t_uint;
  using t_sec  = named::t_explicit<t_sec_, t_sec_tag_>;

  enum t_min_tag_ {};
  using t_min_ = named::t_ushort;
  using t_min  = named::t_explicit<t_min_, t_min_tag_>;

///////////////////////////////////////////////////////////////////////////////

  class t_time {
  public:
    constexpr t_time() noexcept;

    template<typename T>
    constexpr t_time(T) noexcept;

    template<typename T>
    constexpr t_time& operator+=(T) noexcept;

    template<typename T>
    constexpr t_time& operator-=(T) noexcept;

    template<typename T>
    constexpr T to() const noexcept;

    template<typename T>
    constexpr t_bool test_for_overflow(T) noexcept;

    template<typename T>
    constexpr t_bool test_for_underflow(T) noexcept;

  private:
    friend constexpr       timespec& to_(t_time&) noexcept;
    friend constexpr const timespec& to_(const t_time&) noexcept;
    ::timespec spec_;
  };

  constexpr t_time operator"" _nsec(unsigned long long value) {
    return (t_time{} += t_nsec(value));
  }

  constexpr t_time operator"" _usec(unsigned long long value) {
    return (t_time{} += t_usec(value));
  }

  constexpr t_time operator"" _msec(unsigned long long value) {
    return (t_time{} += t_msec(value));
  }

  constexpr t_time operator"" _sec (unsigned long long value) {
    return (t_time{} += t_sec(value));
  }

  constexpr t_time operator"" _min (unsigned long long value) {
    return (t_time{} += t_min(value));
  }

  template<typename T>
  constexpr t_time add(T t) { return (t_time{} += t); }

  template<typename T, typename... Ts>
  constexpr t_time add(T t, Ts... ts) { return (add(t) += add(ts...)); }

///////////////////////////////////////////////////////////////////////////////

  t_time monotonic_now();
  t_time monotonic_now(t_err);
  t_time realtime_now ();
  t_time realtime_now (t_err);

///////////////////////////////////////////////////////////////////////////////

  struct t_timed_scope {
    t_time& time;

    inline
    t_timed_scope(t_time& t) noexcept : time(t) { time = monotonic_now(); }
    inline
    ~t_timed_scope() noexcept         { time = (monotonic_now() -= time); }
  };

  class t_timer {
  public:
    enum t_start_tag_ { START };

    inline
    static t_time get_now() noexcept {
      return monotonic_now();
    }

    inline
    t_timer() noexcept : last_ {} {
    }

    inline
    t_timer(t_start_tag_) noexcept : last_(monotonic_now()) {
    }

    inline
    t_time get_last() const noexcept {
      return last_;
    }

    inline
    named::t_void restart() noexcept {
      last_ = get_now();
    }

    inline
    t_time elapsed() const noexcept {
      return (get_now() -= get_last());
    }

    inline
    t_time elapsed_restart() noexcept {
      t_time now{get_now()};
      t_time elapse{now};
      elapse -= last_;
      last_ = now;
      return elapse;
    };

  private:
    t_time last_;
  };


///////////////////////////////////////////////////////////////////////////////

  constexpr timespec& to_(t_time& time) noexcept {
    return time.spec_;
  }

  constexpr const timespec& to_(const t_time& time) noexcept {
    return time.spec_;
  }

  constexpr timespec to_(t_nsec nsec) noexcept {
    return { get(nsec)/1000000000, get(nsec)%1000000000}; // narrow
  }

  constexpr timespec to_(t_usec usec) noexcept {
    return { get(usec)/1000000, get(usec)%1000000}; // narrow
  }

  constexpr timespec to_(t_msec msec) noexcept {
    return { get(msec)/1000, get(msec)%1000}; // narrow
  }

  constexpr timespec to_(t_sec sec) noexcept {
    return {get(sec), 0}; // narrow
  }

  constexpr timespec to_(t_min min) noexcept {
    return { get(min)*60, 0}; // narrow
  }

///////////////////////////////////////////////////////////////////////////////

  constexpr t_nsec& to_(t_nsec& nsec, const timespec& spec) noexcept {
    set(nsec) = spec.tv_nsec + (1000000000*spec.tv_sec);
    return nsec;
  }

  constexpr t_usec& to_(t_usec& usec, const timespec& spec) noexcept {
    set(usec) = spec.tv_nsec/1000 + (1000000*spec.tv_sec);
    return usec;
  }

  constexpr t_msec& to_(t_msec& msec, const timespec& spec) noexcept {
    set(msec) = spec.tv_nsec/1000000 + (1000*spec.tv_sec);
    return msec;
  }

  constexpr t_sec& to_(t_sec& sec, const timespec& spec) noexcept {
    set(sec) = spec.tv_sec;
    return sec;
  }

  constexpr t_min& to_(t_min& min, const timespec& spec) noexcept {
    set(min) = spec.tv_sec/60;
    return min;
  }

///////////////////////////////////////////////////////////////////////////////

  constexpr t_bool overflow_(const t_time& time, const timespec&) noexcept {
    return true;
  }

  constexpr t_bool overflow_(t_nsec nsec, const timespec&) noexcept {
    return true;
  }

  constexpr t_bool overflow_(t_usec usec, const timespec&) noexcept {
    return true;
  }

  constexpr t_bool overflow_(t_msec msec, const timespec&) noexcept {
    return true;
  }

  constexpr t_bool overflow_(t_sec sec, const timespec&) noexcept {
    return true;
  }

  constexpr t_bool overflow_(t_min min, const timespec&) noexcept {
    return true;
  }

///////////////////////////////////////////////////////////////////////////////

  constexpr t_bool underflow_(t_nsec nsec, const timespec&) noexcept {
    return true;
  }

  constexpr t_bool underflow_(t_usec usec, const timespec&) noexcept {
    return true;
  }

  constexpr t_bool underflow_(t_msec msec, const timespec&) noexcept {
    return true;
  }

  constexpr t_bool underflow_(t_sec sec, const timespec&) noexcept {
    return true;
  }

  constexpr t_bool underflow_(t_min min, const timespec&) noexcept {
    return true;
  }

  constexpr t_bool underflow_(const t_time& time, const timespec&) noexcept {
    return true;
  }

///////////////////////////////////////////////////////////////////////////////

  constexpr t_time::t_time() noexcept : spec_{to_(0_nsec)} {
  }

  template<typename T>
  constexpr t_time::t_time(T value) noexcept : spec_{to_(value)} {
  }

  template<typename T>
  constexpr t_time& t_time::operator+=(T value) noexcept {
    if (test_for_overflow(value))
      throw 1;
    return *this;
  }

  template<typename T>
  constexpr t_time& t_time::operator-=(T value) noexcept {
    if (test_for_underflow(value))
      throw 1;
    return *this;
  }

  template<typename T>
  constexpr T t_time::to() const noexcept {
    T value{0};
    return to_(value, spec_);
  }

  template<typename T>
  constexpr t_bool t_time::test_for_overflow(T value) noexcept {
    return overflow_(value, spec_);
  }

  template<typename T>
  constexpr t_bool t_time::test_for_underflow(T value) noexcept {
    return underflow_(value, spec_);
  }

///////////////////////////////////////////////////////////////////////////////
}
}
}

#endif
