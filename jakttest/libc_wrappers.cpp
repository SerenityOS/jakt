#include "libc_wrappers.h"
#include <Jakt/RefPtr.h>
#include <Jakt/String.h>
#include <Jakt/StringBuilder.h>
#include <libgen.h> // dirname(3)
#include <stdlib.h>
#include <string.h>

namespace Jakt::libc {
ErrorOr<u8*> malloc(size_t size)
{
    auto const mem = ::malloc(size);
    if (mem == NULL)
        return Error::from_errno(ENOMEM);
    return reinterpret_cast<u8*>(mem);
}

void free(u8* ptr)
{
    ::free(ptr);
}
ErrorOr<String> base_name(String path)
{
    char* cpath = ::strdup(path.c_string());
    if (cpath == NULL)
        return Error::from_errno(ENOMEM);
    auto const name = ::basename(cpath);
    auto builder = TRY(StringBuilder::create());
    TRY(builder.append_c_string(name));
    ::free(cpath);
    return builder.to_string();
}

ErrorOr<String> dirname(String path)
{
    char* cpath = ::strdup(path.c_string());
    if (cpath == NULL)
        return Error::from_errno(ENOMEM);
    auto const dir = ::dirname(cpath);
    auto builder = TRY(StringBuilder::create());
    TRY(builder.append_c_string(dir));
    ::free(cpath);
    return builder.to_string();
}
ErrorOr<String> realpath(String path)
{
    auto const real_path = ::realpath(path.c_string(), NULL);
    if (real_path == NULL)
        return Error::from_errno(errno);
    auto builder = TRY(StringBuilder::create());
    TRY(builder.append_c_string(real_path));
    ::free(real_path);
    return builder.to_string();
}

}
