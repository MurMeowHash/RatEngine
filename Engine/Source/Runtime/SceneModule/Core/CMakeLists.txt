add_library(SceneModule.Core STATIC)

target_sources(SceneModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Scene.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Simulation.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Scene.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Simulation.cpp
)

target_include_directories(SceneModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(SceneModule.Core
        PUBLIC
        InjectionModule.Core
        ComponentBehaviourModule.Core
)

if(MSVC)
    target_compile_options(SceneModule.Core PRIVATE /W4)
else()
    target_compile_options(SceneModule.Core PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(SceneModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
