#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "git.h"
namespace Jakt {
namespace git {
ErrorOr<ByteString> commit_hash() {
{
ByteString const hash = ByteString::from_utf8_without_validation("2c56047f8015fa0619ac5354d1274b8bfa12ba5f"sv);
return hash;
}
}

}
} // namespace Jakt
