set(cpplib lmfitcpp)
set(${cpplib}_LIBRARY ${cpplib} PARENT_SCOPE)

set(hpp_files lmfit.hpp)

add_library(${cpplib} ${hpp_files})

target_include_directories(${cpplib} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${lmfit_SOURCE_DIR}/lib)
target_link_libraries(${cpplib} ${lmfit_LIBRARY})

target_compile_definitions(${cpplib} PRIVATE "LMFIT_EXPORT")

set_target_properties(
    ${cpplib} PROPERTIES
    OUTPUT_NAME ${cpplib}
    VERSION ${lmfit_VERSION}
    SOVERSION ${lmfit_VERSION_MAJOR}
    LINKER_LANGUAGE CXX)


install(
     TARGETS ${cpplib}
     LIBRARY DESTINATION ${destination}/lib
     RUNTIME DESTINATION ${destination}/lib
     ARCHIVE DESTINATION ${destination}/lib
     COMPONENT Libraries)

install(
    FILES ${hpp_files}
    DESTINATION ${destination}/include
    COMPONENT Headers)

if(WIN32)
    set(CPACK_PACKAGE_VENDOR "Forschungszentrum Jülich GmbH")
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_PACKAGE_DIRECTORY ${CMAKE_SOURCE_DIR})
    include(CPack)
endif()
