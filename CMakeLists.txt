cmake_minimum_required(VERSION 4.3)

project(kwinpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(KWINPP_NO_QT "Don't have functions return Qt types" ON)
option(KWINPP_SHARED "Build as a shared library" ON)

if(KWINPP_NO_QT)
  set(CMAKE_CXX_STANDARD 20)
else()
  set(CMAKE_CXX_STANDARD 17)
endif()

FILE(GLOB_RECURSE sources src/*.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/submodules/json)

if(KWINPP_SHARED)
  add_library(${PROJECT_NAME} SHARED ${sources})
else()
  add_library(${PROJECT_NAME} STATIC ${sources})
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED IMPORTED_TARGET dbus-1)

if(KWINPP_NO_QT)
  target_compile_definitions(${PROJECT_NAME} PUBLIC KWINPP_NO_QT)
  target_include_directories(${PROJECT_NAME} PRIVATE ${DBUS_INCLUDE_DIRS})
else()
  find_package(Qt6 REQUIRED COMPONENTS Core Gui)
  target_link_libraries(${PROJECT_NAME}
    PUBLIC Qt6::Core Qt6::Gui
    PRIVATE PkgConfig::DBUS)
endif()

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

add_subdirectory(examples)
