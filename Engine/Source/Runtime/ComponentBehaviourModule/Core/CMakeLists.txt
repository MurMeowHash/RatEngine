add_library(ComponentBehaviourModule.Core STATIC)

target_sources(ComponentBehaviourModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Component/IComponent.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Component/Component.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Actor/Actor.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ILifecycleMember.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Component/Component.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Actor/Actor.cpp
)

target_include_directories(ComponentBehaviourModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(ComponentBehaviourModule.Core
        PUBLIC
        InjectionModule.Core
        MemoryModule
)

if(MSVC)
    target_compile_options(ComponentBehaviourModule.Core PRIVATE /W4)
else()
    target_compile_options(ComponentBehaviourModule.Core PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(ComponentBehaviourModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
