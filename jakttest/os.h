#include <Jakt/Types.h>
#include <Jakt/Error.h>

namespace Jakt::os {
    ErrorOr<size_t> get_num_cpus();
    ErrorOr<String> get_system_temporary_directory();
}
