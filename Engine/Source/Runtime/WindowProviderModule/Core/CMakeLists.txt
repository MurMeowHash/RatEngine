add_library(WindowProviderModule.Core STATIC)

target_sources(WindowProviderModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IWindowProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowCreateInfo.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowProviderExecResult.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/WindowProviderExecResult.cpp
)

target_include_directories(WindowProviderModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(WindowProviderModule.Core
)

if(MSVC)
    target_compile_options(WindowProviderModule.Core PRIVATE /W4)
else()
    target_compile_options(WindowProviderModule.Core PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(WindowProviderModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
