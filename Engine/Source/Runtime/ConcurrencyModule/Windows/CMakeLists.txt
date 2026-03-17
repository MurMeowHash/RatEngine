add_library(ConcurrencyModule.Windows STATIC)

target_sources(ConcurrencyModule.Windows
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowsPlatformThread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowsConcurrencyFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowsAtomicSynchronizer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowsMutex.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/WindowsPlatformThread.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/WindowsConcurrencyFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/WindowsMutex.cpp
)

target_include_directories(ConcurrencyModule.Windows
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(ConcurrencyModule.Windows
        PRIVATE
        ConcurrencyModule.Core
        DelegateModule
        CoreModule.Common
)

if(MSVC)
    target_compile_options(ConcurrencyModule.Windows PRIVATE /W4)
else()
    target_compile_options(ConcurrencyModule.Windows PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(ConcurrencyModule.Windows PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
