#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace jakt__platform__utility {
template <typename T>
T null();
template <typename T>
T* allocate(size_t const count);
}
} // namespace Jakt
