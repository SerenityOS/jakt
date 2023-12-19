#pragma once

#include <Jakt/AKIntegration.h>

#include <AK/Error.h>
#include <AK/Noncopyable.h>

namespace Jakt {
class ByteStringBuilder;
}

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

Jakt::ErrorOr<void> output_indentation(auto& builder);
void must_output_indentation(Jakt::ByteStringBuilder&);

}
