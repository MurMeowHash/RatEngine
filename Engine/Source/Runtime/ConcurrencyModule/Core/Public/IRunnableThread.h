#pragma once

#include "IThread.h"

class IRunnableThread : public IThread {
public:
    virtual void Execute() = 0;
};