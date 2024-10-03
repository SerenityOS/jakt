#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "git.h"
namespace Jakt {
namespace git {
ErrorOr<ByteString> commit_hash() {
{
ByteString const hash = ByteString::from_utf8_without_validation("d1fb6cc0e91e3f0164a412b5cdebe7183ad798f5"sv);
return hash;
}
}

}
} // namespace Jakt
