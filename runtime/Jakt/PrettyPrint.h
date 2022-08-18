#pragma once

#include <Jakt/Error.h>
#include <Jakt/Noncopyable.h>

namespace JaktInternal::PrettyPrint {

struct ScopedEnable {
    AK_MAKE_NONCOPYABLE(ScopedEnable);
    AK_MAKE_NONMOVABLE(ScopedEnable);
public:
    ScopedEnable(bool should_enable);

    ~ScopedEnable();
private:
    bool m_previous_enabled;
};

struct ScopedLevelIncrease {
    AK_MAKE_NONCOPYABLE(ScopedLevelIncrease);
    AK_MAKE_NONMOVABLE(ScopedLevelIncrease);
public:
    ScopedLevelIncrease();
    ~ScopedLevelIncrease();
};

ErrorOr<void> output_indentation(auto& builder);

}
