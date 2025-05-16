#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "git.h"
namespace Jakt {
namespace git {
ErrorOr<ByteString> commit_hash() {
{
ByteString const hash = ByteString::from_utf8_without_validation("6a3ebe5a51a713648c0830b34673e5892ed9cc52"sv);
return hash;
}
}

}
} // namespace Jakt
