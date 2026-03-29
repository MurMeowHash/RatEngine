#pragma once

#include "../../../Core/Public/SynchronizationPrimitives/IAtomicSynchronizer.h"
#include <windows.h>
#include <cstdint>
#include <type_traits>
#include "CoreUtils.h"

template<typename TType> requires(sizeof(TType) <= MAX_ATOMIC_BYTES_SIZE)
class WindowsAtomicSynchronizer : public IAtomicSynchronizer<TType> {
public:
    explicit WindowsAtomicSynchronizer(TType value) {
        WindowsAtomicSynchronizer<TType>::StoreValue(value);
    }

    explicit WindowsAtomicSynchronizer() = default;

    void StoreValue(TType value) override {
        if constexpr (std::is_pointer_v<TType>)
            InterlockedExchange64(reinterpret_cast<volatile LONG64*>(&m_value), reinterpret_cast<LONG64>(value));
        else
            InterlockedExchange64(reinterpret_cast<volatile LONG64*>(&m_value), static_cast<LONG64>(value));
    }

    void BitwiseAdd(TType value) override {
        if constexpr (std::is_pointer_v<TType>)
            InterlockedOr64(reinterpret_cast<volatile LONG64*>(&m_value), reinterpret_cast<LONG64>(value));
        else
            InterlockedOr64(reinterpret_cast<volatile LONG64*>(&m_value), static_cast<LONG64>(value));
    }

    TType RetrieveValue() override {
        if constexpr (std::is_pointer_v<TType>)
            return reinterpret_cast<TType>(InterlockedCompareExchange64(reinterpret_cast<volatile LONG64*>(&m_value), 0, 0));
        else
            return static_cast<TType>(InterlockedCompareExchange64(reinterpret_cast<volatile LONG64*>(&m_value), 0, 0));
    }

    TType Increment() override {
        if constexpr (std::is_pointer_v<TType>)
            return reinterpret_cast<TType>(InterlockedIncrement64(reinterpret_cast<volatile LONG64*>(&m_value)));
        else
            return static_cast<TType>(InterlockedIncrement64(reinterpret_cast<volatile LONG64*>(&m_value)));
    }

private:
    volatile uint64_t m_value = 0;
};