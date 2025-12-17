cmake_minimum_required(VERSION 3.20)

project(stat
    VERSION 0.1.0
    DESCRIPTION "Statistical Computing Library (C++)"
    LANGUAGES CXX
)

# Global configuration

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(stat INTERFACE)

# Public API

target_include_directories(stat
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(stat
    INTERFACE
        cxx_std_20
)

include(GNUInstallDirs)

install(
    TARGETS stat
    EXPORT statTargets
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT statTargets
    FILE statTargets.cmake
    NAMESPACE stat::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stat
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/statConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/cmake/statConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/statConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stat
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/statConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/statConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stat
)
