#include <Jakt/AKIntegration.h>
#include <Jakt/ByteStringBuilder.h>
#include <Jakt/PrettyPrint.h>

namespace JaktInternal::PrettyPrint {

static thread_local inline struct {
    int level = 0;
    bool enabled = false;
} s_pretty_print_state {};

ScopedEnable::ScopedEnable(bool should_enable)
    : m_previous_enabled { s_pretty_print_state.enabled }
{
    if (should_enable) {
        s_pretty_print_state.enabled = true;
    }
}

ScopedEnable::~ScopedEnable()
{
    s_pretty_print_state.enabled = m_previous_enabled;
}

ScopedLevelIncrease::ScopedLevelIncrease()
{
    s_pretty_print_state.level++;
}

ScopedLevelIncrease::~ScopedLevelIncrease()
{
    s_pretty_print_state.level--;
}

Jakt::ErrorOr<void> output_indentation(auto& builder)
{
    constexpr auto spaces_per_level = 2;
    if (s_pretty_print_state.enabled) {
        if (s_pretty_print_state.level > 0)
            builder.appendff("\n{:{}}", ""sv, s_pretty_print_state.level * spaces_per_level);
        else
            builder.append('\n');
    }
    return {};
}

template Jakt::ErrorOr<void> output_indentation<Jakt::ByteStringBuilder>(Jakt::ByteStringBuilder& builder);

void must_output_indentation(Jakt::ByteStringBuilder& builder)
{
    constexpr auto spaces_per_level = 2;
    if (s_pretty_print_state.enabled) {
        if (s_pretty_print_state.level > 0)
            builder.appendff("\n{:{}}", ""sv, s_pretty_print_state.level * spaces_per_level);
        else
            builder.append('\n');
    }
}

}
