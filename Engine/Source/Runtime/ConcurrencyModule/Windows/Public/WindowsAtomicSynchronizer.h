#pragma once

#include "IAtomicSynchronizer.h"
#include <windows.h>
#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include "CoreUtils.h"

template<typename TType, bool = std::is_pointer_v<TType>>
class WindowsAtomicSynchronizerPointer : public IAtomicSynchronizer<TType> {
public:
    void StoreValue(TType value) override {
        InterlockedExchangePointer(&m_value, value);
    }

    void BitwiseAdd(TType value) override { }

    TType RetrieveValue() override {
        return InterlockedCompareExchangePointer(&m_value, nullptr, nullptr);
    }

private:
    volatile TType m_value;
};

template<typename TType, bool = !std::is_pointer_v<TType>> requires(sizeof(TType) <= MAX_ATOMIC_BYTES_SIZE)
class WindowsAtomicSynchronizerCommon : public IAtomicSynchronizer<TType> {
public:
    void StoreValue(TType value) override {
        InterlockedExchange(&m_value, static_cast<uint64_t>(value));
    }

    void BitwiseAdd(TType value) override {
        InterlockedOr(&m_value, static_cast<uint64_t>(value));
    }

    TType RetrieveValue() override {
        return static_cast<TType>(InterlockedCompareExchange(&m_value, 0, 0));
    }

private:
    volatile uint64_t m_value = 0;
};

template<typename TType> requires(sizeof(TType) <= MAX_ATOMIC_BYTES_SIZE)
class WindowsAtomicSynchronizer : public IAtomicSynchronizer<TType> {
public:
    explicit WindowsAtomicSynchronizer(TType value) {
        StoreValue(value);
    }

    void StoreValue(TType value) override {
        if constexpr (std::is_pointer_v<TType>) {
            m_pointerAtomic.StoreValue(value);
        }
        else {
            m_commonAtomic.StoreValue(value);
        }
    }

    void BitwiseAdd(TType value) override {
        if constexpr (std::is_pointer_v<TType>) {
            m_pointerAtomic.BitwiseAdd(value);
        }
        else {
            m_commonAtomic.BitwiseAdd(value);
        }
    }

    TType RetrieveValue() override {
        if constexpr (std::is_pointer_v<TType>) {
            return m_pointerAtomic.RetrieveValue();
        }
        else {
            return m_commonAtomic.RetrieveValue();
        }
    }

private:
    WindowsAtomicSynchronizerCommon<TType> m_commonAtomic;
    WindowsAtomicSynchronizerPointer<TType> m_pointerAtomic;
};