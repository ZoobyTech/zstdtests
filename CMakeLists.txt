cmake_minimum_required(VERSION 3.31)
project(libZoobyTests LANGUAGES C)

# ——— Toolchain ——————————————————————————————————————
set(CMAKE_C_COMPILER   clang)
set(CMAKE_CXX_COMPILER clang++)
# force clang to invoke lld
set(CMAKE_C_LINKER     ld.lld)
set(CMAKE_CXX_LINKER   ld.lld)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

# ——— Architecture & extras —————————————————————————————
set(ARCH       "znver3" CACHE STRING "Target CPU architecture")
set(BOLT_FLAGS ""       CACHE STRING "Extra BOLT flags")

# ——— Flag groups ——————————————————————————————————————
set(OPTIMIZATION_FLAGS
    -O3
    -pipe
    -flto=full
    -march=${ARCH}
    -mtune=${ARCH}
    -funroll-loops
    -fstrict-aliasing
    -fmerge-all-constants
    -falign-functions=32
    -ftree-vectorize
    -fno-semantic-interposition
)

set(MEMORY_FLAGS
    -fomit-frame-pointer
)

set(SECURITY_FLAGS
    -fno-stack-protector
    -U_FORTIFY_SOURCE
    -D_FORTIFY_SOURCE=0
    -fcf-protection=none
    -fno-asynchronous-unwind-tables
    -fno-plt
    -mno-retpoline
    -fno-stack-clash-protection
)

set(INSTRUCTION_FLAGS
    -mretpoline
    -mno-speculative-load-hardening
    -fzero-call-used-regs=skip
)

set(STRUCTURE_FLAGS
    -ffunction-sections
    -fdata-sections
    -g0
)

set(GENERAL_FLAGS
    -fPIE
    -fPIC
)

# Consolidated compiler flags
set(COMMON_FLAGS
    ${OPTIMIZATION_FLAGS}
    ${MEMORY_FLAGS}
    ${SECURITY_FLAGS}
    ${INSTRUCTION_FLAGS}
    ${STRUCTURE_FLAGS}
    ${GENERAL_FLAGS}
)

# Linker flags
set(LINKER_FLAGS
    -Wl,-O3
    -Wl,--as-needed
    -Wl,--gc-sections
    -fuse-ld=lld
    -flto=full
    -Wl,--icf=all
    -Wl,-s
    -Wl,--strip-all
    -Wl,--hash-style=gnu
    -Wl,--version-script=ver.map
    -nostdlib
    ${BOLT_FLAGS}
)

# ——— Find test sources ————————————————————————————————————
file(GLOB TEST_SOURCES
    "${CMAKE_SOURCE_DIR}/Tests/*.c"
)

# ——— Build one exe per test ——————————————————————————————
foreach(SRC ${TEST_SOURCES})
  get_filename_component(NAME ${SRC} NAME_WE)
  add_executable(${NAME} ${SRC})
  target_link_libraries(${NAME} PRIVATE libZooby.so)

  # compile‐time flags
  target_compile_options(${NAME} PRIVATE
    ${COMMON_FLAGS}
  )

  # link‐time flags
  target_link_options(${NAME} PRIVATE
    ${LINKER_FLAGS}
  )

  # output dir
  set_target_properties(${NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/bin"
  )

  add_custom_command(TARGET ${NAME} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY}
      --remove-section=.shstrtab
      --remove-section=.gnu.version
      #--remove-section=.gnu.version_r
      --remove-section=.gnu.hash
      --remove-section=.note.*
      --remove-section=.eh_frame
      --remove-section=.eh_frame_hdr
      --remove-section=.comment
      #--remove-section=.interp
      $<TARGET_FILE:${NAME}>
    COMMENT "Obliterating residual ELF metadata"
)

endforeach()
