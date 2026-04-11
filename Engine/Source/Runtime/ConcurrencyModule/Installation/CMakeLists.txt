add_library(ConcurrencyModule.Installation STATIC)

target_sources(ConcurrencyModule.Installation
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ConcurrencyModuleInstaller.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ConcurrencyModuleInstaller.cpp
)

target_include_directories(ConcurrencyModule.Installation
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(ConcurrencyModule.Installation
        PRIVATE
        ConcurrencyModule.Core
        InjectionModule.Core
        ConcurrencyModule.WorldAbstraction
        CoreModule.Common
        EventBusModule.Core
        EventBusModule.Engine
)

if(WIN32)
    target_link_libraries(ConcurrencyModule.Installation
            PRIVATE
            ConcurrencyModule.Windows
    )
else()
    target_link_libraries(RenderHardwareModule.Installation
            PRIVATE
            ConcurrencyModule.Mock
    )
endif()

if(MSVC)
    target_compile_options(ConcurrencyModule.Installation PRIVATE /W4)
else()
    target_compile_options(ConcurrencyModule.Installation PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(ConcurrencyModule.Installation PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
