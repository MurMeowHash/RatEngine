add_library(ConcurrencyModule.WorldAbstraction STATIC)

target_sources(ConcurrencyModule.WorldAbstraction
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WorldThreadWrapper.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/WorldThreadWrapper.cpp
)

target_include_directories(ConcurrencyModule.WorldAbstraction
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(ConcurrencyModule.WorldAbstraction
        PRIVATE
        ConcurrencyModule.Core
        CoreModule.Common
        RenderModule.Threading
        MemoryModule
        DelegateModule
        ConcurrencyModule.ControlSystems
        InjectionModule.Core
)

if(MSVC)
    target_compile_options(ConcurrencyModule.WorldAbstraction PRIVATE /W4)
else()
    target_compile_options(ConcurrencyModule.WorldAbstraction PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(ConcurrencyModule.WorldAbstraction PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
