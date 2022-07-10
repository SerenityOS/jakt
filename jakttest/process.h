#include <Builtins/Array.h>
#include <Jakt/Error.h>
#include <Jakt/String.h>

namespace Jakt::process {
ErrorOr<i32> start_background_process(Array<String> args);
ErrorOr<Optional<i32>> poll_process_exit(i32 pid);
ErrorOr<void> forcefully_kill_process(i32 pid);
}
