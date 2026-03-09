#pragma once

#if defined(__WIN32)
#include "WindowsAtomicSynchronizer.h"
template<typename TType>
using AtomicSynchronizer = WindowsAtomicSynchronizer<TType>;
#else
#include "MockAtomicSynchronizer.h"
template<typename TType>
using AtomicSynchronizer = MockAtomicSynchronizer<TType>;
#endif