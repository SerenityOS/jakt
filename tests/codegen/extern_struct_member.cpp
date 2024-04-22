#include <stdio.h>

namespace Jakt {
struct Test {
    static void say_hi();
};

void Test::say_hi() {
    printf("hello\n");
}
}