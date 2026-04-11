#pragma once

#define MAX_ATOMIC_BYTES_SIZE 8

template<typename TType> requires(sizeof(TType) <= MAX_ATOMIC_BYTES_SIZE)
class IAtomicSynchronizer {
public:
    virtual void StoreValue(TType value) = 0;
    virtual void BitwiseAdd(TType value) = 0;
    virtual TType Increment() = 0;
    [[nodiscard]] virtual TType RetrieveValue() = 0;
    virtual ~IAtomicSynchronizer() = default;
};