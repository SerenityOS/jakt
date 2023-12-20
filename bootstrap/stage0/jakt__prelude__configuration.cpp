#include "jakt__prelude__configuration.h"
namespace Jakt {
namespace jakt__prelude__configuration {
ByteString jakt__prelude__configuration::UserConfiguration::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("UserConfiguration("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
builder.append(")"sv);return builder.to_string(); }
jakt__prelude__configuration::UserConfiguration::UserConfiguration(){}

}
} // namespace Jakt
