add_library(WindowProviderModule STATIC)

target_sources(WindowProviderModule
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IWindowProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/GlfwWindowProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowCreateInfo.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/GlfwWindowProvider.cpp
)

target_include_directories(WindowProviderModule
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(WindowProviderModule
        PRIVATE
            glfw3
)

if(MSVC)
    target_compile_options(WindowProviderModule PRIVATE /W4)
else()
    target_compile_options(WindowProviderModule PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(WindowProviderModule PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
