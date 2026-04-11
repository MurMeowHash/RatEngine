#pragma once

#if defined(__WIN32)
#include "SynchronizationPrimitives/WindowsAtomicSynchronizer.h"
template<typename TType>
using AtomicSynchronizer = WindowsAtomicSynchronizer<TType>;
#else
#include "SynchronizationPrimitives/MockAtomicSynchronizer.h"
template<typename TType>
using AtomicSynchronizer = MockAtomicSynchronizer<TType>;
#endif