
cmake_minimum_required(VERSION 3.15)
project(prizoop_cg100 LANGUAGES C CXX)

include($ENV{FXSDK}/lib/cmake/fxsdk.cmake)
fxsdk_setup()

# Collect Prizoop sources automatically from repo's src/
# (Drop this file at the repo root, next to src/ and Makefile)
file(GLOB_RECURSE PRIZOOP_SRCS
     CONFIGURE_DEPENDS
     "src/*.c" "src/*.cpp" "src/*.cc" "src/*.cxx")

# Exclude Windows simulator/shims if present
foreach(f ${PRIZOOP_SRCS})
  if(f MATCHES "prizmsim|win32|windows|simulator")
    list(REMOVE_ITEM PRIZOOP_SRCS ${f})
  endif()
endforeach()

add_executable(prizoop_cg100
    ${PRIZOOP_SRCS}
    cmake/platform_cg100.c
    cmake/ubc_hook.c
    cmake/main_glue.c
)

target_compile_definitions(prizoop_cg100 PRIVATE FXCG100 PRIZOOP_SAFE_MEM)
fxsdk_add_compile_options(prizoop_cg100 -O3 -m4a-nofpu -mb -ffunction-sections -fdata-sections)
fxsdk_add_link_options(prizoop_cg100 -Wl,--gc-sections)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Gint REQUIRED)
target_link_libraries(prizoop_cg100 Gint::Gint)

set(G3A_NAME "Prizoop CG100")
set(G3A_INTERNAL "PRIZOOPCG100")
set(G3A_VERSION "0.1")

fxsdk_add_g3a(TARGET prizoop_cg100 OUTPUT prizoop_cg100.g3a
              NAME "${G3A_NAME}"
              INTERNAL "${G3A_INTERNAL}"
              VERSION "${G3A_VERSION}")
