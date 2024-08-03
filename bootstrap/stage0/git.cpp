#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "git.h"
namespace Jakt {
namespace git {
ErrorOr<ByteString> commit_hash() {
{
ByteString const hash = (ByteString::from_utf8_without_validation("8f5681207630919e5b90b50657bd71eb8f2db117"sv));
return hash;
}
}

}
} // namespace Jakt
