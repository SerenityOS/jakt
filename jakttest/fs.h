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
ErrorOr<void> mkdir(String path);
ErrorOr<void> rmdir(String path);
ErrorOr<void> unlink(String path);

class StatResults {
    size_t m_modified_time;
    bool m_is_executable;
    bool m_is_regular_file;
    bool m_exists;

public:
    constexpr StatResults(size_t modified_time, bool is_executable, bool is_regular_file, bool exists)
        : m_modified_time(modified_time)
        , m_is_executable(is_executable)
        , m_is_regular_file(is_regular_file)
        , m_exists(exists)
    {
    }
    constexpr size_t modified_time() const { return m_modified_time; }
    constexpr size_t is_executable() const { return m_is_executable; }
    constexpr size_t is_regular_file() const { return m_is_regular_file; }
    constexpr size_t exists() const { return m_exists; }
};
ErrorOr<Optional<StatResults>> stat_silencing_enoent(String path);
}
