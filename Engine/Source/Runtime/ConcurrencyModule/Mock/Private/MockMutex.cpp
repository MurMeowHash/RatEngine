#include "../Public/MockMutex.h"

void MockMutex::Create(bool initiallyLocked) { }

void MockMutex::Lock() const { }

void MockMutex::Unlock() const { }

bool MockMutex::IsValid() const {
    return false;
}

void MockMutex::Terminate() { }