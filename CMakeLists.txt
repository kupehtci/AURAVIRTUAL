cmake_minimum_required(VERSION 3.26)
project(AURAVIRTUAL)

set(CMAKE_CXX_STANDARD 17)

add_executable(AURAVIRTUAL "./src/core/main.cpp")

target_include_directories(AURAVIRTUAL PUBLIC ./src/components)
target_include_directories(AURAVIRTUAL PUBLIC ./src/core)
target_include_directories(AURAVIRTUAL PUBLIC ./src/debug)
target_include_directories(AURAVIRTUAL PUBLIC ./src/math)
target_include_directories(AURAVIRTUAL PUBLIC ./src/physics)
target_include_directories(AURAVIRTUAL PUBLIC ./src/renderer)
target_include_directories(AURAVIRTUAL PUBLIC ./src/scene)
target_include_directories(AURAVIRTUAL PUBLIC ./src/ui)

# Vulkan library
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Building for macOS")

    # Link Vulkan library
    set(VULKAN_PATH "./lib/MoltenVK")
    set(Vulkan_INCLUDE_DIR ${VULKAN_PATH}/include)
    set(Vulkan_LIBRARY ${VULKAN_PATH}/libMoltenVK.dylib)

    find_package(Vulkan REQUIRED)
    target_include_directories(AURAVIRTUAL PUBLIC "${VULKAN_PATH}/include")

    # Link GLFW
    target_include_directories(AURAVIRTUAL PUBLIC "./lib")
    #target_link_libraries(AURAVIRTUAL glfw)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "Building for Windows")
endif()






