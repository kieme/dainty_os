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

  enum t_date_tag_ {};
  using t_date_ = t_nsec::t_value;
  using t_date  = named::t_explicit<t_date_, t_date_tag_>;

  enum t_interval_tag_ {};
  using t_interval_ = t_nsec::t_value;
  using t_interval  = named::t_explicit<t_interval_, t_interval_tag_>;

  constexpr t_nsec to_nsec(t_usec);
  constexpr t_nsec to_nsec(t_msec);
  constexpr t_nsec to_nsec(t_sec);
  constexpr t_nsec to_nsec(t_min);
  constexpr t_nsec to_nsec(t_date);
  constexpr t_nsec to_nsec(t_interval);

  constexpr t_usec to_usec(t_nsec);
  constexpr t_usec to_usec(t_msec);
  constexpr t_usec to_usec(t_sec);
  constexpr t_usec to_usec(t_min);
  constexpr t_usec to_usec(t_date);
  constexpr t_usec to_usec(t_interval);

  constexpr t_msec to_msec(t_nsec);
  constexpr t_msec to_msec(t_usec);
  constexpr t_msec to_msec(t_sec);
  constexpr t_msec to_msec(t_min);
  constexpr t_msec to_msec(t_date);
  constexpr t_msec to_msec(t_interval);

  constexpr t_sec to_sec(t_nsec);
  constexpr t_sec to_sec(t_usec);
  constexpr t_sec to_sec(t_msec);
  constexpr t_sec to_sec(t_min);
  constexpr t_sec to_sec(t_date);
  constexpr t_sec to_sec(t_interval);

  t_interval to_interval(t_nsec);
  t_interval to_interval(t_usec);
  t_interval to_interval(t_msec);
  t_interval to_interval(t_sec);
  t_interval to_interval(t_min);

  constexpr t_nsec& operator+=(t_nsec&, t_nsec);
  constexpr t_nsec& operator+=(t_nsec&, t_usec);
  constexpr t_nsec& operator+=(t_nsec&, t_msec);
  constexpr t_nsec& operator+=(t_nsec&, t_sec);

  constexpr t_usec& operator+=(t_usec&, t_nsec);
  constexpr t_usec& operator+=(t_usec&, t_usec);
  constexpr t_usec& operator+=(t_usec&, t_msec);
  constexpr t_usec& operator+=(t_usec&, t_sec);

  constexpr t_msec& operator+=(t_msec&, t_nsec);
  constexpr t_msec& operator+=(t_msec&, t_usec);
  constexpr t_msec& operator+=(t_msec&, t_msec);
  constexpr t_msec& operator+=(t_msec&, t_sec);

  constexpr t_sec&  operator+=(t_sec&, t_nsec);
  constexpr t_sec&  operator+=(t_sec&, t_usec);
  constexpr t_sec&  operator+=(t_sec&, t_msec);
  constexpr t_sec&  operator+=(t_sec&, t_sec);

  constexpr t_date&  operator+=(t_date&,     t_nsec);
  constexpr t_date&  operator+=(t_date&,     t_usec);
  constexpr t_date&  operator+=(t_date&,     t_msec);
  constexpr t_date&  operator+=(t_date&,     t_sec);
  constexpr t_date&  operator+=(t_date&,     t_sec);
  constexpr t_date&  operator+=(t_interval&, t_sec);

  constexpr t_nsec& operator-=(t_nsec&, t_nsec);
  constexpr t_nsec& operator-=(t_nsec&, t_usec);
  constexpr t_nsec& operator-=(t_nsec&, t_msec);
  constexpr t_nsec& operator-=(t_nsec&, t_sec);

  constexpr t_usec& operator-=(t_usec&, t_nsec);
  constexpr t_usec& operator-=(t_usec&, t_usec);
  constexpr t_usec& operator-=(t_usec&, t_msec);
  constexpr t_usec& operator-=(t_usec&, t_sec);

  constexpr t_msec& operator-=(t_msec&, t_nsec);
  constexpr t_msec& operator-=(t_msec&, t_usec);
  constexpr t_msec& operator-=(t_msec&, t_msec);
  constexpr t_msec& operator-=(t_msec&, t_sec);

  constexpr t_sec&  operator-=(t_sec&, t_nsec);
  constexpr t_sec&  operator-=(t_sec&, t_usec);
  constexpr t_sec&  operator-=(t_sec&, t_msec);
  constexpr t_sec&  operator-=(t_sec&, t_sec);

  constexpr t_date&  operator-=(t_date&,     t_nsec);
  constexpr t_date&  operator-=(t_date&,     t_usec);
  constexpr t_date&  operator-=(t_date&,     t_msec);
  constexpr t_date&  operator-=(t_date&,     t_sec);
  constexpr t_date&  operator-=(t_date&,     t_sec);
  constexpr t_date&  operator-=(t_interval&, t_sec);

  t_date monotonic_now();
  t_date realtime_now ();
}
}
}

#endif
