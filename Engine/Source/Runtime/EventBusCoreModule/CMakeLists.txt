add_library(EventBusCoreModule INTERFACE)

target_sources(EventBusCoreModule
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/EventBusBase.h
)

target_include_directories(EventBusCoreModule
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(EventBusCoreModule INTERFACE
        DelegateModule
)

if(MSVC)
    target_compile_options(EventBusCoreModule INTERFACE /W4)
else()
    target_compile_options(EventBusCoreModule INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(EventBusCoreModule PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
