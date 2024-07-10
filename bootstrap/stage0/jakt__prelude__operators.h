#pragma once
#include <lib.h>
namespace Jakt {
namespace jakt__prelude__operators {
enum class Ordering: u8;
}
namespace jakt__prelude__operators {
enum class Ordering : u8 {
Less = (infallible_integer_cast<u8>((static_cast<u64>(0ULL)))),
Equal = (infallible_integer_cast<u8>((static_cast<u64>(1ULL)))),
Greater = (infallible_integer_cast<u8>((static_cast<u64>(2ULL)))),
};
}
} // namespace Jakt
