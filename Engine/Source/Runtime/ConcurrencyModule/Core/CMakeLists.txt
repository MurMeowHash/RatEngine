add_library(ConcurrencyModule.Core STATIC)

target_sources(ConcurrencyModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IClientThread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IThread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IPlatformThread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ClientThreadBase.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ConcurrencyGlobals.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IConcurrencyFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IAtomicSynchronizer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/SynchronizationType.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ClientThreadBase.cpp
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
        PRIVATE
        DelegateModule
        CoreModule.Common
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
