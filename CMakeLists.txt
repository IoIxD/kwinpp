cmake_minimum_required(VERSION 4.3)

project(kwinpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(KWINPP_NO_QT "Don't have functions return Qt types" ON)

FILE(GLOB_RECURSE sources src/*.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/submodules/json)

add_library(${PROJECT_NAME} SHARED ${sources})

find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED IMPORTED_TARGET dbus-1)

# Qt Core is used internally either way; with KWINPP_NO_QT off the API uses
# Qt types (QIcon and QPalette come from Qt Gui), so users need Qt too.
if(KWINPP_NO_QT)
  find_package(Qt6 REQUIRED COMPONENTS Core)
  target_compile_definitions(${PROJECT_NAME} PUBLIC KWINPP_NO_QT)
  target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Core PkgConfig::DBUS)
else()
  find_package(Qt6 REQUIRED COMPONENTS Core Gui)
  target_link_libraries(${PROJECT_NAME}
    PUBLIC Qt6::Core Qt6::Gui
    PRIVATE PkgConfig::DBUS)
endif()
target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include)
# kwinppi.hpp (included by kwinpp.hpp) uses nlohmann::json, so users need it
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

add_subdirectory(examples)
