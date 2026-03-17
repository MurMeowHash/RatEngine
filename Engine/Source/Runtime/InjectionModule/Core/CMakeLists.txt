add_library(InjectionModule.Core STATIC)

target_sources(InjectionModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/DiContainer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IDependencyInstaller.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/DependencyInstallerBase.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/DependencyContextBase.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IDependencyContext.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/DiContainer.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/DependencyContextBase.cpp
)

target_include_directories(InjectionModule.Core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(InjectionModule.Core
        PUBLIC
        CoreModule.Common
)

if(MSVC)
    target_compile_options(InjectionModule.Core PRIVATE /W4)
else()
    target_compile_options(InjectionModule.Core PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(InjectionModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
