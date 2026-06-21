#pragma once

#include <assert.h>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <functional>
#include "RatSubMapper.h"

struct RatMappingKey {
    std::type_index m_from;
    std::type_index m_to;

    RatMappingKey(std::type_index from, std::type_index to)
        : m_from(from), m_to(to) {}

    bool operator==(const RatMappingKey& rhs) const {
        return m_from == rhs.m_from && m_to == rhs.m_to;
    }
};

struct RatMappingKeyHash {
    std::size_t operator()(const RatMappingKey& key) const {
        std::size_t fromHash = std::hash<std::type_index>{}(key.m_from);
        std::size_t toHash   = std::hash<std::type_index>{}(key.m_to);

        std::size_t rotated = (fromHash << 31) | (fromHash >> (sizeof(std::size_t) * 8 - 31));
        return rotated ^ toHash;
    }
};

class RatMapper {
public:
    template<typename TMapped, typename TResolved>
    void AddMapping(IRatSubMapper<TMapped, TResolved>* subMapper) {
        RatMappingKey mappingKey(typeid(TMapped), typeid(TResolved));
        m_mapping.emplace(mappingKey, subMapper);
    }

    void ClearMapping() {
        m_mapping.clear();
    }

    template<typename TMapped, typename TResolved>
    TResolved ResolveMapping(TMapped value) {
        RatMappingKey mappingKey(typeid(TMapped), typeid(TResolved));
        auto mapperIterator = m_mapping.find(mappingKey);
        assert(mapperIterator != m_mapping.end());
        auto* subMapper = static_cast<IRatSubMapper<TMapped, TResolved>*>(mapperIterator->second);
        return subMapper->Resolve(value);
    }

private:
    std::unordered_map<RatMappingKey, IMapperBase*, RatMappingKeyHash> m_mapping;
};