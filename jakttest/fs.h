// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
//
// SPDX-License-Identifier: BSD-2-Clause
#pragma once
#include <Jakt/Forward.h>
#include <Jakt/String.h>
#include <dirent.h>
#include <sys/stat.h>

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
ErrorOr<void> mkdir(String path);
ErrorOr<void> rmdir(String path);
ErrorOr<void> unlink(String path);

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
ErrorOr<Optional<StatResults>> stat_silencing_enoent(String path);
ErrorOr<void> chdir(String path);
}
