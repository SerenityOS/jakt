#include "unknown_fs.h"
namespace Jakt {
namespace unknown_fs {
ErrorOr<void> make_directory(const String path) {
{
warnln(String("NOT IMPLEMENTED: make_directory {}"),path);
return Error::from_errno(static_cast<i32>(38));
}
return {};
}

}
} // namespace Jakt
