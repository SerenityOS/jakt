#pragma once
#include <lib.h>
namespace Jakt {
namespace jakt__platform__utility {
ErrorOr<ByteString> join(JaktInternal::DynamicArray<ByteString> const strings, ByteString const separator);

}
namespace jakt__platform__utility {
template <typename T>
T null();
template <typename T>
T* allocate(size_t const count);
}
} // namespace Jakt
