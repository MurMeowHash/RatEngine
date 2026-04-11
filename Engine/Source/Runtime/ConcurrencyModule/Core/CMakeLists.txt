add_library(ConcurrencyModule.Core STATIC)

target_sources(ConcurrencyModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IClientThread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IThread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IPlatformThread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ClientThreadBase.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ConcurrencyGlobals.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IConcurrencyFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/SynchronizationPrimitives/IAtomicSynchronizer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/SynchronizationPrimitives/IMutex.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ThreadContext.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/InfiniteThread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/InfiniteThreadContext.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IClientThreadWrapper.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IThreadContextUnit.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ThreadStorage.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRunnable.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/SynchronizationPrimitives/ExclusiveThreadGuard.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/SynchronizationPrimitives/SharedThreadGuard.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/CommandConsumerThreadContext.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRunnableClientThread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/CommandProducerThreadContext.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/SynchronizationPrimitives/IFence.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/SynchronizationPrimitives/Fence.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/CommandThreadStorage.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ThreadProcessor.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IConcurrencySystem.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/CommandThreadContextBase.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ThreadSearchService.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/SynchronizationPrimitives/ISemaphore.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/FrameLagContext.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Runner/ThreadRunner.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Runner/ThreadRunnerAssembler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ConcurrentEvent.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/CommandWriter.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ClientThreadWrapperBase.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Events/ImmediateCommandExecuteRequestUnit.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Events/ImmediateCommandExecuteRequest.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ClientThreadBase.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/InfiniteThread.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ThreadProcessor.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Runner/ThreadRunner.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ThreadStorage.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ClientThreadWrapperBase.cpp
)

target_include_directories(ConcurrencyModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(ConcurrencyModule.Core
        PUBLIC
        ConcurrencyModule.SynchronizationCommon
        ConcurrencyModule.CommandBuffers
        DelegateModule
        MemoryModule
        InjectionModule.Core
        CoreModule.Common
        PRIVATE
        EventBusModule.Core
        EventBusModule.Engine
)

if(MSVC)
    target_compile_options(ConcurrencyModule.Core PRIVATE /W4)
else()
    target_compile_options(ConcurrencyModule.Core PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(ConcurrencyModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
