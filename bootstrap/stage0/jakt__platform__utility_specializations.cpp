#include "jakt__platform__utility.h"
#include "jakt__libc__io.h"
namespace Jakt {
namespace jakt__platform__utility {

/* specialisation 0 of function null: ["FILE*"] */
template<> FILE* null<FILE*>();

/* specialisation 1 of function null: ["char*"] */
template<> char* null<char*>();

/* specialisation 0 of function allocate: ["char"] */
template<> char* allocate<char>(size_t const count);
template<>
FILE* null<FILE*>() {
{
Function<FILE*()> const make_null = []() -> FILE* {{
bool const dep = true;
{
return nullptr;
}

Jakt::abort();
}
}
;
return make_null();
}
}
template<>
char* null<char*>() {
{
Function<char*()> const make_null = []() -> char* {{
bool const dep = true;
{
return nullptr;
}

Jakt::abort();
}
}
;
return make_null();
}
}
template<>
char* allocate<char>(size_t const count) {
{
Function<void(char*&)> const alloc_impl = [count](char*& ptr) -> void {{
{
ptr = static_cast<RemoveReference<decltype(ptr)>>(calloc(count, sizeof(*ptr)));
}

}
}
;
char* ptr = Jakt::jakt__platform__utility::null<char*>();
alloc_impl(ptr);
return ptr;
}
}
}
} // namespace Jakt
