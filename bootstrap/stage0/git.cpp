#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "git.h"
namespace Jakt {
namespace git {
ErrorOr<ByteString> commit_hash() {
{
ByteString const hash = (ByteString::from_utf8_without_validation("2292180107ee78f9618c7adf898df218dde1e270"sv));
return hash;
}
}

}
} // namespace Jakt
