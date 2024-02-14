cmake_minimum_required(VERSION 3.26)
project(AURAVIRTUAL)

set(CMAKE_CXX_STANDARD 17)

#--------- define executable *.cpp files ---------
#add_executable(AURAVIRTUAL "./src/core/main.cpp")
file(GLOB SRCFILES CONFIGURE_DEPENDS
        "./src/core/*.h" "./src/core/*.cpp"
        "./src/renderer/*.h" "./src/renderer/*.cpp"
        "./src/components/*.h" "./src/components/*.cpp"
        "./src/debug/*.h" "./src/debug/*.cpp"
        "./src/math/*.h" "./src/math/*.cpp"
        "./src/physics/*.h" "./src/physics/*.cpp"
        "./src/scene/*.h" "./src/scene/*.cpp"
        "./src/ui/*.h" "./src/ui/*.cpp")

add_executable(AURAVIRTUAL ${SRCFILES})

target_include_directories(AURAVIRTUAL PUBLIC ./src/components)
target_include_directories(AURAVIRTUAL PUBLIC ./src/renderer)
target_include_directories(AURAVIRTUAL PUBLIC ./src/core)
target_include_directories(AURAVIRTUAL PUBLIC ./src/debug)
target_include_directories(AURAVIRTUAL PUBLIC ./src/math)
target_include_directories(AURAVIRTUAL PUBLIC ./src/physics)
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


elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "Building for Windows")
endif()

# Link GLFW
set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( GLAD_GL "" )

add_subdirectory( ./lib/GLFW )   # This works with /lib/GLFW/CMakeLists.txt


option( USE-GLFW-GLAD "Use GLAD from GLFW" ON )

if( USE-GLFW-GLAD )
    include_directories("${GLFW_SOURCE_DIR}/deps")
    include_directories("${GLFW_SOURCE_DIR}/include")
    set( GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" )
endif()

target_link_libraries(AURAVIRTUAL glfw)






