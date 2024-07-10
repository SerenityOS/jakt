#pragma once
#include <lib.h>
#include "jakt__prelude__configuration.h"
#include "jakt__platform.h"
namespace Jakt {
namespace platform {



ErrorOr<ByteString> library_name_for_target(ByteString const name, Jakt::jakt__platform::Target const target);

}
} // namespace Jakt
