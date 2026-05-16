add_library(WorldModule.Scene STATIC)

target_sources(WorldModule.Scene
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Scene.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Scene.cpp
)

target_include_directories(WorldModule.Scene
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(WorldModule.Scene
        PRIVATE
        WorldModule.ComponentBehaviour
        ComponentBehaviourModule
        MemoryModule
)

if(MSVC)
    target_compile_options(WorldModule.Scene PRIVATE /W4)
else()
    target_compile_options(WorldModule.Scene PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(WorldModule.Scene PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
