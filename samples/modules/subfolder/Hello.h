/// Expect: Skip

#pragma once

#include <Jakt/AKIntegration.h>
#include <AK/String.h>
#include <AK/Format.h>

inline Jakt::ByteString get_hello() { return Jakt::ByteString("Hello"); }

struct Printer {
    static void print_something() { Jakt::outln("printed"); }
};
