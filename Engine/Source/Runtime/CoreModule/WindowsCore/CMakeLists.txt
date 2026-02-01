add_library(CoreModule.Windows STATIC)

target_sources(CoreModule.Windows
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/PlatformInteractors/WindowsPlatformInteractor.h
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/PlatformInteractors/WindowsPlatformInteractor.cpp
)

target_include_directories(CoreModule.Windows
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(CoreModule.Windows
        PRIVATE
        CoreModule.Common
)

if(MSVC)
    target_compile_options(CoreModule.Windows PRIVATE /W4)
else()
    target_compile_options(CoreModule.Windows PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(CoreModule.Windows PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
