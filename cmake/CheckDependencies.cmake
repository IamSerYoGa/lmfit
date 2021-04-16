###### Find Python
# python-dev and interpreter
set(Python_ADDITIONAL_VERSIONS 3.7 3.6 3.5 3.4)
find_package(PythonInterp 3)
find_package(PythonLibs 3)

execute_process (
    COMMAND ${PYTHON_EXECUTABLE} -c "from __future__ import print_function; import numpy; print(numpy.get_include())"
    ERROR_VARIABLE NUMPY_FIND_ERROR
    RESULT_VARIABLE NUMPY_FIND_RESULT
    OUTPUT_VARIABLE NUMPY_FIND_OUTPUT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

## process the output from the execution of the command
if(NOT NUMPY_FIND_RESULT)
    set (NUMPY_INCLUDES ${NUMPY_FIND_OUTPUT})
    message(STATUS "numpy includes ${NUMPY_INCLUDES}")
    include_directories(SYSTEM ${NUMPY_INCLUDES})
else()
    message(FATAL_ERROR "Could NOT find numpy headers")
endif()

# Python packages dir
execute_process(COMMAND ${PYTHON_EXECUTABLE} -c
    "from __future__ import print_function; from distutils import sysconfig as sc; print(sc.get_python_lib(prefix='', plat_specific=True))"
    RESULT_VARIABLE PYTHON_SITE_RESULT
    OUTPUT_VARIABLE PYTHON_SITE
    OUTPUT_STRIP_TRAILING_WHITESPACE)

if(NOT PYTHON_SITE_RESULT)
    message(STATUS "python package destination is ${PYTHON_SITE}")
else()
    message(FATAL_ERROR "could NOT determine python package directory")
endif()

# swig
find_package(SWIG REQUIRED)
include(UseSWIG)
