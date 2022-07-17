#include "fs.h"
#include <Jakt/RefPtr.h>
#include <Jakt/String.h>
#include <Jakt/StringBuilder.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace Jakt::fs {
ErrorOr<void> mkdir(String path)
{
    if (::mkdir(path.c_string(), S_IRWXU) == -1)
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}

ErrorOr<Optional<String>> DirectoryIterator::next()
{
    if (m_dirfd == NULL) {
        return JaktInternal::NullOptional {};
    }
    auto const next_dir = readdir(m_dirfd);
    if (next_dir == NULL) {
        closedir(m_dirfd);
        m_dirfd = NULL;
        return JaktInternal::NullOptional {};
    }
    auto builder = TRY(StringBuilder::create());
    TRY(builder.append_c_string(next_dir->d_name));
    return Optional<String>(TRY(builder.to_string()));
}
DirectoryIterator::~DirectoryIterator()
{
    if (m_dirfd != NULL) {
        closedir(m_dirfd);
        m_dirfd = NULL;
    }
}

ErrorOr<NonnullRefPtr<DirectoryIterator>> DirectoryIterator::from_raw_dirfd(DIR* dirfd)
{
    return adopt_nonnull_ref_or_enomem(new (nothrow) DirectoryIterator(dirfd));
}

ErrorOr<NonnullRefPtr<DirectoryIterator>> list_directory(String path)
{
    auto const dirfd = opendir(path.c_string());
    if (dirfd == NULL) {
        return Error::from_errno(errno);
    }
    return DirectoryIterator::from_raw_dirfd(dirfd);
}

ErrorOr<bool> is_directory(String path)
{
    struct stat st;
    if (stat(path.c_string(), &st) < 0) {
        return Error::from_errno(errno);
    }
    return S_ISDIR(st.st_mode);
}

ErrorOr<void> mkdir(String path)
{
    int const result = ::mkdir(path.c_string(), S_IRWXU);
    if (result == -1 && errno != EEXIST)
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}

ErrorOr<void> rmdir(String path)
{
    if (::rmdir(path.c_string()) == -1)
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}
ErrorOr<void> unlink(String path)
{
    if (::unlink(path.c_string()) == -1)
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}
}
