add_library(CoreModule STATIC)

target_sources(CoreModule
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ILogger.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/EngineLogger.cpp
)

target_include_directories(CoreModule
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(CoreModule

)

if(MSVC)
    target_compile_options(CoreModule PRIVATE /W4)
else()
    target_compile_options(CoreModule PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(CoreModule PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
