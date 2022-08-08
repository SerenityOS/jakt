/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <IO/File.h>
#include <errno.h>
#ifdef _WIN32
#    include <direct.h>
#else
#    include <dirent.h>
#    include <sys/stat.h>
#endif

namespace JaktInternal {

File::File()
{
}

File::~File()
{
    fclose(m_stdio_file);
}

ErrorOr<NonnullRefPtr<File>> File::open_for_reading(String path)
{
    auto* stdio_file = fopen(path.c_string(), "rb");
    if (!stdio_file) {
        return Error::from_errno(errno);
    }
    auto file = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) File));
    file->m_stdio_file = stdio_file;
    return file;
}

ErrorOr<NonnullRefPtr<File>> File::open_for_writing(String path)
{
    auto* stdio_file = fopen(path.c_string(), "wb");
    if (!stdio_file) {
        return Error::from_errno(errno);
    }
    auto file = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) File));
    file->m_stdio_file = stdio_file;
    return file;
}

ErrorOr<Array<u8>> File::read_all()
{
    auto entire_file = TRY(Array<u8>::create_empty());

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

ErrorOr<size_t> File::read(Array<u8> buffer)
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

ErrorOr<size_t> File::write(Array<u8> data)
{
    auto nwritten = fwrite(data.unsafe_data(), 1, data.size(), m_stdio_file);
    if (nwritten == 0) {
        auto error = ferror(m_stdio_file);
        return Error::from_errno(error);
    }
    return nwritten;
}

bool File::exists(String path)
{
    // FIXME: This is a pretty sad-looking function. It could be better, but don't forget about Windows.
    auto* file = fopen(path.c_string(), "r");
    if (!file)
        return false;
    fclose(file);
    return true;
}

ErrorOr<void> mkdir(String path)
{
#ifdef _WIN32
    if (::mkdir(path.c_string()) == -1)
#else
    if (::mkdir(path.c_string(), S_IRWXU) == -1)
#endif
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}

}
