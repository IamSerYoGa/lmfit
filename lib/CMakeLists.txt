set(lib lmfit)
set(${lib}_LIBRARY ${lib} PARENT_SCOPE)

set(src_files lmcurve.c lmmin.c lminvert.c)
set(inc_files lmcurve.h lmmin.h lmstruct.h lmdecls.h lmfit.hpp)

add_library(${lib} ${src_files})

target_compile_definitions(${lib} PRIVATE "LMFIT_EXPORT") # for Windows DLL export&import

set_target_properties(
    ${lib} PROPERTIES
    OUTPUT_NAME ${lib}
    VERSION ${lmfit_VERSION}
    SOVERSION ${lmfit_VERSION_MAJOR})

include(LinkLibMath)
link_libm(${lib})

install(
    TARGETS ${lib}
    LIBRARY DESTINATION ${destination}/lib
    RUNTIME DESTINATION ${destination}/lib
    ARCHIVE DESTINATION ${destination}/lib
    COMPONENT Libraries)
install(
    FILES ${inc_files}
    DESTINATION ${destination}/include
    COMPONENT Headers)

if(WIN32)
    set(CPACK_PACKAGE_VENDOR "Forschungszentrum Jülich GmbH")
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_PACKAGE_DIRECTORY ${CMAKE_SOURCE_DIR})
    include(CPack)
endif()
