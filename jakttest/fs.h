#include <Jakt/Forward.h>
#include <Jakt/String.h>
#include <dirent.h>

namespace Jakt::fs {
ErrorOr<void> mkdir(String path);

class DirectoryIterator : public RefCounted<DirectoryIterator> {
    DIR* m_dirfd;
    constexpr DirectoryIterator(DIR* dirfd)
        : m_dirfd(dirfd)
    {
    }

public:
    static ErrorOr<NonnullRefPtr<DirectoryIterator>> from_raw_dirfd(DIR* dirfd);
    ~DirectoryIterator();
    constexpr DirectoryIterator(DirectoryIterator&& other)
        : m_dirfd(other.m_dirfd)
    {
        other.m_dirfd = NULL;
    }
    ErrorOr<Optional<String>> next();
};
ErrorOr<NonnullRefPtr<DirectoryIterator>> list_directory(String path);
ErrorOr<bool> is_directory(String path);
}
