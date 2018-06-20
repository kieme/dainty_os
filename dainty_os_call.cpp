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

#include "dainty_os_call.h"

namespace dainty
{
namespace os
{
///////////////////////////////////////////////////////////////////////////////

  t_int call_pthread_mutex_init(pthread_mutex_t& mutex,
                                const pthread_mutexattr_t* attr) noexcept {
     return {::pthread_mutex_init(&mutex, attr)};
  }

  t_validity call_pthread_mutex_init(t_err err, pthread_mutex_t& mutex,
                                     const pthread_mutexattr_t* attr) noexcept {
    if (!err) {
      int j = call_pthread_mutex_init(mutex, attr);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_mutex_destroy(pthread_mutex_t& mutex) noexcept {
    return {::pthread_mutex_destroy(&mutex)};
  }

  t_validity call_pthread_mutex_destroy(t_err err,
                                        pthread_mutex_t& mutex) noexcept {
    if (!err) {
      int j = call_pthread_mutex_destroy(mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_mutex_lock(pthread_mutex_t& mutex) noexcept {
    return {::pthread_mutex_lock(mutex)};
  }

  t_validity call_pthread_mutex_lock(t_err err,
                                     pthread_mutex_t& mutex) noexcept {
    if (!err) {
      int j = call_pthread_mutex_lock(mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_mutex_trylock(pthread_mutex_t& mutex) noexcept {
    return {::pthread_mutex_trylock(mutex)};
  }

  t_validity call_pthread_mutex_trylock(t_err err,
                                        pthread_mutex_t& mutex) noexcept {
    if (!err) {
      int j = call_pthread_mutex_trylock(mutex);
      switch (j) {
        case 0: return VALID;
        case EBUSY: {
          err = 8; //XXX
        } break;
        default: {
          err = 10; //XXX
        } break;
      }
    }
    return INVALID;
  }

  t_int call_pthread_mutex_unlock(pthread_mutex_t& mutex) noexcept {
    return {::pthread_mutex_unlock(mutex)};
  }

  t_validity call_pthread_mutex_unlock(t_err err,
                                       pthread_mutex_t& mutex) noexcept {
    if (!err) {
      int j = call_pthread_mutex_unlock(mutex);
      switch (j) {
        case 0: return VALID;
        default: {
          err = 10; //XXX
        } break;
      }
    }
    return INVALID;
  }

///////////////////////////////////////////////////////////////////////////////

}
}

