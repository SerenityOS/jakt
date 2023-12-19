/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <IO/File.h>

#include <AK/RefPtr.h>
#include <AK/ScopeGuard.h>

#include <errno.h>

#if defined(AK_OS_MACOS)
#   include <mach-o/dyld.h>
#elif defined(_WIN32)
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   include <Windows.h>
#   ifdef Yield
#       undef Yield
#   endif
#   include <libloaderapi.h>
#else
    #include <unistd.h>
#endif

namespace JaktInternal {

File::File()
{
}

File::~File()
{
    fclose(m_stdio_file);
}

ErrorOr<NonnullRefPtr<File>> File::open_for_reading(StringView path_)
{
    auto path = ByteString(path_);
    auto* stdio_file = fopen(path.characters(), "rb");
    if (!stdio_file)
        return Error::from_errno(errno);

    ArmedScopeGuard close_file = [&] {
        fclose(stdio_file);
    };
    auto file = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) File));
    close_file.disarm();
    file->m_stdio_file = stdio_file;
    return file;
}

ErrorOr<NonnullRefPtr<File>> File::open_for_writing(StringView path_)
{
    auto path = ByteString(path_);
    auto* stdio_file = fopen(path.characters(), "wb");
    if (!stdio_file)
        return Error::from_errno(errno);

    ArmedScopeGuard close_file = [&] {
        fclose(stdio_file);
    };
    auto file = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) File));
    close_file.disarm();
    file->m_stdio_file = stdio_file;
    return file;
}

ErrorOr<DynamicArray<u8>> File::read_all()
{
    auto entire_file = DynamicArray<u8>::create_empty();

    // Try to guess the file size so we can pre-allocate the buffer.
    size_t file_size = 0;
    if (fseek(m_stdio_file, 0, SEEK_END) == 0) {
        file_size = ftell(m_stdio_file);
        fseek(m_stdio_file, 0, SEEK_SET);
    }

    if (file_size > 0)
        entire_file.ensure_capacity(file_size);

    while (true) {
        u8 buffer[4096];
        auto nread = fread(buffer, 1, sizeof(buffer), m_stdio_file);
        if (nread == 0) {
            if (feof(m_stdio_file)) {
                return entire_file;
            }
            auto error = ferror(m_stdio_file);
            return Error::from_errno(error);
        }
        size_t old_size = entire_file.size();
        TRY(entire_file.add_size(nread));
        memcpy(entire_file.unsafe_data() + old_size, buffer, nread);
    }
}

ErrorOr<size_t> File::read(DynamicArray<u8> buffer)
{
    auto nread = fread(buffer.unsafe_data(), 1, buffer.size(), m_stdio_file);
    if (nread == 0) {
        if (feof(m_stdio_file))
            return 0;
        auto error = ferror(m_stdio_file);
        return Error::from_errno(error);
    }
    return nread;
}

ErrorOr<size_t> File::write(DynamicArray<u8> data)
{
    if (data.is_empty()) {
        return 0;
    }
    auto nwritten = fwrite(data.unsafe_data(), 1, data.size(), m_stdio_file);
    if (nwritten == 0) {
        auto error = ferror(m_stdio_file);
        return Error::from_errno(error);
    }
    return nwritten;
}

bool File::exists(StringView path_)
{
    auto path = ByteString(path_);
#ifdef _WIN32
    auto res = GetFileAttributesA(path.characters());
    return res != INVALID_FILE_ATTRIBUTES;
#else
    return access(path.characters(), F_OK) == 0;
#endif
}

ErrorOr<ByteString> File::current_executable_path()
{
    char path[4096] {};
#ifdef _WIN32
    DWORD ret = GetModuleFileName(nullptr, path, sizeof(path));
    if (ret < 0)
        return Error::from_errno(GetLastError());
#else
    const char* path_to_readlink = nullptr;
#  ifdef AK_OS_MACOS
    uint32_t size = sizeof(path);
    auto os_ret = _NSGetExecutablePath(path, &size);
    if (os_ret != 0) {
        return Error::from_errno(ENAMETOOLONG);
    }
#  elif defined(AK_OS_BSD_GENERIC)
#   error "TODO: Implement current_executable_path using sysctl(KERN_PROC_PATHNAME) for non-macOS BSDs"
#  else
    // Linux, Serenity, non-BSD unix, etc
    path_to_readlink = "/proc/self/exe";
    ssize_t ret = readlink(path_to_readlink, path, sizeof(path) -1 );

    // Ignore if wasn't a a symlink
    if (ret == -1 && errno != EINVAL)
        return Error::from_errno(errno);
#endif
#endif
    path[sizeof(path) - 1] = '\0';

    return ByteString(StringView { path, strlen(path) });
}

}
