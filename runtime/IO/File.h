/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Array.h>
#include <AK/Error.h>
#include <AK/RefCounted.h>
#include <AK/String.h>
#include <stdio.h>

class File final : public RefCounted<File> {
public:
    static ErrorOr<NonnullRefPtr<File>> open_for_reading(String path);
    static ErrorOr<NonnullRefPtr<File>> open_for_writing(String path);

    ErrorOr<size_t> read(Array<u8>);
    ErrorOr<size_t> write(Array<u8>);

    ErrorOr<Array<u8>> read_all();

    ~File();

private:
    File();

    FILE* m_stdio_file { nullptr };
};
