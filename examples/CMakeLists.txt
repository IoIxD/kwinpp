FILE(GLOB examples CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(CMAKE_CXX_STANDARD 23) # std::println

foreach(example ${examples})
  get_filename_component(name ${example} NAME_WE)
  add_executable(${name} ${example})
  target_link_libraries(${name} PRIVATE ${PROJECT_NAME})
endforeach()

target_link_libraries(moving_window PRIVATE SDL3)
