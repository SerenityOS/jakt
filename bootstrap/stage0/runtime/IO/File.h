/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Jakt/AKIntegration.h>

#include <AK/Error.h>
#include <AK/RefCounted.h>
#include <AK/ByteString.h>

#include <Builtins/DynamicArray.h>
#include <stdio.h>

namespace JaktInternal {
class File final : public RefCounted<File> {
public:
    static ErrorOr<NonnullRefPtr<File>> open_for_reading(StringView path);
    static ErrorOr<NonnullRefPtr<File>> open_for_writing(StringView path);

    ErrorOr<size_t> read(DynamicArray<u8>);
    ErrorOr<size_t> write(DynamicArray<u8>);

    ErrorOr<DynamicArray<u8>> read_all();

    ~File();

    static bool exists(StringView path);
    static ErrorOr<ByteString> current_executable_path();

private:
    File();

    FILE* m_stdio_file { nullptr };
};
}

namespace Jakt {
using JaktInternal::File;
}
