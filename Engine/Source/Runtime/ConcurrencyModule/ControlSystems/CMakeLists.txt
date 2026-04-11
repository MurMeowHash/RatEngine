add_library(ConcurrencyModule.ControlSystems STATIC)

target_sources(ConcurrencyModule.ControlSystems
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/FrameCommandSubmitSystem.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/CommandProcessSystem.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/FrameLagConstraintSystem.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/FrameIncrementSystem.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/FrameIncrementSystem.cpp
)

target_include_directories(ConcurrencyModule.ControlSystems
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(ConcurrencyModule.ControlSystems
        PUBLIC
        EventBusModule.Core
        EventBusModule.Engine
        DelegateModule
        CoreModule.Common
        ConcurrencyModule.Core
        ConcurrencyModule.CommandBuffers
)

if(MSVC)
    target_compile_options(ConcurrencyModule.ControlSystems PRIVATE /W4)
else()
    target_compile_options(ConcurrencyModule.ControlSystems PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(ConcurrencyModule.ControlSystems PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
