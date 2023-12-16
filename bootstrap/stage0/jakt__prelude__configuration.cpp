#include "jakt__prelude__configuration.h"
namespace Jakt {
namespace jakt__prelude__configuration {
ErrorOr<ByteString> jakt__prelude__configuration::UserConfiguration::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("UserConfiguration("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
TRY(builder.append(")"sv));return builder.to_string(); }
jakt__prelude__configuration::UserConfiguration::UserConfiguration(){}

}
} // namespace Jakt
