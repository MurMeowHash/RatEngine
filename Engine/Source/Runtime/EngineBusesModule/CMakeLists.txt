add_library(EngineBusesModule INTERFACE)

target_sources(EngineBusesModule
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/EngineCoreEventBus.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/EngineCoreEvents.h
)

target_include_directories(EngineBusesModule
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(EngineBusesModule INTERFACE
        EventBusCoreModule
)

if(MSVC)
    target_compile_options(EngineBusesModule INTERFACE /W4)
else()
    target_compile_options(EngineBusesModule INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(EngineBusesModule PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
