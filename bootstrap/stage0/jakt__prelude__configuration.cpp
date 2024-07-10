#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "jakt__prelude__configuration.h"
#include "jakt__prelude__configuration.h"
namespace Jakt {
namespace jakt__prelude__configuration {
ByteString Jakt::jakt__prelude__configuration::UserConfiguration::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("UserConfiguration("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
builder.append(")"sv);return builder.to_string(); }
Jakt::jakt__prelude__configuration::UserConfiguration::UserConfiguration(){}

}
} // namespace Jakt
