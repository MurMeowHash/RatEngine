add_library(WorldModule.ComponentBehaviour STATIC)

target_sources(WorldModule.ComponentBehaviour
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Component/SceneComponent.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Actor/SceneActor.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Component/SceneComponent.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Actor/SceneActor.cpp
)

target_include_directories(WorldModule.ComponentBehaviour
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(WorldModule.ComponentBehaviour
        PRIVATE
        ComponentBehaviourModule
        MathModule
)

if(MSVC)
    target_compile_options(WorldModule.ComponentBehaviour PRIVATE /W4)
else()
    target_compile_options(WorldModule.ComponentBehaviour PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(WorldModule.ComponentBehaviour PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
