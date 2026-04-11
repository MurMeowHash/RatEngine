#pragma once

#include <cstdint>
#include "ThreadSearchService.h"
#include "InfiniteThreadContext.h"
#include "IThreadContextUnit.h"

template<typename TCommand>
class CommandThreadContextBase : public IThreadContextUnit {
public:
    explicit CommandThreadContextBase(ThreadSearchService* threadSearchService)
    : m_threadSearchService(threadSearchService) {}

    [[nodiscard]] uint32_t GetAuthorityFrameOffset() const { return m_authorityFrameOffset; }

protected:
    void Initialize() {
        InfiniteThreadContext* infiniteThreadContext;
        if (!m_threadSearchService->TryGetAuthorityThreadContext<TCommand, InfiniteThreadContext>(infiniteThreadContext))
            return;

        m_authorityFrameOffset = infiniteThreadContext->m_threadFrameIndex.RetrieveValue();
    }

private:
    ThreadSearchService* m_threadSearchService;

    uint64_t m_authorityFrameOffset = 0;
};
