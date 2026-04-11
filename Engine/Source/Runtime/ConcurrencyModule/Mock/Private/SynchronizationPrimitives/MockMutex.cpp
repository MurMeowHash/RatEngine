#include "../Public/SynchronizationPrimitives/MockMutex.h"

void MockMutex::Create() { }

bool MockMutex::IsValid() const { return false; }

void MockMutex::LockExclusive() const { }

void MockMutex::UnlockExclusive() const { }

void MockMutex::LockShared() { }

void MockMutex::UnlockShared() { }

void MockMutex::Terminate() { }
