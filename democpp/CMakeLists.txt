set(cppdemos
curve1cpp
nonlin1cpp
surface1cpp)

foreach(app ${cppdemos})
    add_executable(${app} ${app}.cpp)
    target_include_directories(${app} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${lmfit_SOURCE_DIR}/cpplib)
    target_link_libraries(${app} ${lmfitcpp_LIBRARY})
endforeach()
