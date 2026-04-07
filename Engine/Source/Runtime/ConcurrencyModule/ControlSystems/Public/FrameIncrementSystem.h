#pragma once

#include "IConcurrencySystem.h"

class EngineCoreEventBus;
class ThreadSearchService;
template<typename...Args>
class IDelegate;
namespace EngineCoreEvents {
    class EngineBeginFrameEvent;
}
class InfiniteThreadContext;


class FrameIncrementSystem : public IConcurrencySystem {
public:
    FrameIncrementSystem(EngineCoreEventBus* engineCoreEventBus, ThreadSearchService* threadSearchService);
    ~FrameIncrementSystem() override;
    void Start(uint32_t localThreadId) override;
    void Tick() override;
    void Terminate() override;
private:
    EngineCoreEventBus* m_engineCoreEventBus;
    ThreadSearchService* m_threadSearchService;

    IDelegate<const EngineCoreEvents::EngineBeginFrameEvent&>* m_engineBeginFrameDelegate;
    uint32_t m_localThreadId = 0;
    InfiniteThreadContext* m_infiniteThreadContext = nullptr;

    void OnEngineBeginFrame(const EngineCoreEvents::EngineBeginFrameEvent& beginFrameEvent);
};