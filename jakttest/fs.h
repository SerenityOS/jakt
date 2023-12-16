// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
// Copyright (c) 2022, Andrew Kaster <akaster@serenityos.org>
//
// SPDX-License-Identifier: BSD-2-Clause
#pragma once
#include <Jakt/AKIntegration.h>

#include <AK/Forward.h>
#include <AK/ByteString.h>
#include <AK/RefPtr.h>
#ifndef _WIN32
#include <dirent.h>
#include <sys/stat.h>
#endif

namespace Jakt::fs {
#ifndef _WIN32
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
    ErrorOr<Optional<ByteString>> next();
};

class StatResults {
    size_t m_modified_time;
    mode_t m_mode;

public:
    constexpr StatResults(size_t modified_time, mode_t mode)
        : m_modified_time(modified_time)
        , m_mode(mode)
    {
    }
    constexpr size_t modified_time() const { return m_modified_time; }
    constexpr size_t is_executable() const { return (m_mode & S_IXUSR) != 0; }
    constexpr size_t is_regular_file() const { return S_ISREG(m_mode); }
    constexpr size_t is_directory() const { return S_ISDIR(m_mode); }
};
#else
class DirectoryIterator : public RefCounted<DirectoryIterator> {
public:
    // Don't hold onto a HANDLE directly here, that requires <windows.h>
    class Impl;

    static ErrorOr<NonnullRefPtr<DirectoryIterator>> create(RefPtr<Impl>);
    ~DirectoryIterator();
    DirectoryIterator(DirectoryIterator&& other);
    ErrorOr<Optional<ByteString>> next();

private:
    DirectoryIterator(RefPtr<Impl> impl);
    RefPtr<Impl> m_impl;
};

class StatResults {
    // We could store the file attributes here, but that forces <windows.h> include, which causes issues
    u64 m_modified_time = 0;
    bool m_is_executable = false;
    bool m_is_regular_file = false;
    bool m_is_directory = false;

public:
    constexpr StatResults(u64 modified_time, bool is_executable, bool is_regular_file, bool is_directory)
        : m_modified_time(modified_time)
        , m_is_executable(is_executable)
        , m_is_regular_file(is_regular_file)
        , m_is_directory(is_directory)
    {
    }

    constexpr size_t modified_time() const { return m_modified_time; }
    constexpr size_t is_executable() const { return m_is_executable; }
    constexpr size_t is_regular_file() const { return m_is_regular_file; }
    constexpr size_t is_directory() const { return m_is_directory; }
};
#endif

ErrorOr<void> mkdir(ByteString path);
ErrorOr<void> rmdir(ByteString path);
ErrorOr<void> unlink(ByteString path);

ErrorOr<NonnullRefPtr<DirectoryIterator>> list_directory(ByteString path);
ErrorOr<Optional<StatResults>> stat_silencing_enoent(ByteString path);
}
