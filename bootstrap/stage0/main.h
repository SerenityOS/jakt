#pragma once
#include <lib.h>
#include "platform__unknown_compiler.h"
#include "git.h"
#include "repl.h"
#include "jakt__libc__io.h"
#include "platform.h"
#include "project.h"
#include "ide.h"
#include "formatter.h"
#include "codegen.h"
#include "typechecker.h"
#include "interpreter.h"
#include "types.h"
#include "parser.h"
#include "lexer.h"
#include "compiler.h"
#include "error.h"
#include "utility.h"
#include "build.h"
#include "jakt__file_iterator.h"
#include "jakt__platform__unknown_fs.h"
#include "jakt__path.h"
#include "jakt__platform.h"
#include "jakt__arguments.h"
#include "jakt__prelude__prelude.h"
namespace Jakt {
struct FormatRange;
ByteString usage();

ByteString help();

ByteString indent(size_t const level);

JaktInternal::Optional<Jakt::FormatRange> parse_format_range(ByteString const range, size_t const input_file_length);

ErrorOr<void> install(Jakt::jakt__path::Path const from, Jakt::jakt__path::Path const to);

ErrorOr<int> selfhost_crosscompiler_main(JaktInternal::DynamicArray<ByteString> const args);

ErrorOr<void> mkdir_p(Jakt::jakt__path::Path const path);

ErrorOr<JaktInternal::DynamicArray<Jakt::jakt__path::Path>> find_with_extension(Jakt::jakt__path::Path const path, ByteString const extension);

ByteString escape_for_depfile(ByteString const input);

ErrorOr<int> compiler_main(JaktInternal::DynamicArray<ByteString> const args);

ErrorOr<void> format_output(Jakt::jakt__path::Path const file_path, JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens, JaktInternal::Optional<Jakt::FormatRange> const format_range, bool const format_debug, bool const format_inplace);

ErrorOr<void> write_only_if_updated(ByteString const data, ByteString const output_filename);

bool file_needs_updating(ByteString const path, ByteString const new_contents);

struct FormatRange {
  public:
public: size_t start;public: size_t end;public: FormatRange(size_t a_start, size_t a_end);

public: ByteString debug_description() const;
};template <typename T>
ErrorOr<T> value_or_throw(JaktInternal::Optional<T> const maybe);
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::FormatRange> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::FormatRange const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
