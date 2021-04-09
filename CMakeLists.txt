cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(PreventInSourceBuilds)

project(lmfit VERSION 8.2.1)

## Options.

option(FITTEST "Build with FitTest" OFF)
if(NOT DEFINED BUILD_SHARED_LIBS)
    option(BUILD_SHARED_LIBS "Build as shared library" ON)
endif()
if(NOT DEFINED LIB_MAN)
    option(LIB_MAN "Build library man pages" ON)
endif()
option(PEDANTIC "Compile with pedantic warnings" ON)
option(WERROR "Treat warnings as errors" OFF)
option(BUILD_CPP "Build with cpp wrapper and demos" ON)

## Compiler settings.

set(CMAKE_C_STANDARD 99)

if(BUILD_CPP)
    set(CMAKE_CXX_STANDARD 17)
endif()

if(WIN32)
    set(CTEST_CONFIGURATION_TYPE "${JOB_BUILD_CONFIGURATION}")
#    if(BUILD_SHARED_LIBS)
#        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
#        set(WINDOWS_EXPORT_ALL_SYMBOLS ON)
#    endif()
#    add_compile_options(-export-all-symbols)
endif()
add_compile_options(-O2)
if(PEDANTIC)
    add_compile_options(-pedantic -Wall)
endif()
if(WERROR)
    add_compile_options(-Werror)
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

## Install settings.

set(destination ${CMAKE_INSTALL_PREFIX})
configure_file("lmfit.pc.in" "lmfit.pc" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/lmfit.pc"
    DESTINATION "${destination}/lib/pkgconfig/")

include(CTest)

add_subdirectory(lib)
add_subdirectory(demo)
add_subdirectory(test)
if(BUILD_CPP)
    add_subdirectory(cpplib)
    add_subdirectory(democpp)
endif()
if (LIB_MAN)
    add_subdirectory(man)
endif()
if (FITTEST)
    find_package(FitTest REQUIRED)
    add_subdirectory(fittest)
endif()
