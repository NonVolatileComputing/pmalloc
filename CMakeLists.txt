cmake_minimum_required(VERSION 2.8.11)
project(pmalloc)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)
include_directories(${PROJECT_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")
set(pmalloc_VERSION_MAJOR 1)
set(pmalloc_VERSION_MINOR 8)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O3 -Wall")

find_library(LIBRT_LIBRARIES rt)

enable_testing()
add_subdirectory(src)
add_subdirectory(perf)
add_subdirectory(tests)

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
  "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
  set (CPACK_PACKAGE_VERSION_MAJOR "${pmalloc_VERSION_MAJOR}")
  set (CPACK_PACKAGE_VERSION_MINOR "${pmalloc_VERSION_MINOR}")
  include (CPack)
