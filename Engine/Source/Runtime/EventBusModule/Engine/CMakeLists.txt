add_library(EventBusModule.Engine STATIC)

target_sources(EventBusModule.Engine
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/EngineCoreEventBus.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/EngineCoreEvents.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Installers/EventBusModuleInstaller.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Installers/EventBusModuleInstaller.cpp
)

target_include_directories(EventBusModule.Engine
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(EventBusModule.Engine
        PRIVATE
        EventBusModule.Core
        InjectionModule.Core
)

if(MSVC)
    target_compile_options(EventBusModule.Engine PRIVATE /W4)
else()
    target_compile_options(EventBusModule.Engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(EventBusModule.Engine PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
