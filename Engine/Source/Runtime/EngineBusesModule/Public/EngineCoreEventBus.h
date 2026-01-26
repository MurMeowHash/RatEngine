#pragma once

#include "EngineCoreEvents.h"
#include "EventBusBase.h"

class EngineCoreEventBus : public EventBusBase<EngineCoreEvents::EngineCoreEvent> {};