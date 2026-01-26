add_library(EventBusModule STATIC)

target_sources(EventBusModule
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/EventBusBase.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/EventBusBase.cpp
)

target_include_directories(EventBusModule
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(EventBusModule
        DelegateModule
)

if(MSVC)
    target_compile_options(EventBusModule PRIVATE /W4)
else()
    target_compile_options(EventBusModule PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(EventBusModule PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)