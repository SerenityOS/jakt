#include "parser.h"
#include "lexer.h"
#include "compiler.h"
#include "error.h"
#include "utility.h"
namespace Jakt {
namespace parser {

/* specialisation 0 of function u64_to_float: ["f64"] */
template<> f64 u64_to_float<f64>(u64 const number);
template<>
f64 u64_to_float<f64>(u64 const number) {
{
f64 float_value = static_cast<i64>(0LL);
{
float_value = number;
}

return float_value;
}
}
}
} // namespace Jakt
