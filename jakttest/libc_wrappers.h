#include <Jakt/Error.h>
#include <Jakt/Types.h>

namespace Jakt::libc {
ErrorOr<u8*> malloc(size_t size);
void free(u8* ptr);
ErrorOr<String> realpath(String path);
ErrorOr<String> dirname(String path);
// NOTE: if I use `basename` linker can't seem to find it.
ErrorOr<String> base_name(String path);
}
