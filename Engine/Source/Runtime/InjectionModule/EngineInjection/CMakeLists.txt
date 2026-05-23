add_library(InjectionModule.Engine STATIC)

target_sources(InjectionModule.Engine
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/EngineDependencyContext.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/EngineDependencyContext.cpp
)

target_include_directories(InjectionModule.Engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(InjectionModule.Engine
        PRIVATE
        InjectionModule.Core
        DebugModule
        EventBusModule.Engine
        CoreModule.Installation
        WindowProviderModule.Installation
        RenderHardwareModule.Installation
        ConcurrencyModule.Installation
        RenderModule.Core
)

if(MSVC)
    target_compile_options(InjectionModule.Engine PRIVATE /W4)
else()
    target_compile_options(InjectionModule.Engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(InjectionModule.Engine PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
