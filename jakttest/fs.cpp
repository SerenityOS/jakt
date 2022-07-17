#include "fs.h"
#include <Jakt/String.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace Jakt::fs {
ErrorOr<void> mkdir(String path)
{
    if (::mkdir(path.c_string(), S_IRWXU) == -1)
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}
}
