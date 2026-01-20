cmake_minimum_required(VERSION 3.20)

# ==========================================
# Third Party Dependencies
# ==========================================

# GLFW
set(GLFW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/ThirdParty/glfw3")
add_library(glfw3 STATIC IMPORTED)

# Platform-specific libraries for GLFW
if(WIN32)
    # Check which library file exists and use it
    if(EXISTS "${GLFW_DIR}/lib/glfw3.lib")
        # MSVC .lib file exists
        set_target_properties(glfw3 PROPERTIES
                IMPORTED_LOCATION "${GLFW_DIR}/lib/glfw3.lib"
                INTERFACE_INCLUDE_DIRECTORIES "${GLFW_DIR}/include"
        )
    elseif(EXISTS "${GLFW_DIR}/lib/libglfw3.a")
        # MinGW .a file exists (static)
        set_target_properties(glfw3 PROPERTIES
                IMPORTED_LOCATION "${GLFW_DIR}/lib/libglfw3.a"
                INTERFACE_INCLUDE_DIRECTORIES "${GLFW_DIR}/include"
        )
    elseif(EXISTS "${GLFW_DIR}/lib/libglfw3dll.a")
        # MinGW .a file exists (DLL import library)
        set_target_properties(glfw3 PROPERTIES
                IMPORTED_LOCATION "${GLFW_DIR}/lib/libglfw3dll.a"
                INTERFACE_INCLUDE_DIRECTORIES "${GLFW_DIR}/include"
        )
    else()
        message(FATAL_ERROR "GLFW library not found in ${GLFW_DIR}/lib/")
    endif()
    set(GLFW_LIBRARIES glfw3 gdi32 user32 shell32)
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    set(GLFW_LIBRARIES glfw3 ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
else() # Linux
    find_package(X11 REQUIRED)
    find_package(Threads REQUIRED)
    set(GLFW_LIBRARIES glfw3 ${X11_LIBRARIES} ${CMAKE_DL_LIBS} Threads::Threads)
endif()

# GLM (header-only)
set(GLM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/ThirdParty/glm")
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE "${GLM_DIR}/include")

# Vulkan
set(VULKAN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/ThirdParty/vulkan")
add_library(vulkan STATIC IMPORTED)

if(WIN32)
    set_target_properties(vulkan PROPERTIES
            IMPORTED_LOCATION "${VULKAN_DIR}/lib/vulkan-1.lib"
            INTERFACE_INCLUDE_DIRECTORIES "${VULKAN_DIR}/include"
    )
elseif(APPLE)
    set_target_properties(vulkan PROPERTIES
            IMPORTED_LOCATION "${VULKAN_DIR}/lib/libvulkan.dylib"
            INTERFACE_INCLUDE_DIRECTORIES "${VULKAN_DIR}/include"
    )
else() # Linux
    set_target_properties(vulkan PROPERTIES
            IMPORTED_LOCATION "${VULKAN_DIR}/lib/libvulkan.so"
            INTERFACE_INCLUDE_DIRECTORIES "${VULKAN_DIR}/include"
    )
endif()

# ==========================================
# Engine Runtime Source Files
# ==========================================

set(RUNTIME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/Runtime")

# Collect all source files (adjust patterns as needed)
file(GLOB_RECURSE ENGINE_SOURCES
        "${RUNTIME_DIR}/*.cpp"
        "${RUNTIME_DIR}/*.c"
)

file(GLOB_RECURSE ENGINE_HEADERS
        "${RUNTIME_DIR}/*.h"
        "${RUNTIME_DIR}/*.hpp"
)

# ==========================================
# Engine Executable/Library
# ==========================================

# Create executable (change to add_library if building a library)
add_executable(RatEngine ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# Include directories
target_include_directories(RatEngine PRIVATE
        ${RUNTIME_DIR}
)

# Link libraries
target_link_libraries(RatEngine PRIVATE
        vulkan
        ${GLFW_LIBRARIES}
        glm
)

# Compiler warnings
if(MSVC)
    target_compile_options(RatEngine PRIVATE /W4)
else()
    target_compile_options(RatEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ==========================================
# Platform-specific settings
# ==========================================

if(WIN32)
    # Set subsystem to CONSOLE for debugging
    set_target_properties(RatEngine PROPERTIES
            WIN32_EXECUTABLE FALSE
    )
endif()