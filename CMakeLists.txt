cmake_minimum_required(VERSION 2.8.4)
project(flor-sidh-x64 C)

include_directories(./include)
link_directories(./lib)
set(EXECUTABLE_OUTPUT_PATH ./bin)
set(LIBRARY_OUTPUT_PATH ./lib)
set(TARGET flor-sidh-x64)
set(SRC ./src)
enable_language(ASM)

add_definitions(-D_AMD64_)
add_definitions(-D__LINUX__)

#-pedantic -std=c99
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -mbmi -mbmi2 -march=native -mtune=native -fwrapv -fomit-frame-pointer")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3 -mbmi -mbmi2 -march=native -mtune=native -fwrapv -fomit-frame-pointer")

SET(obj_HW
	AMD64/ZMULT_HW.h
    AMD64/ZREDC_6x4_SH_HW.S
)

SET(obj_SK
	AMD64/ZMULT_SK.h
    AMD64/ZREDC_6x4_SH_SK.S
)

SET(objects
		AMD64/Z_ADD_SUB.h
		AMD64/fp_x64.c
		AMD64/fp_x64_asm.S
		fpx.c
		ec_isogeny.c
		look_up_tables.h
		SIDH_internal.h
		SIDH_setup.c
		SIDH.c
		kex.c
		tests/test_extras.c
		tests/test_extras.h
)

add_executable(kex_native tests/kex_tests.c ${objects})
add_executable(kex_haswell ${obj_HW} tests/kex_tests.c ${objects})
add_executable(kex_skylake ${obj_SK} tests/kex_tests.c ${objects})
add_executable(arith_native  tests/arith_tests.c ${objects})
add_executable(arith_haswell ${obj_HW} tests/arith_tests.c ${objects})
add_executable(arith_skylake ${obj_SK} tests/arith_tests.c ${objects})

target_compile_definitions(  kex_native  PRIVATE -D__NATIVE__ )
target_compile_definitions(  kex_haswell PRIVATE -D__HASWELL__)
target_compile_definitions(  kex_skylake PRIVATE -D__SKYLAKE__)
target_compile_definitions(arith_native  PRIVATE -D__NATIVE__ )
target_compile_definitions(arith_haswell PRIVATE -D__HASWELL__)
target_compile_definitions(arith_skylake PRIVATE -D__SKYLAKE__)
