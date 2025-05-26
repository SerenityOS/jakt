#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "git.h"
namespace Jakt {
namespace git {
ErrorOr<ByteString> commit_hash() {
{
ByteString const hash = ByteString::from_utf8_without_validation("0e7731ee310a9d9b1164bb2bdb1d78664239d8b2"sv);
return hash;
}
}

}
} // namespace Jakt
