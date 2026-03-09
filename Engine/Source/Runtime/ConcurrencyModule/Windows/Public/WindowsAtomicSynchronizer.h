#pragma once

#include "IAtomicSynchronizer.h"
#include <windows.h>
#include <cstdint>
#include <type_traits>

template<typename TType> requires(sizeof(TType) <= MAX_ATOMIC_BYTES_SIZE)
class WindowsAtomicSynchronizer : public IAtomicSynchronizer<TType> {
public:
    explicit WindowsAtomicSynchronizer(TType value) {
        StoreValue(value);
    }

    void StoreValue(TType value) override {
        if constexpr (std::is_pointer_v<TType>) {
            InterlockedExchangePointer(&m_originalValue, value);
        }
        else {
            InterlockedExchange(&m_rawValue, static_cast<uint64_t>(value));
        }
    }

    void BitwiseAdd(TType value) override {
        if constexpr (std::is_pointer_v<TType>) {
            return;
        }

        InterlockedOr(&m_rawValue, static_cast<uint64_t>(value));
    }

    TType RetrieveValue() override {
        if constexpr (std::is_pointer_v<TType>) {
            return InterlockedCompareExchangePointer(&m_originalValue, nullptr, nullptr);
        }
        else {
            uint64_t retrievedRawValue = InterlockedCompareExchange(&m_rawValue, 0, 0);
            return static_cast<TType>(retrievedRawValue);
        }
    }

private:
    uint64_t m_rawValue = 0;
    TType m_originalValue;
};