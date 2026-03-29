add_library(ConcurrencyModule.Mock STATIC)

target_sources(ConcurrencyModule.Mock
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockConcurrencyFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockPlatformThread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/SynchronizationPrimitives/MockAtomicSynchronizer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/SynchronizationPrimitives/MockMutex.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/MockConcurrencyFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/MockPlatformThread.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/SynchronizationPrimitives/MockMutex.cpp
)

target_include_directories(ConcurrencyModule.Mock
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(ConcurrencyModule.Mock
        PRIVATE
        ConcurrencyModule.Core
        DelegateModule
)

if(MSVC)
    target_compile_options(ConcurrencyModule.Mock PRIVATE /W4)
else()
    target_compile_options(ConcurrencyModule.Mock PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(ConcurrencyModule.Mock PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
