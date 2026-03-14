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
            case SynchronizationType::Local:
                m_value = value;
                break;
            case SynchronizationType::Global:
                InterlockedExchangePointer(&m_value, value);
                break;
            default:
                throw std::runtime_error(StringFormatter("Synchronization of type ", synchronizationType, " is not supported"));
        }
    }

    void BitwiseAdd(TType value, SynchronizationType synchronizationType) override { }

    TType RetrieveValue(SynchronizationType synchronizationType) override {
        switch (synchronizationType) {
            case SynchronizationType::Local:
                return m_value;
            case SynchronizationType::Global:
                return InterlockedCompareExchangePointer(&m_value, nullptr, nullptr);
            default:
                throw std::runtime_error(StringFormatter("Synchronization of type ", synchronizationType, " is not supported"));
        }
    }

    void Synchronize() override {
        StoreValue(m_value, SynchronizationType::Global);
    }

private:
    volatile TType m_value;
};

template<typename TType, bool = !std::is_pointer_v<TType>> requires(sizeof(TType) <= MAX_ATOMIC_BYTES_SIZE)
class WindowsAtomicSynchronizerCommon : public IAtomicSynchronizer<TType> {
public:
    void StoreValue(TType value, SynchronizationType synchronizationType) override {
        switch (synchronizationType) {
            case SynchronizationType::Local:
                m_value = static_cast<uint64_t>(value);
                break;
            case SynchronizationType::Global:
                InterlockedExchange(&m_value, static_cast<uint64_t>(value));
                break;
            default:
                throw std::runtime_error(StringFormatter("Synchronization of type ", synchronizationType, " is not supported"));
        }
    }

    void BitwiseAdd(TType value, SynchronizationType synchronizationType) override {
        switch (synchronizationType) {
            case SynchronizationType::Local:
                m_value |= static_cast<uint64_t>(value);
                break;
            case SynchronizationType::Global:
                InterlockedOr(&m_value, static_cast<uint64_t>(value));
                break;
            default:
                throw std::runtime_error(StringFormatter("Synchronization of type ", synchronizationType, " is not supported"));
        }
    }

    TType RetrieveValue(SynchronizationType synchronizationType) override {
        switch (synchronizationType) {
            case SynchronizationType::Local:
                return static_cast<TType>(m_value);
            case SynchronizationType::Global:
                return static_cast<TType>(InterlockedCompareExchange(&m_value, 0, 0));
            default:
                throw std::runtime_error(StringFormatter("Synchronization of type ", synchronizationType, " is not supported"));
        }
    }

    void Synchronize() override {
        StoreValue(m_value, SynchronizationType::Global);
    }

private:
    volatile uint64_t m_value = 0;
};

template<typename TType> requires(sizeof(TType) <= MAX_ATOMIC_BYTES_SIZE)
class WindowsAtomicSynchronizer : public IAtomicSynchronizer<TType> {
public:
    explicit WindowsAtomicSynchronizer(TType value) {
        StoreValue(value, SynchronizationType::Global);
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

    void Synchronize() override {
        if constexpr (std::is_pointer_v<TType>) {
            return m_pointerAtomic.Synchronize();
        }
        else {
            return m_commonAtomic.Synchronize();
        }
    }

private:
    WindowsAtomicSynchronizerCommon<TType> m_commonAtomic;
    WindowsAtomicSynchronizerPointer<TType> m_pointerAtomic;
};