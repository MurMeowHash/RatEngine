add_library(CoreModule.Mock INTERFACE)

target_sources(CoreModule.Mock
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/PlatformInteractors/MockPlatformInteractor.h
)

target_include_directories(CoreModule.Mock
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(CoreModule.Mock
        INTERFACE
        CoreModule.Common
)

if(MSVC)
    target_compile_options(CoreModule.Mock INTERFACE /W4)
else()
    target_compile_options(CoreModule.Mock INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(CoreModule.Mock PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
