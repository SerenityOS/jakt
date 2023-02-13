/*
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Format.h>
#include <AK/HashFunctions.h>
#include <AK/Vector.h>

namespace AK::Detail {

template<auto... Hashes>
struct BloomFilter;

template<auto Hash, auto... Hashes>
struct BloomFilter<Hash, Hashes...> : public BloomFilter<Hashes...> {
    BloomFilter() = default;

    void set(auto&& key)
    {
        hash |= Hash(key);
        BloomFilter<Hashes...>::set(key);
    }

    bool maybe_contains(auto key) const
    {
        return (hash & Hash(key)) != 0 && BloomFilter<Hashes...>::maybe_contains(key);
    }

    void clear()
    {
        hash = 0;
        BloomFilter<Hashes...>::clear();
    }

    u64 hash { 0 };
};

template<auto Hash>
struct BloomFilter<Hash> {
    BloomFilter() = default;

    void set(auto&& key)
    {
        hash |= Hash(key);
    }

    bool maybe_contains(auto key) const
    {
        return (hash & Hash(key)) != 0;
    }

    void clear()
    {
        hash = 0;
    }

    u64 hash { 0 };
};
}

namespace AK {
template<auto... Hashes>
struct BloomFilter {
    BloomFilter()
        : filters({ Detail::BloomFilter<Hashes...>() })
    {
    }

    void set(auto&& key)
    {
        if (maybe_contains(key) && members >= 1.5 * growth) {
            filters.append(Detail::BloomFilter<Hashes...>());
            dbgln("Growing filters to {} (members: {}, growth: {})", filters.size(), members, growth);
            growth = 9 * 64 * exp2(filters.size());
        }

        filters[filters.size() - 1].set(key + filters.size() - 1);
        members++;
    }

    bool maybe_contains(auto key) const
    {
        for (size_t i = 0; i < filters.size(); ++i)
            if (!filters[i].maybe_contains(key + i))
                return false;
        return true;
    }

    void clear()
    {
        filters.remove(1, filters.size() - 1);
        growth = 9 * 64;
        members = 0;
        for (auto& filter : filters)
            filter.clear();
    }

    Vector<Detail::BloomFilter<Hashes...>, 1> filters;
    size_t members { 0 };
    size_t growth { static_cast<size_t>(9 * 64) };
};
}

using AK::BloomFilter;
