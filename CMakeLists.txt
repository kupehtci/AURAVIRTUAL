cmake_minimum_required(VERSION 3.26)
project(AURAVIRTUAL)
include(FindVulkan)

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

add_executable(AURAVIRTUAL ${SRCFILES}
        src/renderer/triangle-vulkan.c)

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
    message(STATUS "Building vulkan for macOS")

    if(NOT DEFINED VULKAN_PATH)
        set(VULKAN_PATH "/Users/dlaplana/VulkanSDK/1.3.275.0/macOS" ) #previous: ./lib/MoltenVK    "/Users/dlaplana/VulkanSDK/1.3.275.0/macOS"
    endif()
    set(Vulkan_INCLUDE_DIR ${VULKAN_PATH}/include)
    set(Vulkan_LIBRARY ${VULKAN_PATH}/lib)
    set(VK_ICD_FILENAMES ${VULKAN_PATH}/share/vulkan/icd.d)

    find_package(Vulkan REQUIRED)
    target_include_directories(AURAVIRTUAL PUBLIC "${VULKAN_PATH}/include")
    target_link_directories(AURAVIRTUAL PUBLIC "${VULKAN_PATH}/lib")
    target_link_directories(AURAVIRTUAL PUBLIC "${VULKAN_PATH}/share/vulkan/icd.d/")
    target_compile_definitions(AURAVIRTUAL PUBLIC VK_USE_PLATFORM_MACOS_MVK)     # define macOs usage

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "Building vulkan for Windows")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Building vulkan for Linux")
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

target_link_libraries(AURAVIRTUAL glfw vulkan)

# Link GLM
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Linking GLM Headers")
    #find_package(glm REQUIRED)
    target_include_directories(AURAVIRTUAL PUBLIC "${VULKAN_PATH}/include")
    message(STATUS "Vulkan path: ${VULKAN_PATH}")
endif()




#    if (DEFINED VULKAN_SDK_PATH)
#        set(Vulkan_INCLUDE_DIRS "${VULKAN_SDK_PATH}/Include") # 1.1 Make sure this include path is correct
#        set(Vulkan_LIBRARIES "${VULKAN_SDK_PATH}/Lib") # 1.2 Make sure lib path is correct
#        set(Vulkan_FOUND "True")
#    else()
#        find_package(Vulkan REQUIRED) # throws error if could not find Vulkan
#        message(STATUS "Found Vulkan: $ENV{VULKAN_SDK}")
#    endif()
#    if (NOT Vulkan_FOUND)
#        message(FATAL_ERROR "Could not find Vulkan library!")
#    else()
#        message(STATUS "Using vulkan lib at: ${Vulkan_LIBRARIES}")
#    endif()





