#pragma once

#include "EngineCoreEvents.h"
#include "ConcurrentEventBusBase.h"

class EngineCoreEventBus : public ConcurrentEventBusBase<EngineCoreEvents::EngineCoreEvent> {
public:
    explicit EngineCoreEventBus(IConcurrencyFactory* concurrencyFactory)
    : ConcurrentEventBusBase(concurrencyFactory) {}
};