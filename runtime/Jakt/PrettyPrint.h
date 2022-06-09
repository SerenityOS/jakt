#pragma once

#include <Jakt/Error.h>

namespace JaktInternal {

static thread_local inline int _pretty_print_level = 0;
static thread_local inline bool _pretty_print_enabled = false;

ErrorOr<void> _output_pretty_indent(auto& builder) {
    if (_pretty_print_enabled) {
        if(_pretty_print_level > 0)
            TRY(builder.appendff("\n{:{}}", "", _pretty_print_level * 2));
        else
            TRY(builder.append('\n'));
    }
    return {};
}

}
