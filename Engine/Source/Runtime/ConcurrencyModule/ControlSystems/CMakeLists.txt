add_library(ConcurrencyModule.ControlSystems INTERFACE)

target_sources(ConcurrencyModule.ControlSystems
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ConcurrencyCommandSubmitSystem.h
)

target_include_directories(ConcurrencyModule.ControlSystems
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(ConcurrencyModule.ControlSystems
        INTERFACE
        EventBusModule.Core
        EventBusModule.Engine
        DelegateModule
        CoreModule.Common
        ConcurrencyModule.Core
        ConcurrencyModule.CommandBuffers
)

if(MSVC)
    target_compile_options(ConcurrencyModule.ControlSystems INTERFACE /W4)
else()
    target_compile_options(ConcurrencyModule.ControlSystems INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(ConcurrencyModule.ControlSystems PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
