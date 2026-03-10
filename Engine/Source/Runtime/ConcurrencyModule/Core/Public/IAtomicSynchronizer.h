#pragma once

#include "SynchronizationType.h"

#define MAX_ATOMIC_BYTES_SIZE 8

template<typename TType> requires(sizeof(TType) <= MAX_ATOMIC_BYTES_SIZE)
class IAtomicSynchronizer {
public:
    virtual void StoreValue(TType value, SynchronizationType synchronizationType) = 0;
    virtual void BitwiseAdd(TType value, SynchronizationType synchronizationType) = 0;
    [[nodiscard]] virtual TType RetrieveValue(SynchronizationType synchronizationType) = 0;
    virtual void Synchronize() = 0;
    virtual ~IAtomicSynchronizer() = default;
};