add_library(WindowProviderModule.Mock INTERFACE)

target_sources(WindowProviderModule.Mock
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockWindowProvider.h
)

target_include_directories(WindowProviderModule.Mock
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(WindowProviderModule.Mock
        INTERFACE
            WindowProviderModule.Core
)

if(MSVC)
    target_compile_options(WindowProviderModule.Mock INTERFACE /W4)
else()
    target_compile_options(WindowProviderModule.Mock INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(WindowProviderModule.Mock PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
