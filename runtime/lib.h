#pragma once

template<typename Block>
class ScopeGuard {
public:
    ScopeGuard(Block block) : m_block(block) { }
    ~ScopeGuard() { m_block(); }

private:
    Block m_block;
};
