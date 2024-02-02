project(ethrin)
cmake_minimum_required(VERSION 3.10)

option(EMULATE "QemuEmulate" OFF)

enable_language(C)
enable_language(CXX)
enable_language(ASM_NASM)

file(GLOB LINKER_SCRIPT "$ENV{TARGET_BUILD}/boot/linker.ld")
file(GLOB_RECURSE CXX_SOURCE "*.cpp")
file(GLOB_RECURSE C_SOURCE "*.c")
file(GLOB_RECURSE ASM_NASM_SOURCE "*.asm")
file(GLOB_RECURSE ASM_SOURCE ".s")

set(TARGET_ARCH $ENV{TARGET_ARCH})
set(TARGET_BUILD $ENV{TARGET_BUILD})
set(OUTPUT "$ENV{OUTPUT_DIR}/${TARGET_BUILD}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT})
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_FLAGS "-ffreestanding -O2 -Wall --target=${TARGET_BUILD} -march=${TARGET_ARCH}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-ffreestanding -O2 -Wall -fno-exceptions -fno-rtti -nostdlib -nostdinc --target=${TARGET_BUILD} -march=${TARGET_ARCH} ./font.o")
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

add_executable(${PROJECT_NAME}.bin ${CXX_SOURCE} ${C_SOURCE} ${ASM_SOURCE} ${ASM_NASM_SOURCE})

set_target_properties(${PROJECT_NAME}.bin PROPERTIES LINK_FLAGS "-T ${LINKER_SCRIPT}")

target_include_directories(${PROJECT_NAME}.bin PRIVATE "include")
