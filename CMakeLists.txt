cmake_minimum_required(VERSION 3.20)
project(cpplings VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Every file that `cpplings init` writes out is compiled into the binary, so the
# installed program works from any directory without the repository.
file(GLOB_RECURSE EMBEDDED_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_SOURCE_DIR}/exercises/*
  ${CMAKE_SOURCE_DIR}/solutions/*
  ${CMAKE_SOURCE_DIR}/include/*)
list(APPEND EMBEDDED_SOURCES ${CMAKE_SOURCE_DIR}/info.toml)

set(EMBEDDED_CPP ${CMAKE_BINARY_DIR}/embedded_files.cpp)
add_custom_command(
  OUTPUT ${EMBEDDED_CPP}
  COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${CMAKE_SOURCE_DIR} -DOUTPUT=${EMBEDDED_CPP}
          -P ${CMAKE_SOURCE_DIR}/cmake/embed.cmake
  DEPENDS ${EMBEDDED_SOURCES} ${CMAKE_SOURCE_DIR}/cmake/embed.cmake
  COMMENT "Embedding exercises and solutions")

add_executable(cpplings
  src/main.cpp
  src/app_state.cpp
  src/cmd.cpp
  src/dev.cpp
  src/embedded.cpp
  src/exercise.cpp
  src/info_file.cpp
  src/init.cpp
  src/list.cpp
  src/term.cpp
  src/toolchain.cpp
  src/watch.cpp
  ${EMBEDDED_CPP})
target_include_directories(cpplings PRIVATE src)
target_compile_definitions(cpplings PRIVATE CPPLINGS_VERSION="${PROJECT_VERSION}")
target_compile_options(cpplings PRIVATE -Wall -Wextra -Wpedantic)

find_package(Threads REQUIRED)
target_link_libraries(cpplings PRIVATE Threads::Threads)

include(GNUInstallDirs)
install(TARGETS cpplings RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
