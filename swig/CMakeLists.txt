if(POLICY CMP0071)
	cmake_policy(SET CMP0071 NEW)
endif()

if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR ( CMAKE_CXX_COMPILER_ID MATCHES "CLANG"))
	# suppress warning from swig::container_owner<T>::back_reference(PyObject*, PyObject*)
	add_compile_options(-Wno-unused-parameter;-Wno-deprecated-declarations;-Wno-sometimes-uninitialized;-Wno-missing-field-initializers)
endif()

set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR} )
include_directories(${PYTHON_INCLUDE_DIRS})

set_property(SOURCE lmfit.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE lmfit.i PROPERTY SWIG_MODULE_NAME pylmfit)

# Set the core headers path at the swig level
get_directory_property(PYLMFIT_INCLUDE_DIRECTORIES INCLUDE_DIRECTORIES)
list(REMOVE_DUPLICATES PYLMFIT_INCLUDE_DIRECTORIES)
set(PYLMFIT_SWIG_INCLUDE_DIRECTORIES)
foreach(it ${PYLMFIT_INCLUDE_DIRECTORIES})
	set(PYLMFIT_SWIG_INCLUDE_DIRECTORIES ${PYLMFIT_SWIG_INCLUDE_DIRECTORIES} "-I${it}")
endforeach()
set_property(SOURCE lmfit.i PROPERTY SWIG_FLAGS ${PYLMFIT_SWIG_INCLUDE_DIRECTORIES})

swig_add_library(pylmfit TYPE MODULE LANGUAGE python SOURCES lmfit.i)
swig_link_libraries(pylmfit ${PYTHON_LIBRARIES} lmfit)
