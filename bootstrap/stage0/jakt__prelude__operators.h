#pragma once
#include <lib.h>
namespace Jakt {
namespace jakt__prelude__operators {
enum class Ordering: u8;
}
namespace jakt__prelude__operators {
enum class Ordering : u8 {
Less = static_cast<u8>(static_cast<u8>(0)),
Equal = static_cast<u8>(static_cast<u8>(1)),
Greater = static_cast<u8>(static_cast<u8>(2)),
};
}
} // namespace Jakt
