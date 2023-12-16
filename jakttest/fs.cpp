// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
// Copyright (c) 2022, Andrew Kaster <akaster@serenityos.org>
//
// SPDX-License-Identifier: BSD-2-Clause
#include "fs.h"
#include <Jakt/ByteString.h>

#include <AK/RefPtr.h>
#include <AK/ByteString.h>
#include <Jakt/ByteStringBuilder.h>
#include <fcntl.h>
#if defined(__APPLE__)
#    define st_atim st_atimespec
#    define st_ctim st_ctimespec
#    define st_mtim st_mtimespec
#endif
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <fileapi.h>
#include <direct.h>
#include <stdio.h>
#include <system_error>
#ifdef _MSVC_EXECUTION_CHARACTER_SET
// See: https://docs.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
static_assert(_MSVC_EXECUTION_CHARACTER_SET == 65001, "Must be compiled with /utf-8!");
#endif
#endif

namespace Jakt::fs {
#ifndef _WIN32
ErrorOr<void> mkdir(ByteString path)
{
    if (::mkdir(path.characters(), S_IRWXU) == -1)
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}

ErrorOr<Optional<ByteString>> DirectoryIterator::next()
{
    if (m_dirfd == NULL) {
        return JaktInternal::OptionalNone {};
    }
    auto const next_dir = readdir(m_dirfd);
    if (next_dir == NULL) {
        closedir(m_dirfd);
        m_dirfd = NULL;
        return JaktInternal::OptionalNone {};
    }
    auto builder = ByteStringBuilder::create();
    TRY(builder.append_c_string(next_dir->d_name));
    return Optional<ByteString>(TRY(builder.to_string()));
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

ErrorOr<NonnullRefPtr<DirectoryIterator>> list_directory(ByteString path)
{
    auto const dirfd = opendir(path.characters());
    if (dirfd == NULL) {
        return Error::from_errno(errno);
    }
    return DirectoryIterator::from_raw_dirfd(dirfd);
}

ErrorOr<bool> is_directory(ByteString path)
{
    struct stat st;
    if (stat(path.characters(), &st) < 0) {
        return Error::from_errno(errno);
    }
    return S_ISDIR(st.st_mode);
}

ErrorOr<void> rmdir(ByteString path)
{
    if (::rmdir(path.characters()) == -1)
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}
ErrorOr<void> unlink(ByteString path)
{
    if (::unlink(path.characters()) == -1)
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}
ErrorOr<Optional<StatResults>> stat_silencing_enoent(ByteString path)
{
    struct stat st;
    if (stat(path.characters(), &st) < 0) {
        if (errno == ENOENT) {
            return JaktInternal::OptionalNone {};
        }
        return Error::from_errno(errno);
    }
    return Optional<StatResults>(StatResults(st.st_mtim.tv_sec, st.st_mode));
}
#else // ^ !_WIN32 v _WIN32

static int last_error_to_errno(DWORD error)
{
    // Shh, there's no ::std here
    return ::std::system_category().default_error_condition(error).value();
}

ErrorOr<void> mkdir(ByteString path)
{
    auto ret = ::mkdir(path.characters());
    if (ret == -1) {
        // Note: CRT methods *do* set errno
        return Error::from_errno(errno);
    }
    return ErrorOr<void> {};
}

class DirectoryIterator::Impl : public RefCounted<Impl> {
private:
    friend DirectoryIterator;
    HANDLE m_dirhandle = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA m_first_file_data = {};
    bool m_first = true;

    constexpr Impl(HANDLE dirhandle, WIN32_FIND_DATA first_file_data)
        : m_dirhandle(dirhandle)
        , m_first_file_data(move(first_file_data))
    {
    }
public:
    static ErrorOr<NonnullRefPtr<Impl>> create(HANDLE dirhandle, WIN32_FIND_DATA first_file_data)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) Impl(dirhandle, move(first_file_data)));
    }
    ~Impl()
    {
        if (m_dirhandle != INVALID_HANDLE_VALUE) {
            FindClose(m_dirhandle);
            m_dirhandle = INVALID_HANDLE_VALUE;
        }
    }
};

