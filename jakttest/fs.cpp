#include "fs.h"
#include <Jakt/String.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace Jakt::fs {
ErrorOr<void> touch(String path)
{
    int const fd = open(path.c_string(), O_WRONLY | O_CREAT | O_NOCTTY | O_NONBLOCK | O_TRUNC, 0666);
    if (fd == -1)
        return Error::from_errno(errno);
    close(fd);
    return ErrorOr<void> {};
}

ErrorOr<void> mkdir(String path) {
    if (::mkdir(path.c_string(), S_IRWXU) == -1)
        return Error::from_errno(errno);
    return ErrorOr<void>{};
}
}
