cmake_minimum_required(VERSION 3.5)

project(libcnabl)
add_compile_options(-std=c11 -Wall -Werror)

file(GLOB_RECURSE src src/cnabl/*.c)

add_library(lib_static STATIC ${src})
set_target_properties(lib_static PROPERTIES OUTPUT_NAME cnabl)
target_include_directories(lib_static PUBLIC src)

add_executable(test ${src} src/main.c)
target_compile_options(test PUBLIC -fsanitize=undefined -O2 -g)
target_include_directories(test PUBLIC src)
target_link_libraries(test ubsan)

file(GLOB inc src/cnabl/*.h)
install(FILES ${inc} DESTINATION include/cnabl)
install(FILES build/libcnabl.a DESTINATION lib)
