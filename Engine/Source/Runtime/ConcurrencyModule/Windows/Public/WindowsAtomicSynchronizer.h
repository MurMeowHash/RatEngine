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
    void StoreValue(TType value, SynchronizationType synchronizationType) override {
        switch (synchronizationType) {
            case SynchronizationType::None:
                m_value = value;
                break;
            case SynchronizationType::ThreadSynchronized:
                InterlockedExchangePointer(&m_value, value);
                break;
            default:
                throw std::runtime_error(StringFormatter("Synchronization of type ", synchronizationType, " is not supported"));
        }
    }

    void BitwiseAdd(TType value, SynchronizationType synchronizationType) override { }

    TType RetrieveValue(SynchronizationType synchronizationType) override {
        switch (synchronizationType) {
            case SynchronizationType::None:
                return m_value;
            case SynchronizationType::ThreadSynchronized:
                return InterlockedCompareExchangePointer(&m_value, nullptr, nullptr);
            default:
                throw std::runtime_error(StringFormatter("Synchronization of type ", synchronizationType, " is not supported"));
        }
    }

private:
    TType m_value;
};

template<typename TType, bool = !std::is_pointer_v<TType>> requires(sizeof(TType) <= MAX_ATOMIC_BYTES_SIZE)
class WindowsAtomicSynchronizerCommon : public IAtomicSynchronizer<TType> {
public:
    void StoreValue(TType value, SynchronizationType synchronizationType) override {
        switch (synchronizationType) {
            case SynchronizationType::None:
                m_value = static_cast<uint64_t>(value);
                break;
            case SynchronizationType::ThreadSynchronized:
                InterlockedExchange(&m_value, static_cast<uint64_t>(value));
                break;
            default:
                throw std::runtime_error(StringFormatter("Synchronization of type ", synchronizationType, " is not supported"));
        }
    }

    void BitwiseAdd(TType value, SynchronizationType synchronizationType) override {
        switch (synchronizationType) {
            case SynchronizationType::None:
                m_value |= static_cast<uint64_t>(value);
                break;
            case SynchronizationType::ThreadSynchronized:
                InterlockedOr(&m_value, static_cast<uint64_t>(value));
                break;
            default:
                throw std::runtime_error(StringFormatter("Synchronization of type ", synchronizationType, " is not supported"));
        }
    }

    TType RetrieveValue(SynchronizationType synchronizationType) override {
        switch (synchronizationType) {
            case SynchronizationType::None:
                return static_cast<TType>(m_value);
            case SynchronizationType::ThreadSynchronized:
                return static_cast<TType>(InterlockedCompareExchange(&m_value, 0, 0));
            default:
                throw std::runtime_error(StringFormatter("Synchronization of type ", synchronizationType, " is not supported"));
        }
    }

private:
    uint64_t m_value = 0;
};

template<typename TType> requires(sizeof(TType) <= MAX_ATOMIC_BYTES_SIZE)
class WindowsAtomicSynchronizer : public IAtomicSynchronizer<TType> {
public:
    explicit WindowsAtomicSynchronizer(TType value) {
        StoreValue(value, SynchronizationType::ThreadSynchronized);
    }

    void StoreValue(TType value, SynchronizationType synchronizationType) override {
        if constexpr (std::is_pointer_v<TType>) {
            m_pointerAtomic.StoreValue(value, synchronizationType);
        }
        else {
            m_commonAtomic.StoreValue(value, synchronizationType);
        }
    }

    void BitwiseAdd(TType value, SynchronizationType synchronizationType) override {
        if constexpr (std::is_pointer_v<TType>) {
            m_pointerAtomic.BitwiseAdd(value, synchronizationType);
        }
        else {
            m_commonAtomic.BitwiseAdd(value, synchronizationType);
        }
    }

    TType RetrieveValue(SynchronizationType synchronizationType) override {
        if constexpr (std::is_pointer_v<TType>) {
            return m_pointerAtomic.RetrieveValue(synchronizationType);
        }
        else {
            return m_commonAtomic.RetrieveValue(synchronizationType);
        }
    }

private:
    WindowsAtomicSynchronizerCommon<TType> m_commonAtomic;
    WindowsAtomicSynchronizerPointer<TType> m_pointerAtomic;
};