#pragma once
#include <lib.h>
namespace Jakt {
namespace jakt__compiler {
namespace debug {

}
extern ErrorOr<ByteString> target_triple_string();

extern JaktInternal::Optional<StringView> user_configuration_value(StringView const name);

extern i32 debug_this_scope(bool const breakpoint);

}
} // namespace Jakt
