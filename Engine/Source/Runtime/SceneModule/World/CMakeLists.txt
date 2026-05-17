add_library(SceneModule.World STATIC)

target_sources(SceneModule.World
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WorldScene.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/WorldScene.cpp
)

target_include_directories(SceneModule.World
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(SceneModule.World
        PUBLIC
        ComponentBehaviourModule.World
        ComponentBehaviourModule.Core
        PRIVATE
        SceneModule.Core
        CoreModule.Common
)

if(MSVC)
    target_compile_options(SceneModule.World PRIVATE /W4)
else()
    target_compile_options(SceneModule.World PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(SceneModule.World PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
