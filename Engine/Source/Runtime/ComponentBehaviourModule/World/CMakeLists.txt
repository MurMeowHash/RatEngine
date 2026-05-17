add_library(ComponentBehaviourModule.World STATIC)

target_sources(ComponentBehaviourModule.World
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Component/WorldComponent.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Actor/WorldActor.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Component/WorldComponent.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Actor/WorldActor.cpp
)

target_include_directories(ComponentBehaviourModule.World
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(ComponentBehaviourModule.World
        PUBLIC
        MathModule
        PRIVATE
        ComponentBehaviourModule.Core
)

if(MSVC)
    target_compile_options(ComponentBehaviourModule.World PRIVATE /W4)
else()
    target_compile_options(ComponentBehaviourModule.World PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(ComponentBehaviourModule.World PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
