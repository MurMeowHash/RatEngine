#pragma once

#include <cstdint>

namespace EngineCoreEvents {
    class EngineCoreEvent {};
    class EngineInitializedEvent : public EngineCoreEvent {};
    class EngineBeginFrameEvent : public EngineCoreEvent {
    public:
        explicit EngineBeginFrameEvent(uint32_t threadId)
        : m_threadId(threadId) {}

        uint32_t m_threadId;
    };

    class EngineEndFrameEvent : public EngineCoreEvent {
    public:
        explicit EngineEndFrameEvent(uint32_t threadId)
        : m_threadId(threadId) {}

        uint32_t m_threadId;
    };

    class EnginePostEndFrameEvent : public EngineCoreEvent {
    public:
        explicit EnginePostEndFrameEvent(uint32_t threadId)
        : m_threadId(threadId) {}

        uint32_t m_threadId;
    };

    class EngineExitRequestedEvent : public EngineCoreEvent {};
}