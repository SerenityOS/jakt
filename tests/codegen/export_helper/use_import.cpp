#include <Exported.h>

// NOTE: codegen currently puts extern functions under Jakt namespace for
// simplicity. In reality, it should declare them without the Jakt namespacing,
// and use Jakt:: prefix for any Jakt types that it uses. But that is too big
// of a scope for what this test is trying to achieve.
namespace Jakt {
void use_exported(Exported const &e) {
    e.print_value();
}
}
