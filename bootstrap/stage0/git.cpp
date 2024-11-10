#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "git.h"
namespace Jakt {
namespace git {
ErrorOr<ByteString> commit_hash() {
{
ByteString const hash = ByteString::from_utf8_without_validation("4fbe58fe99988156bf36ca4e8db4312a29d2c471"sv);
return hash;
}
}

}
} // namespace Jakt
