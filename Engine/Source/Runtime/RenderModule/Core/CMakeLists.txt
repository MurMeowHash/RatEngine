add_library(RenderModule.Core STATIC)

target_sources(RenderModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRenderer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ForwardRenderer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RendererType.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRendererFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RendererFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Installers/RenderModuleCoreInstaller.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ForwardRenderer.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/RendererFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Installers/RenderModuleCoreInstaller.cpp
)

target_include_directories(RenderModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderModule.Core
        PRIVATE
        CoreModule.Common
        InjectionModule.Core
        DebugModule
)

if(MSVC)
    target_compile_options(RenderModule.Core PRIVATE /W4)
else()
    target_compile_options(RenderModule.Core PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
