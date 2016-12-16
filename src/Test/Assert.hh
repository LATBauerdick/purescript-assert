///////////////////////////////////////////////////////////////////////////////
//
// Module      :  Assert.hh
// Copyright   :  (c) Andy Arvanitis 2015
// License     :  MIT
//
// Maintainer  :  Andy Arvanitis <andy.arvanitis@gmail.com>
// Stability   :  experimental
// Portability :
//
// Assert FFI functions
//
///////////////////////////////////////////////////////////////////////////////
//
#ifndef Test_Assert_FFI_HH
#define Test_Assert_FFI_HH

#include "PureScript/PureScript.hh"

namespace Test_Assert {
  using namespace PureScript;

  // foreign import assert'
  //   :: forall e
  //    . String
  //   -> Boolean
  //   -> Eff (assert :: ASSERT | e) Unit
  //
  inline auto assert$prime(const any& message, const bool success) -> any {
    return [=]() -> any {
      if (not success) throw runtime_error(message);
      return Data_Unit::unit;
    };
  }

  // foreign import checkThrows
  //   :: forall e a
  //    . (Unit -> a)
  //   -> Eff (assert :: ASSERT | e) Boolean
  //
  inline auto checkThrows(const any& f) -> any {
    return [=]() -> any {
      try {
        f(Data_Unit::unit);
        return false;
      } catch (std::runtime_error&) {
        return true;
      } catch (std::exception&) {
        throw runtime_error("Threw something other than an Error");
      }
      return Data_Unit::unit;
    };
  }

}

#endif // Test_Assert_FFI_HH
