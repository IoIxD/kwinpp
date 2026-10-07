cmake_minimum_required(VERSION 4.3)

project(kwinpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB_RECURSE sources src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${sources})

find_package(Qt6 REQUIRED COMPONENTS Core Gui)
find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED IMPORTED_TARGET dbus-1)

target_link_libraries(${PROJECT_NAME}
  PUBLIC Qt6::Core Qt6::Gui
  PRIVATE PkgConfig::DBUS)
target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(examples)
