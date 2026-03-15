#pragma once

#include "IAtomicSynchronizer.h"

template<typename TType> requires(sizeof(TType) <= MAX_ATOMIC_BYTES_SIZE)
class MockAtomicSynchronizer : public IAtomicSynchronizer<TType> {
public:
    void StoreValue(TType value) override {
        m_originalValue = value;
    }

    TType RetrieveValue() override {
        return m_originalValue;
    }

    void BitwiseAdd(TType value) override {
        m_originalValue |= value;
    }

private:
    TType m_originalValue;
};