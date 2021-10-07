cmake_minimum_required(VERSION 3.20)

# Determine if quadpp is built as a subproject (using add_subdirectory) or if it
# is the master project.
if(NOT DEFINED QUADPP_MASTER_PROJECT)
  set(QUADPP_MASTER_PROJECT OFF)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(QUADPP_MASTER_PROJECT ON)
    message(STATUS "CMake version: ${CMAKE_VERSION}")
  endif()
endif()

project(quadpp CXX)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

# add headers and sources
set(quadpp_headers quadpp.h spline.h)
set(quadpp_sources spline.cpp)

# define quadpp library and add source files
add_library(quadpp ${quadpp_sources})
add_library(quadpp::quadpp ALIAS quadpp)

# ##############################################################################
# find external projects/dependencies
# ##############################################################################

if(NOT TARGET Eigen3::Eigen)
  find_package(Eigen3 REQUIRED)
endif()

if(NOT TARGET GSL::gsl)
  find_package(GSL REQUIRED)
endif()

# ##############################################################################
# link dependencies
# ##############################################################################

target_link_libraries(
  quadpp
  PUBLIC Eigen3::Eigen
  PRIVATE GSL::gsl)

# ##############################################################################
# define include directory
# ##############################################################################
cmake_path(GET quadpp_SOURCE_DIR PARENT_PATH quadpp_PARENT_DIR)
target_include_directories(
  quadpp INTERFACE $<BUILD_INTERFACE:${quadpp_PARENT_DIR}>
                   $<INSTALL_INTERFACE:include>)

# ##############################################################################
# define installation rules
# ##############################################################################
install(
  TARGETS quadpp
  DESTINATION lib
  EXPORT quadppTargets)
install(FILES ${quadpp_headers} DESTINATION include/quadpp)

install(
  EXPORT quadppTargets
  NAMESPACE quadpp::
  FILE quadppTargets.cmake
  DESTINATION lib/cmake/quadpp)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/quadppConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/quadpp"
  NO_SET_AND_CHECK_MACRO NO_CHECK_REQUIRED_COMPONENTS_MACRO)
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/quadppConfigVersion.cmake"
  VERSION "${quadpp_VERSION_MAJOR}.${quadpp_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion)

# install the configuration file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/quadppConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/quadppConfigVersion.cmake
        DESTINATION lib/cmake/quadpp)

export(
  EXPORT quadppTargets
  NAMESPACE quadpp::
  FILE "${CMAKE_CURRENT_BINARY_DIR}/quadppTargets.cmake")
