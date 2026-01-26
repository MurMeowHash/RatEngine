add_library(DelegateModule INTERFACE)

target_include_directories(DelegateModule
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

if(MSVC)
    target_compile_options(DelegateModule INTERFACE /W4)
else()
    target_compile_options(DelegateModule INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(DelegateModule PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
