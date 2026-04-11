add_library(EventBusModule.Core INTERFACE)

target_sources(EventBusModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/EventBusBase.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ConcurrentEventBusBase.h
)

target_include_directories(EventBusModule.Core
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(EventBusModule.Core
        INTERFACE
        DelegateModule
        ConcurrencyModule.Core
)

if(MSVC)
    target_compile_options(EventBusModule.Core INTERFACE /W4)
else()
    target_compile_options(EventBusModule.Core INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(EventBusModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
