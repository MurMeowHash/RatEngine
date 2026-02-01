add_library(CoreModule.Common STATIC)

target_sources(CoreModule.Common
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ProjectSettings/ProjectSettings.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ProjectSettings/IProjectSettingsInitializer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ProjectSettings/HardCodedProjectSettingsInitializer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/CoreUtils.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/CoreGlobals.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/PlatformInteractors/IPlatformInteractor.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ProjectSettings/ProjectSettings.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ProjectSettings/HardCodedProjectSettingsInitializer.cpp
)

target_include_directories(CoreModule.Common
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(CoreModule.Common

)

if(MSVC)
    target_compile_options(CoreModule.Common PRIVATE /W4)
else()
    target_compile_options(CoreModule.Common PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(CoreModule.Common PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
