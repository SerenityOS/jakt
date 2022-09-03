/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Builtins/Array.h>
#include <Jakt/Error.h>
#include <Jakt/RefCounted.h>
#include <Jakt/String.h>
#include <stdio.h>

namespace JaktInternal {
class File final : public RefCounted<File> {
public:
    static ErrorOr<NonnullRefPtr<File>> open_for_reading(String path);
    static ErrorOr<NonnullRefPtr<File>> open_for_writing(String path);

    ErrorOr<size_t> read(Array<u8>);
    ErrorOr<size_t> write(Array<u8>);

    ErrorOr<Array<u8>> read_all();

    ~File();

    static bool exists(String path);
    static ErrorOr<String> current_executable_path();

private:
    File();

    FILE* m_stdio_file { nullptr };
};
}

namespace Jakt {
using JaktInternal::File;
}
