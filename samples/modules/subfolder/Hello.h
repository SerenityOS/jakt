/// Expect: Skip

#include <Jakt/String.h>
#include <Jakt/Format.h>

inline Jakt::String get_hello() { return Jakt::String("Hello"); }

struct Printer {
    static void print_something() { Jakt::outln("printed"); }
};
