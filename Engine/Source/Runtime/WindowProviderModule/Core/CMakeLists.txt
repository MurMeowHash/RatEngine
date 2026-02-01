add_library(WindowProviderModule.Core INTERFACE)

target_sources(WindowProviderModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IWindowProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowCreateInfo.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowProviderExecResult.h
)

target_include_directories(WindowProviderModule.Core
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(WindowProviderModule.Core
)

if(MSVC)
    target_compile_options(WindowProviderModule.Core INTERFACE /W4)
else()
    target_compile_options(WindowProviderModule.Core INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(WindowProviderModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
