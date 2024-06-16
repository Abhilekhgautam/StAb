// enables location tracking of tokens in STAB 

#pragma once

#include <cstddef>
#include <ostream>
#include <utility>

namespace STAB {
  using position = std::size_t;
  using location = std::pair<std::size_t, std::size_t>;
}

inline std::ostream& operator << (std::ostream& os, const STAB::location& loc) {
   return os << "[" << loc.first << "-" << loc.second << "]";	
}
