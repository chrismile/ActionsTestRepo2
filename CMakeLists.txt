cmake_minimum_required (VERSION 3.7)
cmake_policy(VERSION 3.7...3.20)

project(ActionsTest)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
#MESSAGE(STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.c src/*.hpp src/*.h)
include_directories(src)

if(WIN32)
    add_executable(ActionsTest WIN32 ${SOURCES})
elseif(APPLE)
    add_executable(ActionsTest MACOSX_BUNDLE ${SOURCES})
else()
    add_executable(ActionsTest ${SOURCES})
endif()

find_package(Vulkan REQUIRED)
target_link_libraries(ActionsTest PRIVATE Vulkan::Headers)

