cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
  CMakeModules
  GIT_REPOSITORY https://github.com/ZIMO-Elektronik/CMakeModules
  GIT_TAG v0.4.0
  SOURCE_DIR ${CMAKE_BINARY_DIR}/CMakeModules)
FetchContent_MakeAvailable(CMakeModules)

version_from_git()
project(
  .github-workflows
  VERSION ${VERSION_FROM_GIT}
  LANGUAGES C CXX)

file(GLOB_RECURSE SRC src/*.cpp)
add_library(.github-workflows STATIC ${SRC})

target_compile_features(.github-workflows PUBLIC cxx_std_23)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  target_include_directories(
    .github-workflows
    INTERFACE include
    PRIVATE include/workflows)
else()
  target_include_directories(
    .github-workflows SYSTEM
    INTERFACE include
    PRIVATE include/workflows)
endif()

target_common_warnings(.github-workflows PRIVATE)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
  file(
    DOWNLOAD
    https://raw.githubusercontent.com/ZIMO-Elektronik/.clang-format/master/.clang-format
    ${CMAKE_CURRENT_LIST_DIR}/.clang-format)
  add_clang_format_target(.github-workflowsFormat OPTIONS -i FILES ${SRC})
endif()

if(BUILD_TESTING
   AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME
   AND CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME)
  add_subdirectory(tests)
endif()