ErrorOr<Optional<ByteString>> DirectoryIterator::next()
{
    if (m_impl->m_dirhandle == INVALID_HANDLE_VALUE)
        return JaktInternal::OptionalNone {};

    WIN32_FIND_DATA file_data = {};
    LPWIN32_FIND_DATA pfile_data = m_impl->m_first ? &m_impl->m_first_file_data : &file_data;
    if (!m_impl->m_first) {
        if (!FindNextFile(m_impl->m_dirhandle, &file_data)) {
            DWORD err = GetLastError();
            FindClose(m_impl->m_dirhandle);
            m_impl->m_dirhandle = INVALID_HANDLE_VALUE;
            if (err != ERROR_NO_MORE_FILES) {
                return Error::from_errno(last_error_to_errno(err));
            }
            return JaktInternal::OptionalNone {};
        }
    }
    m_impl->m_first = false;
    auto filepath = TRY(__jakt_format("{}", StringView { pfile_data->cFileName, strnlen(pfile_data->cFileName, sizeof(pfile_data->cFileName)) }));
    return Optional<ByteString>(move(filepath));
}

DirectoryIterator::~DirectoryIterator() = default;
DirectoryIterator::DirectoryIterator(DirectoryIterator&& other)
    : m_impl(exchange(other.m_impl, nullptr))
{
}

DirectoryIterator::DirectoryIterator(RefPtr<Impl> impl)
    : m_impl(impl)
{
}

ErrorOr<NonnullRefPtr<DirectoryIterator>> DirectoryIterator::create(RefPtr<Impl> impl)
{
    return adopt_nonnull_ref_or_enomem(new (nothrow) DirectoryIterator(move(impl)));
}

ErrorOr<NonnullRefPtr<DirectoryIterator>> list_directory(ByteString path)
{
    path = TRY(__jakt_format("{}\\*", path));
    WIN32_FIND_DATA first_file_data = {};
    HANDLE dirhandle = FindFirstFile(path.characters(), &first_file_data);
    if (dirhandle == INVALID_HANDLE_VALUE) {
        return Error::from_errno(last_error_to_errno(GetLastError()));
    }
    auto impl = TRY(DirectoryIterator::Impl::create(dirhandle, move(first_file_data)));
    return DirectoryIterator::create(move(impl));
}

ErrorOr<bool> is_directory(ByteString path)
{
    DWORD file_attributes = GetFileAttributes(path.characters());
    if (file_attributes == INVALID_FILE_ATTRIBUTES) {
        return Error::from_errno(last_error_to_errno(GetLastError()));
    }
    return file_attributes & FILE_ATTRIBUTE_DIRECTORY;
}

ErrorOr<void> rmdir(ByteString path)
{
    if (::rmdir(path.characters()) == -1)
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}
ErrorOr<void> unlink(ByteString path)
{
    if (::unlink(path.characters()) == -1)
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}
ErrorOr<Optional<StatResults>> stat_silencing_enoent(ByteString path)
{
    WIN32_FILE_ATTRIBUTE_DATA attribute_data {};
    if (!GetFileAttributesEx(path.characters(), GetFileExInfoStandard, &attribute_data)) {
        DWORD err = GetLastError();
        if (err == ERROR_FILE_NOT_FOUND) {
            return JaktInternal::OptionalNone {};
        }
        return Error::from_errno(last_error_to_errno(err));
    }

    u64 modified_time = (u64)attribute_data.ftLastWriteTime.dwLowDateTime | (u64)attribute_data.ftLastWriteTime.dwHighDateTime << 32;
    bool is_executable = path.ends_with(".exe"sv);
    bool is_regular_file = attribute_data.dwFileAttributes & FILE_ATTRIBUTE_NORMAL;
    bool is_directory = attribute_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;

    return Optional<StatResults>(StatResults(modified_time, is_executable, is_regular_file, is_directory));
}

#endif // _WIN32
}
