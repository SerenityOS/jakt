#pragma once

#include <stdint.h>

template<typename Block>
class ScopeGuard {
public:
    ScopeGuard(Block block) : m_block(block) { }
    ~ScopeGuard() { m_block(); }

private:
    Block m_block;
};

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

static_assert(sizeof(f32) == 4);
static_assert(sizeof(f64) == 8);
