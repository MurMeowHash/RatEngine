add_library(WindowProviderModule.Desktop STATIC)

target_sources(WindowProviderModule.Desktop
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/GlfwProvider/GlfwWindowProvider.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/GlfwProvider/GlfwWindowProvider.cpp
)

target_include_directories(WindowProviderModule.Desktop
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(WindowProviderModule.Desktop
        PRIVATE
            glfw3
            WindowProviderModule.Core
)

if(MSVC)
    target_compile_options(WindowProviderModule.Desktop PRIVATE /W4)
else()
    target_compile_options(WindowProviderModule.Desktop PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(WindowProviderModule.Desktop PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
