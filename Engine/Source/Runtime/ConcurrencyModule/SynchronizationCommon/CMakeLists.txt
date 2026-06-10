add_library(ConcurrencyModule.SynchronizationCommon INTERFACE)

target_sources(ConcurrencyModule.SynchronizationCommon
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/SynchronizationCommon.h
)

target_include_directories(ConcurrencyModule.SynchronizationCommon
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(ConcurrencyModule.SynchronizationCommon

)

if(WIN32)
    target_link_libraries(ConcurrencyModule.SynchronizationCommon
            INTERFACE
            ConcurrencyModule.Windows
    )
else()
    target_link_libraries(RHLModule.SynchronizationCommon
            INTERFACE
            ConcurrencyModule.Mock
    )
endif()

if(MSVC)
    target_compile_options(ConcurrencyModule.SynchronizationCommon INTERFACE /W4)
else()
    target_compile_options(ConcurrencyModule.SynchronizationCommon INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(ConcurrencyModule.SynchronizationCommon PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
